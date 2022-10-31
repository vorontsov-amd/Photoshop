#pragma once
#include "widget.hpp"
#include "color.hpp"
#include <SFML/Graphics.hpp>
#include <string>


class Button : public Widget
{
protected:
    sf::RectangleShape class_button;
    bool class_is_pressed = false;
public:
    Button(const Vector& position, unsigned width, unsigned height) :
        class_button{sf::Vector2f{width, height}} {
            class_button.setPosition(position);
        }

    virtual void setSize(unsigned width, unsigned height) {
        class_button.setSize(sf::Vector2f{width, height});
    }

    virtual void draw(sf::RenderWindow& window) const override {
        window.draw(class_button);
    }

    virtual bool contains(unsigned x, unsigned y) const final override {
        return class_button.getGlobalBounds().contains(x, y);
    }

    virtual void pressButton(const sf::Vector2i& coord) override {
    } 

    void move(int dx, int dy) override {
        class_button.setPosition(class_button.getPosition().x + dx, class_button.getPosition().y + dy);
    }

    void setThinkes(bool flag) {
        class_button.setOutlineThickness(flag);
        class_button.setOutlineColor(sf::Color::Yellow);
    }

    ~Button() = 0;
};

inline Button::~Button() {}


class TextureButton : public Button
{
private:
    sf::Texture class_texture;
public:
    TextureButton(const Vector& position, unsigned width, unsigned height, const std::string& path) :
        Button{position, width, height} {
            class_texture.loadFromFile(path);
            class_button.setTexture(&class_texture);
        }
};



class ColorButton : public Button
{
public:
    ColorButton(const Vector& position, unsigned width, unsigned height, const sf::Color& color) :
        Button{position, width, height} {
            class_button.setFillColor(color);
        }

    const sf::Color& color() const { return class_button.getFillColor(); } 
    void setColor(const sf::Color& color) { class_button.setFillColor(color); } 

};


class TextButton : public ColorButton 
{
private: 
    sf::Text class_text;
    sf::Font class_font;
public:
    TextButton(const Vector& position, unsigned width, unsigned height, const std::string& str, const sf::Color& background_color) :
        ColorButton{position, width, height, background_color} {
            class_font.loadFromFile("../font/Open_Sans/OpenSans.ttf");
            class_text.setFont(class_font);
            class_text.setString(str);
            class_text.setCharacterSize(height * 0.8);
            class_text.setFillColor(sf::Color::Black);
            class_text.setPosition(position);
    }

    void setTextColor(const sf::Color& color) {
        class_text.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) const override {
        ColorButton::draw(window);
        window.draw(class_text);
    }

    void moveText(int dx, int dy) {
        class_text.setPosition(class_text.getPosition().x + dx, class_text.getPosition().y + dy);
    }

    void move(int dx, int dy) override {
        ColorButton::move(dx, dy);
        moveText(dx, dy);
    }
};


using Panel = ColorButton;