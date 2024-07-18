//
// Created by oscar on 14/07/2024.
//

#include "headers/solver.hpp"

VerletObject &Solver::addObject(sf::Vector2f position, float radius) {
    objects.emplace_back(position, radius);
    return objects.back();
}

void Solver::update() {
    time += frameDt;
    const float stepDt = getStepDt();
    for (uint32_t i{subSteps}; i--;) {
        applyGravity();
//        updateGravity();
        checkCollisions(0);
//        applyConstraint();
        applyCircleConstraint();
        updatePositions(stepDt);
    }
}

void Solver::updatePositions(float dt) {
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
        const Vector2f distance = constraintCenter - obj.position;
        const float dist = sqrt(distance.x * distance.x + distance.y * distance.y);
        if (dist > constraintRadius - obj.radius) {
            const Vector2f normal = distance / dist;
            obj.position = constraintCenter - normal * (constraintRadius - obj.radius);
        }
    }
}

void Solver::applyCircleConstraint() {
    for (auto& obj: objects) {
        const Vector2f distance = constraintCenter - obj.position;
        const float dist = sqrt(distance.x * distance.x + distance.y * distance.y);
        if (dist != constraintRadius - obj.radius) {
            const Vector2f normal = distance / dist;
            obj.position = constraintCenter - normal * (constraintRadius - obj.radius);
        }
    }
}

void Solver::checkCollisions(float dt) {
    const float responseCoef = 0.75f;
    const uint64_t size = objects.size();
    for (uint64_t i{0}; i < size; ++i) {
        VerletObject& obj1 = objects[i];
        for (uint64_t k{i + 1}; k < size; ++k) {
            VerletObject& obj2 = objects[k];
            const sf::Vector2f v        = obj1.position - obj2.position;
            const float        dist2    = v.x * v.x + v.y * v.y;
            const float        minDist = obj1.radius + obj2.radius;
            if (dist2 < minDist * minDist) {
                const float        dist  = sqrt(dist2);
                const sf::Vector2f n     = v / dist;
                const float mass_ratio_1 = obj1.radius / (obj1.radius + obj2.radius);
                const float mass_ratio_2 = obj2.radius / (obj1.radius + obj2.radius);
                const float delta        = 0.5f * responseCoef * (dist - minDist);
                // Update positions
                obj1.position -= n * (mass_ratio_2 * delta);
                obj2.position += n * (mass_ratio_1 * delta);
            }
        }
    }
}