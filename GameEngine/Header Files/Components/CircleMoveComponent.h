#pragma once
#include "Actor.h"
#include "Component.h"
#include "Vector2.h"

class CircleMoveComponent : public Component
{
public:
	CircleMoveComponent(Actor* ownerP, float radiusP, int updateOrderP = 100); // By default, update before other components
	CircleMoveComponent() = delete;
	CircleMoveComponent(const CircleMoveComponent&) = delete;
	CircleMoveComponent& operator=(const CircleMoveComponent&) = delete;

	float getRadius() const { return radius; }
	void updatePosition(float dt);
	void accelerate(Vector2 accelerationP);
	Vector2 getCurrentPosition() const { return currentPosition; }
	void setCurrentPosition(Vector2 positionP);
	Vector2 getVelocity() { return currentPosition - lastPosition; }
	void addVelocity(Vector2 velocityP, float dt);
	void setVelocity(Vector2 velocityP, float dt);

protected:
	float radius;
	Vector2 acceleration;
	Vector2 currentPosition;
	Vector2 lastPosition;
};