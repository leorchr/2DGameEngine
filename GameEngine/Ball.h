#pragma once
#include "Actor.h"

class Ball : public Actor
{
public:
	Ball();
	void updateActor(float dt) override;
};

