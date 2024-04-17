#include "ControllerInputComponent.h"
#include <SDL_scancode.h>
#include "Game.h"
#include "Fruit.h"
#include <iostream>
using namespace std;

ControllerInputComponent::ControllerInputComponent(Actor* ownerP, float speedXP, float offsetP, float timeNextInputP) :
	ControllerMoveComponent(ownerP),
	maxSpeedX(speedXP),
	offset(offsetP),
	timeNextInput(timeNextInputP),
	leftKey(SDL_SCANCODE_A),
	rightKey(SDL_SCANCODE_D)
{
	time = 0.0f;
}

void ControllerInputComponent::update(float dt) {
	ControllerMoveComponent::update(dt);
	time -= dt;
}

void ControllerInputComponent::processInput(const struct InputState& inputState)
{
	float currentSpeedX = 0.0f;
	const float leftBorder = owner.getGame().getPhysics().getLeftBorder();
	const float rightBorder = owner.getGame().getPhysics().getRightBorder();

	if (inputState.keyboard.getKeyState(leftKey) == ButtonState::Pressed && owner.getPosition().x <= leftBorder + offset)
	{
		owner.setPosition(Vector2(rightBorder - offset, owner.getPosition().y));
	}
	if (inputState.keyboard.getKeyState(rightKey) == ButtonState::Pressed && owner.getPosition().x >= rightBorder - offset)
	{
		owner.setPosition(Vector2(leftBorder + offset, owner.getPosition().y));
	}

	if (inputState.keyboard.getKeyState(leftKey) == ButtonState::Held && owner.getPosition().x > leftBorder + offset)
	{
		currentSpeedX -= maxSpeedX;
	}
	if (inputState.keyboard.getKeyState(rightKey) == ButtonState::Held && owner.getPosition().x < rightBorder - offset)
	{
		currentSpeedX += maxSpeedX;
	}
	setSpeedX(currentSpeedX);

	if(inputState.mouse.getButtonState(SDL_BUTTON_LEFT) == ButtonState::Pressed)
	{
		if(time <= 0){
			Fruit fruit = Game::fruits[rand() % Game::fruits.size()];
			CircleActor* circle = new CircleActor(owner.getPosition(), fruit);
			owner.getGame().getPhysics().setObjectVelocity(*circle->getMoveComponent(), Vector2(rand() % 5, 50.0f));
			owner.getGame().addCircle(circle);
			time = timeNextInput;
		}
	}
}

void ControllerInputComponent::setMaxSpeedX(float maxSpeedXP)
{
	maxSpeedX = maxSpeedXP;
}

void ControllerInputComponent::setLeftKey(SDL_Scancode key)
{
	leftKey = key;
}

void ControllerInputComponent::setRightKey(SDL_Scancode key)
{
	rightKey = key;
}