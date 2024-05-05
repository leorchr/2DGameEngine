#pragma once
#include "Actor.h"
#include "CircleMoveComponent.h"
#include "Fruit.h"
#include "SpriteComponent.h"
#include "Vector2.h"

class FruitActor : public Actor
{
public:
	FruitActor(Vector2 positionP, const Fruit& fruitP);
	~FruitActor();
	float getRadius() { return radius; }
	CircleMoveComponent* getMoveComponent() { return moveComponent; }
	Fruit getFruit() const { return fruit; }

private:
	class CircleMoveComponent* moveComponent;
	class SpriteComponent* spriteComponent;
	float radius;
	Fruit fruit;
};