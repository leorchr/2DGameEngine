#include "InputComponent.h"
#include <SDL_scancode.h>

InputComponent::InputComponent(Actor* ownerP) :
	MoveComponent(ownerP),
	maxForwardSpeed(100.0f),
	maxAngularSpeed(1.0f),
	forwardKey(SDL_SCANCODE_D),
	backKey(SDL_SCANCODE_A),
	forwardKey2(SDL_SCANCODE_RIGHT),
	backKey2(SDL_SCANCODE_LEFT),
	clockwiseKey(SDL_SCANCODE_E),
	counterClockwiseKey(SDL_SCANCODE_Q)
{
}

void InputComponent::processInput(const Uint8* keyState)
{
	float forwardSpeed = 0.0f;
	if (keyState[forwardKey])
	{
		forwardSpeed += maxForwardSpeed;
	}
	if (keyState[backKey])
	{
		forwardSpeed -= maxForwardSpeed;
	}
	setForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keyState[clockwiseKey])
	{
		angularSpeed -= maxAngularSpeed;
	}
	if (keyState[counterClockwiseKey])
	{
		angularSpeed += maxAngularSpeed;
	}
	setAngularSpeed(angularSpeed);
}

void InputComponent::setMaxForwardSpeed(float maxForwardSpeedP)
{
	maxForwardSpeed = maxForwardSpeedP;
}

void InputComponent::setMaxAngularSpeed(float maxAngularSpeedP)
{
	maxAngularSpeed = maxAngularSpeedP;
}

void InputComponent::setForwardKey(int key)
{
	forwardKey = key;
}

void InputComponent::setBackKey(int key)
{
	backKey = key;
}

void InputComponent::setClockwiseKey(int key)
{
	clockwiseKey = key;
}

void InputComponent::setCounterClockwiseKey(int key)
{
	counterClockwiseKey = key;
}