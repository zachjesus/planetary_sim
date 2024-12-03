#ifndef PLANET_H
#define PLANET_H

#include <utility>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

constexpr double long RADIUS_SCALE = 10e-9f;
constexpr double long DISTANCE_SCALE = 1.3e-10f;

struct Planet {
double long mass;             // kg
double long radius;          // m Purely for Scale Purposes no impact on Physics
    sf::Vector2f velocity;  // (m/s, m/s)
    sf::Vector2f position; // (m, m)
    sf::CircleShape shape;
    sf::Color color;
    bool isStatic;

    Planet(const double long mass, const double long radius, const sf::Vector2f velocity, const sf::Vector2f position, const sf::Color color, const bool isStatic);
};


struct PlanetGroup {
    std::map<std::string, Planet> planets;

    bool addPlanet(const std::string& name, const Planet& p);
    const Planet& getPlanet(const std::string& name);
    bool removePlanet(const std::string& name);
    void updatePlanet(const std::string& name, const Planet& p);
};

#endif