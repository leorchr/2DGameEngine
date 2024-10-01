#include "Boids.h"
#include "Assets.h"
#include "Vector2.h"
#include <cstdlib>

Boids::Boids(Group groupP, float preyFactor) :
    Actor(),
    sprite(nullptr),
    moveComponent(nullptr),
    group(groupP),
    preyFactor(preyFactor)
{
    switch(group)
    {
    case Group::RED :
        sprite = new SpriteComponent(this, Assets::getTexture("RedFish"), 101);
        break;
    case Group::GREEN :
        sprite = new SpriteComponent(this, Assets::getTexture("GreenFish"), 101);
        break;
    case Group::BLUE :
        sprite = new SpriteComponent(this, Assets::getTexture("BlueFish"), 101);
    }
    moveComponent = new BoidsMoveComponent(this, 10,Vector2(1,1), 400,30,0.6f, 100, 0.3f, 50, 0.05f, 0.5f, 200, 1.0f, group, 5, preyFactor, 30);

}

void Boids::updateActor(float dt)
{
}

