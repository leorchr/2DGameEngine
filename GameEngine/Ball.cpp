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
	rc = new RectangleComponent(this, mSizeX, mSizeY);
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
		if(rcc->getPosition().y + rcc->getSizeY() - 10 < paddle->getPosition().y)
		{
			if (mc->getUpwardSpeed() < 0) {
				mc->setUpwardSpeed(-mc->getUpwardSpeed());
			}
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
			brick->setState(ActorState::Dead);

			if (rcc->getPosition().y + rcc->getSizeY() - 10 < paddle->getPosition().y)
			{
				if (mc->getUpwardSpeed() < 0) {
					mc->setUpwardSpeed(-mc->getUpwardSpeed());
				}
			}

			if (rcc->getPosition().y - 10 > paddle->getPosition().y + paddle->getSizeY())
			{
				if (mc->getUpwardSpeed() > 0) {
					mc->setUpwardSpeed(-mc->getUpwardSpeed());
				}
			}

			break;
		}
	}
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
