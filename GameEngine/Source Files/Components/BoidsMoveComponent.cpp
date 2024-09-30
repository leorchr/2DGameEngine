#include "Actor.h"
#include "BoidsMoveComponent.h"
#include "Maths.h"
#include "Vector2.h"
#include "Window.h"
#include "Game.h"

BoidsMoveComponent::BoidsMoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), speedX(0.0f), speedY(0.0f)
{

}

void BoidsMoveComponent::setSpeedX(float speedX)
{
	this->speedX = speedX;
	baseSpeedX = speedX;
}

void BoidsMoveComponent::setSpeedY(float speedY)
{
	this->speedY = speedY;
	baseSpeedY = speedY;
}

void BoidsMoveComponent::update(float dt)
{
	Vector2 separation = separate(Game::instance().getBoids());

	Vector2 dir = Vector2{speedX,speedY};
	if(separation.length()!=0)separation.normalize();
	dir+=separation * separationFactor;
	dir.normalize();

	speedX = dir.x * baseSpeedX;
	speedY = dir.y * baseSpeedY;
	
	
	if (!Maths::nearZero(speedX))
	{
		Vector2 newPosition = Vector2(owner.getPosition().x + speedX * dt,owner.getPosition().y);
		owner.setPosition(newPosition);
	}

	if (!Maths::nearZero(speedY))
	{
		Vector2 newPosition = Vector2(owner.getPosition().x,owner.getPosition().y + speedY * dt);
		owner.setPosition(newPosition);
	}

}

Vector2 BoidsMoveComponent::separate(vector<BoidsMoveComponent*> others)
{
	size_t length = others.size();
	Vector2 sum{0.0f,0.0f};
	int count = 0;


	int rightWallDist = WINDOW_WIDTH - owner.getPosition().x;
	if(rightWallDist < separationDist)
	{
		sum+= Vector2(-rightWallDist,0);
		count++;
	}

	int bottomWallDist = WINDOW_HEIGHT - owner.getPosition().y;
	if(bottomWallDist < separationDist)
	{
		sum+= Vector2(0,-bottomWallDist);
		count++;
	}

	int leftWallDist = owner.getPosition().x;
	if(leftWallDist < separationDist)
	{
		sum+= Vector2(leftWallDist,0);
		count++;
	}

	int topWallDist = owner.getPosition().y;
	if(topWallDist < separationDist)
	{
		sum+= Vector2(0,topWallDist);
		count++;
	}
	
	
	for(int i = 0; i < length; i++)
	{
		if(others[i]->owner.getId() == owner.getId())
		{
			continue;
		}
		Vector2 posBoid = others[i]->getOwner().getPosition();
		Vector2 posSelf = owner.getPosition();
		
		Vector2 distVector2 = posSelf - posBoid;
		
		float dist = distVector2.length();
		if(dist < 100)
		{
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