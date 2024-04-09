#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Vector3.h"
#include "CircleActor.h"
#include "Physics.h"
using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true), isUpdatingActors(false) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	Renderer& getRenderer() { return renderer; }
	Physics& getPhysics() { return physics; }

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	Renderer renderer;
	Physics physics;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
};
