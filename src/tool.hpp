#pragma once
#include <SFML/Graphics.hpp>
#include "utility.hpp"

class ColorPallete;


class PropsPallete : public WidgetManager
{
private:
    unsigned class_button_size = 40;
    unsigned class_offset_of_top = 20;

    Vector class_position;

    Panel class_background;
public:
    PropsPallete(unsigned x_resolution = 0) : class_position{0, class_offset_of_top}, class_background{
        class_position, 
        x_resolution, 
        class_button_size, 
        sf::Color{86, 83, 92}} 
        {}
    
    void draw(sf::RenderWindow& window) const override {
        class_background.draw(window);
        WidgetManager::draw(window);
    }

    const Vector& position() const {
        return class_position;
    }
};


class BaseTool
{
public:
    virtual void mousePressed(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) = 0;
    virtual void mouseReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) = 0;
    virtual void pressButton(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) = 0;
    virtual ~BaseTool() {}
};


class Tool : public BaseTool
{
protected:
    PropsPallete class_props_pallet;
public:
    Tool(unsigned x_resolution) : class_props_pallet{x_resolution} {}
    virtual void draw(sf::RenderWindow& window) const {
        class_props_pallet.draw(window);
    } 
};



class ToolManager : public BaseTool
{
protected:
    std::vector<shared_ptr<Tool>> class_tools;
    shared_ptr<Tool> class_active_tool;

public:
    void addTool(const shared_ptr<Tool>& tool_ptr) { class_tools.push_back(tool_ptr); }

    void mousePressed(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {
        for (const auto& tool : class_tools) tool->mousePressed(texture, x_resolution, y_resolution, x, y);
    }
    void mouseReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {
        for (const auto& tool : class_tools) tool->mouseReleased(texture, x_resolution, y_resolution, x, y);
    }
    void pressButton(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {
        for (const auto& tool : class_tools) tool->pressButton(texture, x_resolution, y_resolution, x, y);
    }

    const shared_ptr<Tool>& activeTool() const { return class_active_tool; }

    void setActiveTool(unsigned distance) {
        class_active_tool = class_tools[distance];
    }

};




class Pencil : public Tool
{
private:
    shared_ptr<ColorPallete> class_pallete;
public:
    Pencil(const shared_ptr<ColorPallete>& pallete, unsigned x_resolution) : Tool{x_resolution}, class_pallete(pallete) {
        class_props_pallet.addWidget(make_shared<TextButton>(class_props_pallet.position(), 100, 25, "active: Pencil", sf::Color{0,0,0,0}));
    }

    void mousePressed(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override;

    void mouseReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {}

    void pressButton(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {
        mousePressed(texture, x_resolution, y_resolution, x, y);
    }
};


class Line : public Tool
{
private:
    shared_ptr<ColorPallete> class_pallete;
public:
    Vector P1, P2;

    Line(const shared_ptr<ColorPallete>& pallete, unsigned x_resolution) : Tool{x_resolution}, class_pallete(pallete) {
        class_props_pallet.addWidget(make_shared<TextButton>(class_props_pallet.position(), 100, 25, "active: Line", sf::Color{0,0,0,0}));
    }

    void mousePressed(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override;

    void mouseReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override;

    void pressButton(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {}

    bool contains(int x, int y) const {
        double k = (P2.y() - P1.y()) / (P2.x() - P1.x());
        double b = P1.y() - k * P1.x();
        return isEqual(y, k * x + b);
    }
};

