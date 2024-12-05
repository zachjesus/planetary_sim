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
    //Panel
    auto panel = tgui::Panel::create({"600px", "1000px"});
    panel->setPosition(1200, 0);
    panel->getRenderer()->setBackgroundColor(tgui::Color(145, 145, 145));
    panel->getRenderer()->setBorderColor(tgui::Color(243,243,243));
    panel->getRenderer()->setBorders(6);

    //Widgets
    auto massSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto radSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto velSlider = tgui::Slider::create(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    auto redSlider = tgui::Slider::create(0, 255);
    auto blueSlider = tgui::Slider::create(0, 255);
    auto greenSlider = tgui::Slider::create(0, 255);
    auto staticBox = tgui::CheckBox::create();
    staticBox->setScale({0.4f, 0.95f});
 
    //Labels
    auto massLabel = tgui::Label::create("Mass");
    massLabel->setTextSize(16);
    massLabel->getRenderer()->setTextColor(tgui::Color(0,230,52));

    auto radLabel = tgui::Label::create("Radius");
    radLabel->setTextSize(16);
    radLabel->getRenderer()->setTextColor(tgui::Color(0,230,52));

    auto velLabel = tgui::Label::create("Velocity");
    velLabel->setTextSize(16);
    velLabel->getRenderer()->setTextColor(tgui::Color(0,230,52));

    auto redLabel = tgui::Label::create("R");
    redLabel->setTextSize(16);
    redLabel->getRenderer()->setTextColor(tgui::Color(0,230,52));

    auto blueLabel = tgui::Label::create("G");
    blueLabel->setTextSize(16);
    blueLabel->getRenderer()->setTextColor(tgui::Color(0,230,52));

    auto greenLabel = tgui::Label::create("B");
    greenLabel->setTextSize(16);
    greenLabel->getRenderer()->setTextColor(tgui::Color(0,230,52));

    auto staticLabel = tgui::Label::create("Static");
    staticLabel->setTextSize(16);
    staticLabel->getRenderer()->setTextColor(tgui::Color(0,230,52));

    //Mass Velocity Radius 
    auto layout = tgui::VerticalLayout::create();
    layout->setSize("475px", "170px");
    layout->setPosition("50px", "40px"); 
    layout->add(massLabel, "massLabel");
    layout->add(massSlider, "massSlider");
    layout->add(radLabel, "radLabel");
    layout->add(radSlider, "radSlider");
    layout->add(velLabel, "velLabel");
    layout->add(velSlider, "velSlider");
    
    //Checkbox
    auto checkboxLayout = tgui::HorizontalLayout::create();
    checkboxLayout->setSize("104px", "21px"); 
    checkboxLayout->setPosition("50px", "215px");
    checkboxLayout->add(staticLabel);
    checkboxLayout->add(staticBox);

    //RGB
    auto rgbLayout = tgui::HorizontalLayout::create();
    rgbLayout->setSize("125px", "50px");
    rgbLayout->setPosition("150px", "220px");
    rgbLayout->add(redLabel);
    rgbLayout->add(redSlider);
    rgbLayout->add(blueLabel);
    rgbLayout->add(blueSlider);
    rgbLayout->add(greenLabel);
    rgbLayout->add(greenSlider);
    
    //Canvas
    auto canvas = tgui::CanvasSFML::create({"600px", "600px"});
    canvas->setPosition("0px", "300px");
    canvas->clear(sf::Color(20, 20, 20));
    canvas->display();
    this->planetCanvas = canvas;
        
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