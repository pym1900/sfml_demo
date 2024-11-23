#include "constraint.hpp"

Constraint::Constraint(physics::Particle* p1, physics::Particle* p2)
    : p1_{p1}, p2_{p2}, active_{true} {
    sf::Vector2f delta = p2_->get_position() - p1_->get_position();
    initial_length_ = std::hypot(delta.x, delta.y);
}

void Constraint::satisfy() {
    if (!active_) return;

    sf::Vector2f delta = p2_->get_position() - p1_->get_position();
    float current_length = std::hypot(delta.x, delta.y);
    float difference = (current_length - initial_length_) / current_length;
    sf::Vector2f correction = delta * 0.5f * difference;

    p1_->apply_correction(correction);
    p2_->apply_correction(-correction);
}

void Constraint::deactivate() {
    active_ = false;
}

bool Constraint::is_active() const {
    return active_;
}

const physics::Particle* Constraint::get_p1() const {
    return p1_;
}

const physics::Particle* Constraint::get_p2() const {
    return p2_;
}
