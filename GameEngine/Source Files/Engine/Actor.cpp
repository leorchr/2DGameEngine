#include "Actor.h"
#include "Component.h"
#include "Game.h"
#include "InputSystem.h"
#include "Maths.h"
#include "Vector2.h"
#include <stdlib.h>

int Actor::ActorsCreated = 0;

Actor::Actor() :
	game(Game::instance()),
	state(Actor::ActorState::Active),
	position(Vector2::zero),
	scale(1.0f),
	rotation(0.0f),
	id(0),
	size(0)
{
	game.addActor(this);
	id = ActorsCreated;
	ActorsCreated++;
}

Actor::~Actor()
{
	game.removeActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::setPosition(Vector2 positionP)
{
	position = positionP;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
}

void Actor::setRotation(float rotationP)
{
	rotation = rotationP;
}

void Actor::setId(int id)
{
	this->id = id;
}

void Actor::setSize(int size)
{
	this->size = size;
}

void Actor::setState(ActorState stateP)
{
	state = stateP;
}

Vector2 Actor::getForward() const
{
	return Vector2(Maths::cos(rotation), -Maths::sin(rotation));
}

void Actor::processInput(const struct InputState& inputState)
{
	if (state == Actor::ActorState::Active)
	{
		for (auto component : components)
		{
			component->processInput(inputState);
		}
		actorInput(inputState);
	}
}

void Actor::actorInput(const struct InputState& inputState)
{
}

void Actor::update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		updateComponents(dt);
		updateActor(dt);
	}
}

void Actor::updateComponents(float dt)
{
	for (auto component : components)
	{
		component->update(dt);
	}
}

void Actor::updateActor(float dt)
{
}

void Actor::addComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}