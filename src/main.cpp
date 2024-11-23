#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "particle.hpp"
#include "constraint.hpp"
#include "input_handler.hpp"

constexpr int WIDTH = 1080;
constexpr int HEIGHT = 640;
constexpr float PARTICLE_RADIUS = 10.0f;
constexpr float GRAVITY = 10.0f;
constexpr float TIME_STEP = 0.1f;

constexpr int ROW = 10;
constexpr int COL = 10;
constexpr float REST_DISTANCE = 30.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");
    window.setFramerateLimit(60);

    // Initialize particles and constraints
    std::vector<physics::Particle> particles;
    particles.reserve(ROW * COL);

    std::vector<Constraint> constraints;

    // Create particles
    for (int row = 0; row < ROW; ++row) {
        for (int col = 0; col < COL; ++col) {
            float x = col * REST_DISTANCE + WIDTH / 3.0f;
            float y = row * REST_DISTANCE + HEIGHT / 3.0f;
            bool pinned = (row == 0); // Pin the first row
            particles.emplace_back(x, y, pinned);
        }
    }

    // Create constraints
    for (int row = 0; row < ROW; ++row) {
        for (int col = 0; col < COL; ++col) {
            if (col < COL - 1) {
                // Horizontal constraint
                constraints.emplace_back(&particles[row * COL + col], &particles[row * COL + col + 1]);
            }
            if (row < ROW - 1) {
                // Vertical constraint
                constraints.emplace_back(&particles[row * COL + col], &particles[(row + 1) * COL + col]);
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle mouse clicks for tearing constraints
            InputHandler::handle_mouse_click(event, particles, constraints);
        }

        // Apply gravity and update particles
        for (auto& particle : particles) {
            particle.apply_force({0, GRAVITY});
            particle.update(TIME_STEP);
            particle.constrain_to_bounds(WIDTH, HEIGHT);
        }

        // Satisfy constraints
        constexpr size_t constraint_iterations = 5;
        for (size_t i = 0; i < constraint_iterations; ++i) {
            for (auto& constraint : constraints) {
                constraint.satisfy();
            }
        }

        // Render
        window.clear(sf::Color::Black);

        // Draw particles as points
        for (const auto& particle : particles) {
            sf::Vertex point(particle.get_position(), sf::Color::White);
            window.draw(&point, 1, sf::Points);
        }

        // Draw constraints as lines
        for (const auto& constraint : constraints) {
            if (!constraint.is_active()) {
                continue;
            }
            sf::Vertex line[] = {
                sf::Vertex(constraint.get_p1()->get_position(), sf::Color::White),
                sf::Vertex(constraint.get_p2()->get_position(), sf::Color::White),
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}
