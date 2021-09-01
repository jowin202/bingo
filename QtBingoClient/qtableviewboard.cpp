#include "qtableviewboard.h"
#include "custombutton.h"

QTableViewBoard::QTableViewBoard()
{
    // do not use this constructor
}
QTableViewBoard::QTableViewBoard(QWidget *parent)
{
    header.push_back( QJsonTableModel::Heading( { {"title","ID"},    {"index","board_id"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Name"},    {"index","board_owner"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Numbers"},    {"index","numbers"} }) );
    //header.push_back( QJsonTableModel::Heading( { {"title","Veranstalter"},   {"index","game_owner"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title",""},  {"index",""} }) );
    header.push_back( QJsonTableModel::Heading( { {"title",""},  {"index",""} }) );


    model = new QJsonTableModel( header, this );
    this->setModel(model);

    this->hideColumn(0);

    connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_double_clicked(const QModelIndex &)));
}

void QTableViewBoard::setJson( const QJsonArray& array )
{
    this->model->setJson(array);

    for (int i = 0; i < this->model->rowCount(); i++)
    {
        int board_id = this->model->index(i,0).data().toInt();
        CustomButton *btn = new CustomButton();
        btn->set_id(board_id);
        btn->setText("Del");
        connect(btn, SIGNAL(clicked()), this, SLOT(delete_board()));
        this->setIndexWidget(this->model->index(i,3)
                             , btn);


        CustomButton *btn2 = new CustomButton();
        btn2->set_id(board_id);
        //btn2->set_name(this->model->index(i,2).data().toString());
        btn2->setText("View");
        connect(btn2, SIGNAL(pressed()), this, SLOT(board_view_pressed()));

        this->setIndexWidget(this->model->index(i,4), btn2);
    }
}

void QTableViewBoard::setProtocol(Protocol *protocol)
{
    this->protocol = protocol;
    //for changing contents of board (not recommended)
    //connect(model, SIGNAL(rowEdit(QList<QVariant>)), this->protocol, SLOT(change_game(QList<QVariant>)));
}

void QTableViewBoard::on_double_clicked(const QModelIndex &index)
{
    this->edit(index);
}

void QTableViewBoard::delete_board()
{
    CustomButton *btn = (CustomButton*) sender();
    if (btn != 0)
    {
        if (QMessageBox::question(this, "Delete Board", "Are you sure?") == QMessageBox::Yes)
            this->protocol->delete_board(btn->get_id());
    }
}

void QTableViewBoard::board_view_pressed()
{
    CustomButton *btn = (CustomButton*)sender();

    if (btn != 0)
    {
        //emit edit_game(btn->get_id());
    }
}

void QTableViewBoard::retr_boards(QJsonDocument doc)
{
    this->setJson(doc.object().value("data").toArray());
    this->resizeColumnsToContents();
}
