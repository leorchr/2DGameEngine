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

	if (!Maths::nearZero(forwardSpeed))
	{
		Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt;
		owner.setPosition(newPosition);
	}
	if (!Maths::nearZero(upwardSpeed))
	{
		Vector2 newPosition = owner.getPosition() + owner.getUpward() * upwardSpeed * dt;
		owner.setPosition(newPosition);
	}	
}