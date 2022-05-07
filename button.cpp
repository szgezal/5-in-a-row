#include "button.hpp"

using namespace genv;


//Button
Button::Button(Application* _parent, int _x, int _y, int _sx, int _sy): Widget(_parent, _x, _y, _sx, _sy) {}

Button::Button(Spinbox* _parent, int _x, int _y, int _sx, int _sy): Widget(_parent, _x, _y, _sx, _sy) {}

Button::Button(Dropdown* _parent, int _x, int _y, int _sx, int _sy): Widget(_parent, _x, _y, _sx, _sy) {}

Button::Button(Textreader* _parent, int _x, int _y, int _sx, int _sy): Widget(_parent, _x, _y, _sx, _sy) {}

void Button::handle(genv::event ev, Widget* w) {
    if (this->on_widget(ev) && ev.button > 0)
        this->down = true;
    else if (!this->on_widget(ev) || ev.button == -btn_left)
        this->down = false;
}


//Simple Button
SimpleButton::SimpleButton(Application* _parent, int _x, int _y, int _sx, int _sy):
                                 Button(_parent, _x, _y, _sx, _sy) {}

void SimpleButton::draw() {
    if (down)
        gout << color(100, 100, 100) << move_to(x, y) << box(size_x, size_y);
    else
        gout << color(150, 150, 150) << move_to(x, y) << box(size_x, size_y);
}

bool SimpleButton::on_widget(genv::event ev) {
    return ev.pos_x > x && ev.pos_y > y &&
           ev.pos_x < x + size_x && ev.pos_y < y + size_y;
}


//ButtonUp
ButtonUp::ButtonUp(Spinbox* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

ButtonUp::ButtonUp(Textreader* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

void ButtonUp::draw() {
    if (down) {
        gout << color(100, 100, 100) << move_to(x, y) << box(size_x, size_y);
        for (int i = 0; i < 5; i++)
            gout << color(50, 50, 50) << move_to(x + 5 + i, y + 12 - i) << line(10 - 2*i, 0);
    } else {
        gout << color(150, 150, 150) << move_to(x, y) << box(size_x, size_y);
        for (int i = 0; i < 5; i++)
            gout << color(50, 50, 50) << move_to(x + 5 + i, y + 12 - i) << line(10 - 2*i, 0);
    }
}


//ButtonDown
ButtonDown::ButtonDown(Spinbox* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

ButtonDown::ButtonDown(Textreader* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

ButtonDown::ButtonDown(Dropdown* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

void ButtonDown::draw() {
    if (down) {
        gout << color(100, 100, 100) << move_to(x, y) << box(size_x, size_y);
        for (int i = 0; i < 5; i++)
            gout << color(50, 50, 50) << move_to(x + 5 + i, y + size_y/2 - 2 + i) << line(10 - 2*i, 0);
    } else {
        gout << color(150, 150, 150) << move_to(x, y) << box(size_x, size_y);
        for (int i = 0; i < 5; i++)
            gout << color(50, 50, 50) << move_to(x + 5 + i, y + size_y/2 - 2 + i) << line(10 - 2*i, 0);
    }
}
