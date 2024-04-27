#pragma once
#include "Actor.h"
#include "FruitActor.h"
#include "ControllerActor.h"
#include "Fruit.h"
#include "InputSystem.h"
#include "Physics.h"
#include "Renderer.h"
#include "UIScreen.h"
#include "Vector2.h"
#include "Window.h"
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
	Physics& getPhysics() { return physics; }

	const vector<class UIScreen*>& getUIStack() { return UIStack; }
	void pushUI(class UIScreen* screen);

	//Game specific
	void addCircle(FruitActor* circle);
	void removeCircle(FruitActor* circle);
	void spawnFruit(Fruit fruitP, Vector2 posP);
	static vector<Fruit> fruits;
	void gameOver();
	Fruit getNextFruit() { return nextFruit; }
	void setNextFruit();
	void addScore(int scoreP);

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	Renderer renderer;
	Physics physics;
	InputSystem inputSystem;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	vector<class UIScreen*> UIStack;

	//Game Specific attributes
	ControllerActor* controller;
	vector<FruitActor*> circles;
	float timeBetweenSpawn;
	float baseTimeBetweenSpawn;
	float spawnSpeed;
	Vector2 spawnPos;

	Fruit nextFruit;
	Actor* nextFruitDisplay;

	UIScreen* scoreT;
	UIScreen* scorePointsT;
	UIScreen* nextFruitT;
	UIScreen* circleT;
	UIScreen* evolutionT;

	int score;
};