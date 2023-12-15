#pragma once
#include "Actor.h"
#include "RectangleComponent.h"
#include "InputPaddle.h"

class Paddle : public Actor
{
public:
	Paddle(float mSizeX, float mSizeY);
	void updateActor(float dt) override;

protected:
	RectangleComponent* rc;
	InputPaddle* ic;
};