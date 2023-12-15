#include "Ball.h"
#include "Maths.h"
#include "Window.h"
#include "Actor.h"
#include "Game.h"

Ball::Ball(float mSizeX, float mSizeY) : Actor()
{
	setSizeX(mSizeX);
	setSizeY(mSizeY);
	rc = new RectangleComponent(this, mSizeX, mSizeY);
	mc = new MoveBall(this);
	mc->setForwardSpeed(500.0f);
	mc->setUpwardSpeed(500.0f);
	mc->setAngularSpeed(0.0f);
	rcc = new RectangleCollisionComponent(this);
}

void Ball::updateActor(float dt)
{
	auto paddle = getGame().getPaddle();
	if (Intersect(*rcc, paddle->getCollision()))
	{
		if(rcc->getPosition().y + rcc->getSizeY() - 10 < paddle->getPosition().y)
		{
			if (mc->getUpwardSpeed() < 0) {
				mc->setUpwardSpeed(-mc->getUpwardSpeed());
			}
		}
	}
}
