#include <SFML/Graphics.hpp>
#include <utility>
#include <string>
#include <map>
#include "../include/planet.h"

Planet::Planet(const double mass, const double radius, const sf::Vector2f velocity, const sf::Vector2f position, const sf::Color color, const bool isStatic)
: mass(mass), radius(radius), velocity(velocity), position(position), color(color), isStatic(isStatic){
    shape.setRadius(radius * RADIUS_SCALE);
    shape.setFillColor(color);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(position.x * DISTANCE_SCALE, position.y * DISTANCE_SCALE);
}

bool PlanetGroup::addPlanet(const std::string& name, const Planet& p) {
    auto result = planets.emplace(name, p);
    return result.second;
}

const Planet& PlanetGroup::getPlanet(const std::string& name) {
    return planets.at(name);
}

bool PlanetGroup::removePlanet(const std::string& name) {
    return planets.erase(name) > 0;
}

void PlanetGroup::updatePlanet(const std::string& name, const Planet& p) {
    planets.at(name) = p;
}