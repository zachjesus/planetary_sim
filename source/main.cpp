#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
#include "../include/planet.h"
#include "../include/physics.h"

int main() {
    PlanetGroup group;
    
    // Main Window
    sf::RenderWindow mainWindow(sf::VideoMode(1200, 1000), "Gravity Simulation", sf::Style::Close, sf::ContextSettings(0, 0, 8));
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(mainWindow.getSize().x, mainWindow.getSize().y));

    mainWindow.setView(view);
    mainWindow.setFramerateLimit(60);
    mainWindow.setVerticalSyncEnabled(true);
    mainWindow.setPosition(sf::Vector2i(0,0));

    // GUI
    sf::RenderWindow guiWindow(sf::VideoMode(600, 1000), "", sf::Style::Close, sf::ContextSettings(0, 0, 8));
    tgui::Gui gui(guiWindow);
    guiWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x+1244, (mainWindow.getPosition().y+44)));

    // Event Loop
    while(mainWindow.isOpen()) {        
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }
        }

        mainWindow.clear(sf::Color(20,20,20,255));
        guiWindow.clear(sf::Color(20,20,20,255));

        for(const auto& [name, planet] : group.planets) {
            mainWindow.draw(planet.shape);
        }

        mainWindow.display();

        guiWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x+1244, (mainWindow.getPosition().y+44)));
        gui.draw();
        guiWindow.display();
    }
}
