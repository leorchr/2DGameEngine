#include "Boids.h"
#include "Assets.h"
#include "Vector2.h"
#include <cstdlib>

Boids::Boids() :
    Actor(),
    sprite(nullptr),
    moveComponent(nullptr),
    size(0)
{
    sprite = new SpriteComponent(this, Assets::getTexture("Pineapple"), 101);
    size = Assets::getTexture("Pineapple").getWidth();
    moveComponent = new BoidsMoveComponent(this);
    moveComponent->setSpeedX(50);
    moveComponent->setSpeedY(50);    
}

void Boids::updateActor(float dt)
{
    
}

