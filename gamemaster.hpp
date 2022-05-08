#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include <vector>
#include <string>

class Tile;

class Widget;

class Gamemaster {
protected:
    const int width = 600, height = 600;
    std::string turn = "o";
    std::vector<std::vector<Tile*>> game_area;
    Tile* focused;

public:
    Gamemaster();
    void eventloop();
    void create_game_area(int);
    bool is_in_progress();
    bool five_in_a_row();
//    virtual void write(genv::event) = 0;
};


#endif // GAMEMASTER_HPP
