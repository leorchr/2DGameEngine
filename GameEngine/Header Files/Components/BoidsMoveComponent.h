#pragma once
#include "Component.h"

class BoidsMoveComponent : public Component
{
public:
	BoidsMoveComponent(Actor* ownerP, int updateOrderP, Vector2 forward, int speed,
		 float maxSteerValue, int separationDist, float separationFactor, int maxPerceiveDistance,
		 float alignementFactor, int cohesionRadius, float groupementFactor, int eatRange,
		 int preyRange, int mouseRange, float mouseImpact, bool shouldBait, float preyFactor, enum Group groupName);
	BoidsMoveComponent() = delete;
	BoidsMoveComponent(const BoidsMoveComponent&) = delete;
	BoidsMoveComponent& operator=(const BoidsMoveComponent&) = delete;

	void update(float dt) override;

	Vector2 separate(vector<BoidsMoveComponent*> others);
	Vector2 align(vector<BoidsMoveComponent*> others);
	Vector2 group(vector<BoidsMoveComponent*> others);
	Vector2 handleSteer(Vector2& oldValue, Vector2& newValue);
	Vector2 bait(int mouseX, int mouseY);
	Vector2 eat(vector<BoidsMoveComponent*> others);

	Vector2 getForward(){ return forward; }
	Group getGroupName(){ return groupName; }


private:
	Vector2 forward;
	int speed;
	float maxSteerValue;
	int separationDist;
	float separationFactor;
	int maxPerceiveDistance;
	float alignementFactor;
	int cohesionRadius;
	float groupementFactor;
	int eatRange;
	int preyRange;
	int mouseRange;
	float mouseImpact;
	bool shouldBait;
	float preyFactor;
	Group groupName;
};