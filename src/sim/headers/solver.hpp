//
// Created by oscar on 14/07/2024.
//

#ifndef VERLETSIMULATION_SOLVER_HPP
#define VERLETSIMULATION_SOLVER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "verletobject.hpp"
#include "../../config.hpp"

using namespace sf;
using namespace std;

class Solver {
    Vector2<double> gravity = config::gravity;
    uint32_t subSteps = 1;
    Vector2<double> constraintCenter;
    double constraintRadius = 100.0f;
    Vector2<double> centerOfGravity;
    double centerOfGravityRadius;
    vector<VerletObject> objects;
    double time = 0.0f;
    double frameDt = 0.0f;

public:
    Solver() = default;
    int64_t
    addObject(Vector2<double> position, double radius, int64_t constrainedToId = -1, bool renderTrail = false, Color color = Color::White);
    void setSubSteps(uint32_t steps);
    void setSimulationUpdateRate(uint32_t rate);
    void setConstraint(Vector2<double> center, double radius);
    void setObjectVelocity(VerletObject& object, Vector2<double> velocity);

    [[nodiscard]] const vector<VerletObject>& getObjects() const;
    [[nodiscard]] double getStepDt() const;

    [[nodiscard]] double getTime() const;
    [[nodiscard]] uint64_t getObjectsCount() const;
    [[nodiscard]] Vector3<double> getConstraint(int64_t i = -1) const;

    void update();
    void updatePositions(double dt);
    void applyGravity();
    void applyConstraint();
    void applyCircleConstraint();
    void checkCollisions(double dt);

    void updateGravity();
    void setGravity(Vector2<double> center, double radius);
    [[nodiscard]] Vector3<double> getGravity() const;
};


#endif //VERLETSIMULATION_SOLVER_HPP
