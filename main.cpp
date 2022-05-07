#include "spinbox.hpp"
#include "dropdown.hpp"
#include "gamemaster.hpp"
#include <time.h>


class App : public Gamemaster {
protected:
//    Spinbox* spb1;
//    Spinbox* spb2;
//    Dropdown* sl1;
//    Dropdown* sl2;
//    SimpleButton* sb;
//    Textreader* tr;


public:
    App() : Gamemaster() {
        this->create_game_area(17);
//        std::vector<std::string> elements1 = {"Text 0","Text 1","Text 2","Text 3","Text 4","Text 5","Text 6","Text 7","Text 8","Text 9"};
//        std::vector<std::string> elements2 = {"Text 10","Text 11","Text 12","Text 13","Text 14","Text 15","Text 16","Text 17","Text 18","Text 19"};
//        spb1 = new Spinbox(this, 20, 20, 200, 40, -20, 20);
//        spb2 = new Spinbox(this, 300, 20, 200, 40, -30, 30);
//        sl1 = new Dropdown(this, 20, 100, 200, 40, elements1, 4);
//        sl2 = new Dropdown(this, 300, 100, 200, 40, elements2, 6);
//        sb = new SimpleButton(this, 550, 20, 40, 40);
    }

//    void write(genv::event ev) override {
//        if (sb->on_widget(ev)) {
//            std::ofstream f("ellenorzes.txt");
//            f << spb1->getNum() << ", ";
//            f << spb2->getNum() << "\n";
//            f << sl1->getElement() << ", ";
//            f << sl2->getElement();
//            f.close();
//        }
//    }
};


int main()
{
    srand(time(NULL));

    App app;

    app.eventloop();

    return 0;
}
