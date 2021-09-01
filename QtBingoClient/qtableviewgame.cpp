#include "qtableviewgame.h"
#include "custombutton.h"

QTableViewGame::QTableViewGame()
{
    // do not use this constructor
}
QTableViewGame::QTableViewGame(QWidget *parent)
{
    header.push_back( QJsonTableModel::Heading( { {"title","ID"},    {"index","game_id"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Name"},    {"index","game_name"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Veranstalter"},   {"index","game_owner"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Beschreibung"},  {"index","description"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title",""},  {"index",""} }) );
    header.push_back( QJsonTableModel::Heading( { {"title",""},  {"index",""} }) );


    model = new QJsonTableModel( header, this );
    this->setModel(model);

    this->hideColumn(0);

    connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_double_clicked(const QModelIndex &)));
}

void QTableViewGame::setJson( const QJsonArray& array )
{
    this->model->setJson(array);

    for (int i = 0; i < this->model->rowCount(); i++)
    {
        int game_id = this->model->index(i,0).data().toInt();
        CustomButton *btn = new CustomButton();
        btn->set_id(game_id);
        btn->setText("Del");
        connect(btn, SIGNAL(clicked()), this, SLOT(delete_game()));
        this->setIndexWidget(this->model->index(i,4), btn);


        CustomButton *btn2 = new CustomButton();
        btn2->set_id(game_id);
        btn2->set_name(this->model->index(i,1).data().toString());
        btn2->setText("Edit");
        connect(btn2, SIGNAL(pressed()), this, SLOT(game_edit_pressed()));

        this->setIndexWidget(this->model->index(i,5), btn2);
    }
}

void QTableViewGame::setProtocol(Protocol *protocol)
{
    this->protocol = protocol;
    connect(model, SIGNAL(rowEdit(QList<QVariant>)), this->protocol, SLOT(change_game(QList<QVariant>)));
}

void QTableViewGame::on_double_clicked(const QModelIndex &index)
{
    this->edit(index);
}

void QTableViewGame::delete_game()
{
    CustomButton *btn = (CustomButton*) sender();
    if (btn != 0)
    {
        if (QMessageBox::question(this, "Delete Game", "Are you sure?") == QMessageBox::Yes)
            this->protocol->delete_game(btn->get_id());
    }
}

void QTableViewGame::game_edit_pressed()
{
    CustomButton *btn = (CustomButton*)sender();

    if (btn != 0)
    {
        emit edit_game(btn->get_id());
    }
}

void QTableViewGame::retr_game_list(QJsonDocument doc)
{
    this->setJson(doc.object().value("data").toArray());
    this->resizeColumnsToContents();
}
