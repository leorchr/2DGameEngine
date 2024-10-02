#pragma once
#include "Component.h"
#include "RectangleComponent.h"

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

	Vector2 separate(BoidsMoveComponent* other);
	Vector2 obstacles(vector<RectangleComponent*> others);
	Vector2 align(BoidsMoveComponent* other);
	Vector2 group(BoidsMoveComponent* other);
	Vector2 handleSteer(Vector2& oldValue, Vector2& newValue);
	Vector2 bait();
	Vector2 eat(vector<BoidsMoveComponent*> others);

	void setGroup();

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
