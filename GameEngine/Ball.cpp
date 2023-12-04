#include "Ball.h"
#include "Maths.h"
#include "Window.h"
#include "Actor.h"

Ball::Ball(float mSizeX, float mSizeY) : Actor()
{
	setSizeX(mSizeX);
	setSizeY(mSizeY);
	rc = new RectangleComponent(this, mSizeX, mSizeY);
	mc = new MoveBall(this);
	mc->setForwardSpeed(500.0f);
	mc->setUpwardSpeed(500.0f);
	mc->setAngularSpeed(0.0f);
}

void Ball::updateActor(float dt)
{
}
