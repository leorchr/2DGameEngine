#pragma once
#include "Component.h"

class BoidsMoveComponent : public Component
{
public:
	BoidsMoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
	BoidsMoveComponent() = delete;
	BoidsMoveComponent(const BoidsMoveComponent&) = delete;
	BoidsMoveComponent& operator=(const BoidsMoveComponent&) = delete;

	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }

	void setSpeedX(float speedX);
	void setSpeedY(float speedY);

	void update(float dt) override;

	Vector2 separate(vector<BoidsMoveComponent*> others);


private:
	float speedX;
	float speedY;

	float baseSpeedX;
	float baseSpeedY;

	const int separationDist = 50;
	const float separationFactor = 1.0f;
};