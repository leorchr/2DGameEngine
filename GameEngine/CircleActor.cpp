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

	getGame().getPhysics().setObjectVelocity(*moveComponent, Vector2(0.0f,500.0f)/*50.0f * Vector2(cos(50.0f), sin(50.0f))*/);
}

CircleActor::~CircleActor(){}
