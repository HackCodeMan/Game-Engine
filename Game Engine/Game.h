#pragma once
#include <iostream>
//conio.h = отслеживание клавиш
#include <conio.h>

#include "Game_World.h"
#include "Player.h"


class Game
{
public:
    Game(Game_World* world, Player* player);
    ~Game();

    void setup();
    void loop();

    std::string print();

private:
    Game_World* world;
    Player* player; 

    // Устанавливает начальную позицию игрока на первый попавшийся в мире объект,
    // По дефолту дорога (чтобы игрок в начале игры не оказался в стене)
    void set_start_location(Player* pl, char obj);

};

////////////////////////////////////////////////////////

Game::Game(Game_World* world, Player* player)
{
    this->world = world;
    this->player = player;
    this->setup();
}

Game::~Game() 
{
    delete world;
    delete player;
}

void Game::setup()
{
    set_start_location(player, world->ROAD);
    std::cout << this->print() << '\n';
}

void Game::loop()
{
    if (_kbhit())
    {
        system("cls");
        player->move(world, _getch()); 
        std::cout << this->print() << '\n';
    }
}

std::string Game::print()
{
    string rep = world->print();
    rep += "Player:\nX = " + to_string(player->x) + "\nY = " + to_string(player->y);
    return rep;
}

void Game::set_start_location(Player* pl, char obj)
{
    for (int i = 1; i < world->get_rows() - 1; i++)
    {
        for (int j = 1; j < world->get_cols() - 1; j++)
        {
            if (world->get(i, j) == obj)
            {
                pl->y = i;
                pl->x = j;
                world->set(pl->y,pl->x, player->ico());

                return;
            }
        }
    }
}
