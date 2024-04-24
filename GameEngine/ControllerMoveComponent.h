#pragma once
#include "Actor.h"
#include "Component.h"
class ControllerMoveComponent : public Component
{
public:
	ControllerMoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
	ControllerMoveComponent() = delete;
	ControllerMoveComponent(const ControllerMoveComponent&) = delete;
	ControllerMoveComponent& operator=(const ControllerMoveComponent&) = delete;

	float getSpeedX() const { return speedX; }
	void setSpeedX(float speedXP);
	void update(float dt) override;

private:
	float speedX;
};