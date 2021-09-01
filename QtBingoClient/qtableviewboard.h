#ifndef QTABLEVIEWBOARD_H
#define QTABLEVIEWBOARD_H

#include <QWidget>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>

#include <QModelIndex>
#include <QPushButton>

#include "protocol.h"
#include "qjsontablemodel.h"

class QTableViewBoard : public QTableView
{
    Q_OBJECT
public:
    QTableViewBoard();
    QTableViewBoard(QWidget *parent);
    void setJson( const QJsonArray& array );
    void setProtocol( Protocol *protocol);

public slots:
    void on_double_clicked(const QModelIndex &index);
    void delete_board();
    void board_view_pressed();
    void retr_boards(QJsonDocument doc);



private:
    QJsonTableModel::Header header;
    QJsonTableModel *model;
    Protocol *protocol;

};

#endif // QTABLEVIEWBOARD_H
