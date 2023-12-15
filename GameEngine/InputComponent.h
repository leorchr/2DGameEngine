#pragma once
#include "MoveComponent.h"
#include <SDL_stdinc.h>

class InputComponent : public MoveComponent
{
public:
	InputComponent(Actor* ownerP);
	InputComponent() = delete;
	InputComponent(const InputComponent&) = delete;
	InputComponent& operator=(const InputComponent&) = delete;

	virtual void processInput(const Uint8* keyState);

	void setMaxForwardSpeed(float maxForwardSpeedP);
	void setMaxAngularSpeed(float maxAngularSpeedP);
	void setForwardKey(int key);
	void setBackKey(int key);
	void setClockwiseKey(int key);
	void setCounterClockwiseKey(int key);


protected:
	float maxForwardSpeed;
	float maxAngularSpeed;

	int forwardKey;
	int backKey;
	int forwardKey2;
	int backKey2;
	int clockwiseKey;
	int counterClockwiseKey;
};
