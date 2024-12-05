#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
#include "../include/planet.h"
#include "../include/physics.h"
#include "../include/guiHelper.h"

int main() {
    PlanetGroup group;
    
    sf::RenderWindow mainWindow(sf::VideoMode(1800, 1000), "Gravity Simulation", sf::Style::Close, sf::ContextSettings(0, 0, 8));
    sf::View mainView(sf::FloatRect(0, 0, 1200, 1000));

    mainWindow.setView(mainView);
    mainWindow.setFramerateLimit(60);
    mainWindow.setVerticalSyncEnabled(true);
    mainWindow.setPosition(sf::Vector2i(0,0));

    GuiHelper gui = GuiHelper(mainWindow, group);
    gui.createPanel();
    
    // Event Loop
    while(mainWindow.isOpen()) {        
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }
            gui.guiHandleEvent(event);
        }

        for(const auto& [name, planet] : group.planets) {
            mainWindow.draw(planet.shape);
        }

        mainWindow.display();
        mainWindow.clear(sf::Color(20,20,20,255));
        gui.draw();
    }
}
