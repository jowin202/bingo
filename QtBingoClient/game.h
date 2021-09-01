#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    //explicit Game(QObject *parent = nullptr);
    Game();
    Game(const Game&);
    Game(int id, QString name, QString owner, QString description, QList<int> drawn_numbers);

signals:

private:
    int id;
    QString name;
    QString owner;
    QString description;
    QList<int> drawn_numbers;

};

#endif // GAME_H
