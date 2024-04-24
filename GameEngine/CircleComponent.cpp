#include "Actor.h"
#include "CircleComponent.h"
#include "Component.h"
#include "Renderer.h"
#include "Vector3.h"
#include "Game.h"

CircleComponent::CircleComponent(Actor* ownerP, float radiusP, Vector3 colorP, int drawOrderP) :
	Component(ownerP),
	radius(radiusP),
	drawOrder(drawOrderP),
	color(colorP)
{
	owner.getGame().getRenderer().addCircle(this);
}

void CircleComponent::draw(Renderer& renderer)
{
	renderer.drawCircle(owner.getPosition(), radius, color);
}

CircleComponent::~CircleComponent()
{
	owner.getGame().getRenderer().removeCircle(this);
}