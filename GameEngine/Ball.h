#pragma once
#include "Actor.h"
#include "RectangleComponent.h"
#include "MoveBall.h"
#include "RectangleCollisionComponent.h"
#include "Vector2.h"

class Ball : public Actor
{
public:
	Ball(float mSizeX, float mSizeY);
	void updateActor(float dt) override;
	void setLives(int livesP);
	void TouchScreenBottom();

protected:
	MoveBall* mc;
	RectangleCollisionComponent* rcc;
	int lives = 3;
	Vector2 positionLastFrame;
};
