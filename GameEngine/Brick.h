#pragma once
#include "Actor.h"
#include "RectangleComponent.h"
#include "RectangleCollisionComponent.h"

class Brick : public Actor
{
public:
	Brick(float mSizeX, float mSizeY);
	~Brick();
	void updateActor(float dt) override;

	RectangleCollisionComponent& getCollision() { return *rcc; }

protected:
	RectangleComponent* rc;
	RectangleCollisionComponent* rcc;
};

