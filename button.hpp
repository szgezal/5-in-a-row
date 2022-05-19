#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"

class Button : public Widget
{
protected:
    bool down = false;

public:
    Button(Gamemaster*, int, int, int, int);
    Button(Spinbox*, int, int, int, int);
    Button(Dropdown*, int, int, int, int);
    virtual void draw() override = 0;
    void handle(genv::event, Widget*) override;
};

class SimpleButton : Button {
public:
    SimpleButton(Gamemaster*, int, int, int, int);
    void draw() override;
    bool on_widget(genv::event) override;
    bool clicked();
};

class ButtonUp : public Button {
public:
    ButtonUp(Spinbox*, int, int, int, int);
    void draw() override;
};

class ButtonDown : public Button {
public:
    ButtonDown(Spinbox*, int, int, int, int);
    ButtonDown(Dropdown*, int, int, int, int);
    void draw() override;
};

#endif // BUTTON_HPP
