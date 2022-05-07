#ifndef DROPDOWN_H
#define DROPDOWN_H

#include "widget.hpp"
#include "button.hpp"

class Dropdown : public Widget
{
protected:
    std::vector<std::string> elements; 
    const int e;
    std::string selected;
    ButtonDown* btn;
    bool open = false;
    const int original_size_y;
    int wheel_offset = 0;

public:
    Dropdown(Gamemaster*, int, int, int, int, std::vector<std::string>, int);
    void draw() override;
    void handle(genv::event, Widget*) override;
    std::string getElement();
};

#endif // DROPDOWN_H
