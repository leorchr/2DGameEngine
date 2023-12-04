#pragma once
#include "MoveComponent.h"
#include <SDL_stdinc.h>

class MoveBall : public MoveComponent
{
public:
	MoveBall(Actor* ownerP);
	MoveBall() = delete;
	MoveBall(const MoveBall&) = delete;
	MoveBall& operator=(const MoveBall&) = delete;

	void update(float dt) override;

	float getForwardSpeed();
	float getUpwardSpeed();
};