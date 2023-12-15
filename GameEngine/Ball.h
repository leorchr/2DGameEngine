#pragma once
#include "Actor.h"
#include "RectangleComponent.h"
#include "MoveBall.h"
#include "RectangleCollisionComponent.h"

class Ball : public Actor
{
public:
	Ball(float mSizeX, float mSizeY);
	void updateActor(float dt) override;

protected:
	RectangleComponent* rc;
	MoveBall* mc;
	RectangleCollisionComponent* rcc;
};