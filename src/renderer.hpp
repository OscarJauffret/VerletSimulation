//
// Created by oscar on 14/07/2024.
//

#ifndef VERLETSIMULATION_RENDERER_HPP
#define VERLETSIMULATION_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "sim/headers/solver.hpp"

using namespace sf;

class Renderer {
public:
    explicit
    Renderer(RenderTarget& target) : m_target{target} {}

    void render(const Solver& solver) const {
        const sf::Vector3f constraint = solver.getConstraint();
        sf::CircleShape constraint_background{constraint.z};
        constraint_background.setOrigin(constraint.z, constraint.z);
        constraint_background.setFillColor(sf::Color::Black);
        constraint_background.setPosition(constraint.x, constraint.y);
        constraint_background.setPointCount(128);
        m_target.draw(constraint_background);

        const Vector3f gravity = solver.getGravity();
        sf::CircleShape gravity_background{gravity.z};
        gravity_background.setOrigin(gravity.z, gravity.z);
        gravity_background.setFillColor(sf::Color::White);
        gravity_background.setPosition(gravity.x, gravity.y);
        gravity_background.setPointCount(128);
//        m_target.draw(gravity_background);

        sf::CircleShape circle{1.0f};
        circle.setPointCount(32);
        circle.setOrigin(1.0f, 1.0f);
        const auto& objects = solver.getObjects();
        for (const auto& obj : objects) {
            circle.setPosition(obj.position);
            circle.setScale(obj.radius, obj.radius);
            circle.setFillColor(obj.color);
            m_target.draw(circle);
        }
    }

private:
    sf::RenderTarget& m_target;
};

#endif //VERLETSIMULATION_RENDERER_HPP
