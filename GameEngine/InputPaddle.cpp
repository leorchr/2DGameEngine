#include "InputPaddle.h"
#include "Actor.h"
#include "Window.h"
#include <SDL_scancode.h>

InputPaddle::InputPaddle(Actor* ownerP) :
	InputComponent(ownerP)
{
}

void InputPaddle::processInput(const Uint8* keyState)
{
	float forwardSpeed = 0.0f;

	if (owner.getPosition().x + owner.getSizeX() < WINDOW_WIDTH) {
		if (keyState[forwardKey] || keyState[forwardKey2])
		{
			forwardSpeed += maxForwardSpeed;
		}
	}

	if (owner.getPosition().x > 0) {
		if (keyState[backKey] || keyState[backKey2])
		{
			forwardSpeed -= maxForwardSpeed;
		}
	}

	setForwardSpeed(forwardSpeed);

	//Angular speed if needed
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