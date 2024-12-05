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
    tgui::Gui gui;
    PlanetGroup& group;

public:
    GuiHelper(sf::RenderWindow& mainWindow, PlanetGroup& group);

    void createPanel();
    void draw();
    void guiHandleEvent(sf::Event& event);
};

#endif
