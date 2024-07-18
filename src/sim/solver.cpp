//
// Created by oscar on 14/07/2024.
//

#include "headers/solver.hpp"

int64_t
Solver::addObject(Vector2<double> position, double radius, int64_t constrainedToId, bool renderTrail, Color color) {
    objects.emplace_back(position, radius, constrainedToId, renderTrail, color);
    return objects.size() - 1;
}

void Solver::update() {
    time += frameDt;
    const float stepDt = getStepDt();
    for (uint32_t i{subSteps}; i--;) {
        applyGravity();
//        checkCollisions(0);
        applyCircleConstraint();
        updatePositions(stepDt);
    }
}

void Solver::updatePositions(double dt) {
    for (auto& object : objects) {
        object.updatePosition(dt);
    }
}

void Solver::applyGravity() {
    for (auto& object : objects) {
        object.accelerate(gravity);
    }
}

void Solver::applyConstraint() {
    for (auto& obj: objects) {
        const Vector2<double> distance = constraintCenter - obj.position;
        const double dist = sqrt(distance.x * distance.x + distance.y * distance.y);
        if (dist > constraintRadius - obj.radius) {
            const Vector2<double> normal = distance / dist;
            obj.position = constraintCenter - normal * (constraintRadius - obj.radius);
        }
    }
}

void Solver::applyCircleConstraint() {
    Vector2<double> center;
    for (auto& obj: objects) {
        center = constraintCenter;
        if (obj.constrainedToId != -1) {
            center = objects[obj.constrainedToId].position;
        }
        const Vector2<double> distance = center - obj.position;
        const double dist = sqrt(distance.x * distance.x + distance.y * distance.y);
        if (dist != constraintRadius - obj.radius) {
            const Vector2<double> normal = distance / dist;
            obj.position = center - normal * (constraintRadius - obj.radius);
        }
    }
}

void Solver::checkCollisions(double dt) {
    const double responseCoef = 0.75f;
    const uint64_t size = objects.size();
    for (uint64_t i{0}; i < size; ++i) {
        VerletObject& obj1 = objects[i];
        for (uint64_t k{i + 1}; k < size; ++k) {
            VerletObject& obj2 = objects[k];
            const sf::Vector2<double> v = obj1.position - obj2.position;
            const double dist2 = v.x * v.x + v.y * v.y;
            const double minDist = obj1.radius + obj2.radius;
            if (dist2 < minDist * minDist) {
                const double dist  = sqrt(dist2);
                const sf::Vector2<double> n = v / dist;
                const double mass_ratio_1 = obj1.radius / (obj1.radius + obj2.radius);
                const double mass_ratio_2 = obj2.radius / (obj1.radius + obj2.radius);
                const double delta = 0.5f * responseCoef * (dist - minDist);
                // Update positions
                obj1.position -= n * (mass_ratio_2 * delta);
                obj2.position += n * (mass_ratio_1 * delta);
            }
        }
    }
}