#include "Actor.h"
#include "SpriteComponent.h"
#include "BoidsMoveComponent.h"
#pragma once

class Boids : public Actor
{
public:
    Boids();

    void updateActor(float dt) override;
    int getSize() const { return size; }
    BoidsMoveComponent* getBoidsMoveComponent() const { return moveComponent;}
private:
    SpriteComponent* sprite;
    BoidsMoveComponent* moveComponent;
    int size;
};
