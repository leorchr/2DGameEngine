#include "BoidsMoveComponent.h"
#include "Actor.h"
#include "Boids.h"
#include "Game.h"
#include "Maths.h"
#include "Vector2.h"
#include "Window.h"

BoidsMoveComponent::BoidsMoveComponent(Actor* ownerP, int updateOrderP, Vector2 forward, int speed,
                                       float maxSteerValue, int separationDist, float separationFactor, int maxPerceiveDistance,
                                       float alignementFactor, int cohesionRadius, float groupementFactor, int eatRange,
                                       int preyRange, int mouseRange, float mouseImpact, bool shouldBait, float preyFactor, Group groupName)
	: Component(ownerP, updateOrderP),
	forward(forward),
	speed(speed),
	maxSteerValue(maxSteerValue),
	separationDist(separationDist),
	separationFactor(separationFactor),
	maxPerceiveDistance(maxPerceiveDistance),
	alignementFactor(alignementFactor),
	cohesionRadius(cohesionRadius),
	groupementFactor(groupementFactor),
	eatRange(eatRange),
	preyRange(preyRange),
	mouseRange(mouseRange),
	mouseImpact(mouseImpact),
	shouldBait(shouldBait),
	preyFactor(preyFactor),
	groupName(groupName)
{

}
void BoidsMoveComponent::update(float dt)
{
	vector<BoidsMoveComponent*> others = Game::instance().getBoids();
	
	Vector2 separationValue = Vector2::zero;
	int separationSum = 0;
	Vector2 alignementValue = Vector2::zero;
	int alignementSum = 0;
	Vector2 groupementValue = Vector2::zero;
	int groupementSum = 0;
	
	for(int i = 0; i < others.size(); i++)
	{
		if(others[i]->owner.getId() == owner.getId()) continue;
		if(groupName != others[i]->getGroupName()) continue;
		
		Vector2 separationTemp = separate(others[i]);
		if(separationTemp.x != Vector2::zero.x && separationTemp.y != Vector2::zero.y)
		{
			separationValue += separationTemp;
			separationSum++;
		}
		Vector2 alignementTemp = align(others[i]);
		if(alignementTemp.x != Vector2::zero.x && alignementTemp.y != Vector2::zero.y)
		{
			alignementValue += alignementTemp;
			alignementSum++;
		}
		Vector2 groupementTemp = group(others[i]);
		if(groupementTemp.x != Vector2::zero.x && groupementTemp.y != Vector2::zero.y)
		{
			groupementValue += groupementTemp;
			groupementSum++;
		}
	}
	
	if(separationSum != 0) separationValue /= separationSum;
	if(alignementSum != 0) alignementValue /= alignementSum;
	if(groupementSum != 0) groupementValue /= groupementSum;
	
	Vector2 separation = separationValue;
	Vector2 obstacle = obstacles(Game::instance().getObstacles());
	Vector2 alignement = alignementValue;
	Vector2 groupement = groupementValue;
	Vector2 prey = eat(Game::instance().getBoids());
	Vector2 mouse = bait();

	Vector2 dir = forward;
	dir+=separation * separationFactor;
	dir+= obstacle * separationFactor;
	dir+=alignement * alignementFactor;
	dir+=groupement * groupementFactor;
	dir+=mouse * mouseImpact;
	dir+=prey * preyFactor;

	dir.normalize();
	forward += handleSteer(forward,dir);
	owner.setRotation(Maths::atan2(forward.y,-forward.x));
	
	if (!Maths::nearZero(forward.x))
	{
		Vector2 newPosition = Vector2(owner.getPosition().x + forward.x * (dt * speed),owner.getPosition().y);
		owner.setPosition(newPosition);
	}

	if (!Maths::nearZero(forward.y))
	{
		Vector2 newPosition = Vector2(owner.getPosition().x,owner.getPosition().y + forward.y * (dt * speed));
		owner.setPosition(newPosition);
	}
}

Vector2 BoidsMoveComponent::separate(BoidsMoveComponent* other)
{
	Vector2 posBoid = other->getOwner().getPosition() + other->getOwner().getSize()/2;
	Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
	Vector2 distVector2 = posSelf - posBoid;
		
	float dist = distVector2.length();
	if(dist < separationDist)
	{
		distVector2.normalize();
		return distVector2;
	}
	else return Vector2::zero;
}

Vector2 BoidsMoveComponent::obstacles(vector<RectangleComponent*> others)
{
	Vector2 sum{0.0f,0.0f};
	int count = 0;
	
	int rightWallDist = WINDOW_WIDTH - owner.getPosition().x;
	if(rightWallDist < separationDist)
	{
		sum+= Vector2(-1,0);
		count++;
	}
	int bottomWallDist = WINDOW_HEIGHT - owner.getPosition().y;
	if(bottomWallDist < separationDist)
	{
		sum+= Vector2(0,-1);
		count++;
	}
	
	int leftWallDist = owner.getPosition().x;
	if(leftWallDist < separationDist)
	{
		sum+= Vector2(1,0);
		count++;
	}
	
	int topWallDist = owner.getPosition().y;
	if(topWallDist < separationDist)
	{
		sum+= Vector2(0,1);
		count++;
	}
	return count > 0 ? sum/count : Vector2(0.0f,0.0f);
}

Vector2 BoidsMoveComponent::align(BoidsMoveComponent* other)
{
	Vector2 posBoid = other->getOwner().getPosition() + other->getOwner().getSize()/2;
	Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
	Vector2 distVector2 = posSelf - posBoid;
				
	float dist = distVector2.length();
	if(dist < maxPerceiveDistance)
	{
		return other->getForward();
	}
	else return Vector2::zero;
}

Vector2 BoidsMoveComponent::group(BoidsMoveComponent* other)
{
	Vector2 posBoid = other->getOwner().getPosition() + other->getOwner().getSize()/2;
	Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
	Vector2 distVector2 = posSelf - posBoid;
				
	float dist = distVector2.length();
	if(dist < cohesionRadius)
	{
		Vector2 dirResult = owner.getPosition() + owner.getSize()/2 - other->getOwner().getPosition();
		dirResult.normalize();
		return dirResult;
	}
	else return Vector2::zero;	
}

Vector2 BoidsMoveComponent::handleSteer(Vector2& oldValue, Vector2& newValue)
{
	return (newValue - oldValue) * maxSteerValue;
}

Vector2 BoidsMoveComponent::bait()
{
	int mouseX,mouseY;
	SDL_GetGlobalMouseState(&mouseX,&mouseY);
	Vector2 dist = Vector2(mouseX,mouseY) - owner.getPosition();
	if(dist.length() < mouseRange)
	{
		int b = 0;
		shouldBait ? b = 1 : b = -1;
		dist.normalize();
		dist = Vector2(dist.x*b,dist.y*b);
		return dist;
	}
	else
	{
		return Vector2::zero;
	}
}

Vector2 BoidsMoveComponent::eat(vector<BoidsMoveComponent*> others)
{
	size_t length = others.size();
	Vector2 sum{0.0f,0.0f};
	int count = 0;
	for(int i = 0; i < length; i++)
	{
		if(others[i]->owner.getId() == owner.getId())
		{
			continue;
		}
		
		Vector2 posBoid = others[i]->getOwner().getPosition() + others[i]->getOwner().getSize()/2;
		Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
		Vector2 distVector2 = posSelf - posBoid;
		float dist = distVector2.length();
		if(dist < preyRange)
		{
			distVector2.normalize();
			
			if(groupName == Group::RED && others[i]->getGroupName() == Group::GREEN)
			{
				sum-=distVector2;
				count++;
			}
			if(groupName == Group::GREEN && others[i]->getGroupName() == Group::BLUE)
			{
				sum-=distVector2;
				count++;
			}
			if(groupName == Group::BLUE && others[i]->getGroupName() == Group::RED)
			{
				sum-=distVector2;
				count++;
			}
		}

		
		if(dist < eatRange)
		{
			if(groupName == Group::RED && others[i]->getGroupName() == Group::GREEN)
			{
				others[i]->setGroup();
			}
			if(groupName == Group::GREEN && others[i]->getGroupName() == Group::BLUE)
			{
				others[i]->setGroup();
			}
			if(groupName == Group::BLUE && others[i]->getGroupName() == Group::RED)
			{
				others[i]->setGroup();
			}
		}
	}
	return count > 0 ? sum/count : Vector2(0.0f,0.0f);
}

void BoidsMoveComponent::setGroup()
{
	switch (groupName)
	{
	case Group::RED:
		groupName = Group::BLUE;
		preyFactor = 1.0f;
		break;
	case Group::GREEN:
		groupName = Group::RED;
		preyFactor = 0.1f;
		break;
	case Group::BLUE:
		groupName = Group::GREEN;
		preyFactor = 0.5f;
		break;
	}
	auto actor = static_cast<Boids*>(&owner);
	actor->setGroup(groupName);
}
