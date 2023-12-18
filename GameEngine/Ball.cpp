#include "Ball.h"
#include "Maths.h"
#include "Window.h"
#include "Actor.h"
#include "Game.h"
#include <iostream>
using namespace std;

Ball::Ball(float mSizeX, float mSizeY) : Actor()
{
	setSizeX(mSizeX);
	setSizeY(mSizeY);
	//rc = new RectangleComponent(this, mSizeX, mSizeY);
	mc = new MoveBall(this);
	mc->setForwardSpeed(500.0f);
	mc->setUpwardSpeed(500.0f);
	mc->setAngularSpeed(0.0f);
	rcc = new RectangleCollisionComponent(this);

	getGame().setBall(this);
}

void Ball::updateActor(float dt)
{
	auto paddle = getGame().getPaddle();
	if (Intersect(*rcc, paddle->getCollision()))
	{
		if (positionLastFrame.y + rcc->getSizeY() <= paddle->getPosition().y)
		{
			mc->setUpwardSpeed(-mc->getUpwardSpeed());
		}
	}

	auto bricks = getGame().getBricks();
	if (bricks.size() <= 0)
	{
		cout << "GG WP" << endl;
		getGame().endGame();
	}
	for (auto brick : bricks)
	{
		if (Intersect(*rcc, brick->getCollision()))
		{
			if (positionLastFrame.y + rcc->getSizeY() <= brick->getPosition().y || positionLastFrame.y >= brick->getPosition().y + brick->getSizeY())
			{
				mc->setUpwardSpeed(-mc->getUpwardSpeed());
			}
			else {
				mc->setForwardSpeed(-mc->getForwardSpeed());
			}
			brick->setState(ActorState::Dead);
			break;
		}
	}
	positionLastFrame = rcc->getPosition();
}

void Ball::setLives(int livesP)
{
	lives = livesP;
}

void Ball::TouchScreenBottom()
{
	if (lives >= 1)
	{
		mc->setUpwardSpeed(abs(mc->getUpwardSpeed()));
		setPosition(Vector2{ 400,400 });
		lives--;
		cout << "Vies restantes : " << lives << endl;
	}
	else
	{
		getGame().endGame();
	}
}
