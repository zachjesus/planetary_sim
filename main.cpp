#include <SFML/Graphics.hpp>
#include "planet.h"
#include "physics.h"
#include <iostream>

int main() {
    PlanetGroup group;

    Planet moon(0.07346e24f, 1737.4e3f, sf::Vector2f(0.0f, 1082.0f), sf::Vector2f(0.3633e9f, 0.0f), sf::Color(0, 45, 4, 255), false);
    Planet earth(5.9724e24f, 6371.0e3f, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Color(128, 128, 128, 255),  true); 
    Planet asteriod(939e12f, 476000.0f, sf::Vector2f(800.0f, 0.0f), sf::Vector2f(-0.3633e9f, 0.3633e9f), sf::Color(128, 128, 128, 255), false);

    group.addPlanet("moon", moon);
    group.addPlanet("earth", earth);
    group.addPlanet("asteriod", asteriod);

    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Gravity Simulation", sf::Style::Close, sf::ContextSettings(0, 0, 8));

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y));
    window.setView(view);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setPosition(sf::Vector2i(0,0));

    // const float timeStep = 10000.0f; 
    // sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(20,20,20,255));

        nextPosition(1000.0f, group);
        for(const auto& [name, planet] : group.planets) {
            window.draw(planet.shape);
        }

        window.display();
    }
}
