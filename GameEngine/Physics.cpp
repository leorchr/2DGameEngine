#include "Physics.h"
#include "Window.h"

void Physics::addCircle(CircleActor* circle)
{
	circles.emplace_back(circle);
}

void Physics::removeCircle(CircleActor* circle)
{
	auto iter = std::find(begin(circles), end(circles), circle);
	circles.erase(iter);
}

void Physics::computePhysics(float dt)
{
	applyGravity();
	applyConstraint();
	updatePositions(dt);
}

void Physics::updatePositions(float dt)
{
	for (auto circle : circles)
	{
		circle->getMoveComponent()->updatePosition(dt);
	}
}

void Physics::applyGravity()
{
	for (auto circle : circles)
	{
		circle->getMoveComponent()->accelerate(gravity);
	}
}

void Physics::applyConstraint()
{

	for (auto circle : circles)
	{
		float actorRadius = circle->getRadius();

		const Vector2 position = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		const float radius = 300.0f;

		const Vector2 toObject = circle->getMoveComponent()->getCurrentPosition() - position;
		const float distance = toObject.length();

		if (distance > radius - actorRadius) {
			const Vector2 normal = toObject / distance;
			circle->getMoveComponent()->setCurrentPosition(position + normal * (radius - actorRadius));
		}
	}
}