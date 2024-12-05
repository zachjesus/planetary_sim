#include <SFML/Graphics.hpp>
#include "../include/physics.h"
#include "../include/planet.h"
#include <cmath>
#include <utility>

void nextPosition(float dt, PlanetGroup& group) {
    std::map<std::string, std::pair<float, float>> netForces;   

    for (const auto& [name, planet] : group.planets) {
        netForces[name] = {0.0f, 0.0f};
    }

    for(auto& [n1, p1]: group.planets) {
        if (p1.isStatic) continue;
        for(auto& [n2, p2]: group.planets) {
            if (n1 == n2) continue;

            float m1 = p1.mass;
            float m2 = p2.mass;
            float dx = p2.position.x - p1.position.x;
            float dy = p2.position.y - p1.position.y;
            float rSquared =  dx * dx + dy * dy;

            if (rSquared == 0.0f) continue;

            float force = static_cast<float>((G * m1 * m2) / rSquared);

            float r = sqrt(rSquared);
            float unitDx = dx / r;
            float unitDy = dy / r;

            float fx = force * unitDx;
            float fy = force * unitDy;

            netForces[n1].first += fx;
            netForces[n1].second += fy;
        }
    }

    for (auto& [name, planet] : group.planets) {
        float fx = netForces[name].first;
        float fy = netForces[name].second;
        
        float ax = fx / planet.mass;
        float ay = fy / planet.mass;
        
        planet.velocity.x += ax * dt;
        planet.velocity.y += ay * dt;
        
        planet.position.x += planet.velocity.x * dt;
        planet.position.y += planet.velocity.y * dt;

        planet.shape.setPosition(planet.position.x * DISTANCE_SCALE, planet.position.y * DISTANCE_SCALE);
    }
}