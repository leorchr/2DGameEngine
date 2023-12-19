#include "Live.h"
#include "Game.h"

Live::Live(float mSizeX, float mSizeY) : Actor()
{
	setSizeX(mSizeX);
	setSizeY(mSizeY);
	getGame().addLive(this);
}

Live::~Live()
{
	getGame().removeLive(this);
}

void Live::updateActor(float dt)
{
}