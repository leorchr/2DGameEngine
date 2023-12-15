#pragma once
#include "Component.h"
#include "Vector2.h"

class RectangleCollisionComponent : public Component
{
public :
	RectangleCollisionComponent(Actor* owner);
	RectangleCollisionComponent() = delete;
	RectangleCollisionComponent(const RectangleCollisionComponent&) = delete;
	RectangleCollisionComponent& operator=(const RectangleCollisionComponent&) = delete;

	const Vector2 getPosition() const;
	const float getSizeX() const;
	const float getSizeY() const;
};

bool Intersect(const RectangleCollisionComponent& a, const RectangleCollisionComponent& b);