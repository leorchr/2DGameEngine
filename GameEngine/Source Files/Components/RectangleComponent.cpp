#include "Actor.h"
#include "RectangleComponent.h"
#include "Component.h"
#include "Renderer.h"
#include "Vector3.h"
#include "Game.h"

RectangleComponent::RectangleComponent(Actor* ownerP, float xP, float yP, float widthP, float heightP, Vector3 colorP, int drawOrderP) :
    Component(ownerP),
    rect(Rectangle(xP,yP, widthP, heightP)),
    color(colorP),
    drawOrder(drawOrderP)
{
    owner.getGame().getRenderer().addRectangle(this);
}

void RectangleComponent::draw(Renderer& renderer)
{
    renderer.drawRect(rect, color);
}

RectangleComponent::~RectangleComponent()
{
    owner.getGame().getRenderer().removeRectangle(this);
}