#include "Actor.h"
#include "Assets.h"
#include "ControllerActor.h"
#include "ControllerInputComponent.h"
#include "ControllerMoveComponent.h"
#include "SpriteComponent.h"
#include "Vector2.h"
#include "Window.h"

ControllerActor::ControllerActor(float speedXP, float offsetP) :
	Actor(),
	speedX(speedXP),
	moveComponent(nullptr),
	inputComponent(nullptr),
	spriteComponent(nullptr)
{
	setPosition(Vector2(WINDOW_WIDTH/2, 80.0f));
	moveComponent = new ControllerMoveComponent(this);
	inputComponent = new ControllerInputComponent(this, speedXP, offsetP, 0.5f);
	spriteComponent = new SpriteComponent(this, Assets::getTexture("Cloud"), 101);
}

ControllerActor::~ControllerActor(){}