#include "Boids.h"
#include "Assets.h"
#include "Vector2.h"
#include <cstdlib>

Boids::Boids() :
    Actor(),
    sprite(nullptr),
    moveComponent(nullptr)
{
    sprite = new SpriteComponent(this, Assets::getTexture("WhiteFish"), 101);
    moveComponent = new BoidsMoveComponent(this, 10,Vector2(1,1), 1200,30,0.6f, 100, 0.3f, 50, 0.05f, 0.5f);
}

void Boids::updateActor(float dt)
{
    
}

