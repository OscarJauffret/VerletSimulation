//
// Created by oscar on 14/07/2024.
//

#ifndef VERLETSIMULATION_VERLETOBJECT_HPP
#define VERLETSIMULATION_VERLETOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <deque>

using namespace sf;
using namespace std;

struct VerletObject {
    Vector2<double> position;
    Vector2<double> previousPosition;
    Vector2<double> acceleration;
    double radius = 10.0f;
    Color color = Color::White;
    int64_t constrainedToId = -1;
    deque<pair<Vector2<double>, Color>> trail;
    const size_t maxTrailLength = 300;
    bool renderTrail = false;

    VerletObject() = default;
    VerletObject(Vector2<double> position, double radius, int64_t constrainedToId = -1, bool renderTrail = false, Color color = Color::White)
    : position(position), previousPosition(position), acceleration{0.0f, 0.0f}, radius(radius),
    constrainedToId(constrainedToId), renderTrail(renderTrail), color(color) {}

    void updatePosition(double dt) {
        const Vector2<double> velocity = position - previousPosition;
        const double VELOCITY_DAMPING = 40.0f;
        previousPosition = position;
        position = position + velocity + (acceleration - velocity * VELOCITY_DAMPING) * dt * dt;
        acceleration = {};

        trail.emplace_back(position, color);
        if (trail.size() > maxTrailLength) {
            trail.pop_front();
        }
    }

    void accelerate(Vector2<double> force) {
        acceleration += force;
    }

    void setVelocity(sf::Vector2<double> v, double dt) {
        previousPosition = position - (v * dt);
    }

    void addVelocity(sf::Vector2<double> v, double dt)
    {
        previousPosition -= v * dt;
    }

    [[nodiscard]] Vector2<double> getVelocity(double dt) const {
        return (position - previousPosition) / dt;
    }
};

#endif //VERLETSIMULATION_VERLETOBJECT_HPP
