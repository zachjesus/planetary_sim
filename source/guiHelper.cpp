#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
#include "../include/planet.h"
#include "../include/physics.h"
#include "../include/guiHelper.h"

GuiHelper::GuiHelper(sf::RenderWindow& mainWindow, PlanetGroup& group)
    : mainWindow(mainWindow), group(group) {
    gui.setWindow(mainWindow);
}

void GuiHelper::createPanel() {
    auto massSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto radSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto velSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto redSlider = tgui::Slider::create(0, 255);
    auto blueSlider = tgui::Slider::create(0, 255);
    auto greenSlider = tgui::Slider::create(0, 255);
    auto staticBox = tgui::CheckBox::create(tgui::String("Static:"));
    
    auto rgbLayout = tgui::HorizontalLayout::create();
    rgbLayout->setSize("200px", "20px");
    rgbLayout->setPosition("100px", "200px");
    rgbLayout->add(redSlider);
    rgbLayout->add(blueSlider);
    rgbLayout->add(greenSlider);

    auto checkboxLayout = tgui::HorizontalLayout::create();
    checkboxLayout->setSize("20px", "20px"); 
    checkboxLayout->setPosition("50px", "195px");
    checkboxLayout->add(staticBox);
    
    tgui::Panel::Ptr panel = tgui::Panel::create({"600px", "1000px"});
    panel->setPosition(1200, 0);
    panel->getRenderer()->setBackgroundColor(tgui::Color(20, 20, 20));
    panel->getRenderer()->setBorderColor(tgui::Color(0, 144, 17));
    panel->getRenderer()->setBorders(6);
    
    tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
    layout->setSize("475px", "165px");
    layout->setPosition("50px", "20px"); 
    
    layout->add(massSlider, "massSlider");
    layout->add(radSlider, "radSlider");
    layout->add(velSlider, "velSlider");
        
    panel->add(layout);
    panel->add(checkboxLayout);
    panel->add(rgbLayout);
    gui.add(panel);
}

void GuiHelper::draw() {
    gui.draw();
}

void GuiHelper::guiHandleEvent(sf::Event& event) {
    gui.handleEvent(event);
}