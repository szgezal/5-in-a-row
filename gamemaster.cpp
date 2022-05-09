#include "gamemaster.hpp"
#include "widget.hpp"
#include "tile.hpp"
#include <math.h>

#include <iostream>
using namespace std;

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
        if (ev.button == btn_left) {
            selected = false;
            for (size_t i = 0; i < game_area.size(); i++)
                for (Tile* t: game_area[i])
                    if (t->on_widget(ev)) {
                        focused = t;
                        selected = true;
                    }
        }

        if (selected && valid_move(focused, ev) && ev.type == ev_mouse && ev.button > 0) {
            if (player == "o") {
                player = "x";
            } else if (player == "x")
                player = "o";

            turn_counter++;

            focused->onClick(player);
        }

        for (size_t i = 0; i < game_area.size(); i++)
            for (Tile* t: game_area[i]) {
                t->draw();
            }

        gout << refresh;

        if (!this->is_in_progress(ev) && ev.type == ev_mouse && ev.button > 0) {
            cout << "vége" << endl;
            break;
        }
    }
}

bool Gamemaster::valid_move(Tile* focused, genv::event ev) {

    int k, l;
    if (turn_counter > 1 && ev.type == ev_mouse && ev.button > 0) {

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {

                k = focused->getIndex()[0] + i;
                l = focused->getIndex()[1] + j;
                if (k < 0 || k >= int(game_area.size()) || l < 0 || l >= int(game_area.size())) {
                    k = focused->getIndex()[0];
                    l = focused->getIndex()[1];
                }
                if (game_area[k][l]->getState() != "") {
                    return true;
                }
            }
        }
        return false;
    } else
        return true;
}

// játék logika:

bool Gamemaster::is_in_progress(genv::event ev) {
    if (!five_in_a_row(ev))
        return true;
    else
        return false;
}

bool Gamemaster::five_in_a_row(genv::event ev) {
    for (int i = 0; i < int(game_area.size()); i++)
        for (int j = 0; j < int(game_area.size()); j++)
            if (game_area[i][j]->getState() == player && ev.type == ev_mouse && ev.button > 0) {
                int counter;
                for (int k = 0; k < 4; k++) {
                    counter = 0;
                    switch (k) {
                    case 0:
                        for (int l = -2; l <= 2; l++) {
                            if (i+l < 0 || i+l >= int(game_area.size()) || j+l < 0 || j+l >= int(game_area.size())) {}
                            else if (game_area[i + l][j + l]->getState() == player) {
                                counter++;
                            }
                        }
                        break;
                    case 1:
                        for (int l = -2; l <= 2; l++) {
                            if (i-l < 0 || i-l >= int(game_area.size()) || j+l < 0 || j+l >= int(game_area.size())) {}
                            else if (game_area[i - l][j + l]->getState() == player) {
                                counter++;
                            }
                        }
                        break;
                    case 2:
                        for (int l = -2; l <= 2; l++) {
                            if (i+l < 0 || i+l >= int(game_area.size()) || j < 0 || j >= int(game_area.size())) {}
                            else if (game_area[i + l][j]->getState() == player) {
                                counter++;
                            }
                        }
                        break;
                    case 3:
                        for (int l = -2; l <= 2; l++) {
                            if (i < 0 || i >= int(game_area.size()) || j+l < 0 || j+l >= int(game_area.size())) {}
                            else if (game_area[i][j + l]->getState() == player) {
                                counter++;
                            }
                        }
                        break;
                    }

                    if (counter == 5)
                        return true;
                }
            }
    return false;
}

void Gamemaster::create_game_area(int area_size) {
    int size = area_size/2.0;

    if (area_size % 2 == 0)
        for (int i = -size; i < size; i++) {
            std::vector<Tile*> v;
            for(int j = -size; j < size; j++) {
                v.push_back(new Tile(this, width/2 + 30 * j, height/2 + 30 * i, 30, 30, "", i + size, j + size));
            }
            game_area.push_back(v);
        }
    else
        for (int i = -size; i <= size; i++) {
            std::vector<Tile*> v;
            for(int j = -size; j <= size; j++) {
                v.push_back(new Tile(this, width/2 + 30 * j - 15, height/2 + 30 * i - 15, 30, 30, "", i + size, j + size));
            }
            game_area.push_back(v);
        }
}
