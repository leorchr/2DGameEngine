#include "CircleActor.h"
#include "CircleComponent.h"
#include "CircleMoveComponent.h"
#include "Physics.h"
#include "Game.h"

CircleActor::CircleActor(Vector2 positionP, float radiusP, Vector3 colorP) :
	Actor(),
	circleComponent(nullptr),
	moveComponent(nullptr)
{
	radius = radiusP;
	setPosition(positionP);
	circleComponent = new CircleComponent(this, radiusP, colorP);
	moveComponent = new CircleMoveComponent(this);
	getGame().getPhysics().addCircle(this);
}

CircleActor::~CircleActor(){}
