#include "ControllerInputComponent.h"
#include <SDL_scancode.h>
#include "Game.h"

#include <iostream>
using namespace std;

ControllerInputComponent::ControllerInputComponent(Actor* ownerP, float speedXP) :
	ControllerMoveComponent(ownerP),
	maxSpeedX(speedXP),
	leftKey(SDL_SCANCODE_A),
	rightKey(SDL_SCANCODE_D)
{
}

void ControllerInputComponent::processInput(const Uint8* keyState)
{
	float currentSpeedX = 0.0f;
	const float leftBorder = owner.getGame().getPhysics().getLeftBorder();
	const float rightBorder = owner.getGame().getPhysics().getRightBorder();

	if (owner.getPosition().x <= leftBorder)
	{
		owner.setPosition(Vector2(rightBorder - 50.0f, owner.getPosition().y));
	}
	if (owner.getPosition().x >= rightBorder)
	{
		owner.setPosition(Vector2(leftBorder + 50.0f, owner.getPosition().y));
	}

	if (keyState[leftKey] && owner.getPosition().x > owner.getGame().getPhysics().getLeftBorder())
	{
		currentSpeedX -= maxSpeedX;
	}
	if (keyState[rightKey] && owner.getPosition().x < owner.getGame().getPhysics().getRightBorder())
	{
		currentSpeedX += maxSpeedX;
	}
	setSpeedX(currentSpeedX);
}

void ControllerInputComponent::setMaxSpeedX(float maxSpeedXP)
{
	maxSpeedX = maxSpeedXP;
}

void ControllerInputComponent::setLeftKey(int key)
{
	leftKey = key;
}

void ControllerInputComponent::setRightKey(int key)
{
	rightKey = key;
}