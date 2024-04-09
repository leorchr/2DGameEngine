#pragma once
#include "Actor.h"
#include "Vector3.h"

class CircleActor : public Actor
{
public:
	CircleActor(Vector2 positionP, float radiusP, Vector3 colorP);
	~CircleActor();
	float getRadius() { return radius; }

private:
	class CircleComponent* circleComponent;
	class CircleMoveComponent* moveComponent;
	float radius;
};

