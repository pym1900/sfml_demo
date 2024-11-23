#include "input_handler.hpp"

void InputHandler::handle_mouse_click(const sf::Event& event, std::vector<physics::Particle>& particles,
                                      std::vector<Constraint>& constraints) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const float mouse_x = static_cast<float>(event.mouseButton.x);
        const float mouse_y = static_cast<float>(event.mouseButton.y);
        tear_cloth(mouse_x, mouse_y, constraints);
    }
}

float InputHandler::point_to_segment_distance(float px, float py, float x1, float y1, float x2, float y2) {
    const sf::Vector2f AB{x2 - x1, y2 - y1};
    const sf::Vector2f AP{px - x1, py - y1};
    const sf::Vector2f BP{px - x2, py - y2};

    const float AB_dot_AP = AB.x * AP.x + AB.y * AP.y;
    const float AB_dot_AB = AB.x * AB.x + AB.y * AB.y;
    const float t = AB_dot_AP / AB_dot_AB;

    if (t < 0.0f) {
        // Closer to A
        return std::hypot(AP.x, AP.y);
    } else if (t > 1.0f) {
        // Closer to B
        return std::hypot(BP.x, BP.y);
    } else {
        // Projection on the segment
        const float proj_x = x1 + t * AB.x;
        const float proj_y = y1 + t * AB.y;
        return std::hypot(px - proj_x, py - proj_y);
    }
}

std::optional<Constraint*> InputHandler::find_nearest_constraint(float mouse_x, float mouse_y,
                                                                 std::vector<Constraint>& constraints) {
    Constraint* nearest_constraint = nullptr;
    float min_distance = CLICK_TOLERANCE;

    for (auto& constraint : constraints) {
        const float distance = point_to_segment_distance(mouse_x, mouse_y,
                                                         constraint.get_p1()->get_position().x,
                                                         constraint.get_p1()->get_position().y,
                                                         constraint.get_p2()->get_position().x,
                                                         constraint.get_p2()->get_position().y);
        if (distance < min_distance) {
            min_distance = distance;
            nearest_constraint = &constraint;
        }
    }

    if (nearest_constraint) {
        return nearest_constraint;
    } else {
        return std::nullopt;
    }
}

void InputHandler::tear_cloth(float mouse_x, float mouse_y, std::vector<Constraint>& constraints) {
    auto nearest = find_nearest_constraint(mouse_x, mouse_y, constraints);
    if (nearest) {
        nearest.value()->deactivate();
    }
}
