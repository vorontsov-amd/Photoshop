#pragma once
#include "button.hpp"
#include "widgetManager.hpp"



class ColorPallete : public WidgetManager
{
private:
    unsigned class_button_size = 30;
    unsigned class_button_distance = 10;

    Panel class_backgroud;

    shared_ptr<Widget> class_active_color; 
    shared_ptr<Widget> class_candidate_for_active_color;

    void setActiveColor(const shared_ptr<Widget>& color_ptr) {
        class_active_color = color_ptr;
        
        std::dynamic_pointer_cast<ColorButton>(WidgetManager::arrayOfWidgets().front())->setColor(
            std::dynamic_pointer_cast<ColorButton>(class_active_color)->color()
        );
    }


public:
    ColorPallete(const Vector& position) : class_backgroud{position - Vector{class_button_distance / 2,    
        class_button_distance / 2}, 0, 0, sf::Color{86, 83, 92}} {

        const std::vector<sf::Color> color = {
            sf::Color::Black,
            sf::Color::Blue,
            sf::Color::Cyan,
            sf::Color::Green,
            sf::Color::Magenta,
            sf::Color::Red,
            sf::Color::White,
            sf::Color::Yellow
        };

        class_backgroud.setSize(
            class_button_size + class_button_distance, 
            (color.size() + 1) * (class_button_size + class_button_distance)
        );

        int num_of_color = 0;

        WidgetManager::addWidget(make_shared<ColorButton>(
            position + Vector{0, (num_of_color) * (class_button_size + class_button_distance)},
            class_button_size, 
            class_button_size,
            color[num_of_color]
        ));
        
        for (auto size = color.size(); num_of_color < size; ++num_of_color) {
            WidgetManager::addWidget(make_shared<ColorButton>(
                position + Vector{0, (num_of_color+1) * (class_button_size + class_button_distance)},
                class_button_size, 
                class_button_size,
                color[num_of_color]
            ));
        }

        class_candidate_for_active_color  = WidgetManager::arrayOfWidgets().back(); 
        setActiveColor(class_candidate_for_active_color);
    }

    void draw(sf::RenderWindow& window) const override {
        class_backgroud.draw(window);
        WidgetManager::draw(window);
    }

    void mousePressed(sf::Vector2i position) override {
        for (const auto& button : class_widgets) {
            if (button->contains(position.x, position.y)) {
                class_candidate_for_active_color = button;
            }
        }
    }

    void mouseReleased(sf::Vector2i position) override {
        if (class_candidate_for_active_color->contains(position)) {
            setActiveColor(class_candidate_for_active_color);
        }
    }
};




class ToolPallete : public WidgetManager
{
private:
    unsigned class_button_size = 30;
    unsigned class_button_distance = 10;

    Panel class_backgroud;

    shared_ptr<Widget> class_active_tool; 
    shared_ptr<Widget> class_candidate_for_active_tool;

    void setActiveTool(const shared_ptr<Widget>& tool_ptr) {
        class_active_tool = tool_ptr;
        std::dynamic_pointer_cast<TextureButton>(class_active_tool)->setThinkes(true);
    }

    void resetActiveTool(const shared_ptr<Widget>& tool_ptr) {
        std::dynamic_pointer_cast<TextureButton>(class_active_tool)->setThinkes(false);
        setActiveTool(tool_ptr);
    }


public:
    ToolPallete(const Vector& position) : class_backgroud{position - Vector{class_button_distance / 2,    
        class_button_distance / 2}, 0, 0, sf::Color{86, 83, 92}} {

        const std::vector<std::string> img_path = {
            "../Textures/pencil.png",
            "../Textures/dropper.png",
            "../Textures/watering-can.png",
            "../Textures/zoom_out.png",
            "../Textures/zoom.png",
        };

        class_backgroud.setSize(
            (class_button_size + class_button_distance), 
            (img_path.size() + 1) * (class_button_size + class_button_distance)
        );

        int num_of_instr = 0;
        for (auto size = img_path.size(); num_of_instr < size; ++num_of_instr) {
            WidgetManager::addWidget(make_shared<TextureButton>(
                position + Vector{0, num_of_instr * (class_button_size + class_button_distance)},
                class_button_size, 
                class_button_size,
                img_path[num_of_instr]
            ));
        }

        // WidgetManager::addWidget(make_shared<ColorButton>(
        //     position + Vector{0, num_of_instr * (class_button_size + class_button_distance)},
        //     class_button_size, 
        //     class_button_size,
        //     sf::Color::Black
        // ));

        WidgetManager::addWidget(make_shared<ColorPallete>(
            position + Vector{0, num_of_instr * (class_button_size + class_button_distance)}
        ));

        class_candidate_for_active_tool = WidgetManager::arrayOfWidgets().front(); 
        setActiveTool(class_candidate_for_active_tool);
    }

    void draw(sf::RenderWindow& window) const override {
        class_backgroud.draw(window);
        WidgetManager::draw(window);
    }

    void mousePressed(sf::Vector2i position) override {

        class_widgets.back()->mousePressed(position);

        for (const auto& button : class_widgets) {
            if (button->contains(position.x, position.y)) {
                class_candidate_for_active_tool = button;
            }
        }
    }

    void mouseReleased(sf::Vector2i position) override {
        
        class_widgets.back()->mouseReleased(position);

        if (class_candidate_for_active_tool->contains(position)) {
            if (std::dynamic_pointer_cast<TextureButton>(class_candidate_for_active_tool) != nullptr) {
                resetActiveTool(class_candidate_for_active_tool);
            }
        }
    }
};
