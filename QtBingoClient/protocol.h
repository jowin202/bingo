#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include "game.h"
#include "board.h"

class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = nullptr);
    void update_games();
    void update_boards(int game_id);

    void get_game_by_id(int game_id);

public slots:
    void retr_games();
    void retr_games_finished();

    void retr_boards();
    void retr_boards_finished();

    void get_game_finished();

    void delete_game(int game_id);
    void delete_board(int board_id);
    void change_game(QList<QVariant> game);
    void add_game(QString name, QString owner, QString description);

    void create_instance(int game_id, QString owner, QList<int> numbers);

    void on_change_game_finished();

    void draw_num(int game_id, int num);
    void draw_num_finished();


    void get_drawn_nums(int game_id);
    void drawn_nums_finished();

    void debug_request();

signals:
    void game_list_available(QJsonDocument);
    void board_list_available(QJsonDocument);
    void game_by_id(Game);
    void drawn_nums_available(QVariantList);

private:
    QNetworkAccessManager nam;
    QByteArray retr_games_json;
    QByteArray retr_boards_json;

    bool lock_games;
    bool lock_boards;

    QList<Game> game_list;
    QList<Board> board_list;
signals:

};

#endif // PROTOCOL_H
