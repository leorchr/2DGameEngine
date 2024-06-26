#pragma once
#include "Actor.h"
#include "ControllerMoveComponent.h"
#include "InputSystem.h"
#include <SDL_scancode.h>

class ControllerInputComponent : public ControllerMoveComponent
{
public:
	ControllerInputComponent(Actor* ownerP, float speedXP, float offsetP, float timeNextInputP);
	ControllerInputComponent() = delete;
	ControllerInputComponent(const ControllerInputComponent&) = delete;
	ControllerInputComponent& operator=(const ControllerInputComponent&) = delete;

	void update(float dt) override;

	void processInput(const struct InputState& inputState);

	void setMaxSpeedX(float speedXP);
	void setLeftKey(SDL_Scancode key);
	void setRightKey(SDL_Scancode key);
	void setArrowLeftKey(SDL_Scancode key);
	void setArrowRightKey(SDL_Scancode key);


private:
	float maxSpeedX;
	float offset;
	float time;
	float timeNextInput;
	SDL_Scancode leftKey;
	SDL_Scancode rightKey;
	SDL_Scancode arrowLeftKey;
	SDL_Scancode arrowRightKey;
};