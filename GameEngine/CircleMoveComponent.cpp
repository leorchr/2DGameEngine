#include "CircleMoveComponent.h"
#include "Maths.h"
#include "Actor.h"

CircleMoveComponent::CircleMoveComponent(Actor* ownerP, int updateOrderP)
	:Component(ownerP, updateOrderP)
{
	lastPosition = owner.getPosition();
	currentPosition = owner.getPosition();
}

void CircleMoveComponent::accelerate(Vector2 accelerationP)
{
	acceleration += accelerationP;
}

void CircleMoveComponent::update(float dt)
{
	accelerate(gravity);


	const Vector2 velocity = currentPosition - lastPosition;

	lastPosition = currentPosition;

	currentPosition += velocity + acceleration * dt * dt;

	acceleration = Vector2::zero;

	owner.setPosition(currentPosition);
}