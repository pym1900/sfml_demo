#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <optional>
#include "particle.hpp"
#include "constraint.hpp"

constexpr float CLICK_TOLERANCE = 5.0f;

class InputHandler {
public:
    static void handle_mouse_click(const sf::Event& event, std::vector<physics::Particle>& particles,
                                   std::vector<Constraint>& constraints);

private:
    static float point_to_segment_distance(float px, float py, float x1, float y1, float x2, float y2);
    static std::optional<Constraint*> find_nearest_constraint(float mouse_x, float mouse_y,
                                                              std::vector<Constraint>& constraints);
    static void tear_cloth(float mouse_x, float mouse_y, std::vector<Constraint>& constraints);
};
