#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include <vector>
using std::vector;

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* ownerP, const vector<Texture*>& textureP, int drawOrderP = 100);
	virtual ~AnimSpriteComponent();
	AnimSpriteComponent() = delete;
	AnimSpriteComponent(const AnimSpriteComponent&) = delete;
	AnimSpriteComponent& operator=(const AnimSpriteComponent&) = delete;

	float getAnimFPS() const { return animFPS; }
	void setAnimTextures(const vector<Texture*>& textures);
	void setAnimFPS(float animFPSP);

	void update(float dt) override;


private:
	vector<Texture*> animTextures;
	float currentFrame;
	float animFPS;
};