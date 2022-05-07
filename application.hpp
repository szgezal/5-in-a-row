#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include "graphics.hpp"

class Widget;

class Application {
protected:
    std::vector<Widget*> widgets;
    Widget* focused;

public:
    Application(int, int);
    void eventloop();
    void add_widget(Widget*);
//    virtual void write(genv::event) = 0;
};


#endif // APPLICATION_HPP
