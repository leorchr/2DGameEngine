#include "Actor.h"
#include "SpriteComponent.h"
#include "BoidsMoveComponent.h"
#pragma once

enum Group{ RED, GREEN, BLUE };

class Boids : public Actor
{
public:
    Boids(Group groupP, float preyFactor);

    void updateActor(float dt) override;
    BoidsMoveComponent* getBoidsMoveComponent() const { return moveComponent;}
private:
    SpriteComponent* sprite;
    BoidsMoveComponent* moveComponent;
    Group group;
    float preyFactor;
};

