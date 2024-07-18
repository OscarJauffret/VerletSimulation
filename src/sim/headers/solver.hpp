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
    Vector2f gravity = config::gravity;
    uint32_t subSteps = 1;
    Vector2f constraintCenter;
    float constraintRadius = 100.0f;
    Vector2f centerOfGravity;
    float centerOfGravityRadius;
    vector<VerletObject> objects;
    float time = 0.0f;
    float frameDt = 0.0f;

public:
    Solver() = default;
    uint64_t addObject(sf::Vector2f position, float radius, int64_t constrainedToId = -1, bool renderTrail = false);
    void setSubSteps(uint32_t steps);
    void setSimulationUpdateRate(uint32_t rate);
    void setConstraint(Vector2f center, float radius);
    void setObjectVelocity(VerletObject& object, Vector2f velocity);

    [[nodiscard]] const vector<VerletObject>& getObjects() const;
    [[nodiscard]] float getStepDt() const;

    [[nodiscard]] float getTime() const;
    [[nodiscard]] uint64_t getObjectsCount() const;
    [[nodiscard]] Vector3f getConstraint(int64_t i = -1) const;

    void update();
    void updatePositions(float dt);
    void applyGravity();
    void applyConstraint();
    void applyCircleConstraint();
    void checkCollisions(float dt);

    void updateGravity();
    void setGravity(Vector2f center, float radius);
    [[nodiscard]] Vector3f getGravity() const;
};


#endif //VERLETSIMULATION_SOLVER_HPP
