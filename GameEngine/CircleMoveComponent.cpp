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
	Vector2 velocity = currentPosition - lastPosition;
	lastPosition = currentPosition;
	if (velocity.y < -0.2f) {
		velocity.y = 0.0f;
	}
	if (abs(velocity.x) > 0.7f) { 
		velocity.x = 0.0f;
	}
	if (velocity.length() > 2.8f) {
		velocity = Vector2::zero;
	}
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
