#include <vector>
#include "Ball.h"
#include "Maths.h"
#include "Window.h"
#include "Actor.h"
#include "Game.h"
#include "Live.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

Ball::Ball(float mSizeX, float mSizeY) : Actor()
{
	setSizeX(mSizeX);
	setSizeY(mSizeY);
	//rc = new RectangleComponent(this, mSizeX, mSizeY);
	baseForwardSpeed = 500;
	mc = new MoveBall(this);
	mc->setForwardSpeed(baseForwardSpeed);
	mc->setUpwardSpeed(500.0f);
	mc->setAngularSpeed(0.0f);
	rcc = new RectangleCollisionComponent(this);

	getGame().setBall(this);
	srand(time(NULL));
}

void Ball::updateActor(float dt)
{
	auto paddle = getGame().getPaddle();
	if (Intersect(*rcc, paddle->getCollision()))
	{
		if (positionLastFrame.y + rcc->getSizeY() <= paddle->getPosition().y)
		{
			mc->setUpwardSpeed(-mc->getUpwardSpeed());

			int randSpeed = rand() % 150 + (baseForwardSpeed-150);
			if (mc->getForwardSpeed() > 0) {
				mc->setForwardSpeed(randSpeed);
			}
			else {
				mc->setForwardSpeed(-randSpeed);
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
		if (getGame().getLives().size() != 0) {
			auto visualLives = getGame().getLives();
			visualLives.back()->setState((ActorState::Dead));
		}
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
