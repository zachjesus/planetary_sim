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

void GuiHelper::addPlanet(sf::Vector2f pos) {
    Planet copyPlanet = this->newPlanet;
    copyPlanet.position = sf::Vector2f(pos.x/DISTANCE_SCALE, pos.y/DISTANCE_SCALE);
    std::cout << "Adding planet at: " << pos.x/DISTANCE_SCALE << ", " << pos.y/DISTANCE_SCALE << std::endl;

    copyPlanet.id = this->group.currID;
    std::cout << "Planet Static: " << copyPlanet.isStatic << std::endl;

    this->group.addPlanet(copyPlanet); 
}

void GuiHelper::createPanel() {
    //Panel
    auto panel = tgui::Panel::create({"600px", "1000px"});
    panel->setPosition(1200, 0);
    panel->getRenderer()->setBackgroundColor(tgui::Color(165, 165, 165));
    panel->getRenderer()->setBorderColor(tgui::Color(133, 133, 133));
    panel->getRenderer()->setBorders(6);

    //Widgets
    auto massSlider = tgui::Slider::create(-30.0f, 30.0f);
    massSlider->setStep(.1f);
    massSlider->setValue(1.989e30f);
    auto radSlider = tgui::Slider::create(0, 4e9);
    radSlider->setValue(6.9634e8f);
    auto velSlider = tgui::Slider::create(0, 50000);
    auto redSlider = tgui::Slider::create(0, 255);
    redSlider->setValue(255);
    auto blueSlider = tgui::Slider::create(0, 255);
    blueSlider->setValue(255);
    auto greenSlider = tgui::Slider::create(0, 255);
    auto staticBox = tgui::CheckBox::create();
    staticBox->setScale({0.3f, .8f});
    staticBox->setChecked(true);
    auto clearButton = tgui::Button::create("Clear");

    //Hooks
    massSlider->onValueChange([this](float value) {
        this->newPlanet.mass = pow(10, value) * 1.98892e30;
        std::cout << this->newPlanet.mass << std::endl;
    });

    radSlider->onValueChange([this](float value) {
        this->newPlanet.radius = value;
        this->newPlanet.shape.setOrigin(static_cast<float>(value * RADIUS_SCALE), static_cast<float>(value * RADIUS_SCALE));
        this->newPlanet.shape.setRadius(static_cast<float>(value * RADIUS_SCALE));
        std::cout << this->newPlanet.radius << std::endl;
    });

    velSlider->onValueChange([this](float value) {
        this->newPlanet.velocity = sf::Vector2f(value, value);
        std::cout << this->newPlanet.velocity.x << std::endl;
    });

    redSlider->onValueChange([this](float value) {
        this->newPlanet.color.r = value;
        this->newPlanet.shape.setFillColor(this->newPlanet.color);
    });

    blueSlider->onValueChange([this](float value) {
        this->newPlanet.color.b = value;
        this->newPlanet.shape.setFillColor(this->newPlanet.color);
    });

    greenSlider->onValueChange([this](float value) {
        this->newPlanet.color.g = value;
        this->newPlanet.shape.setFillColor(this->newPlanet.color);
    });

    staticBox->onClick([this]() {
        this->newPlanet.isStatic = !this->newPlanet.isStatic;
        std::cout << this->newPlanet.isStatic << std::endl;
    });

    clearButton->onPress([this]() {
        this->group.clearPlanets();
    });
 
    //Labels
    auto massLabel = tgui::Label::create("Mass");
    massLabel->setTextSize(16);
    massLabel->getRenderer()->setTextColor(tgui::Color(0,128,128));

    auto radLabel = tgui::Label::create("Radius");
    radLabel->setTextSize(16);
    radLabel->getRenderer()->setTextColor(tgui::Color(0,128,128));

    auto velLabel = tgui::Label::create("Velocity");
    velLabel->setTextSize(16);
    velLabel->getRenderer()->setTextColor(tgui::Color(0,128,128));

    auto redLabel = tgui::Label::create("R");
    redLabel->setTextSize(16);
    redLabel->getRenderer()->setTextColor(tgui::Color::Red);

    auto blueLabel = tgui::Label::create("G");
    blueLabel->setTextSize(16);
    blueLabel->getRenderer()->setTextColor(tgui::Color::Blue);

    auto greenLabel = tgui::Label::create("B");
    greenLabel->setTextSize(16);
    greenLabel->getRenderer()->setTextColor(tgui::Color::Green);

    auto staticLabel = tgui::Label::create("Static");
    staticLabel->setTextSize(16);
    staticLabel->getRenderer()->setTextColor(tgui::Color(0,128,128));

    //Mass Velocity Radius 
    auto layout = tgui::VerticalLayout::create();
    layout->setSize("500px", "170px");
    layout->setPosition("50px", "40px"); 
    layout->add(massLabel, "massLabel");
    layout->add(massSlider, "massSlider");
    layout->add(radLabel, "radLabel");
    layout->add(radSlider, "radSlider");
    layout->add(velLabel, "velLabel");
    layout->add(velSlider, "velSlider");
    
    //Checkbox
    auto checkboxLayout = tgui::VerticalLayout::create();
    checkboxLayout->setSize("70px", "45px"); 
    checkboxLayout->setPosition("50px", "215px");
    checkboxLayout->add(staticLabel);
    checkboxLayout->add(staticBox);

    //RGB
    auto rgbLayout = tgui::HorizontalLayout::create();
    rgbLayout->setSize("130px", "60px");
    rgbLayout->setPosition("150px", "220px");
    rgbLayout->add(redLabel);
    rgbLayout->add(redSlider);
    rgbLayout->add(blueLabel);
    rgbLayout->add(blueSlider);
    rgbLayout->add(greenLabel);
    rgbLayout->add(greenSlider);

    //Clear
    auto clearLayout = tgui::HorizontalLayout::create();
    clearLayout->setSize("40px", "25px");
    clearLayout->setPosition("305px", "225px");
    clearLayout->add(clearButton);
    
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
    panel->add(clearLayout);
    this->gui.add(panel);
}

void GuiHelper::draw() {
    this->gui.draw();
    this->newPlanet.shape.setPosition(300,300); 
    this->planetCanvas->clear(sf::Color(20, 20, 20));
    this->planetCanvas->draw(this->newPlanet.shape);
    this->planetCanvas->display();
}

void GuiHelper::guiHandleEvent(sf::Event& event) {
    this->gui.handleEvent(event);
}