#include "widgetManager.hpp"
#include "button.hpp"

class SettingsPanel : public WidgetManager
{
private:
    unsigned class_height = 25;
    sf::Color class_panel_color = sf::Color{240, 240, 240};
public:
    SettingsPanel(unsigned width) {
        WidgetManager::addWidget(make_shared<TextButton>(
            Vector{0, 0},
            100,
            class_height,
            "File",
            class_panel_color
        ));
        WidgetManager::addWidget(make_shared<ColorButton>(
            Vector{0, 0} + Vector{100 , 0},
            width - 100,
            class_height,
            class_panel_color
        ));
    }
};

