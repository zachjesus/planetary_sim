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
    //todo: add labels to sliders
    // add hooks for sliders
    // add create planet with canvas
    // add velolicty direction arrow for planets
    // done for now
    auto massSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto radSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto velSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto redSlider = tgui::Slider::create(0, 255);
    auto blueSlider = tgui::Slider::create(0, 255);
    auto greenSlider = tgui::Slider::create(0, 255);
    auto staticBox = tgui::CheckBox::create(tgui::String("Static:"));

    auto canvas = tgui::CanvasSFML::create({"600px", "600px"});
    canvas->setPosition("0px", "300px");
    canvas->clear(sf::Color(20, 20, 20));
    canvas->display();
    this->planetCanvas = canvas;

    auto rgbLayout = tgui::HorizontalLayout::create();
    rgbLayout->setSize("200px", "20px");
    rgbLayout->setPosition("100px", "190px");
    rgbLayout->add(redSlider);
    rgbLayout->add(blueSlider);
    rgbLayout->add(greenSlider);

    auto checkboxLayout = tgui::HorizontalLayout::create();
    checkboxLayout->setSize("20px", "20px"); 
    checkboxLayout->setPosition("50px", "185px");
    checkboxLayout->add(staticBox);
    
    auto panel = tgui::Panel::create({"600px", "1000px"});
    panel->setPosition(1200, 0);
    panel->getRenderer()->setBackgroundColor(tgui::Color(145, 145, 145));
    panel->getRenderer()->setBorderColor(tgui::Color(243,243,243));
    panel->getRenderer()->setBorders(6);
    
    auto layout = tgui::VerticalLayout::create();
    layout->setSize("475px", "125px");
    layout->setPosition("50px", "40px"); 
    layout->add(massSlider, "massSlider");
    layout->add(radSlider, "radSlider");
    layout->add(velSlider, "velSlider");
        
    panel->add(layout);
    panel->add(checkboxLayout);
    panel->add(rgbLayout);
    panel->add(planetCanvas);
    gui.add(panel);
}

void GuiHelper::draw() {
    gui.draw();
    this->newPlanet.shape.setPosition(300,300); 
    this->planetCanvas->draw(this->newPlanet.shape);
    this->planetCanvas->display();
}

void GuiHelper::guiHandleEvent(sf::Event& event) {
    gui.handleEvent(event);
}