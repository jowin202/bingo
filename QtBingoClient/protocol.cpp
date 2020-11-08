#include "protocol.h"
#include "custombutton.h"

Protocol::Protocol(QObject *parent) : QObject(parent)
{

}

void Protocol::update_games()
{
    this->retr_games_json = "";
    QNetworkRequest req(QUrl("http://localhost:5000/game/"));
    QNetworkReply *rep = nam.get(req);
    connect(rep, SIGNAL(readyRead()), this, SLOT(retr_games()));
    connect(rep, SIGNAL(finished()), this, SLOT(retr_games_finished()));
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
    QJsonDocument doc = QJsonDocument::fromJson(this->retr_games_json);
    emit game_list_available(doc);
}

void Protocol::delete_game(int game_id)
{
    QNetworkRequest req(QUrl(QString("http://localhost:5000/game/%1/").arg(game_id)));
    QNetworkReply *reply = nam.deleteResource(req);
    connect(reply, SIGNAL(finished()), this, SLOT(on_change_game_finished()));
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

void Protocol::debug_request()
{
    QNetworkReply *rep = (QNetworkReply*)sender();

    if (rep != 0)
    {
        while (rep->canReadLine())
            qDebug() << rep->readLine();
    }
}
