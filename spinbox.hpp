#ifndef SPINBOX_HPP
#define SPINBOX_HPP

#include "button.hpp"

class Spinbox : public Widget
{
protected:
    int lowerlim, upperlim, n = 22;
    ButtonUp* btn1;
    ButtonDown* btn2;

public:
    Spinbox(Gamemaster*, int, int, int, int, int, int);
    void draw() override;
    void handle(genv::event, Widget*) override;
    int getNum();
};

#endif // SPINBOX_HPP
