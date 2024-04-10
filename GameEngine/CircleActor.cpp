#include "CircleActor.h"
#include "Game.h"

CircleActor::CircleActor(Vector2 positionP, const Fruit& fruitP) :
	Actor(),
	circleComponent(nullptr),
	moveComponent(nullptr)
{
	fruit = fruitP;
	radius = fruit.getRadius();
	setPosition(positionP);
	circleComponent = new CircleComponent(this, fruit.getRadius(), fruit.getColor());
	moveComponent = new CircleMoveComponent(this, radius);
	getGame().getPhysics().addCircle(moveComponent);
}

CircleActor::~CircleActor(){}