#include "CircleMoveComponent.h"
#include "CircleActor.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

CircleMoveComponent::CircleMoveComponent(Actor* ownerP, int updateOrderP)
	:Component(ownerP, updateOrderP)
{
	lastPosition = owner.getPosition();
	currentPosition = owner.getPosition();
}


void CircleMoveComponent::update(float dt)
{
	accelerate(gravity);
	applyConstraint();
	updatePosition(dt);
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

void CircleMoveComponent::applyConstraint()
{
	CircleActor* circleActor = static_cast<CircleActor*>(&owner);
	float actorRadius = circleActor->getRadius();

	const Vector2 position = Vector2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	const float radius = 300.0f;

	const Vector2 toObject = currentPosition - position;
	const float distance = toObject.length();

	if (distance > radius - actorRadius) {
		const Vector2 normal = toObject / distance;
		currentPosition = position + normal * (radius - actorRadius);
	}
}
