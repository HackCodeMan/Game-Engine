#include <iostream>
using namespace std;

#include "Game_World.h"
#include "Player.h"
#include "Game.h"

// ВЫПОЛНЕННЫЕ ЗАДАЧИ:
    // СОЗДАНА ПЕРВИЧНАЯ СТРУКТУРА ПРОГРАММЫ С ПЕРВИЧНЫМИ 2D КЛАССАМИ
    // РЕАЛИЗОВАНО ПЕРВИЧНОЕ УПРАВЛЕНИЕ ИГРОКОМ
    // СОЗДАН ПЕРВИЧНЫЙ 2D МИР-КАРТА
    // ВЫСТРОЕНА ВЗАИМОСВЯЗЬ МЕЖДУ ЭТИМИ КЛАССАМИ В КЛАССЕ GAME
    
// ЗАДАЧИ:
    // СДЕЛАТЬ ПОДДЕРЖКУ РУССКОЙ РАССКЛАДКИ
    // ДОБАВИТЬ PRINT() МЕТОД К КЛАССАМ
    // ПОМЕНЯТЬ ТЕЛО ОТСЧЕТА ( ось y смотрела вверх, а не вниз)
    // ОПТИМИЗИРОВАТЬ ВВОД И ВЫВОД В ИГРЕ (не при каждом нажатии смена карты)
    // СДЕЛАТЬ БОЛЕЕ БЫСТРЫЙ ВЫВОД
    // РАЗБИТЬ БИБЛЕОТЕКИ НА ФАЙЛ ЗАГОЛОВКИ И ФАЙЛЫ РЕАЛИЗАЦИИ => ИЗУЧЕНИЕ CMAKE
    // УВЕЛИЧЕНИЕ СКОРОСТИ ОТКЛИКА И СМЕНЫ КАДРОВ

int main()
{
    try
    {
        setlocale(LC_ALL, "Rus");
        Game_World* wr1 = new Game_World(20, 50);
        wr1->set(1, 1, wr1->WALL);
        Player* pl1 = new Player('O');
        Game gm(wr1, pl1);
        while (true)
        {
            gm.loop();
        }
        return 0;   
    }
    catch (std::out_of_range& e)
    {
        cerr << "Out of range error: " << e.what() << endl;
        return 1;
    }
    catch (std::exception& e)
    {
        cerr << "Error" << e.what() << endl;
        return 2;
    }
    catch (...)
    {
        cerr << "Undefined error" << endl;
        return 3;
    }

}
