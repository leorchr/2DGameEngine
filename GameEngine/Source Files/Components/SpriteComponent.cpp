#include "Actor.h"
#include "Component.h"
#include "Game.h"
#include "Rectangle.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Vector2.h"

SpriteComponent::SpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP, Vector2 positionP) :
	Component(ownerP),
	texture(textureP),
	drawOrder(drawOrderP),
	texWidth(textureP.getWidth()),
	texHeight(textureP.getHeight()),
	position(positionP)
{
	owner.getGame().getRenderer().addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	owner.getGame().getRenderer().removeSprite(this);
}

void SpriteComponent::setTexture(const Texture& textureP)
{
	texture = textureP;
	texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw(Renderer& renderer)
{
	Vector2 origin = Vector2::zero;
	if (position.x != Maths::infinity && position.y != Maths::infinity) origin = position;
	else origin = Vector2{ texWidth / 2.f, texHeight / 2.f };
	renderer.drawSprite(owner, texture, Rectangle::nullRect, origin, Renderer::Flip::None);
}