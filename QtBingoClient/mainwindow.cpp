#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->protocol = new Protocol();
    this->ui->tableView->setProtocol(this->protocol); //set protocol before setJson
    this->ui->game_widget->setProtocol(this->protocol);

    connect(this->ui->tableView, SIGNAL(edit_game(int)), this, SLOT(edit_game(int)));
    connect(this->protocol, SIGNAL(game_list_available(QJsonDocument)), this->ui->tableView , SLOT(retr_game_list(QJsonDocument)));

    this->protocol->update_games();

    this->ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->protocol->add_game(this->ui->lineEdit->text(),this->ui->lineEdit_2->text(),this->ui->lineEdit_3->text());

    this->ui->lineEdit->setText("");
    this->ui->lineEdit_2->setText("");
    this->ui->lineEdit_3->setText("");
}






void MainWindow::on_button_refresh_games_clicked()
{
    this->protocol->update_games();
}

void MainWindow::edit_game(int game_id)
{
    this->ui->game_widget->set_game_id(game_id);
    this->ui->stackedWidget->setCurrentIndex(1);
}


