#pragma once
#include "Actor.h"
#include "InputSystem.h"
#include "Renderer.h"
#include "UIScreen.h"
#include "Vector2.h"
#include "Window.h"
#include "BoidsMoveComponent.h"
#include <vector>
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
	Game() : isRunning(true), isUpdatingActors(false){}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	Renderer& getRenderer() { return renderer; }

	const vector<class UIScreen*>& getUIStack() { return UIStack; }
	void pushUI(class UIScreen* screen);

	vector<BoidsMoveComponent*> getBoids() {return boids; }

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	Renderer renderer;
	InputSystem inputSystem;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	vector<class UIScreen*> UIStack;

	vector<BoidsMoveComponent*> boids;
};