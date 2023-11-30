#include "Ball.h"
#include "RectangleComponent.h"
#include "MoveComponent.h"
#include "Maths.h"

Ball::Ball() : Actor()
{
	RectangleComponent* rc = new RectangleComponent(this, 50, 50);
	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(500.0f);
	mc->setUpwardSpeed(500.0f);
	mc->setAngularSpeed(0.0f);
}

void Ball::updateActor(float dt)
{
}