#include "Brick.h"
#include "Game.h"

Brick::Brick(float mSizeX, float mSizeY) : Actor()
{
	setSizeX(mSizeX);
	setSizeY(mSizeY);
	rc = new RectangleComponent(this, mSizeX, mSizeY);
	rcc = new RectangleCollisionComponent(this);

	getGame().addBrick(this);
}

Brick::~Brick()
{
	getGame().removeBrick(this);
}

void Brick::updateActor(float dt)
{
}