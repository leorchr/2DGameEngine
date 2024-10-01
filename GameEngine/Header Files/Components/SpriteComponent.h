#pragma once
#include "Actor.h"
#include "Component.h"
#include "Renderer.h"
#include "Texture.h"
#include "Vector2.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP = 100, Vector2 positionP = Vector2(Maths::infinity, Maths::infinity)); // Lower draw order: further back
	virtual ~SpriteComponent();
	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator=(const SpriteComponent&) = delete;

	virtual void setTexture(const Texture& textureP);
	virtual void draw(Renderer& renderer);

	int getDrawOrder() const { return drawOrder; }
	int getTexWidth() const { return texWidth; }
	int getTexHeight() const { return texHeight; }
	Vector2 getOriginX() const { return position; }
	Texture getTexture() const { return texture; }

protected:
	Texture texture;
	int drawOrder;
	int texWidth;
	int texHeight;
	Vector2 position;
};