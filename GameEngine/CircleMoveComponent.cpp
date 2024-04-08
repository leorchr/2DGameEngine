#include "CircleMoveComponent.h"
#include "Maths.h"
#include "Actor.h"

CircleMoveComponent::CircleMoveComponent(Actor* ownerP, float speedXP, float speedYP, int updateOrderP)
	:Component(ownerP, updateOrderP), speedX(speedXP), speedY(speedYP)
{
}

void CircleMoveComponent::setSpeedX(float speedXP)
{
	speedX = speedXP;
}

void CircleMoveComponent::setSpeedY(float speedYP)
{
	speedY = speedYP;
}

void CircleMoveComponent::update(float dt)
{
	if (!Maths::nearZero(speedX))
	{
		Vector2 newPosition = Vector2(owner.getPosition().x + speedX * dt, owner.getPosition().y);
		owner.setPosition(newPosition);
	}
	if (!Maths::nearZero(speedY))
	{
		Vector2 newPosition = Vector2(owner.getPosition().x, owner.getPosition().y + speedY * dt);
		owner.setPosition(newPosition);
	}
}