#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle(float x, float y, bool pinned = false)
        : position_{x, y}, previous_position_{x, y},
          acceleration_{0.0f, 0.0f}, is_pinned_{pinned} {}

    void apply_force(const sf::Vector2f& force) {
        if (!is_pinned_) {
            acceleration_ += force;
        }
    }

    void update(float time_step) {
        if (!is_pinned_) {
            sf::Vector2f velocity = position_ - previous_position_;
            previous_position_ = position_;
            position_ += velocity + acceleration_ * time_step * time_step;
            acceleration_ = {0.0f, 0.0f};
        }
    }

    void constrain_to_bounds(float width, float height) {
        if (position_.x < 0.0f) position_.x = 0.0f;
        if (position_.x > width) position_.x = width;
        if (position_.y < 0.0f) position_.y = 0.0f;
        if (position_.y > height) position_.y = height;
    }

    // Apply correction for constraints
    void apply_correction(const sf::Vector2f& correction) {
        if (!is_pinned_) {
            position_ += correction;
        }
    }

    // Accessors
    [[nodiscard]] const sf::Vector2f& get_position() const { return position_; }
    [[nodiscard]] bool is_pinned() const { return is_pinned_; }

private:
    sf::Vector2f position_;
    sf::Vector2f previous_position_;
    sf::Vector2f acceleration_;
    bool is_pinned_;
};

#endif // PARTICLE_H
