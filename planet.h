#ifndef PLANET_H
#define PLANET_H

#include <utility>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

constexpr float RADIUS_SCALE = 10e-8f;
constexpr float DISTANCE_SCALE = 1e-9f;

struct Planet {
    float mass;            // kg
    float radius;          // m Purely for Scale Purposes no impact on Physics
    sf::Vector2f velocity; // (m/s, m/s)
    sf::Vector2f position; // (m, m)
    sf::CircleShape shape;
    sf::Color color;
    bool isStatic;

    Planet(const float mass, const float radius, const sf::Vector2f velocity, const sf::Vector2f position, const sf::Color color, const bool isStatic);
};


struct PlanetGroup {
    std::map<std::string, Planet> planets;

    bool addPlanet(const std::string& name, const Planet& p);
    const Planet& getPlanet(const std::string& name);
    bool removePlanet(const std::string& name);
    void updatePlanet(const std::string& name, const Planet& p);
};

#endif