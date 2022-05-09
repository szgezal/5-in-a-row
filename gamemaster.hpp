#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include <vector>
#include <string>
#include "graphics.hpp"

class Tile;

class Widget;

class Gamemaster {
protected:
    const int width = 600, height = 600;
    std::string player = "o";
    int turn_counter = 1;
    std::vector<std::vector<Tile*>> game_area;
    Tile* focused;

public:
    Gamemaster();
    void eventloop();
    void create_game_area(int);
    bool is_in_progress(genv::event);
    bool five_in_a_row(genv::event);
    bool valid_move(Tile*, genv::event);
//    virtual void write(genv::event) = 0;
};


#endif // GAMEMASTER_HPP
