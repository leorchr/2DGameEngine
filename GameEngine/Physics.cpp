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

void Physics::setBottomBorder(float bottomBorderP)
{
	bottomBorder = bottomBorderP;
}

void Physics::setLeftBorder(float leftBorderP)
{
	leftBorder = leftBorderP;
}

void Physics::setRightBorder(float rightBorderP)
{
	rightBorder = rightBorderP;
}

void Physics::setTopBorder(float topBorderP)
{
	topBorder = topBorderP;
}

void Physics::computePhysics(float dt)
{
	deltaTime = dt;
	const float substepDt = getStepDeltaTime();
	for (size_t i = substeps; i > 0; i--)
	{
		// Apply gravity to circles
		applyGravity();

		// Apply constraints to circles
		applyConstraint();

		// Solve collisions between circles
		solveCollisions();

		// Update positions of circles
		updatePositions(substepDt);
	}
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
		if (circle->getCurrentPosition().y > bottomBorder - circle->getRadius())
		{
			circle->setCurrentPosition(Vector2(circle->getCurrentPosition().x, bottomBorder - circle->getRadius()));
		}

		if (circle->getCurrentPosition().y < topBorder + circle->getRadius())
		{
			//circle->setCurrentPosition(Vector2(circle->getCurrentPosition().x, bottomBorder + circle->getRadius()));
		}

		if (circle->getCurrentPosition().x < leftBorder + circle->getRadius())
		{
			circle->setCurrentPosition(Vector2(leftBorder + circle->getRadius(), circle->getCurrentPosition().y));
		}

		if (circle->getCurrentPosition().x > rightBorder - circle->getRadius())
		{
			circle->setCurrentPosition(Vector2(rightBorder - circle->getRadius(), circle->getCurrentPosition().y));
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

void Physics::setObjectVelocity(CircleMoveComponent& circle, Vector2 velocityP) const
{
	circle.setVelocity(velocityP, getStepDeltaTime());
}