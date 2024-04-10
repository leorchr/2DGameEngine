#include "CircleActor.h"
#include "Game.h"

CircleActor::CircleActor(Vector2 positionP, float radiusP, Vector3 colorP) :
	Actor(),
	circleComponent(nullptr),
	moveComponent(nullptr)
{
	radius = radiusP;
	setPosition(positionP);
	circleComponent = new CircleComponent(this, radiusP, colorP);
	moveComponent = new CircleMoveComponent(this, radiusP);
	getGame().getPhysics().addCircle(moveComponent);
}

CircleActor::~CircleActor(){}
