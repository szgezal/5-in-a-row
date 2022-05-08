#ifndef TILE_HPP
#define TILE_HPP

#include "widget.hpp"

class Tile : public Widget
{
protected:
    std::string state;
public:
    Tile(Gamemaster*, int, int, int, int, std::string);
    void draw() override;
    void handle(genv::event, Widget*) override;
    void on_click(std::string);
    void on_click();
    std::string getState();
};

#endif // TILE_HPP
