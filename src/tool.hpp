#pragma once
#include <SFML/Graphics.hpp>
#include "utility.hpp"

class ColorPallete;


class Tool
{
public:
    virtual void mousePressed(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) = 0;
    virtual void mosueReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) = 0;
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
    void mosueReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {
        for (const auto& tool : class_tools) tool->mosueReleased(texture, x_resolution, y_resolution, x, y);
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

    void mosueReleased(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {}

    void pressButton(sf::Uint32* texture, unsigned x_resolution, unsigned y_resolution, unsigned x, unsigned y) override {
        mousePressed(texture, x_resolution, y_resolution, x, y);
    }
};
