#include "Actor.h"
#include "SpriteComponent.h"
#include "BoidsMoveComponent.h"
#pragma once

class Boids : public Actor
{
public:
    Boids();

    void updateActor(float dt) override;
    BoidsMoveComponent* getBoidsMoveComponent() const { return moveComponent;}
private:
    SpriteComponent* sprite;
    BoidsMoveComponent* moveComponent;
    float time;
};
