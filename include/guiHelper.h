#ifndef GUIHELPER_H
#define GUIHELPER_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
#include "planet.h"
#include "physics.h"

struct GuiHelper {
private:
    sf::RenderWindow& mainWindow;
    PlanetGroup& group;
    tgui::Gui gui;
    tgui::CanvasSFML::Ptr planetCanvas; 
    Planet newPlanet = Planet(1.989e30, 6.9634e8, sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Yellow, true); //default the sun.

public:
    GuiHelper(sf::RenderWindow& mainWindow, PlanetGroup& group);
    void createPanel();
    void draw();
    void guiHandleEvent(sf::Event& event);
    void addPlanet(sf::Vector2f pos);
    void velocityDirection();
};

#endif
