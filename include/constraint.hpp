#pragma once

#include "particle.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class Constraint {
public:
    Constraint(physics::Particle* p1, physics::Particle* p2);

    void satisfy();
    void deactivate();

    [[nodiscard]] bool is_active() const;
    [[nodiscard]] const physics::Particle* get_p1() const;
    [[nodiscard]] const physics::Particle* get_p2() const;

private:
    physics::Particle* p1_;
    physics::Particle* p2_;
    float initial_length_;
    bool active_;
};
