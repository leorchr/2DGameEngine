#include "MoveBall.h"
#include "Maths.h"
#include "Actor.h"
#include "Game.h"
#include "Window.h"
#include "RectangleComponent.h"
#include <SDL_scancode.h>

MoveBall::MoveBall(Actor* ownerP) :
	MoveComponent(ownerP)
{
}

void MoveBall::update(float dt)
{
	//MoveComponent::update(dt);

	if (!Maths::nearZero(angularSpeed))
	{
		float newRotation = owner.getRotation() + angularSpeed * dt;
		owner.setRotation(newRotation);
	}

	if (!Maths::nearZero(forwardSpeed) && !Maths::nearZero(upwardSpeed))
	{

		if (owner.getPosition().x < 0) {
			setForwardSpeed(abs(getForwardSpeed()));
		}
		else if (owner.getPosition().x + owner.getSizeX() > WINDOW_WIDTH){
			setForwardSpeed(-abs(getForwardSpeed()));
		}

		if (owner.getPosition().y < 0) {
			setUpwardSpeed(-abs(getUpwardSpeed()));
		}
		else if (owner.getPosition().y + owner.getSizeY() > WINDOW_HEIGHT) {
			owner.getGame().getBall()->TouchScreenBottom();
		}

		Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt + owner.getUpward() * upwardSpeed * dt;
		owner.setPosition(newPosition);
	}
}

float MoveBall::getForwardSpeed()
{
	return forwardSpeed;
}

float MoveBall::getUpwardSpeed()
{
	return upwardSpeed;
}

