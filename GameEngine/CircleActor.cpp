#include "CircleActor.h"
#include "CircleComponent.h"
#include "CircleMoveComponent.h"

CircleActor::CircleActor(Vector2 positionP, float radiusP, Vector3 colorP) :
	Actor(),
	circleComponent(nullptr),
	moveComponent(nullptr)
{
	setPosition(positionP);
	circleComponent = new CircleComponent(this, radiusP, colorP);
	moveComponent = new CircleMoveComponent(this);
}

CircleActor::~CircleActor(){}
