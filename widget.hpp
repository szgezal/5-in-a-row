#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gamemaster.hpp"

class Spinbox;

class Dropdown;

class Widget
{
protected:
    Gamemaster* parent;
    Spinbox* sbparent;
    Dropdown* ddparent;
    int x, y, size_x, size_y;

public:
    Widget(Gamemaster*, int, int, int, int);
    Widget(Spinbox*, int, int, int, int);
    Widget(Dropdown*, int, int, int, int);
    virtual bool on_widget(genv::event);
    virtual void draw() = 0;
    virtual void handle(genv::event, Widget*) = 0;
};

#endif // WIDGET_HPP
