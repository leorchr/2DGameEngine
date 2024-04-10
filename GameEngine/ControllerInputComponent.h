#pragma once
#include "ControllerMoveComponent.h"
#include <SDL_stdinc.h>

class ControllerInputComponent : public ControllerMoveComponent
{
public:
	ControllerInputComponent(Actor* ownerP, float speedXP);
	ControllerInputComponent() = delete;
	ControllerInputComponent(const ControllerInputComponent&) = delete;
	ControllerInputComponent& operator=(const ControllerInputComponent&) = delete;

	void processInput(const Uint8* keyState);

	void setMaxSpeedX(float speedXP);
	void setLeftKey(int key);
	void setRightKey(int key);


private:
	float maxSpeedX;
	int leftKey;
	int rightKey;
};
