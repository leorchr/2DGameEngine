#include "Actor.h"
#include "Component.h"
#include "UIMovementComponent.h"
#include <SDL_timer.h>

UIMovementComponent::UIMovementComponent(Actor* ownerP)
	: Component(ownerP)
{
	basePosition = getOwner().getPosition();
}

void UIMovementComponent::update(float dt)
{
	float time = SDL_GetTicks() / 400.0f;
	getOwner().setPosition(basePosition + Vector2(0, sin(time) * 20));
}