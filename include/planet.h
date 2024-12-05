#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <string>
#include <map>

constexpr double RADIUS_SCALE = 10e-8f;
constexpr double DISTANCE_SCALE = 10e-10f;

struct Planet {
    double mass;            // kg
    double radius;          // m
    sf::Vector2f velocity; // (m/s, m/s)
    sf::Vector2f position; // (m, m)
    sf::CircleShape shape;
    sf::Color color;
    bool isStatic;

    Planet(const double mass, const double radius, const sf::Vector2f velocity, const sf::Vector2f position, const sf::Color color, const bool isStatic);
};


struct PlanetGroup {
    std::map<std::string, Planet> planets;

    bool addPlanet(const std::string& name, const Planet& p);
    const Planet& getPlanet(const std::string& name);
    bool removePlanet(const std::string& name);
    void updatePlanet(const std::string& name, const Planet& p);
};

#endif