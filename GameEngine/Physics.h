#pragma once
#include "CircleMoveComponent.h"
#include <vector>
using std::vector;

class Physics
{
    Physics* PhysicsSystem{ nullptr };

public:

    Physics() = default;
    Physics(const Physics&) = delete;
    Physics& operator = (const Physics&) = delete;

    Physics* getPhysicSystem() const { return PhysicsSystem; }
    void computePhysics(float dt);
    void updatePositions(float dt);
    void applyGravity();
    void applyConstraint();
    void solveCollisions();
    void setObjectVelocity(CircleMoveComponent& circle, Vector2 velocityP) const;
    void addCircle(class CircleMoveComponent* circle);
    void removeCircle(class CircleMoveComponent* circle);
    vector<CircleMoveComponent*>& getCircles() { return circles; }
    float getStepDeltaTime() const { return deltaTime/substeps; }

private:
    vector<CircleMoveComponent*> circles;
    const Vector2 gravity = Vector2(0.0f, 1000.0f);
    float stepDeltaTime, deltaTime;
    const int substeps = 8;
};