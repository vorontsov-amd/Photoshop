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
    std::list<shared_ptr<Widget>> class_widgets;
    bool class_mouse_is_pressed = false;
public:
    void addWidget(const shared_ptr<Widget>& widget_ptr) { class_widgets.push_back(widget_ptr); }
    
    void draw(sf::RenderWindow& window) const override {
        for (const auto& x : class_widgets) if (x != nullptr) x->draw(window);
    }

    bool contains(unsigned x, unsigned y) const override {
        bool status = false;
        for (const auto& widget : class_widgets) if (widget != nullptr) status |= widget->contains(x, y);
        return status;
    }

    bool mousePressed(sf::Vector2i position) override {
        class_mouse_is_pressed = true;
        auto is_pressed = false;
        for (auto widget_it = class_widgets.rbegin(); widget_it != class_widgets.rend(); ++widget_it) {
            if (*widget_it != nullptr) {
                is_pressed = (*widget_it)->mousePressed(position);
                if (is_pressed) {
                    class_widgets.splice(class_widgets.end(), class_widgets, --widget_it.base());
                    break;
                }
            }
        }
        return is_pressed;
    }

    void mouseReleased(sf::Vector2i position) override {
        class_mouse_is_pressed = false;
        for (const auto& widget : class_widgets) if (widget != nullptr) widget->mouseReleased(position);
    }

    void pressButton(const sf::Vector2i& coord) override {
        if (class_mouse_is_pressed)
            for (const auto& widget : class_widgets) if (widget != nullptr) widget->pressButton(coord);
    }

    void move(int dx, int dy) override {
        for (const auto& widget : class_widgets) if (widget != nullptr) widget->move(dx, dy);
    }

    const auto& arrayOfWidgets() const { return class_widgets; }
};


