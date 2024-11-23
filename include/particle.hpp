#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm> // For std::clamp

namespace physics {

class Particle {

public:
   // Default constructor
    Particle() : position_{0.0f, 0.0f}, previous_position_{0.0f, 0.0f},
                 acceleration_{0.0f, 0.0f}, is_pinned_{false} {}

    // Constructor with an sf::Vector2f
    explicit Particle(const sf::Vector2f& position, bool pinned = false)
        : position_{position}, previous_position_{position},
          acceleration_{0.0f, 0.0f}, is_pinned_{pinned} {}

    // Constructor with float values
    Particle(float x, float y, bool pinned = false)
        : position_{x, y}, previous_position_{x, y},
          acceleration_{0.0f, 0.0f}, is_pinned_{pinned} {}
          
    void apply_force(const sf::Vector2f& force);
    void update(float time_step);
    void constrain_to_bounds(float width, float height);
    void apply_correction(const sf::Vector2f& correction);

    [[nodiscard]] const sf::Vector2f& get_position() const;
    [[nodiscard]] bool is_pinned() const;

    void render(sf::RenderWindow& window, float radius = 5.0f) const;

private:
    sf::Vector2f position_;
    sf::Vector2f previous_position_;
    sf::Vector2f acceleration_;
    bool is_pinned_;
};

} // namespace physics
