#include "RectangleComponent.h"
#include "Actor.h"
#include "Game.h"

RectangleComponent::RectangleComponent(Actor* ownerP, float width, float height) :
	Component(ownerP),
	rectangle {Rectangle{ 0,0,width,height }}
{
	owner.getGame().getRenderer().addRectangle(this);
}

RectangleComponent::~RectangleComponent()
{
	owner.getGame().getRenderer().removeRectangle(this);
}

void RectangleComponent::draw(Renderer& renderer)
{
	Rectangle rect = Rectangle{ owner.getPosition().x, owner.getPosition().y, rectangle.width, rectangle.height };
	renderer.drawRectangle(rect);
}