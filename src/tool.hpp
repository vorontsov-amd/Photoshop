#pragma once
#include <SFML/Graphics.hpp>
#include "utility.hpp"

class ColorPallete;


class Tool
{
public:
    virtual void mousePressed(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) = 0;
    virtual void mouseReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) = 0;
    virtual void pressButton(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) = 0;
    virtual ~Tool() {}
};



class ToolManager : public Tool
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

    const shared_ptr<Tool>& activeTool() { return class_active_tool; }

    void setActiveTool(unsigned distance) {
        class_active_tool = class_tools[distance];
    }

};




class Pencil : public Tool
{
private:
    shared_ptr<ColorPallete> class_pallete;
public:
    Pencil(const shared_ptr<ColorPallete>& pallete) : class_pallete(pallete) {}

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

    Line(const shared_ptr<ColorPallete>& pallete) : class_pallete(pallete) {}

    void mousePressed(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override;

    void mouseReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override;

    void pressButton(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {}

    bool contains(int x, int y) const {
        double k = (P2.y() - P1.y()) / (P2.x() - P1.x());
        double b = P1.y() - k * P1.x();
        return isEqual(y, k * x + b);
    }
};

