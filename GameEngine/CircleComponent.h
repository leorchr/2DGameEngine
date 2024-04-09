#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Renderer.h"

class CircleComponent : public Component
{
public:
	CircleComponent(Actor* ownerP, float radiusP, Vector3 colorP, int drawOrderP = 100); // Lower draw order: further back
	virtual ~CircleComponent();
	CircleComponent() = delete;
	CircleComponent(const CircleComponent&) = delete;
	CircleComponent& operator=(const CircleComponent&) = delete;

	virtual void draw(Renderer& renderer);
	int getDrawOrder() const { return drawOrder; }
	float getRadius() const { return radius; }

protected:
	int drawOrder;
	float radius;
	Vector3 color;
};