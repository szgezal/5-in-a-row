#include "gamemaster.hpp"
#include "widget.hpp"
#include "tile.hpp"
#include <math.h>

using namespace genv;

Gamemaster::Gamemaster() {
    gout.open(width, height);
    gout.load_font("LiberationSans-Regular.ttf");
}

void Gamemaster::eventloop() {

    gout << color(0, 0, 0) << move_to(0, 0) << box(width, height) << refresh;

    gout << color(255, 255, 255) << move_to(0, 0) << box(width, height) << refresh;

    for (size_t i = 0; i < game_area.size(); i++) {

        for (Widget* tile: game_area[i]) {
            tile->draw();
        }

    }

    event ev;
    bool selected = false;
    while (gin >> ev && ev.keycode != key_escape) {
        gout << color(255, 255, 255) << move_to(0, 0) << box(width, height);
        if (ev.button == btn_left) {
            selected = false;
            for (size_t i = 0; i < game_area.size(); i++)
                for (Widget* w: game_area[i]) {
                    if (w->on_widget(ev)) {
                        focused = w;
                        selected = true;
                    }
                }
//            write(ev);
        }
        if (selected) {
            focused->handle(ev, focused);
        }

        for (size_t i = 0; i < game_area.size(); i++)
            for (Widget* w: game_area[i]) {
                w->draw();
            }

        gout << refresh;
    }
}



void Gamemaster::create_game_area(int area_size) {
    int size = area_size/2.0;

    if (area_size % 2 == 0)
        for (int i = -size; i < size; i++) {
            std::vector<Tile*> v;
            for(int j = -size; j < size; j++) {
                v.push_back(new Tile(this, width/2 + 30 * j, height/2 + 30 * i, 30, 30));
            }
            game_area.push_back(v);
        }
    else
        for (int i = -size; i <= size; i++) {
            std::vector<Tile*> v;
            for(int j = -size; j <= size; j++) {
                v.push_back(new Tile(this, width/2 + 30 * j - 15, height/2 + 30 * i - 15, 30, 30));
            }
            game_area.push_back(v);
        }
}
