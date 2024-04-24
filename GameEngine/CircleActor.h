#pragma once
#include "Actor.h"
#include "CircleMoveComponent.h"
#include "Fruit.h"
#include "SpriteComponent.h"
#include "Vector2.h"

class CircleActor : public Actor
{
public:
	CircleActor(Vector2 positionP, const Fruit& fruitP);
	~CircleActor();
	float getRadius() { return radius; }
	CircleMoveComponent* getMoveComponent() { return moveComponent; }
	Fruit getFruit() const { return fruit; }

private:
	class CircleMoveComponent* moveComponent;
	class SpriteComponent* spriteComponent;
	float radius;
	Fruit fruit;
};