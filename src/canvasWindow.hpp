#include "widget.hpp"
#include "button.hpp"
#include "utility.hpp"
#include "pallete.hpp"
#include "tool.hpp"


class CanvasWindow : public Widget
{
private:
    sf::RectangleShape class_wnd;
    sf::Color class_marker_color = sf::Color::Black;
    sf::Uint32* class_pixels; 
    sf::Texture class_texture;

    shared_ptr<ToolManager> class_tool_manager;

public:
    CanvasWindow(const Vector& position, unsigned width, unsigned height, const shared_ptr<ToolManager>& tool_manager) : 
        class_wnd{sf::Vector2f{width, height}},
        class_tool_manager{tool_manager} {
            class_wnd.setPosition(position);
            class_pixels = new sf::Uint32 [width * height] {};

            for (int i = 0; i < width * height; ++i) class_pixels[i] = 0xffffffff;

            class_texture.create(width, height);
            class_texture.update((sf::Uint8*)class_pixels);
            class_wnd.setTexture(&class_texture);
        } 
    
    void draw(sf::RenderWindow& window) const override {
        window.draw(class_wnd);
    }

    void move(int dx, int dy) {
        class_wnd.setPosition(class_wnd.getPosition().x + dx, class_wnd.getPosition().y + dy);
    }

    bool contains(unsigned x, unsigned y) const final override {
        return class_wnd.getGlobalBounds().contains(x, y);
    }

    virtual void mousePressed(sf::Vector2i coord) {
        if (!contains(coord.x, coord.y)) return;
        
        unsigned y = coord.y - class_wnd.getPosition().y;
        unsigned x = coord.x - class_wnd.getPosition().x; 

        // for (int dx = -1; dx <= 1; ++dx) {
        //     for (int dy = -1; dy <= 1; ++dy) {
        //         if (y == 0 && dy < 0) continue;
        //         class_pixels[clamp((y + dy) * (int)class_wnd.getSize().x + (x + dx), 0U, unsigned(class_wnd.getSize().x * class_wnd.getSize().y - 1))] = 0xff000000;
        //     }
        // }

        class_tool_manager->activeTool()->mousePressed(class_pixels, class_wnd.getSize().x, class_wnd.getSize().y, x, y);

        class_texture.update((sf::Uint8*)class_pixels, class_wnd.getSize().x, class_wnd.getSize().y, 0, 0);
        
        class_wnd.setTexture(&class_texture);
    }


    virtual void mouseReleased(sf::Vector2i coord) {
        if (!contains(coord.x, coord.y)) return;
        
        unsigned y = coord.y - class_wnd.getPosition().y;
        unsigned x = coord.x - class_wnd.getPosition().x; 

        class_tool_manager->activeTool()->mouseReleased(class_pixels, class_wnd.getSize().x, class_wnd.getSize().y, x, y);

        class_texture.update((sf::Uint8*)class_pixels, class_wnd.getSize().x, class_wnd.getSize().y, 0, 0);
        
        class_wnd.setTexture(&class_texture);
    }


    void pressButton(const sf::Vector2i& coord) override { 
        if (!contains(coord.x, coord.y)) return;
        
        unsigned y = coord.y - class_wnd.getPosition().y;
        unsigned x = coord.x - class_wnd.getPosition().x; 

        // for (int dx = -1; dx <= 1; ++dx) {
        //     for (int dy = -1; dy <= 1; ++dy) {
        //         if (y == 0 && dy < 0) continue;
        //         class_pixels[clamp((y + dy) * (int)class_wnd.getSize().x + (x + dx), 0U, unsigned(class_wnd.getSize().x * class_wnd.getSize().y - 1))] = 0xff000000;
        //     }
        // }

        class_tool_manager->activeTool()->pressButton(class_pixels, class_wnd.getSize().x, class_wnd.getSize().y, x, y);

        class_texture.update((sf::Uint8*)class_pixels, class_wnd.getSize().x, class_wnd.getSize().y, 0, 0);
        
        class_wnd.setTexture(&class_texture);    
    }
};


class DrawingWindow : public WidgetManager
{
private:
    unsigned class_panel_size = 15;
    sf::Color class_panel_color = sf::Color{190, 190, 190};

    sf::Vector2i class_last_position;
    sf::Vector2i class_delta;

    Panel class_panel;

public:
    DrawingWindow(const Vector& position, unsigned width, unsigned height, const shared_ptr<ToolManager>& tool_palete) :
        class_panel{position, width, class_panel_size, class_panel_color} {
        WidgetManager::addWidget(make_shared<TextureButton>(
            position + Vector{width - class_panel_size, 0},
            class_panel_size,
            class_panel_size,
            "../Textures/cross.png"
        ));
        WidgetManager::addWidget(make_shared<CanvasWindow>(
            position + Vector{0, class_panel_size}, 
            width,
            height,
            tool_palete
        ));
    }

    void draw(sf::RenderWindow& window) const override {
        class_panel.draw(window);
        WidgetManager::draw(window);
    }

    bool contains(unsigned x, unsigned y) const override {
        bool status = false;
        for (const auto& widget : class_widgets) status |= widget->contains(x, y);
        return status | class_panel.contains(x, y);
    }


    virtual void mousePressed(sf::Vector2i position) override {
        if (class_panel.contains(position.x, position.y)) {
            class_last_position = position;
            return;
        }      
        WidgetManager::mousePressed(position);
    }

    virtual void pressButton(const sf::Vector2i& position) override {
        if (class_panel.contains(position.x, position.y)) {
            class_delta = position - class_last_position;
            class_last_position = position;
            class_panel.move(class_delta.x, class_delta.y);
            WidgetManager::move(class_delta.x, class_delta.y);
            return;
        }  
        WidgetManager::pressButton(position);
    } 
};

