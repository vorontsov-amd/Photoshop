#pragma once
#include <iostream>
#include "vector.hpp"

class Widget
{
public:    
    virtual ~Widget() = 0;
    virtual void draw(sf::RenderWindow& window) const {}
    virtual void move(int dx, int dy) {}
    virtual bool contains(unsigned x, unsigned y) const = 0;
    virtual bool contains(const sf::Vector2i& position) const final { return contains(position.x, position.y); }
    virtual void pressButton(const sf::Vector2i& coord) {} 
    virtual bool mousePressed(sf::Vector2i position) { return false; }
    virtual bool mouseReleased(sf::Vector2i position) { return false; }
    virtual void scanOffKeyboard(sf::Keyboard::Key key_code) {}
    virtual Vector position() const { return Vector{}; }
    virtual Vector size() const { return Vector{}; }
};

inline Widget::~Widget() {}