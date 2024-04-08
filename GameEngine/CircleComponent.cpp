#include "CircleComponent.h"
#include "Actor.h"
#include "Game.h"

CircleComponent::CircleComponent(Actor* ownerP, float radiusP, int drawOrderP) :
	Component(ownerP),
	radius(radiusP),
	drawOrder(drawOrderP)
{
	owner.getGame().getRenderer().addCircle(this);
}

void CircleComponent::draw(Renderer& renderer)
{
	renderer.drawCircle(owner.getPosition(), radius);
}

CircleComponent::~CircleComponent()
{
	owner.getGame().getRenderer().removeCircle(this);
}