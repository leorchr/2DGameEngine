#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "BoidsMoveComponent.h"

enum Group{ RED, GREEN, BLUE };

struct Parameters
{
    const Vector2 direction = Vector2(1,1);
    const int speed = 400;
    const float maxSteerValue = 0.5f;
    const int separationDist = 30;
    const float separationFactor = 0.6f;
    const int maxPerceiveDistance = 100;
    const float alignementFactor = 0.3f;
    const int cohesionRadius = 50;
    const float groupementFactor = 0.05f;
    const int eatRange = 5;
    const int preyRange = 100;
    const int mouseRange = 200;
    const float mouseImpact = 1.0f;
    const bool shouldBait = true;
};

class Boids : public Actor
{
public:
    
     Boids(Group group);
    static Parameters parameters;
    BoidsMoveComponent* getBoidsMoveComponent() const { return moveComponent;}
    
private:
    
    SpriteComponent* sprite;
    BoidsMoveComponent* moveComponent;
    Group group;
    float preyFactor;
    
};

