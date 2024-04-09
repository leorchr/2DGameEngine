#pragma once
#include "CircleActor.h"

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

    void addCircle(class CircleActor* circle);
    void removeCircle(class CircleActor* circle);
    vector<CircleActor*>& getCircles() { return circles; }

private:
    vector<CircleActor*> circles;
    const Vector2 gravity = Vector2(0.0f, 1000.0f);
};