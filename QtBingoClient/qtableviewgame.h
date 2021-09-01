#ifndef QTABLEVIEWGAME_H
#define QTABLEVIEGAME_H

#include <QWidget>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>

#include <QModelIndex>
#include <QPushButton>

#include "protocol.h"
#include "qjsontablemodel.h"

class QTableViewGame : public QTableView
{
    Q_OBJECT
public:
    QTableViewGame();
    QTableViewGame(QWidget *parent);
    void setJson( const QJsonArray& array );
    void setProtocol( Protocol *protocol);

public slots:
    void on_double_clicked(const QModelIndex &index);
    void delete_game();
    void game_edit_pressed();
    void retr_game_list(QJsonDocument doc);

signals:
    void edit_game(int game_id);

private:
    QJsonTableModel::Header header;
    QJsonTableModel *model;
    Protocol *protocol;

};

#endif // QTABLEVIEWGAME_H
