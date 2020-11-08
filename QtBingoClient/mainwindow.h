#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtNetwork>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "protocol.h"
#include "qjsontablemodel.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void retr_game_list(QJsonDocument doc);
    void on_button_refresh_games_clicked();

public slots:
    void edit_game(int game_id);


private:
    Ui::MainWindow *ui;
    Protocol *protocol;
    QNetworkAccessManager nam;


    int current_game;
};
#endif // MAINWINDOW_H
