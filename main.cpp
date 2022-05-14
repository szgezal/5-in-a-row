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

public:
    Game() : Gamemaster() {
        tshadow = new StaticText(this, 155, -45, 300, 300, "Gomoku", 0, 0, 50, 60);
        title = new StaticText(this, 160, -50, 300, 300, "Gomoku", 0, 0, 100, 60);
        std::vector<std::string> elements1 = {"2 player", "Single player (coming soon)"};
        spb1 = new Spinbox(this, 90, 200, 200, 40, 15, 30);
        sl1 = new Dropdown(this, 300, 200, 250, 40, elements1, 2);
        sb = new SimpleButton(this, 270, 400, 60, 40);
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
