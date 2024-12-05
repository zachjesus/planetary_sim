#include <SFML/Graphics.hpp>
#include "../include/physics.h"
#include "../include/planet.h"
#include <cmath>
#include <utility>

void nextPosition(double dt, PlanetGroup& group) {
    std::map<std::string, std::pair<double, double>> netForces;   

    for (const auto& [name, planet] : group.planets) {
        netForces[name] = {0.0f, 0.0f};
    }

    for(auto& [n1, p1]: group.planets) {
        if (p1.isStatic) continue;
        for(auto& [n2, p2]: group.planets) {
            if (n1 == n2) continue;

            double m1 = p1.mass;
            double m2 = p2.mass;
            double dx = p2.position.x - p1.position.x;
            double dy = p2.position.y - p1.position.y;
            double rSquared =  dx * dx + dy * dy;

            if (rSquared == 0.0f) continue;

            double force = static_cast<double>((G * m1 * m2) / rSquared);

            double r = sqrt(rSquared);
            double unitDx = dx / r;
            double unitDy = dy / r;

            double fx = force * unitDx;
            double fy = force * unitDy;

            netForces[n1].first += fx;
            netForces[n1].second += fy;
        }
    }

    for (auto& [name, planet] : group.planets) {
        double fx = netForces[name].first;
        double fy = netForces[name].second;
        
        double ax = fx / planet.mass;
        double ay = fy / planet.mass;
        
        planet.velocity.x += ax * dt;
        planet.velocity.y += ay * dt;
        
        planet.position.x += planet.velocity.x * dt;
        planet.position.y += planet.velocity.y * dt;

        planet.shape.setPosition(planet.position.x * DISTANCE_SCALE, planet.position.y * DISTANCE_SCALE);
    }
}