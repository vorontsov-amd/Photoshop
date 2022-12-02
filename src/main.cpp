#include <iostream>
#include "vector.hpp"
#include "color.hpp"
#include "widgetManager.hpp"
#include "canvasWindow.hpp"
#include "button.hpp"
#include "pallete.hpp"
#include "settingsPanel.hpp"
#include "objectList.hpp"
#include "main.hpp"
#include "console.hpp"
#include "raytracer.hpp"



int main()
{   
    sf::RenderWindow window(sf::VideoMode(X, Y), "nZemax");


    WidgetManager manager;
    manager.addWidget(make_shared<SettingsPanel>(1600));
    auto tool_pallete = make_shared<ToolPallete>(Vector{20, 80}, 1600);
    manager.addWidget(tool_pallete);
    auto canvas = make_shared<DrawingWindow>(Vector{100, 100}, 960, 640, tool_pallete);
    manager.addWidget(canvas);
    auto object_list = make_shared<ObjectList>(Vector{1200, 100}, 350, 640, &manager);
    manager.addWidget(object_list);
    manager.addWidget(make_shared<RayTracer>(canvas));

    while (window.isOpen())
    {
        window.clear(sf::Color(46, 43, 52));

        sf::Event event;
        auto position = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {            
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                manager.mousePressed(position);
                break;
            case sf::Event::MouseButtonReleased:
                manager.mouseReleased(position);
                break;
            case sf::Event::KeyPressed:
                manager.scanOffKeyboard(event.key.code);
            default:
                break;
            }
        }

        manager.pressButton(position);

        manager.draw(window);
        window.display();

    }
}