#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "particle.hpp"
#include <cmath>

class Constraint {
public:
    Constraint(Particle* p1, Particle* p2)
        : p1_{p1}, p2_{p2}, active_{true} {
        sf::Vector2f delta = p2_->get_position() - p1_->get_position();
        initial_length_ = std::hypot(delta.x, delta.y);
    }

    void satisfy() {
        if (!active_) return;

        sf::Vector2f delta = p2_->get_position() - p1_->get_position();
        float current_length = std::hypot(delta.x, delta.y);
        float difference = (current_length - initial_length_) / current_length;
        sf::Vector2f correction = delta * 0.5f * difference;

        p1_->apply_correction(correction);
        p2_->apply_correction(-correction);
    }

    void deactivate() { active_ = false; }
    [[nodiscard]] bool is_active() const { return active_; }
    [[nodiscard]] const Particle* get_p1() const { return p1_; }
    [[nodiscard]] const Particle* get_p2() const { return p2_; }

private:
    Particle* p1_;
    Particle* p2_;
    float initial_length_;
    bool active_;
};

#endif // CONSTRAINT_H
