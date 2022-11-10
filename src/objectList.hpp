#pragma once
#include "widgetManager.hpp"
#include "button.hpp"


struct ObjInfo
{
    Vector position;
    unsigned width;
    unsigned height;
    int num_widgets = 0;
};


class WindowBody : public WidgetManager
{
private:
    unsigned class_panel_size = 15;
    sf::Color class_panel_color = sf::Color{190, 190, 190};

    sf::Vector2i class_last_position;
    sf::Vector2i class_delta;

    Panel class_panel;

    ObjInfo class_info;

public:
    WindowBody(const ObjInfo& info) : WindowBody(info.position, info.width, info.height) {}
    WindowBody(const Vector& position, unsigned width, unsigned height) :
        class_info{position, width, height},
        class_panel{position, width, class_panel_size, class_panel_color} {
        double koef_button_size = 0.7;
        WidgetManager::addWidget(make_shared<TextureButton>(
            position + Vector{width - class_panel_size * 0.5 * (1 + koef_button_size), class_panel_size * 0.5 * (1 - koef_button_size)},
            class_panel_size * koef_button_size,
            class_panel_size * koef_button_size,
            "../Textures/cross.png"
        ));
        WidgetManager::addWidget(make_shared<Panel>(
            position + Vector{0, class_panel_size}, 
            width,
            height,
            sf::Color{100, 100, 100}
        ));

        class_info.num_widgets = WidgetManager::arrayOfWidgets().size();
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

    ObjInfo info() { return class_info; }
};


class ObjectList;



class ObjectCutaway : public WindowBody 
{
private:
    ObjectList* class_obj_list;

    static ObjInfo createBodyInfo(const ObjInfo& list_info) {
        ObjInfo ret = {
            list_info.position + Vector{20, 20},
            list_info.width - 40,
            list_info.height - 40,
        };
        return ret;
    }
public:
    ObjectCutaway(ObjectList* obj_list);
        //WindowBody::addWidget()
};




class ObjectList : public WindowBody
{
private:
    sf::Color class_panel_color = sf::Color{190, 190, 190};

    unsigned class_panel_size = 25;

    sf::Vector2i class_last_position;
    sf::Vector2i class_delta;
public:
    ObjectList(const Vector& position, unsigned width, unsigned height) : WindowBody{position, width, height} {
        auto text = make_shared<TextButton>(
            position + Vector{0, class_panel_size + height - 25}, 
            width,
            25,
            "New Object",
            sf::Color{80, 80, 80}
        );

        text->setTextColor(sf::Color::White);
        text->moveText(120, 0);

        WindowBody::addWidget(text);
        WindowBody::addWidget(make_shared<ObjectCutaway>(this));
    }

    void draw(sf::RenderWindow& window) const override {
        WindowBody::draw(window);
    }

};

ObjectCutaway::ObjectCutaway(ObjectList* obj_list) : WindowBody{createBodyInfo(obj_list->info())}, class_obj_list{obj_list} {
        //WindowBody::addWidget()
    }