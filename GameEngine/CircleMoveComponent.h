#pragma once
#include "Component.h"

class CircleMoveComponent : Component
{
public:
	CircleMoveComponent(Actor* ownerP, float speedXP, float speedYP, int updateOrderP = 100); // By default, update before other components
	CircleMoveComponent() = delete;
	CircleMoveComponent(const CircleMoveComponent&) = delete;
	CircleMoveComponent& operator=(const CircleMoveComponent&) = delete;

	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }

	void setSpeedX(float speedXP);
	void setSpeedY(float speedYP);

	void update(float dt);


protected:
	float speedX;
	float speedY;
};