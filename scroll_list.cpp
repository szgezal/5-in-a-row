#include "scroll_list.hpp"

Scroll_list::Scroll_list(Application* _parent, int _x, int _y, int _sx, int _sy,
                         std::vector<std::string> _elements, int _e):
                         Widget(_parent, _x, _y, _sx, _sy), elements(_elements), e(_e)
{

}

void Scroll_list::draw() {
    gout << color(150, 150, 150) << move_to(x, y) << box(size_x, size_y);
    gout << color(255, 255, 255) << move_to(x + 4, y + 4) << box(size_x - 8, size_y - 8);
}

void Scroll_list::handle(genv::event ev, Widget* w) {

}

std::string Scroll_list::getElement() {}
