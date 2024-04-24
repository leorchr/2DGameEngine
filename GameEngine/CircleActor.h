#pragma once
#include "Actor.h"
#include "CircleComponent.h"
#include "CircleMoveComponent.h"
#include "Fruit.h"
#include "Vector2.h"

class CircleActor : public Actor
{
public:
	CircleActor(Vector2 positionP, const Fruit& fruitP);
	~CircleActor();
	float getRadius() { return radius; }
	CircleComponent* getCircleComponent() { return circleComponent; }
	CircleMoveComponent* getMoveComponent() { return moveComponent; }
	Fruit getFruit() const { return fruit; }

private:
	class CircleComponent* circleComponent;
	class CircleMoveComponent* moveComponent;
	float radius;
	Fruit fruit;
};