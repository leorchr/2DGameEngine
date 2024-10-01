#pragma once
#include "Component.h"

class BoidsMoveComponent : public Component
{
public:
	BoidsMoveComponent(Actor* ownerP, int updateOrderP, Vector2 forward, int speed, int separationDist,
	                   float separationFactor, int maxPerceiveDistance, float alignementFactor, int cohesionRadius,
	                   float groupementFactor, float maxSteerValue, int mouseRange, float mouseImpact, enum Group groupName); // By default, update before other components
	BoidsMoveComponent() = delete;
	BoidsMoveComponent(const BoidsMoveComponent&) = delete;
	BoidsMoveComponent& operator=(const BoidsMoveComponent&) = delete;

	void update(float dt) override;

	Vector2 separate(vector<BoidsMoveComponent*> others);
	Vector2 align(vector<BoidsMoveComponent*> others);
	Vector2 group(vector<BoidsMoveComponent*> others);
	Vector2 handleSteer(Vector2& oldValue, Vector2& newValue);
	Vector2 bait(int mouseX, int mouseY);

	Vector2 getForward(){ return forward; };
	Group getGroupName(){ return groupName; }


private:
	Vector2 forward;
	int speed;
	int separationDist;
	float separationFactor;
	int maxPerceiveDistance;
	float alignementFactor;
	int cohesionRadius;
	float groupementFactor;
	float maxSteerValue;
	int mouseRange;
	float mouseImpact;
	Group groupName;
};