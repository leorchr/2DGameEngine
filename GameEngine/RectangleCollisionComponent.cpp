#include "RectangleCollisionComponent.h"
#include "Actor.h"

RectangleCollisionComponent::RectangleCollisionComponent(Actor* owner) : Component(owner)
{
}

const Vector2 RectangleCollisionComponent::getPosition() const
{
	return owner.getPosition();
}

const float RectangleCollisionComponent::getSizeX() const
{
	return owner.getSizeX();
}

const float RectangleCollisionComponent::getSizeY() const
{
	return owner.getSizeY();
}

bool Intersect(const RectangleCollisionComponent& a, const RectangleCollisionComponent& b)
{
	float xMinA = a.getPosition().x;
	float xMaxA = a.getPosition().x + a.getSizeX();
	float yMinA = a.getPosition().y;
	float yMaxA = a.getPosition().y + a.getSizeY();
	float xMinB = b.getPosition().x;
	float xMaxB = b.getPosition().x + b.getSizeX();
	float yMinB = b.getPosition().y;
	float yMaxB = b.getPosition().y + b.getSizeY();
	return!(xMinA > xMaxB || xMaxA < xMinB || yMinA > yMaxB || yMaxA < yMinB);
}