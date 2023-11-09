#pragma once
#include "Component.h"

class Renderer;

class DrawCircleComponent : public Component
{
public:
	DrawCircleComponent(Actor* ownerP, int radiusP);
	virtual ~DrawCircleComponent() = default;
	DrawCircleComponent() = delete;
	DrawCircleComponent(const DrawCircleComponent&) = delete;
	DrawCircleComponent& operator=(const DrawCircleComponent&) = delete;

	virtual void draw(Renderer& renderer);

	int getRadius() const { return radius; }

private:

	int radius;

	void drawCircle(Renderer& renderer);
};

