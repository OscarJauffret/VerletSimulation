//
// Created by oscar on 14/07/2024.
//
#include "headers/solver.hpp"

float Solver::getStepDt() const {
    return frameDt / static_cast<float>(subSteps);
}

const vector<VerletObject> &Solver::getObjects() const {
    return objects;
}

void Solver::setSubSteps(uint32_t steps) {
    subSteps = steps;
}

void Solver::setSimulationUpdateRate(uint32_t rate) {
    frameDt = 1.0f / static_cast<float>(rate);
}

void Solver::setConstraint(sf::Vector2f center, float radius) {
    constraintCenter = center;
    constraintRadius = radius;
}

void Solver::setObjectVelocity(VerletObject &object, sf::Vector2f velocity) {
    object.setVelocity(velocity, getStepDt());
}

Vector3f Solver::getConstraint() const {
    return {constraintCenter.x, constraintCenter.y, constraintRadius};
}

uint64_t Solver::getObjectsCount() const {
    return objects.size();
}

float Solver::getTime() const {
    return time;
}

void Solver::updateGravity() {
    for (auto& obj: objects) {
        Vector2f direction = centerOfGravity - obj.position;
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        float newAcceleration = centerOfGravityRadius / (distance * distance) * 10000;
        obj.accelerate(direction * newAcceleration);
    }
}

void Solver::setGravity(Vector2f center, float radius) {
    centerOfGravity = center;
    centerOfGravityRadius = radius;
}

Vector3f Solver::getGravity() const {
    return {centerOfGravity.x, centerOfGravity.y, centerOfGravityRadius};
}