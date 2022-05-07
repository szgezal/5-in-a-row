#ifndef TILE_HPP
#define TILE_HPP

#include "widget.hpp"

class Tile : public Widget
{
public:
    Tile(Gamemaster*, int, int, int, int);
    void draw() override;
    void handle(genv::event, Widget*) override;
};

#endif // TILE_HPP
