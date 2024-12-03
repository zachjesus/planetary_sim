#include "planet.h"
#include <cmath>
#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>

const double G = 6.67430e-11; // m^3 kg^-1 s^-2

void nextPosition(double long dt, PlanetGroup& group) {
    std::map<std::string, std::pair<double long, double long>> netForces;   

    for (const auto& [name, planet] : group.planets) {
        netForces[name] = {0.0f, 0.0f};
    }

    for(auto& [n1, p1]: group.planets) {
        for(auto& [n2, p2]: group.planets) {
            if (n1 == n2) continue;

            double long m1 = p1.mass;
            double long m2 = p2.mass;
            double long dx = p2.position.x - p1.position.x;
            double long dy = p2.position.y - p1.position.y;
            double long rSquared =  dx * dx + dy * dy;

            if (rSquared == 0.0f) continue;

            double long force = static_cast<double long>((G * m1 * m2) / rSquared);

            double long r = sqrt(rSquared);
            double long unitDx = dx / r;
            double long unitDy = dy / r;

            double long fx = force * unitDx;
            double long fy = force * unitDy;

            netForces[n1].first += fx;
            netForces[n1].second += fy;
        }
    }

    for (auto& [name, planet] : group.planets) {
        if (planet.isStatic) continue;
        double long fx = netForces[name].first;
        double long fy = netForces[name].second;
        
        double long ax = fx / planet.mass;
        double long ay = fy / planet.mass;
        
        planet.velocity.x += ax * dt;
        planet.velocity.y += ay * dt;
        
        static_cast<float>(planet.position.x += planet.velocity.x * dt);
        static_cast<float>(planet.position.y += planet.velocity.y * dt);

        if(name == "mercury") {
            std::cout << "Mercury: " << planet.position.x << ", " << planet.position.y << std::endl;
        }
        planet.shape.setPosition(static_cast<float>(planet.position.x * DISTANCE_SCALE), static_cast<float>(planet.position.y * DISTANCE_SCALE));
    }
}