#pragma once
#include "Actor.h"
#include "Rectangle.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Window.h"
#include <SDL.h>

class Renderer
{
public:
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

	Renderer();
	~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initialize(Window& window);

	void beginDraw();
	void draw();
	void endDraw();

	void drawRect(const Rectangle& rect) const;
	void drawCircle(Vector2 positionP, float radiusP, Vector3 colorP) const;
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void addCircle(class CircleComponent* circle);
	void removeCircle(class CircleComponent* circle);
	void drawSprites();
	void drawCircles();
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

	SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
	void close();

private:
	SDL_Renderer* SDLRenderer = nullptr;
	std::vector<SpriteComponent*> sprites;
	std::vector<CircleComponent*> circles;
};