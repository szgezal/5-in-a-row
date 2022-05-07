#include "widget.hpp"
#include "graphics.hpp"

Widget::Widget(Gamemaster* _parent, int _x, int _y, int _size_x, int _size_y):
     parent(_parent), x(_x), y(_y), size_x(_size_x), size_y(_size_y)
{

}

Widget::Widget(Spinbox* _parent, int _x, int _y, int _size_x, int _size_y):
     sbparent(_parent), x(_x), y(_y), size_x(_size_x), size_y(_size_y)
{

}

Widget::Widget(Dropdown* _parent, int _x, int _y, int _size_x, int _size_y):
     ddparent(_parent), x(_x), y(_y), size_x(_size_x), size_y(_size_y)
{

}

Widget::Widget(Tile* _parent, int _x, int _y, int _size_x, int _size_y):
     tparent(_parent), x(_x), y(_y), size_x(_size_x), size_y(_size_y)
{

}

bool Widget::on_widget(genv::event ev)
{
    return ev.pos_x > x && ev.pos_x < x + size_x &&
           ev.pos_y > y && ev.pos_y < y + size_y;
}
