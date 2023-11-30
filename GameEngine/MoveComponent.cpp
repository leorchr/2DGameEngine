#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

#include <iostream>
using namespace std;

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), forwardSpeed(0.0f), upwardSpeed(0.0f), angularSpeed(0.0f)
{
}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::setUpwardSpeed(float upwardSpeedP)
{
	upwardSpeed = upwardSpeedP;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::update(float dt)
{
	if (!Maths::nearZero(angularSpeed))
	{
		float newRotation = owner.getRotation() + angularSpeed * dt;
		owner.setRotation(newRotation);
	}
	//cout << " Forward : " << owner.getForward().x << " , " << owner.getForward().y << endl;
	//cout << " Upward : " << owner.getUpward().x << " , " << owner.getUpward().y << endl;

	if (!Maths::nearZero(forwardSpeed) && !Maths::nearZero(upwardSpeed))
	{
		Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt + owner.getUpward() * upwardSpeed * dt;


		// Screen wrapping (for asteroids)
		if (newPosition.x < 0) { forwardSpeed = -forwardSpeed; }
		else if (newPosition.x > WINDOW_WIDTH) { forwardSpeed = -forwardSpeed; }
		if (newPosition.y < 0) { upwardSpeed = -upwardSpeed; }
		else if (newPosition.y > WINDOW_HEIGHT) { upwardSpeed = -upwardSpeed; }

		owner.setPosition(newPosition);
	}
}