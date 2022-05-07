#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include <vector>

class Tile;

class Widget;

class Gamemaster {
protected:
    const int width = 600, height = 600;
    std::vector<std::vector<Tile*>> game_area;
    Widget* focused;

public:
    Gamemaster();
    void eventloop();
    void create_game_area(int);
//    virtual void write(genv::event) = 0;
};


#endif // GAMEMASTER_HPP
