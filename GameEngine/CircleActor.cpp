#include "Actor.h"
#include "Assets.h"
#include "CircleActor.h"
#include "CircleMoveComponent.h"
#include "Fruit.h"
#include "Vector2.h"
#include "Game.h"

CircleActor::CircleActor(Vector2 positionP, const Fruit& fruitP) :
	Actor(),
	moveComponent(nullptr),
	spriteComponent(nullptr)
{
	fruit = fruitP;
	radius = fruit.getRadius();
	setPosition(positionP);
	moveComponent = new CircleMoveComponent(this, radius);
	spriteComponent = new SpriteComponent(this, Assets::getTexture(fruit.getName()), 100);
	getGame().getPhysics().addCircle(moveComponent);
}

CircleActor::~CircleActor(){}