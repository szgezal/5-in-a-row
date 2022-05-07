#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include "gamemaster.hpp"

class Spinbox;

class Dropdown;

class Tile;

class Widget
{
protected:
    Gamemaster* parent;
    Spinbox* sbparent;
    Dropdown* ddparent;
    Tile* tparent;
    int x, y, size_x, size_y;

public:
    Widget(Gamemaster*, int, int, int, int);
    Widget(Spinbox*, int, int, int, int);
    Widget(Dropdown*, int, int, int, int);
    Widget(Tile* , int, int, int, int);
    virtual bool on_widget(genv::event);
    virtual void draw() = 0;
    virtual void handle(genv::event, Widget*) = 0;
};

#endif // WIDGET_HPP
