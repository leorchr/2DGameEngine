#pragma once
#include "Actor.h"
#include "Component.h"
#include "Renderer.h"
#include "Vector3.h"

class RectangleComponent : public Component
{
public:
    RectangleComponent(Actor* ownerP, float xP, float yP, float widthP, float heightP, Vector3 colorP, int drawOrderP = 100); // Lower draw order: further back
    virtual ~RectangleComponent();
    RectangleComponent() = delete;
    RectangleComponent(const RectangleComponent&) = delete;
    RectangleComponent& operator=(const RectangleComponent&) = delete;

    virtual void draw(Renderer& renderer);
    int getDrawOrder() const { return drawOrder; }
    Rectangle getRect() const { return rect;}
    

protected:
    Rectangle rect;
    Vector3 color;
    int drawOrder;
};