#ifndef QTABLEVIEWCUSTOM_H
#define QTABLEVIEWCUSTOM_H

#include <QWidget>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>

#include <QModelIndex>
#include <QPushButton>

#include "protocol.h"
#include "qjsontablemodel.h"

class QTableViewCustom : public QTableView
{
    Q_OBJECT
public:
    QTableViewCustom();
    QTableViewCustom(QWidget *parent);
    void setJson( const QJsonArray& array );
    void setProtocol( Protocol *protocol);

public slots:
    void on_double_clicked(const QModelIndex &index);
    void delete_game();
    void game_edit_pressed();

signals:
    void edit_game(int game_id);

private:
    QJsonTableModel::Header header;
    QJsonTableModel *model;
    Protocol *protocol;

};

#endif // QTABLEVIEWCUSTOM_H
