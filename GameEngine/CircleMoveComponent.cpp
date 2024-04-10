#include "CircleMoveComponent.h"
#include "Actor.h"

CircleMoveComponent::CircleMoveComponent(Actor* ownerP, float radiusP, int updateOrderP)
	:Component(ownerP, updateOrderP)
{
	radius = radiusP;
	lastPosition = owner.getPosition();
	currentPosition = owner.getPosition();
	int angle = rand() % 360;
}

void CircleMoveComponent::updatePosition(float dt)
{
	const Vector2 velocity = currentPosition - lastPosition;
	lastPosition = currentPosition;
	currentPosition += velocity + acceleration * dt * dt;
	acceleration = Vector2::zero;
	owner.setPosition(currentPosition);
}

void CircleMoveComponent::accelerate(Vector2 accelerationP)
{
	acceleration += accelerationP;
}

void CircleMoveComponent::setCurrentPosition(Vector2 positionP)
{
	currentPosition = positionP;
}

void CircleMoveComponent::addVelocity(Vector2 velocityP, float dt)
{
	lastPosition -= velocityP * dt;
}

void CircleMoveComponent::setVelocity(Vector2 velocityP, float dt)
{
	lastPosition = currentPosition - (velocityP * dt);
}
