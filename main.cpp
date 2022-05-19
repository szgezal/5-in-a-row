#include "spinbox.hpp"
#include "dropdown.hpp"
#include "statictext.hpp"
#include "gamemaster.hpp"


class Game : public Gamemaster {
protected:
    Spinbox* spb1;
    Dropdown* sl1;
    SimpleButton* sb;
    StaticText* title;
    StaticText* tshadow;
    StaticText* text1;
    StaticText* text2;

public:
    Game() : Gamemaster() {
        tshadow = new StaticText(this, 155, -5, 300, 200, "Gomoku", 0, 0, 50, 60);
        title = new StaticText(this, 160, -10, 300, 200, "Gomoku", 0, 0, 100, 60);
        text1 = new StaticText(this, 98, 160, 150, 40, "Select game area size:", 0, 0, 0, 16);
        text2 = new StaticText(this, 295, 160, 150, 40, "Select game mode:", 0, 0, 0, 16);
        std::vector<std::string> elements1 = {"2 player","Single player"};
        spb1 = new Spinbox(this, 90, 200, 200, 40, 15, 30);
        sl1 = new Dropdown(this, 300, 200, 250, 40, elements1, 2);
        sb = new SimpleButton(this, 270, 350, 60, 40);
    }

    int getSelectedNum() override {
        return spb1->getNum();
    }

    std::string getSelectedElement() override {
        return sl1->getElement();
    }

    bool play_button_clicked() override{
        return sb->clicked();
    }
};


int main()
{
    Game game;

    game.main_loop();

    return 0;
}
