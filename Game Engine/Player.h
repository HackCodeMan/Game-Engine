#pragma once

#include <map>
#include "Game_World.h"

// Игрок
class Player
{
public:
    Player(char pl_ico);
    int x, y; // Координаты игрока на карте
    char ico();
    // Движение относительно карты
    void move(Game_World* gm_wd, char mv_key);
  
    Player operator=(Player& pl);
private:
    char PL_ICON; // Сделать константой
    
    // Движение
    void mv_left(Game_World* gw);
    void mv_right(Game_World* gw);
    void mv_down(Game_World* gw);
    void mv_up(Game_World* gw);
};

//////////////////////////////////////////////////

Player::Player(char pl_ico)
{
    PL_ICON = pl_ico;
    x = 0;
    y = 0;
}

char Player::ico()
{
    return PL_ICON;
}

void Player::move(Game_World* gm_wd, char mv_key)
{
    switch (mv_key)
    {
    case 'w':
        mv_up(gm_wd);
        std::cout << "\nW" << '\n';
        break;
    case 'a':
        mv_left(gm_wd);
        std::cout << "\nA" << '\n';
        break;
    case 's':
        mv_down(gm_wd);
        std::cout << "\nS" << '\n';
        break;
    case 'd':
        mv_right(gm_wd);
        std::cout << "\nD" << '\n';
        break;
    default:
        std::cout << "\n\n";
        break;
    }

};

Player Player::operator=(Player& pl) { return *this; }

void Player::mv_left(Game_World* gw)
{
    if (gw->get(y, x) != PL_ICON)
        throw std::exception("player`s location error: pl_ico not found");
    if (gw->get(y, x - 1) != gw->WALL)
    {
        gw->set(y, x--, gw->ROAD);
        gw->set(y, x, PL_ICON);
    }
}

void Player::mv_right(Game_World* gw)
{
    if (gw->get(y, x) != PL_ICON)
        throw std::exception("player`s location error: pl_ico not found");
    if (gw->get(y, x + 1) != gw->WALL)
    {
        gw->set(y, x++ , gw->ROAD);
        gw->set(y, x, PL_ICON);
    }
}

void Player::mv_down(Game_World* gw)
{
    if (gw->get(y, x) != PL_ICON)
        throw std::exception("player`s location error: pl_ico not found");
    if (gw->get(y + 1, x) != gw->WALL)
    {
        gw->set(y++, x, gw->ROAD);
        gw->set(y, x, PL_ICON);
    }
}

void Player::mv_up(Game_World* gw)
{
    if (gw->get(y, x) != PL_ICON)
        throw std::exception("player`s location error: pl_ico not found");
    if (gw->get(y - 1, x) != gw->WALL)
    {
        gw->set(y--, x, gw->ROAD);
        gw->set(y, x, PL_ICON);
    }
}