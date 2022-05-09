#ifndef TILE_HPP
#define TILE_HPP

#include "widget.hpp"

class Tile : public Widget
{
protected:
    std::string state;
    std::vector<int> index;
public:
    Tile(Gamemaster*, int, int, int, int, std::string, int, int);
    void draw() override;
    void handle(genv::event, Widget*) override;
    void onClick(std::string);
    void onClick();
    std::string getState();
    std::vector<int> getIndex();
};

#endif // TILE_HPP
