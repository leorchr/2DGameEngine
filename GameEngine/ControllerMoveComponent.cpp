#include "Actor.h"
#include "Component.h"
#include "ControllerMoveComponent.h"
#include "Maths.h"
#include "Vector2.h"

ControllerMoveComponent::ControllerMoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), speedX(0.0f)
{

}

void ControllerMoveComponent::setSpeedX(float speedXP)
{
	speedX = speedXP;
}

void ControllerMoveComponent::update(float dt)
{
	if (!Maths::nearZero(speedX))
	{
		Vector2 newPosition = Vector2(owner.getPosition().x + speedX * dt,owner.getPosition().y);
		owner.setPosition(newPosition);
	}
}