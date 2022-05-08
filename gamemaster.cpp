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

    gout << color(255, 255, 255) << move_to(0, 0) << box(width, height) << refresh;

    for (size_t i = 0; i < game_area.size(); i++) {
        for (Tile* t: game_area[i]) {
            t->draw();
        }
    }

    event ev;
    bool selected = false;
    while (gin >> ev && ev.keycode != key_escape) {
        if (ev.button == btn_left /*&& valid_move()*/) {
            selected = false;
            for (size_t i = 0; i < game_area.size(); i++)
                for (Tile* t: game_area[i]) {
                    if (t->on_widget(ev)) {
                        focused = t;
                        selected = true;
                    }
                }
            if (turn == "o")
                turn = "x";
            else
                turn = "o";
        }
        if (selected) {
            focused->on_click(turn);

        }

        for (size_t i = 0; i < game_area.size(); i++)
            for (Tile* t: game_area[i]) {
                t->draw();
            }

//        if (!this->is_in_progress())
//            break;

        gout << refresh;
    }
}

// játék logika:

//bool Gamemaster::is_in_progress() {
//    if (!five_in_a_row())
//        return true;
//    else
//        return false;
//}

//bool Gamemaster::five_in_a_row() {
//    for (size_t i = 0; i < game_area.size(); i++)
//        for (size_t j = 0; j < game_area[i].size(); j++)
//            if (game_area[i][j]->getState() == turn) {
//                for (int k = -2; k <= 2; k++)
//                    if (game_area[i + k][j + k]->getState() != turn &&
//                        game_area[i - k][j + k]->getState() != turn &&
//                        game_area[i + k][j]->getState() != turn &&
//                        game_area[i][j + k]->getState() != turn)
//                            return false;
//            }
//    return true;
//}

void Gamemaster::create_game_area(int area_size) {
    int size = area_size/2.0;

    if (area_size % 2 == 0)
        for (int i = -size; i < size; i++) {
            std::vector<Tile*> v;
            for(int j = -size; j < size; j++) {
                v.push_back(new Tile(this, width/2 + 30 * j, height/2 + 30 * i, 30, 30, ""));
            }
            game_area.push_back(v);
        }
    else
        for (int i = -size; i <= size; i++) {
            std::vector<Tile*> v;
            for(int j = -size; j <= size; j++) {
                v.push_back(new Tile(this, width/2 + 30 * j - 15, height/2 + 30 * i - 15, 30, 30, ""));
            }
            game_area.push_back(v);
        }
}
