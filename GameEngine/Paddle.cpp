#include "Paddle.h"
#include "Maths.h"
#include "Window.h"
#include "Actor.h"
#include "Game.h"

#include <iostream>
using namespace std;

Paddle::Paddle(float mSizeX, float mSizeY) : Actor()
{
	setSizeX(mSizeX);
	setSizeY(mSizeY);
	rc = new RectangleComponent(this, mSizeX, mSizeY);
	ic = new InputPaddle(this);
	ic->setMaxForwardSpeed(500.0f);
	ic->setMaxAngularSpeed(0);
	rcc = new RectangleCollisionComponent(this);

	getGame().setPaddle(this);
}

void Paddle::updateActor(float dt)
{
	//cout << ic->getForwardSpeed() << endl;
}
