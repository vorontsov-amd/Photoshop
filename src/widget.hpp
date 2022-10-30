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
    virtual void mousePressed(sf::Vector2i position) {}
    virtual void mouseReleased(sf::Vector2i position) {}

};

inline Widget::~Widget() {}