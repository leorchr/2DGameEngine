#include "ControllerActor.h"
#include "Window.h"
#include "Assets.h"

ControllerActor::ControllerActor(float speedXP, float offsetP) :
	Actor(),
	speedX(speedXP),
	moveComponent(nullptr),
	inputComponent(nullptr),
	spriteComponent(nullptr)
{
	setPosition(Vector2(WINDOW_WIDTH/2, 80.0f));
	moveComponent = new ControllerMoveComponent(this);
	inputComponent = new ControllerInputComponent(this, speedXP, offsetP);
	spriteComponent = new SpriteComponent(this, Assets::getTexture("Cloud"), 100);
}

ControllerActor::~ControllerActor(){}