#include "gamemaster.hpp"
#include "widget.hpp"
#include "statictext.hpp"
#include "tile.hpp"
#include <math.h>

using namespace genv;

Gamemaster::Gamemaster() {
    gout.open(width, height);
    gout.load_font("LiberationSans-Regular.ttf");
}

void Gamemaster::main_loop() {

    event ev;
    bool selected = false;

    while (true) {

        // menu
        gout << color(255, 255, 255) << move_to(0, 0) << box(width, height) << refresh;

        for (Widget* w: menu_widgets)
            w->draw();

        while (gin >> ev) {
            if (ev.button == btn_left) {
                selected = false;
                for (Widget* w: menu_widgets)
                    if (w->on_widget(ev)) {
                        wfocused = w;
                        selected = true;
                    }
            }

            if (selected) {
                wfocused->handle(ev, wfocused);
                wfocused->draw();
            }

            if (ev.keycode == key_escape)
                exit(0);

            if (play_button_clicked())
                break;

            gout << refresh;
        }

        // setup before game
        turn_counter = 1;
        player = "x";
        game_area.clear();
        create_game_area(getSelectedNum());

        // single player mode
        if (getSelectedElement() == "Single player") {

            gout << color(255, 255, 255) << move_to(0, 0) << box(width, height) << refresh;

            StaticText* player_indicator = new StaticText(this, width/2 - 50, 10, 100, 20, "Player (X)", 255, 0, 0, 16);

            for (size_t i = 0; i < game_area.size(); i++)
                for (Tile* t: game_area[i])
                    t->draw();

            com_wins = false;

            gin.timer(1000/60);

            // game loop
            while (true) {
                gin >> ev;

                if (!this->is_in_progress() || com_wins) {
                    if (is_draw) {
                        player_indicator->setText("Draw!", 100, 100, 100);
                        player_indicator->draw();
                    } else if (com_wins) {
                        player_indicator->setText("Winner: COM (O)", 0, 0, 255);
                        player_indicator->draw();
                    } else {
                        player_indicator->setText("Winner: Player (X)", 255, 0, 0);
                        player_indicator->draw();
                    }

                    StaticText* text = new StaticText(this, width/2 - 100, 570, 200, 20, "Press ENTER to continue", 0, 0, 0, 16);
                    text->draw();

                    gout << refresh;

                    while (gin >> ev)
                        if (ev.keycode == key_escape)
                            exit(0);
                        else if (ev.keycode == key_enter)
                            break;

                    menu_widgets.pop_back();
                    menu_widgets.pop_back();
                    break;

                } else {

                    if (ev.button == btn_left && player == "x") {
                        selected = false;
                        for (size_t i = 0; i < game_area.size(); i++)
                            for (Tile* t: game_area[i])
                                if (t->on_widget(ev)) {
                                    tfocused = t;
                                    selected = true;
                                }
                    }

                    if (selected && valid_move(tfocused, ev) && ev.type == ev_mouse && ev.button > 0 && player == "x") {

                        player_indicator->setText("COM (O)", 0, 0, 255);

                        if (player == "o") {
                            player_indicator->setText("Player (X)", 255, 0, 0);
                        }

                        turn_counter++;

                        tfocused->onClick(player);
                    }

                    if (player == "o" && turn_counter % 2 == 0) {

                        com(tfocused, ev);

                        turn_counter++;

                        if (five_in_a_row())
                            com_wins = true;
                        else
                            player = "x";
                    }

                    for (size_t i = 0; i < game_area.size(); i++)
                        for (Tile* t: game_area[i])
                            t->draw();                      

                    if (!five_in_a_row())
                        player_indicator->draw();

                    if (!five_in_a_row() && ev.type == ev_mouse && ev.button > 0 && tfocused->getState() == "x") {
                        player = "o";
                        player_indicator->setText("COM (O)", 0, 0, 255);
                    } else {
                        player = "x";
                        player_indicator->setText("Player (X)", 255, 0, 0);
                    }

                    gout << refresh;

                    if (ev.keycode == key_escape)
                        exit(0);
                }
            }

        // 2 player mode
        } else if (getSelectedElement() == "2 player") {

            gout << color(255, 255, 255) << move_to(0, 0) << box(width, height) << refresh;

            StaticText* player_indicator = new StaticText(this, width/2 - 50, 10, 100, 20, "Player1 (X)", 255, 0, 0, 16);

            for (size_t i = 0; i < game_area.size(); i++)
                for (Tile* t: game_area[i])
                    t->draw();

            // game loop
            while (true) {
                gin >> ev;

                if (!this->is_in_progress()) {
                    if (is_draw) {
                        player_indicator->setText("Draw!", 100, 100, 100);
                        player_indicator->draw();
                    } else {
                        player_indicator->changePlayer("Winner: " + player_indicator->getText());
                        player_indicator->draw();
                    }

                    StaticText* text = new StaticText(this, width/2 - 100, 570, 200, 20, "Press ENTER to continue", 0, 0, 0, 16);
                    text->draw();

                    gout << refresh;

                    while (gin >> ev) {
                        if (ev.keycode == key_escape)
                            exit(0);
                        else if (ev.keycode == key_enter)
                            break;
                    }

                    menu_widgets.pop_back();
                    menu_widgets.pop_back();
                    break;

                } else {

                    if (ev.button == btn_left) {
                        selected = false;
                        for (size_t i = 0; i < game_area.size(); i++)
                            for (Tile* t: game_area[i])
                                if (t->on_widget(ev)) {
                                    tfocused = t;
                                    selected = true;
                                }
                    }

                    if (selected && valid_move(tfocused, ev) && ev.type == ev_mouse && ev.button > 0) {

                        if (player == "x")
                            player_indicator->setText("Player2 (O)", 0, 0, 255);
                        else if (player == "o")
                            player_indicator->setText("Player1 (X)", 255, 0, 0);

                        turn_counter++;

                        tfocused->onClick(player);
                    }

                    for (size_t i = 0; i < game_area.size(); i++)
                        for (Tile* t: game_area[i])
                            t->draw();                      

                    if (!five_in_a_row())
                        player_indicator->draw();


                    gout << refresh;

                    if (!five_in_a_row()) {

                        if (player_indicator->getText() == "Player2 (O)")
                            player = "o";
                        else if (player_indicator->getText() == "Player1 (X)")
                            player = "x";

                    } else {
                        if (player == "x")
                            player_indicator->setText("Player1 (X)", 0, 0, 255);
                        else if (player == "o")
                            player_indicator->setText("Player2 (O)", 255, 0, 0);
                    }


                    if (ev.keycode == key_escape)
                        exit(0);

                }
            }
        }
    }
}

// game logic
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
                if (game_area[k][l]->getState() != "" && focused->getState() == "")
                    return true;
            }
        }
        return false;
    } else
        return true;
}

bool Gamemaster::is_in_progress() {
    int counter = 0;
    for (int i = 0; i < int(game_area.size()); i++)
        for (int j = 0; j < int(game_area.size()); j++)
            if (game_area[i][j]->getState() != "") {counter++;}

    if (counter == int(game_area.size()*game_area.size()))
        is_draw = true;

    if (counter != int(game_area.size()*game_area.size()) && !five_in_a_row())
        return true;
    else
        return false;
}

bool Gamemaster::five_in_a_row() {
    for (int i = 0; i < int(game_area.size()); i++)
        for (int j = 0; j < int(game_area.size()); j++)
            if (game_area[i][j]->getState() == player) {
                int counter;
                for (int k = 0; k < 4; k++) {
                    counter = 0;
                    switch (k) {
                    case 0:
                        for (int l = -2; l <= 2; l++) {
                            if (i+l < 0 || i+l >= int(game_area.size()) || j+l < 0 || j+l >= int(game_area.size())) {}
                            else if (game_area[i + l][j + l]->getState() == player)
                                counter++;
                        }
                        break;
                    case 1:
                        for (int l = -2; l <= 2; l++) {
                            if (i-l < 0 || i-l >= int(game_area.size()) || j+l < 0 || j+l >= int(game_area.size())) {}
                            else if (game_area[i - l][j + l]->getState() == player)
                                counter++;
                        }
                        break;
                    case 2:
                        for (int l = -2; l <= 2; l++) {
                            if (i+l < 0 || i+l >= int(game_area.size()) || j < 0 || j >= int(game_area.size())) {}
                            else if (game_area[i + l][j]->getState() == player)
                                counter++;
                        }
                        break;
                    case 3:
                        for (int l = -2; l <= 2; l++) {
                            if (i < 0 || i >= int(game_area.size()) || j+l < 0 || j+l >= int(game_area.size())) {}
                            else if (game_area[i][j + l]->getState() == player)
                                counter++;
                        }
                        break;
                    }

                    if (counter == 5)
                        return true;
                }
            }
    return false;
}

void Gamemaster::com(Tile* t, genv::event) {
    int i = t->getIndex()[0];
    int j = t->getIndex()[1];

    if (t->getIndex()[0] - 1 < 0 || t->getIndex()[0] - 1 >= int(game_area.size())
            || t->getIndex()[1] - 1 < 0 || t->getIndex()[1] - 1 >= int(game_area.size())) {}
    else if (turn_counter == 2) {
        game_area[t->getIndex()[0] - 1][t->getIndex()[1] - 1]->setState("o");
        return;
    }

    for (int k = -2; k <= 2; k += 2) {
        for (int l = -2; l <= 2; l += 2) {
            if (i + k < 0 || i + k >= int(game_area.size()) || j + l < 0 || j + l >= int(game_area.size())) {}
            else if ((game_area[i + k][j + l]->getState() == "x") &&
                (game_area[i + k/2][j + l/2]->getState() == "")) {
                    game_area[i + k/2][j + l/2]->setState("o");
                    return;
            }
            if (i + k < 0 || i + k >= int(game_area.size()) || j + l < 0 || j + l >= int(game_area.size())) {}
            else if ((game_area[i + k][j + l]->getState() == "x") &&
                (game_area[i + k/2][j + l/2]->getState() == "x") &&
                (game_area[i - k/2][j - l/2]->getState() == "")) {
                    game_area[i - k/2][j - l/2]->setState("o");
                    return;
            }
        }
    }
    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (i + k*2 < 0 || i + k*2 >= int(game_area.size()) || j + l*2 < 0 || j + l*2 >= int(game_area.size())) {}
            else if (game_area[i + k][j + l]->getState() == "x" &&
                game_area[i + k*2][j + l*2]->getState() == "") {
                    game_area[i + k*2][j + l*2]->setState("o");
                    return;
            }
            if (i + k*2 < 0 || i + k*2 >= int(game_area.size()) || j + l*2 < 0 || j + l*2 >= int(game_area.size())) {}
            else if ((game_area[i + k][j + l]->getState() == "x") &&
                (game_area[i + k*2][j + l*2]->getState() == "x") &&
                (game_area[i - k*2][j - l*2]->getState() == "")) {
                    game_area[i - k*2][j - l*2]->setState("o");
                    return;
            }
        }
    }

    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (i + k < 0 || i + k >= int(game_area.size()) || j + l < 0 || j + l >= int(game_area.size())) {}
            else if (game_area[i + k][j + l]->getState() == "") {
                game_area[i + k][j + l]->setState("o");
                return;
            }
        }
    }
}

// creating tiles
void Gamemaster::create_game_area(int area_size) {
    int size = area_size/2.0;

    int area_size_px = 0.9 * width;

    if (area_size % 2 == 0)
        for (int i = -size; i < size; i++) {
            std::vector<Tile*> v;
            for(int j = -size; j < size; j++) {
                v.push_back(new Tile(this, width/2 + (area_size_px/area_size) * j,
                                           height/2 + (area_size_px/area_size) * i,
                                           (area_size_px/area_size),
                                           (area_size_px/area_size), "", i + size, j + size));
                menu_widgets.pop_back();
            }
            game_area.push_back(v);
        }
    else
        for (int i = -size; i <= size; i++) {
            std::vector<Tile*> v;
            for(int j = -size; j <= size; j++) {
                v.push_back(new Tile(this, width/2 + (area_size_px/area_size) * j - (area_size_px/area_size)/2,
                                           height/2 + (area_size_px/area_size) * i - (area_size_px/area_size)/2,
                                           (area_size_px/area_size),
                                           (area_size_px/area_size), "", i + size, j + size));
                menu_widgets.pop_back();
            }
            game_area.push_back(v);
        }
}

void Gamemaster::add_widget(Widget* w) {
    menu_widgets.push_back(w);
}
