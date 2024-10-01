#include "Actor.h"
#include "BoidsMoveComponent.h"

#include <ostream>

#include "Maths.h"
#include "Vector2.h"
#include "Window.h"
#include "Game.h"
#include <iostream>

BoidsMoveComponent::BoidsMoveComponent(Actor* ownerP, int updateOrderP, Vector2 fwd, int speed, int separationDist, float separationFactor, int maxPerceiveDistance, float alignementFactor, int cohesionRadius, float groupementFactor, float maxSteerValue)
	: Component(ownerP, updateOrderP),
	forward(fwd),
	speed(speed),
	separationDist(separationDist),
	separationFactor(separationFactor),
	maxPerceiveDistance(maxPerceiveDistance),
	alignementFactor(alignementFactor),
	cohesionRadius(cohesionRadius),
	groupementFactor(groupementFactor),
	maxSteerValue(maxSteerValue)
{

}
void BoidsMoveComponent::update(float dt)
{
	Vector2 separation = separate(Game::instance().getBoids());
	Vector2 alignement = align(Game::instance().getBoids());
	Vector2 groupement = group(Game::instance().getBoids());

	Vector2 dir = forward;
	
	if(separation.length()!=0)separation.normalize();
	dir+=separation * separationFactor;
	dir+=alignement * alignementFactor;
	dir+=groupement * groupementFactor;
	dir.normalize();

	
	
	forward = dir + handleSteer(forward,dir);
	
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
		// if(count >= 9)
		// {
		// 	break;
		// }
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
		
		Vector2 posBoid = others[i]->getOwner().getPosition() + others[i]->getOwner().getSize()/2;
		Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
		Vector2 distVector2 = posSelf - posBoid;
				
		float dist = distVector2.length();
		if(dist < maxPerceiveDistance)
		{
			sum+=others[i]->getForward();
			count++;
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
		
		Vector2 posBoid = others[i]->getOwner().getPosition() + others[i]->getOwner().getSize()/2;
		Vector2 posSelf = owner.getPosition() + owner.getSize()/2;
		Vector2 distVector2 = posSelf - posBoid;
				
		float dist = distVector2.length();
		if(dist < cohesionRadius)
		{
			sum+=others[i]->getOwner().getPosition();
			count++;
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
