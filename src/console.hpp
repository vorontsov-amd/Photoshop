#pragma once
#include "widget.hpp"
#include "button.hpp"
#include <cassert>
#include <functional>

class Console : public Widget 
{
private:
    TextButton class_console_view;
    std::string class_number;
    std::function<void()> class_disabler; 
public:
    bool is_active_console = false;
public:
    Console(const Vector& position, unsigned width, unsigned heigth, sf::Color color, std::function<void()> disabler) :
        class_console_view{position, width, heigth, "0.0", color},
        class_number{"0.0"},
        class_disabler{disabler}
        {
            class_console_view.setTextColor(sf::Color::White);
        }

    void scanOffKeyboard(sf::Keyboard::Key key_code) {        
        if (is_active_console == false) return;
        
        if (((class_number.size() + 1) * class_console_view.getCharacterSize() >= class_console_view.getSize().x * 1.5) && key_code != sf::Keyboard::BackSpace) return;
        
        if (sf::Keyboard::Num0 <= key_code && key_code <= sf::Keyboard::Num9) {
            if ((class_number.size() == 1 && class_number[0] == '0') or
                (class_number.size() == 2 && class_number[0] == '-' && class_number[1] == '0')) {
                    return;
                }
            class_number += (key_code + '0' - sf::Keyboard::Num0);
        }
        else if (sf::Keyboard::Subtract == key_code || sf::Keyboard::Dash == key_code) {
            if (class_number.empty()) {
                class_number = "-";
            }
        }
        else if (sf::Keyboard::BackSpace == key_code) {
            if (!class_number.empty()) {
                class_number.pop_back();
            }
        }
        else if (sf::Keyboard::Period == key_code) {
            if (class_number.size() == 0 or class_number.size() == 1 && class_number[0] == '-') {
                return;
            }
            if (class_number.find('.') == std::string::npos) {
                class_number.push_back('.');
            }
        }

        class_console_view.setText(class_number);
    }

    void draw(sf::RenderWindow& window) const override {
        class_console_view.draw(window);
    }

    bool contains(unsigned x, unsigned y) const override { 
        return class_console_view.contains(x, y); 
    }

    void move(int dx, int dy) override {
        class_console_view.move(dx, dy);
    }


    virtual bool mousePressed(sf::Vector2i position) override {
        if (contains(position.x, position.y)) {
            class_disabler();
            is_active_console = true;
            return true;
        }      
        return false;
    }



    ~Console() {}
};

