#pragma once
#include "Actor.h"
#include "ControllerMoveComponent.h"
#include "ControllerInputComponent.h"
#include "SpriteComponent.h"

class ControllerActor : public Actor
{
public:
	ControllerActor(float speedXP);
	~ControllerActor();

private:
	class ControllerMoveComponent* moveComponent;
	class ControllerInputComponent* inputComponent;
	class SpriteComponent* spriteComponent;
	float speedX;
};