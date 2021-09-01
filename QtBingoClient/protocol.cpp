#include "protocol.h"
#include "custombutton.h"

Protocol::Protocol(QObject *parent) : QObject(parent)
{
    this->lock_games = false;
    this->lock_boards = false;
}

void Protocol::update_games()
{
    if (lock_games)
        return;
    this->lock_games = true;

    this->retr_games_json = "";
    QNetworkRequest req(QUrl("http://localhost:5000/game/"));
    QNetworkReply *rep = nam.get(req);
    connect(rep, SIGNAL(readyRead()), this, SLOT(retr_games()));
    connect(rep, SIGNAL(finished()), this, SLOT(retr_games_finished()));
}

void Protocol::update_boards(int game_id)
{
    if (lock_boards)
        return;
    this->lock_boards = true;

    this->retr_boards_json = "";
    QNetworkRequest req(QUrl(QString("http://localhost:5000/game/%1/boards/").arg(game_id)));
    QNetworkReply *rep = nam.get(req);
    connect(rep, SIGNAL(readyRead()), this, SLOT(retr_boards()));
    connect(rep, SIGNAL(finished()), this, SLOT(retr_boards_finished()));
}

void Protocol::get_game_by_id(int game_id)
{
    QNetworkRequest req(QUrl(QString("http://localhost:5000/game/%1/").arg(game_id)));
    QNetworkReply *rep = nam.get(req);
    connect(rep, SIGNAL(finished()), this, SLOT(get_game_finished()));

}

void Protocol::retr_games()
{
    QNetworkReply *rep = (QNetworkReply*)sender();
    if (rep != 0)
    {
        while (rep->bytesAvailable())
            this->retr_games_json.append(rep->readAll());
    }
}

void Protocol::retr_games_finished()
{
    this->game_list.clear();
    this->lock_games = false;
    QJsonDocument doc = QJsonDocument::fromJson(this->retr_games_json);
    QJsonArray array = doc.object().value("data").toArray();
    for (int i = 0; i < array.count(); i++)
    {
        QJsonValue game = array.at(i);
        QString description = game.toObject().value("description").toString();
        QString name = game.toObject().value("game_name").toString();
        QString owner = game.toObject().value("game_owner").toString();
        int id = game.toObject().value("game_id").toInt();
        this->game_list.append(Game(id,name,owner,description,QList<int>()));

    }
    emit game_list_available(doc);
}

void Protocol::retr_boards()
{
    QNetworkReply *rep = (QNetworkReply*)sender();
    if (rep != 0)
    {
        while (rep->bytesAvailable())
            this->retr_boards_json.append(rep->readAll());
    }
}

void Protocol::retr_boards_finished()
{
    this->lock_boards = false;
    QJsonDocument doc = QJsonDocument::fromJson(this->retr_boards_json);
    emit board_list_available(doc);
}

void Protocol::get_game_finished()
{
    QTcpSocket *socket = (QTcpSocket *)sender();
    if (socket != 0)
    {
        QJsonDocument doc = QJsonDocument::fromJson(socket->readAll());
        QString description = doc.object().value("data").toObject().value("description").toString();
        QString game_name = doc.object().value("data").toObject().value("game_name").toString();
        QString game_owner = doc.object().value("data").toObject().value("game_owner").toString();
        int id = doc.object().value("data").toObject().value("game_id").toInt();
        QVariantList vlist = doc.object().value("data").toObject().value("nums").toArray().toVariantList();
        QList <int>drawn_numbers;
        for (int i = 0; i < vlist.length(); i++)
        {
            drawn_numbers.append(vlist.at(i).toInt());
        }
        Game g(id,game_name,game_owner,description,drawn_numbers);
        emit game_by_id(g);
    }
}

void Protocol::delete_game(int game_id)
{
    QNetworkRequest req(QUrl(QString("http://localhost:5000/game/%1/").arg(game_id)));
    QNetworkReply *reply = nam.deleteResource(req);
    connect(reply, SIGNAL(finished()), this, SLOT(on_change_game_finished()));
}


void Protocol::delete_board(int board_id)
{
    QNetworkRequest req(QUrl(QString("http://localhost:5000/board/%1/").arg(board_id)));
    QNetworkReply *reply = nam.deleteResource(req);
    //connect(reply, SIGNAL(finished()), this, SLOT(on_change_game_finished()));
}


void Protocol::change_game(QList<QVariant> game)
{
    QJsonDocument doc;
    QJsonObject obj;
    int id = game.at(0).toInt();
    obj["game_id"] = id;
    obj["game_name"] = game.at(1).toString();
    obj["game_owner"] = game.at(2).toString();
    obj["description"] = game.at(3).toString();
    doc.setObject(obj);

    QNetworkRequest req = QNetworkRequest(QUrl(QString("http://localhost:5000/game/%1/").arg(id)));
    req.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    QNetworkReply* reply = nam.put(req, doc.toJson());
    connect(reply, SIGNAL(finished()), this, SLOT(on_change_game_finished()));
}

void Protocol::add_game(QString name, QString owner, QString description)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj["name"] = name;
    obj["owner"] = owner;
    obj["description"] = description;
    doc.setObject(obj);

    QNetworkRequest req = QNetworkRequest(QUrl("http://localhost:5000/game/new"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    QNetworkReply* reply = nam.put(req, doc.toJson());
    connect(reply, SIGNAL(finished()), this, SLOT(on_change_game_finished()));
    //connect(reply, SIGNAL(readyRead()), this, SLOT(debug_request()));
}

void Protocol::create_instance(int game_id, QString owner, QList<int> numbers)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj["game_id"] = game_id;
    obj["board_owner"] = owner;
    QJsonArray arr = {};
    for (int i = 0; i < numbers.length(); i++)
        arr.append(numbers.at(i));

    if (numbers.length() == 25)
        obj["numbers"] = arr; //else randomize
    doc.setObject(obj);

    QNetworkRequest req = QNetworkRequest(QUrl("http://localhost:5000/board/new"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    QNetworkReply* reply = nam.put(req, doc.toJson());
    //connect(reply, SIGNAL(readyRead()), this, SLOT(debug_request()));

}


void Protocol::on_change_game_finished()
{
    //when game list should be updated
    this->update_games();
}





void Protocol::draw_num(int game_id, int num)
{
    QNetworkRequest req = QNetworkRequest(QUrl(QString("http://localhost:5000/game/%1/draw/%2").arg(game_id).arg(num)));
    req.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    QNetworkReply* reply = nam.put(req, "");
    connect(reply, SIGNAL(finished()), this, SLOT(draw_num_finished()));
    //connect(reply, SIGNAL(readyRead()), this, SLOT(debug_request()));
}

void Protocol::draw_num_finished()
{
    //TODO check fails
    QTcpSocket *socket = (QTcpSocket*) sender();
    qDebug() << socket->readAll();

    //if
}

void Protocol::get_drawn_nums(int game_id)
{
    QNetworkRequest req = QNetworkRequest(QUrl(QString("http://localhost:5000/game/%1/drawn/").arg(game_id)));
    req.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    QNetworkReply* reply = nam.get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(drawn_nums_finished()));
}

void Protocol::drawn_nums_finished()
{
    QTcpSocket *socket = (QTcpSocket *)sender();
    if (socket != 0)
    {
        QJsonDocument doc = QJsonDocument::fromJson(socket->readAll());
        QVariantList vlist = doc.object().value("data").toArray().toVariantList();

        emit drawn_nums_available(vlist);
    }
}




void Protocol::debug_request()
{
    QNetworkReply *rep = (QNetworkReply*)sender();

    if (rep != 0)
    {
        while (rep->canReadLine())
            qDebug() << rep->readLine();
    }
}
