#pragma once
#include "Actor.h"
#include "ControllerInputComponent.h"
#include "ControllerMoveComponent.h"
#include "SpriteComponent.h"

class ControllerActor : public Actor
{
public:
	ControllerActor(float speedXP, float offsetP);
	~ControllerActor();

private:
	class ControllerMoveComponent* moveComponent;
	class ControllerInputComponent* inputComponent;
	class SpriteComponent* spriteComponent;
	class SpriteComponent* spriteComponent2;
	float speedX;
};