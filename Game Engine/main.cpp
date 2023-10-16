#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
//#include <SFML\Graphics.hpp>

enum controlKeys
{
    UP_ARROW = 'H',
    LEFT_ARROW = 'K',
    DOWN_ARROW = 'P',
    RIGHT_ARROW = 'M',
};


class GameWorld
{
public:
    const int ROWS = 15;
    const int COLUMNS = ROWS + 1;
    const char WALL = '#';
    const char ROAD = ' ';
    const char PLAYER = 'O';

    char get(int row, int column)
    {
        bool isOutOfRange = ((column > COLUMNS - 1 || row > ROWS) || (row < 0 || column < 0));
        if (isOutOfRange) throw std::out_of_range("Uncorrect Args");
        return map2d[column + (COLUMNS * row)];
    }

    void set(int row, int column, char value)
    {
        bool isOutOfRange = ((row > ROWS || column > COLUMNS - 1) || (row < 0 || column < 0));
        bool isCorrectVal = (value == PLAYER) || (value == ROAD) || (value == WALL);
        if (isOutOfRange || !(isCorrectVal)) throw std::runtime_error("Uncorrect Args");
        map2d[column + (COLUMNS * row)] = value;
    }

    string print() { return map2d; }
    GameWorld operator= (GameWorld& other) { return (*this); }

private:
    string map2d =
    {
    "###############\n"
    "#             #\n"
    "#  #   #####  #\n"
    "# ####        #\n"
    "#    #     ####\n"
    "#             #\n"
    "# ####   #### #\n"
    "# #        #  #\n"
    "#    ####  #  #\n"
    "#         ##  #\n"
    "#    ###      #\n"
    "#  #      ##  #\n"
    "# ##      #   #\n"
    "#             #\n"
    "###############\n"
    };
};

struct Coords
{
    int x;
    int y;
};

class Player
{
public:
    Player()
    {
        coords.x = 0;
        coords.y = 0;
    }

    // getters and setters
    Coords getCoords() { return coords; }
    void setCoords(Coords newCoords ,GameWorld& gw)
    {
        bool isOutOfRange = ((coords.x > gw.COLUMNS - 1 || coords.y > gw.ROWS) || (coords.x < 0 || coords.y < 0));
        if (isOutOfRange) throw std::out_of_range("Uncorrect Args");
        coords.x = newCoords.x;
        coords.y = newCoords.y;
    }

    // Movement relative to the map 
    bool move(GameWorld& gw, char controlKey)
    {
        if (gw.get(coords.y, coords.x) != gw.PLAYER)
            throw std::exception("player`s location error");
        bool isPlayerMove = true;
        switch (controlKey)
        {
        case UP_ARROW: // Стрелка вверх
            if (gw.get(coords.y - 1, coords.x) != gw.WALL) gw.set(coords.y--, coords.x, gw.ROAD);
            else isPlayerMove = false;
            break;
        case LEFT_ARROW: // Стрелка влево
            if (gw.get(coords.y, coords.x - 1) != gw.WALL) gw.set(coords.y, coords.x--, gw.ROAD);
            else isPlayerMove = false;
            break;
        case DOWN_ARROW: // Стрелка вниз
            if (gw.get(coords.y + 1, coords.x) != gw.WALL) gw.set(coords.y++, coords.x, gw.ROAD);
            else isPlayerMove = false;
            break;
        case RIGHT_ARROW: // стрелка вправо
            if (gw.get(coords.y, coords.x + 1) != gw.WALL) gw.set(coords.y, coords.x++, gw.ROAD);
            else isPlayerMove = false;
            break;
        default:
            isPlayerMove = false;
            break;
        }
        gw.set(coords.y, coords.x, gw.PLAYER);  
        return isPlayerMove;
    };
private:
    Coords coords; // Player's Coords in map 
};


class Game
{
public:
    Game(GameWorld& world, Player& player)
    {
        this->world = &world;
        this->player = &player;
        this->setup();
    }
    
    void setup()
    {
        setStartLocation();
        draw();
    }

    void loop()
    {
        while (true)
        {
            char key;
            if (input(key))
            {
                bool isPlayerMove = player->move(*world, key);
                if (isPlayerMove) draw();
            }
        } 
    }

    void draw() { cout << world->print() << '\n'; }

private:
    GameWorld* world;
    Player* player;

    void setStartLocation()
    {
        player->setCoords(Coords{ 1,1 }, *world);
        world->set(player->getCoords().y, player->getCoords().x, world->PLAYER);
    }

    bool input(char& key)
    {
        if (_kbhit())
        {
            key = _getch();
            return true;
        }
        else return false;
    }
};


int main()
{
    setlocale(LC_ALL, "Rus");
    GameWorld wr1;
    Player pl1;
    Game gm(wr1, pl1);
    gm.loop();

    return 0;   

}
