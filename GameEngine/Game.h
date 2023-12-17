#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Renderer.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Vector2.h"
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

	// Game Specific
	vector<Brick*>& getBricks();
	void addBrick(Brick* brick);
	void removeBrick(Brick* brick);

	Paddle* getPaddle();
	void setPaddle(Paddle* paddle);

	Ball* getBall();
	void setBall(Ball* ball);

	void endGame();

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	Renderer renderer;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	// Game Specific
	
	vector<Brick*> bricks;
	Paddle* paddle = nullptr;
	Ball* ball = nullptr;
};