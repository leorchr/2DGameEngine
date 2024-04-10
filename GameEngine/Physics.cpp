#include "Physics.h"
#include "Window.h"

void Physics::addCircle(CircleMoveComponent* circle)
{
	circles.emplace_back(circle);
}

void Physics::removeCircle(CircleMoveComponent* circle)
{
	auto iter = std::find(begin(circles), end(circles), circle);
	circles.erase(iter);
}

void Physics::computePhysics(float dt)
{
	applyGravity();
	applyConstraint();
	solveCollisions();
	updatePositions(dt);
}

void Physics::updatePositions(float dt)
{
	for (auto circle : circles)
	{
		circle->updatePosition(dt);
	}
}

void Physics::applyGravity()
{
	for (auto circle : circles)
	{
		circle->accelerate(gravity);
	}
}

void Physics::applyConstraint()
{

	for (auto circle : circles)
	{
		float actorRadius = circle->getRadius();

		const Vector2 position = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		const float radius = 300.0f;

		const Vector2 toObject = circle->getCurrentPosition() - position;
		const float distance = toObject.length();

		if (distance > radius - actorRadius) {
			const Vector2 normal = toObject / distance;
			circle->setCurrentPosition(position + normal * (radius - actorRadius));
		}
	}
}

void Physics::solveCollisions()
{
	const int size = circles.size();
	for (size_t i = 0; i < size; i++)
	{
		CircleMoveComponent* circle1 = circles[i];
		for (size_t k = i+1; k < size; k++)
		{
			CircleMoveComponent* circle2 = circles[k];
			const Vector2 collisionDir = circle1->getCurrentPosition() - circle2->getCurrentPosition();
			const float distance = collisionDir.length();

			const float radiusSum = circle1->getRadius() + circle2->getRadius();

			if (distance < radiusSum) {
				const Vector2 normal = collisionDir / distance;
				const float delta = radiusSum - distance;

				circle1->setCurrentPosition(circle1->getCurrentPosition() + normal * delta / 2);
				circle2->setCurrentPosition(circle2->getCurrentPosition() - normal * delta / 2);
			}
		}
	}
}
