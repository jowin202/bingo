#include "game.h"



Game::Game()
{

}

Game::Game(const Game &)
{
}

Game::Game(int id, QString name, QString owner, QString description, QList<int> drawn_numbers)
{
    this->id = id;
    this->name = name;
    this->owner = owner;
    this->description = description;
    this->drawn_numbers = drawn_numbers;
}
