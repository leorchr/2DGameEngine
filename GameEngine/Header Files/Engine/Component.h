#pragma once
#include "Actor.h"

class Actor;

class Component
{
public:
	Component(Actor* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }
	Actor& getOwner() const { return owner; }
	virtual void processInput(const struct InputState& inputState);
	virtual void update(float dt);

protected:
	Actor& owner;
	int updateOrder;		// Order of the component in the actor's updateComponent method
};