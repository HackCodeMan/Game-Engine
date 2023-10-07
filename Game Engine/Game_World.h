#pragma once
#include <string>
#include "Array2d.h"

//Игровой мир
class Game_World: public Array2d <char>
{
public:
    Game_World();
    Game_World(int height, int width);
    ~Game_World();

    const char WALL = '#';
    const char ROAD = '.';

    // Вывод карты на экран
    std::string print();

    Game_World operator=(Game_World& gw);

private:

    // Установка начальной карты
    void build();
};

///////////////////////////////////////////////////////////////////////


Game_World::Game_World(int height, int width) : Array2d(height, width)
{
    this->build();
}

Game_World::Game_World() {}

Game_World::~Game_World(){}

std::string Game_World::print()
{
    std::string res = "";
    for (int i = 0; i < get_rows(); i++)
    {
        for (int j = 0; j < get_cols(); j++)
        {
            if (get(i, j) == ROAD) res += " ";
            else res += get(i, j);
        }
        res += '\n';
    }
    return res;
}

Game_World Game_World::operator=(Game_World& gw) { return *this; }

void Game_World::build()
{
    // Создание дорог
    for (int i = 0; i < get_rows(); i++)
        for (int j = 0; j < get_cols(); j++) set(i, j, ROAD);

    // Создание границ карты
    for (int i = 0; i < get_cols(); i++)
    {
        set(0, i, WALL);
        set(get_rows() - 1, i, WALL);
    }
    for (int i = 1; i < (get_rows() - 1); i++)
    {
        set(i, 0, WALL);
        set(i, get_cols() - 1, WALL);
    }

}