#include <SFML/Graphics.hpp>
#include <utility>
#include <string>
#include <map>
#include "../include/planet.h"

Planet::Planet(const double mass, const double radius, const sf::Vector2f velocity, const sf::Vector2f position, const sf::Color color, const bool isStatic)
: mass(mass), radius(radius), velocity(velocity), position(position), color(color), isStatic(isStatic){
    shape.setRadius(static_cast<float>(radius * RADIUS_SCALE));
    shape.setFillColor(color);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(static_cast<float>(position.x * DISTANCE_SCALE), static_cast<float>(position.y * DISTANCE_SCALE));
}

void PlanetGroup::addPlanet(const Planet p) {
    planets.push_front(p);
    currID++;
}

void PlanetGroup::clearPlanets() {
    planets.clear();
}
