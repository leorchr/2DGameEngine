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
	void setLives(int livesP);
	void TouchScreenBottom();

protected:
	RectangleComponent* rc;
	MoveBall* mc;
	RectangleCollisionComponent* rcc;
	int lives = 3;
};
