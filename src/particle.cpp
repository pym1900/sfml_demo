#include "particle.hpp"

namespace physics {


void Particle::apply_force(const sf::Vector2f& force) {
    if (!is_pinned_) {
        acceleration_ += force;
    }
}

void Particle::update(float time_step) {
    if (!is_pinned_) {
        sf::Vector2f velocity = position_ - previous_position_;
        previous_position_ = position_;
        position_ += velocity + acceleration_ * time_step * time_step;
        acceleration_ = {0.0f, 0.0f};
    }
}

void Particle::constrain_to_bounds(float width, float height) {
    position_.x = std::clamp(position_.x, 0.0f, width);
    position_.y = std::clamp(position_.y, 0.0f, height);
}

void Particle::apply_correction(const sf::Vector2f& correction) {
    if (!is_pinned_) {
        position_ += correction;
    }
}

const sf::Vector2f& Particle::get_position() const {
    return position_;
}

bool Particle::is_pinned() const {
    return is_pinned_;
}

void Particle::render(sf::RenderWindow& window, float radius) const {
    sf::CircleShape shape(radius);
    shape.setPosition(position_.x - radius, position_.y - radius);
    shape.setFillColor(sf::Color::White);
    window.draw(shape);
}

} // namespace physics
