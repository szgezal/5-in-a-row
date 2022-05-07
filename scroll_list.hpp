#ifndef SCROLL_LIST_HPP
#define SCROLL_LIST_HPP

#include "widget.hpp"

class Scroll_list : public Widget
{
protected:
    std::vector<std::string> elements;
    int e;
    std::string s;
public:
    Scroll_list(Application*, int, int, int, int, std::vector<std::string>, int);
    void draw() override;
    void handle(genv::event, Widget*) override;
    std::string getElement() override;
};

#endif // SCROLL_LIST_HPP
