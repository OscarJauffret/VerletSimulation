//
// Created by oscar on 14/07/2024.
//
#include "headers/solver.hpp"

double Solver::getStepDt() const {
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

void Solver::setConstraint(Vector2<double> center, double radius) {
    constraintCenter = center;
    constraintRadius = radius;
}

void Solver::setObjectVelocity(VerletObject &object, Vector2<double> velocity) {
    object.setVelocity(velocity, getStepDt());
}

Vector3<double> Solver::getConstraint(int64_t i) const {
    if (i < 0) {
        return {constraintCenter.x, constraintCenter.y, constraintRadius};
    }
    return {objects[i].position.x, objects[i].position.y, constraintRadius};
}

uint64_t Solver::getObjectsCount() const {
    return objects.size();
}

double Solver::getTime() const {
    return time;
}

void Solver::updateGravity() {
    for (auto& obj: objects) {
        Vector2<double> direction = centerOfGravity - obj.position;
        double distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        double newAcceleration = centerOfGravityRadius / (distance * distance) * 10000;
        obj.accelerate(direction * newAcceleration);
    }
}

void Solver::setGravity(Vector2<double> center, double radius) {
    centerOfGravity = center;
    centerOfGravityRadius = radius;
}

Vector3<double> Solver::getGravity() const {
    return {centerOfGravity.x, centerOfGravity.y, centerOfGravityRadius};
}