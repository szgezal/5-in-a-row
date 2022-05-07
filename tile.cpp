#include "tile.hpp"
using namespace genv;

Tile::Tile(Gamemaster* _parent, int _x, int _y, int _size_x, int _size_y) : Widget(_parent, _x, _y, _size_x, _size_y)
{

}

void Tile::draw() {
    gout << color(0, 0, 0) << move_to(x, y) << box(size_x, size_y);
    gout << color(255, 255, 255) << move_to(x + 1, y + 1) << box(size_x - 2, size_y - 2);
}

void Tile::handle(genv::event ev, Widget* w) {}
