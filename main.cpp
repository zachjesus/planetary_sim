#include <SFML/Graphics.hpp>
#include "planet.h"
#include "physics.h"
#include <iostream>

int main() {
    PlanetGroup group;
    Planet sun(1.989e30f, 6.9634e8f, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Color::Yellow, true);
    Planet mercury(3.3011e23f, 2.4397e6f, sf::Vector2f(0.0f, 47870.0f), sf::Vector2f(57.9e9f, 0.0f), sf::Color::White, false);
    Planet venus(4.8675e24f, 6.0518e6f, sf::Vector2f(0.0f, 35020.0f), sf::Vector2f(108.2e9f, 0.0f), sf::Color(255, 160, 122), false);
    Planet earth(5.9724e24f, 6.3710e6f, sf::Vector2f(0.0f, 29780.0f), sf::Vector2f(149.6e9f, 0.0f), sf::Color::Blue, false); 
    Planet mars(6.4171e23f, 3.3895e6f, sf::Vector2f(0.0f, 24070.0f), sf::Vector2f(227.9e9f, 0.0f), sf::Color::Red, false);
    Planet jupiter(1.8982e27f, 6.9911e7f, sf::Vector2f(0.0f, 13070.0f), sf::Vector2f(778.6e9f, 0.0f), sf::Color(218,165,32), false);
    Planet saturn(5.6834e26f, 5.8232e7f, sf::Vector2f(0.0f, 9680.0f), sf::Vector2f(1.4335e12f, 0.0f), sf::Color(210,180,140), false);
    Planet uranus(8.6810e25f, 2.5362e7f, sf::Vector2f(0.0f, 6800.0f), sf::Vector2f(2.8725e12f, 0.0f), sf::Color::Cyan, false);
    Planet neptune(1.0241e26f, 2.4622e7f, sf::Vector2f(0.0f, 5430.0f), sf::Vector2f(4.4951e12f, 0.0f), sf::Color::Blue, false);

    group.addPlanet("sun", sun);
    group.addPlanet("mercury", mercury);
    group.addPlanet("venus", venus);
    group.addPlanet("earth", earth);
    group.addPlanet("mars", mars);
    group.addPlanet("jupiter", jupiter);
    group.addPlanet("saturn", saturn);
    group.addPlanet("uranus", uranus);
    group.addPlanet("neptune", neptune);

    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Gravity Simulation", sf::Style::Close, sf::ContextSettings(0, 0, 8));

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y));
    window.setView(view);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setPosition(sf::Vector2i(0,0));
    std::cout << "Window size: " << (window.getSize().x, window.getSize().y) << std::endl;      
    // const double long timeStep = 10000.0f; 
    // sf::Clock clock;
    window.clear(sf::Color(20,20,20,255));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                view.zoom(0.9f);
            } else {
                view.zoom(1.1f);
            }
            window.setView(view);
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    view.move(0.0f, -10.0f);
                }
                if (event.key.code == sf::Keyboard::A) {
                    view.move(-10.0f, 0.0f);
                }
                if (event.key.code == sf::Keyboard::D) {
                    view.move(10.0f, 0.0f);
                }
                if (event.key.code == sf::Keyboard::S) {
                    view.move(0.0f, 10.0f);
                }
                window.setView(view);
            }
        }

        nextPosition(500000.0f, group);
        for(const auto& [name, planet] : group.planets) {
            window.draw(planet.shape);
            sf::CircleShape point(1.0f);
            point.setFillColor(planet.color);
            point.setPosition(planet.position.x * DISTANCE_SCALE, planet.position.y * DISTANCE_SCALE);
            window.draw(point);
        }

        window.display();
    }
}
