#pragma once
#include "Actor.h"
#include "Component.h"
#include "Vector2.h"

class UIMovementComponent : public Component
{
public:
	UIMovementComponent(Actor* ownerP); // By default, update before other components
	UIMovementComponent() = delete;
	UIMovementComponent(const UIMovementComponent&) = delete;
	UIMovementComponent& operator=(const UIMovementComponent&) = delete;

	void update(float dt) override;
private:
	Vector2 basePosition;
};