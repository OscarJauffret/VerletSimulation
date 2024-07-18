//
// Created by oscar on 14/07/2024.
//

#ifndef VERLETSIMULATION_VERLETOBJECT_HPP
#define VERLETSIMULATION_VERLETOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <deque>
using namespace sf;

struct VerletObject {
    Vector2f position;
    Vector2f previousPosition;
    Vector2f acceleration;
    float radius = 10.0f;
    Color color = Color::White;
    int64_t constrainedToId = -1;
    std::deque<std::pair<Vector2f, Color>> trail;
    const size_t maxTrailLength = 200;
    bool renderTrail = false;

    VerletObject() = default;
    VerletObject(Vector2f position, float radius, int64_t constrainedToId = -1, bool renderTrail = false)
    : position(position), previousPosition(position), acceleration{0.0f, 0.0f}, radius(radius), color(Color::White), constrainedToId(constrainedToId), renderTrail(renderTrail) {}

    void updatePosition(float dt) {
        const Vector2f velocity = position - previousPosition;
        const float VELOCITY_DAMPING = 40.0f;
        previousPosition = position;
        position = position + velocity + (acceleration - velocity * VELOCITY_DAMPING) * dt * dt;
        acceleration = {};

        trail.emplace_back(position, color);
        if (trail.size() > maxTrailLength) {
            trail.pop_front();
        }
    }

    void accelerate(Vector2f force) {
        acceleration += force;
    }

    void setVelocity(sf::Vector2f v, float dt) {
        previousPosition = position - (v * dt);
    }

    void addVelocity(sf::Vector2f v, float dt)
    {
        previousPosition -= v * dt;
    }

    [[nodiscard]] Vector2f getVelocity(float dt) const {
        return (position - previousPosition) / dt;
    }
};

#endif //VERLETSIMULATION_VERLETOBJECT_HPP
