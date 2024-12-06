#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <string>
#include <map>
#include <forward_list>

constexpr double RADIUS_SCALE = 10e-8f;
constexpr double DISTANCE_SCALE = 10e-10f;

struct Planet {
    double mass;              // kg
    double radius;           // m
    sf::Vector2f velocity;  // (m/s, m/s)
    sf::Vector2f position; // (m, m)
    sf::CircleShape shape;
    sf::Color color;
    bool isStatic;
    int id;

    Planet(const double mass, const double radius, const sf::Vector2f velocity, const sf::Vector2f position, const sf::Color color, const bool isStatic);
};


struct PlanetGroup {
    std::forward_list<Planet> planets;
    int currID = 0;

    void addPlanet(const Planet p);
    void clearPlanets();
};

#endif