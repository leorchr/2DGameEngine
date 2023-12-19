#pragma once
#include "Actor.h"

class Live : public Actor
{
public:
	Live(float mSizeX, float mSizeY);
	~Live();
	void updateActor(float dt) override;
};