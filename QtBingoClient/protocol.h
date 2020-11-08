#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>

class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = nullptr);
    void update_games();

public slots:
    void retr_games();
    void retr_games_finished();

    void delete_game(int game_id);
    void change_game(QList<QVariant> game);
    void add_game(QString name, QString owner, QString description);

    void create_instance(int game_id, QString owner, QList<int> numbers);

    void on_change_game_finished();


    void debug_request();

signals:
    void game_list_available(QJsonDocument);

private:
    QNetworkAccessManager nam;
    QByteArray retr_games_json;
signals:

};

#endif // PROTOCOL_H
