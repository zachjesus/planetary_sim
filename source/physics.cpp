#include <SFML/Graphics.hpp>
#include "../include/physics.h"
#include "../include/planet.h"
#include <cmath>
#include <utility>
#include <iostream>

void nextPosition(double dt, PlanetGroup& group) {
    std::map<int, std::pair<double, double>> netForces;   

    for (auto& planet : group.planets) {
        netForces[planet.id] = {0.0f, 0.0f};
    }

    for(auto& p1 : group.planets) {
        if (p1.isStatic) continue;
        for(auto& p2 : group.planets) {
            if (p1.id == p2.id) continue;

            double m1 = p1.mass;
            double m2 = p2.mass;
            double dx = p2.position.x - p1.position.x;
            double dy = p2.position.y - p1.position.y;
            double rSquared =  dx * dx + dy * dy;

            if (rSquared == 0.0f) continue;

            double force = static_cast<double>((G * m1 * m2) / rSquared);

            double r = std::sqrt(rSquared);
            double unitDx = dx / r;
            double unitDy = dy / r;

            double fx = force * unitDx;
            double fy = force * unitDy;

            netForces[p1.id].first += fx;
            netForces[p1.id].second += fy;
        }
    }

    for (auto& planet : group.planets) {
        double fx = netForces[planet.id].first;
        double fy = netForces[planet.id].second;
        
        double ax = fx / planet.mass;
        double ay = fy / planet.mass;
        
        planet.velocity.x += ax * dt;
        planet.velocity.y += ay * dt;
        
        planet.position.x += planet.velocity.x * dt;
        planet.position.y += planet.velocity.y * dt;

        planet.shape.setPosition(static_cast<float>(planet.position.x * DISTANCE_SCALE), static_cast<float>(planet.position.y * DISTANCE_SCALE));
    }
}