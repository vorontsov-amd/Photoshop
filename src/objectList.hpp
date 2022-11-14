#pragma once
#include "widgetManager.hpp"
#include "button.hpp"
#include "main.hpp"

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

    ObjInfo class_info;

public:
    WindowBody(const ObjInfo& info) : WindowBody(info.position, info.width, info.height) {}
    WindowBody(const Vector& position, unsigned width, unsigned height) :
        class_info{position, width, height} {

        double koef_button_size = 0.7;
        
        WidgetManager::addWidget(make_shared<MovePanel>(
            position, 
            width,
            class_panel_size,
            class_panel_color,
            this
        ));

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
            sf::Color{86, 83, 92}
        ));

        class_info.num_widgets = WidgetManager::arrayOfWidgets().size();
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


class ObjectCreater : public WindowBody
{
public:
    ObjectCreater(const Vector& position, unsigned width, unsigned height) : WindowBody{position, width, height} {
        WindowBody::addWidget(make_shared<TextButton>(
            position + Vector{20, 30},
            50,
            25,
            "Material: ",
            sf::Color{0, 0, 0, 0}
        ));

        WindowBody::addWidget(make_shared<DropdownButton>(
            position + Vector{120, 30},
            250,
            25,
            sf::Color{50, 50, 50}
        ));
    }


    bool mousePressed(sf::Vector2i position) override {
        class_mouse_is_pressed = true;
        auto is_pressed = false;
        for (auto widget_it = class_widgets.rbegin(); widget_it != class_widgets.rend(); ++widget_it) {
            if (*widget_it != nullptr) {
                is_pressed = (*widget_it)->mousePressed(position);
                if (is_pressed) {
                    break;
                }
            }
        }
        return is_pressed;
    }
};

void CreateObjButton::mouseReleased(sf::Vector2i position)
{
    if (contains(position.x, position.y) && class_is_pressed) {
        class_widget_manager_ptr->addWidget(make_shared<ObjectCreater>(
            Vector{X / 2 - 200, Y / 2 - 200}, 400, 400
        ));
    }
    
    class_is_pressed = false;
}


class ObjectList : public WindowBody
{
private:
    sf::Color class_panel_color = sf::Color{190, 190, 190};

    unsigned class_panel_size = 25;

    sf::Vector2i class_last_position;
    sf::Vector2i class_delta;
public:
    ObjectList(const Vector& position, unsigned width, unsigned height, WidgetManager* global_manager) : WindowBody{position, width, height} {
        WindowBody::addWidget(make_shared<CreateObjButton>(
            position + Vector{0, height - 25 + 15}, 
            width,
            25,
            "New Object",
            sf::Color{71, 68, 67},
            global_manager   
        ));
    }

    bool mousePressed(sf::Vector2i position) override {
        class_mouse_is_pressed = true;
        auto is_pressed = false;
        for (auto widget_it = class_widgets.rbegin(); widget_it != class_widgets.rend(); ++widget_it) {
            if (*widget_it != nullptr) {
                is_pressed = (*widget_it)->mousePressed(position);
                if (is_pressed) {
                    break;
                }
            }
        }
        return is_pressed;
    }

};

ObjectCutaway::ObjectCutaway(ObjectList* obj_list) : WindowBody{createBodyInfo(obj_list->info())}, class_obj_list{obj_list} {
        //addWidget()
    }