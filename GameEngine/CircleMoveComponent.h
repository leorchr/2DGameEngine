#pragma once
#include "Component.h"
#include "Vector2.h"

class CircleMoveComponent : Component
{
public:
	CircleMoveComponent(Actor* ownerP, int updateOrderP = 100); // By default, update before other components
	CircleMoveComponent() = delete;
	CircleMoveComponent(const CircleMoveComponent&) = delete;
	CircleMoveComponent& operator=(const CircleMoveComponent&) = delete;

	void update(float dt);
	void accelerate(Vector2 accelerationP);

protected:
	Vector2 acceleration;
	Vector2 currentPosition;
	Vector2 lastPosition;

	const Vector2 gravity = Vector2(0.0f, 1000.0f);
};