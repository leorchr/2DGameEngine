#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Rectangle.h"

class RectangleComponent : public Component
{
public:
	RectangleComponent(Actor* ownerP, float width, float height);
	virtual ~RectangleComponent();
	RectangleComponent() = delete;
	RectangleComponent(const RectangleComponent&) = delete;
	RectangleComponent& operator=(const RectangleComponent&) = delete;

	virtual void draw(Renderer& renderer);

protected:
	Rectangle rectangle;
};