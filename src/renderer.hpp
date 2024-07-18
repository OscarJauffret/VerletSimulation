//
// Created by oscar on 14/07/2024.
//

#ifndef VERLETSIMULATION_RENDERER_HPP
#define VERLETSIMULATION_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "sim/headers/solver.hpp"

using namespace sf;
#define M_PI 3.14159265358979323846f

class Renderer {
    const Color constraintColor = Color(80, 80, 80);
    const float thickness = 2.0f;
public:
    explicit
    Renderer(RenderTarget& target) : m_target{target} {}

    void render(const Solver& solver) const {
        sf::CircleShape circle{1.0f};
        circle.setPointCount(32);
        circle.setOrigin(1.0f, 1.0f);
        const auto& objects = solver.getObjects();
        for (const auto& obj : objects) {
            circle.setPosition(obj.position);
            circle.setScale(obj.radius, obj.radius);
            circle.setFillColor(obj.color);
            m_target.draw(circle);
            Vector3f constraint = solver.getConstraint(obj.constrainedToId);
            Vector2f direction = {constraint.x - obj.position.x, constraint.y - obj.position.y};
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            float angle = atan2(direction.y, direction.x) * 180 / M_PI;

            sf::RectangleShape line;
            line.setSize({length, thickness}); // Set the desired thickness
            line.setOrigin(0, thickness / 2);
            line.setPosition(obj.position);
            line.setRotation(angle);
            line.setFillColor(constraintColor);

            m_target.draw(line);

            if (obj.renderTrail) {
                for (const auto &[trailPosition, trailColor]: obj.trail) {
                    circle.setPosition(trailPosition);
                    circle.setFillColor(trailColor);
                    m_target.draw(circle);
                }
            }
        }
    }

private:
    sf::RenderTarget& m_target;
};

#endif //VERLETSIMULATION_RENDERER_HPP
