#include "Boids.h"
#include "Assets.h"
#include "Vector2.h"
#include <cstdlib>

#include "Random.h"

Parameters Boids::parameters;

Boids::Boids(Group group) :
    Actor(),
    sprite(nullptr),
    moveComponent(nullptr),
    group(group),
    preyFactor(0)
{
    switch(group)
    {
    case Group::RED :
        sprite = new SpriteComponent(this, Assets::getTexture("RedFish"), 101);
        preyFactor = 0.1f;
        break;
    case Group::GREEN :
        sprite = new SpriteComponent(this, Assets::getTexture("GreenFish"), 101);
        preyFactor = 0.5f;
        break;
    case Group::BLUE :
        sprite = new SpriteComponent(this, Assets::getTexture("BlueFish"), 101);
        preyFactor = 1.0f;
    }

    float nombre1 = 0;
    float nombre2 = 0;
    nombre1 = (float)rand() / (float)RAND_MAX;
    nombre2 = (float)rand() / (float)RAND_MAX;
    parameters.direction = Vector2(nombre1,nombre2);
    
    moveComponent = new BoidsMoveComponent(this, 10, parameters.direction,
        parameters.speed, parameters.maxSteerValue, parameters.separationDist, parameters.separationFactor,
        parameters.maxPerceiveDistance, parameters.alignementFactor, parameters.cohesionRadius, parameters.groupementFactor,
        parameters.eatRange, parameters.preyRange, parameters.mouseRange, parameters.mouseImpact, parameters.shouldBait, preyFactor, group);
}

void Boids::setGroup(enum Group groupName)
{
    switch (groupName)
    {
    case Group::RED:
        sprite->setTexture(Assets::getTexture("RedFish"));
        break;
    case Group::GREEN:
        sprite->setTexture(Assets::getTexture("GreenFish"));
        break;
    case Group::BLUE:
        sprite->setTexture(Assets::getTexture("BlueFish"));
        break;
    }
}

