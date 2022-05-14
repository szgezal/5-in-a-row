#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include "graphics.hpp"

class Tile;

class Widget;

class Gamemaster {
protected:
    const int width = 600, height = width;
    std::string player;
    int turn_counter;
    std::vector<std::vector<Tile*>> game_area;
    std::vector<Widget*> menu_widgets;
    Tile* tfocused;
    Widget* wfocused;
    bool is_draw = false;

public:
    Gamemaster();
    void main_loop();
    void create_game_area(int);
    bool is_in_progress();
    bool five_in_a_row();
    bool valid_move(Tile*, genv::event);
    void add_widget(Widget*);
    virtual int getSelectedNum() = 0;
    virtual std::string getSelectedElement() = 0;
    virtual bool play_button_clicked() = 0;
};


#endif // GAMEMASTER_HPP
