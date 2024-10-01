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
	Vector2 separation = separate(Game::instance().getBoids());
	Vector2 alignement = align(Game::instance().getBoids());
	Vector2 groupement = group(Game::instance().getBoids());
	Vector2 prey = eat(Game::instance().getBoids());
	
	int mouseX,mouseY;
	SDL_GetGlobalMouseState(&mouseX,&mouseY);
	Vector2 mouse = bait(mouseX,mouseY);

	Vector2 dir = forward;
	
	if(separation.length()!=0)separation.normalize();
	dir+=separation * separationFactor;
	dir+=alignement * alignementFactor;
	dir+=groupement * groupementFactor;
	dir+=mouse * mouseImpact;
	dir+=prey * preyFactor;

	dir.normalize();
	
	forward += handleSteer(forward,dir);
	
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
	
	getOwner().setRotation(Maths::atan2(forward.y,-forward.x));
}

Vector2 BoidsMoveComponent::separate(vector<BoidsMoveComponent*> others)
{
	size_t length = others.size();
	Vector2 sum{0.0f,0.0f};
	int count = 0;
	
	int rightWallDist = WINDOW_WIDTH - owner.getPosition().x - owner.getSize()/2;
	if(rightWallDist < separationDist)
	{
	sum+= Vector2(-1,0);
	 	count++;
	}
	int bottomWallDist = WINDOW_HEIGHT - owner.getPosition().y - owner.getSize()/2;
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
	
	
	for(int i = 0; i < length; i++)
	{
		if(others[i]->owner.getId() == owner.getId())
		{
			continue;
		}
		if(groupName != others[i]->getGroupName()) continue;
		Vector2 posBoid = others[i]->getOwner().getPosition() + others[i]->getOwner().getSize()/2;
		Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
		
		Vector2 distVector2 = posSelf - posBoid;
		
		float dist = distVector2.length();
		if(dist < separationDist)
		{
			distVector2.normalize();
			sum+=distVector2;
			count++;
		}
		if(count >= 9)
		{
		 	break;
		}
	}	
	return count > 0 ? sum/count : Vector2(0.0f,0.0f);
}

Vector2 BoidsMoveComponent::align(vector<BoidsMoveComponent*> others)
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
		if(groupName != others[i]->getGroupName()) continue;
		Vector2 posBoid = others[i]->getOwner().getPosition() + others[i]->getOwner().getSize()/2;
		Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
		Vector2 distVector2 = posSelf - posBoid;
				
		float dist = distVector2.length();
		if(dist < maxPerceiveDistance)
		{
			sum+=others[i]->getForward();
			count++;
		}
		if(count >= 9)
		{
			break;
		}
	}
	return count > 0 ? sum/count : Vector2(0.0f,0.0f);
}

Vector2 BoidsMoveComponent::group(vector<BoidsMoveComponent*> others)
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
		if(groupName != others[i]->getGroupName()) continue;
		Vector2 posBoid = others[i]->getOwner().getPosition() + others[i]->getOwner().getSize()/2;
		Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
		Vector2 distVector2 = posSelf - posBoid;
				
		float dist = distVector2.length();
		if(dist < cohesionRadius)
		{
			sum+=others[i]->getOwner().getPosition();
			count++;
		}
		if(count >= 9)
		{
			break;
		}
	}
	Vector2 result = sum/count;
	Vector2 dirResult = owner.getPosition() + owner.getSize()/2 - result;
	dirResult.normalize();
	return count > 0 ? dirResult : Vector2(0.0f,0.0f);
}

Vector2 BoidsMoveComponent::handleSteer(Vector2& oldValue, Vector2& newValue)
{
	return (newValue - oldValue) * maxSteerValue;
}

Vector2 BoidsMoveComponent::bait(int mouseX, int mouseY)
{
	Vector2 dist = Vector2(mouseX,mouseY) - owner.getPosition();
	if(dist.length() < mouseRange)
	{
		dist.normalize();
		dist = Vector2(-dist.x,-dist.y);
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
				sum+=distVector2;
			}
			if(groupName == Group::GREEN && others[i]->getGroupName() == Group::BLUE)
			{
				sum+=distVector2;
			}
			if(groupName == Group::BLUE && others[i]->getGroupName() == Group::RED)
			{
				sum+=distVector2;
			}
		}

		
		if(dist < eatRange)
		{
			if(groupName == Group::RED && others[i]->getGroupName() == Group::GREEN)
			{
				others[i]->getOwner().setScale(others[i]->getOwner().getScale()*0.9f);
				owner.setScale(owner.getScale()*1.03f);
			}
			if(groupName == Group::GREEN && others[i]->getGroupName() == Group::BLUE)
			{
				others[i]->getOwner().setScale(others[i]->getOwner().getScale()*0.9f);
				owner.setScale(owner.getScale()*1.03f);
			}
			if(groupName == Group::BLUE && others[i]->getGroupName() == Group::RED)
			{
				others[i]->getOwner().setScale(others[i]->getOwner().getScale()*0.9f);
				owner.setScale(owner.getScale()*1.03f);
			}
		}
	}
	return count > 0 ? sum/count : Vector2(0.0f,0.0f);
}
