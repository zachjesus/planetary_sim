#ifndef PHYSICS_H
#define PHYSICS_H

#include <cmath>
#include <utility>
#include "planet.h"

inline constexpr double G = 6.67430e-11; // m^3 kg^-1 s^-2

void nextPosition(float dt, PlanetGroup& group);

#endif