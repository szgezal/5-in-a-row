#include "application.hpp"
#include "widget.hpp"

using namespace genv;


Application::Application(int width, int height) {
    gout.open(width, height);
    gout.load_font("LiberationSans-Regular.ttf");
}

void Application::eventloop() {
    for (Widget* w: widgets) {
        w->draw();
    }
    gout << refresh;

    event ev;
    bool selected = false;
    while (gin >> ev && ev.keycode != key_escape) {
        if (ev.button == btn_left) {
            selected = false;
            for (Widget* w: widgets) {
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

        for (Widget* w: widgets) {
            w->draw();
        }

        gout << refresh;
    }
}

void Application::add_widget(Widget* w) {
    widgets.push_back(w);
}
