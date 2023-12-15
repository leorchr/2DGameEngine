#pragma once
#include "Actor.h"
#include "RectangleComponent.h"
#include "InputPaddle.h"
#include "RectangleCollisionComponent.h"

class Paddle : public Actor
{
public:
	Paddle(float mSizeX, float mSizeY);
	void updateActor(float dt) override;

	RectangleCollisionComponent& getCollision() { return *rcc; }

protected:
	RectangleComponent* rc;
	InputPaddle* ic;
	RectangleCollisionComponent* rcc;
};