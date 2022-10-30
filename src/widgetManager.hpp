#pragma once
#include "widget.hpp"
#include <list>
#include <algorithm>
#include <memory>


using std::shared_ptr;
using std::make_shared;

class WidgetManager : public Widget
{
protected:
    std::vector<shared_ptr<Widget>> class_widgets;
    bool class_mouse_is_pressed = false;
public:
    void addWidget(const shared_ptr<Widget>& widget_ptr) { class_widgets.push_back(widget_ptr); }
    
    void draw(sf::RenderWindow& window) const override {
        for (const auto& x : class_widgets) x->draw(window);
    }

    bool contains(unsigned x, unsigned y) const override {
        bool status = false;
        for (const auto& widget : class_widgets) status |= widget->contains(x, y);
        return status;
    }

    void mousePressed(sf::Vector2i position) override {
        class_mouse_is_pressed = true;
        for (const auto& widget : class_widgets) widget->mousePressed(position);
    }

    void mouseReleased(sf::Vector2i position) override {
        class_mouse_is_pressed = false;
        for (const auto& widget : class_widgets) widget->mouseReleased(position);
    }

    void pressButton(const sf::Vector2i& coord) override {
        if (class_mouse_is_pressed)
            for (const auto& widget : class_widgets) widget->pressButton(coord);
    }

    void move(int dx, int dy) override {
        for (const auto& widget : class_widgets) widget->move(dx, dy);
    }

    const auto& arrayOfWidgets() const { return class_widgets; }
};


