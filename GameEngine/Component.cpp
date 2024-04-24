#include "Actor.h"
#include "Component.h"

Component::Component(Actor* ownerP, int updateOrderP) :
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::processInput(const struct InputState& inputState)
{
}

void Component::update(float dt)
{
}