#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "Timer.h"
#include "Assets.h"
#include "BackgroundSpriteComponent.h"
#include "RectangleComponent.h"
#include "Ball.h"
#include "Paddle.h"
#include <stdlib.h>
#include <time.h>

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	// Load textures
	Assets::loadTexture(renderer, "Res\\Ship01.png", "Ship01");
	Assets::loadTexture(renderer, "Res\\Ship02.png", "Ship02");
	Assets::loadTexture(renderer, "Res\\Ship03.png", "Ship03");
	Assets::loadTexture(renderer, "Res\\Ship04.png", "Ship04");
	Assets::loadTexture(renderer, "Res\\Farback01.png", "Farback01");
	Assets::loadTexture(renderer, "Res\\Farback02.png", "Farback02");
	Assets::loadTexture(renderer, "Res\\Stars.png", "Stars");
	Assets::loadTexture(renderer, "Res\\Astroid.png", "Astroid");
	Assets::loadTexture(renderer, "Res\\Ship.png", "Ship");
	Assets::loadTexture(renderer, "Res\\Laser.png", "Laser");
	Assets::loadTexture(renderer, "Res\\Strawberry2.png", "Strawberry");
	Assets::loadTexture(renderer, "Res\\Apple.png", "Apple");
	Assets::loadTexture(renderer, "Res\\Brique.png", "Brique");
	Assets::loadTexture(renderer, "Res\\Wood.png", "Wood");
	Assets::loadTexture(renderer, "Res\\Wood2.png", "Wood2");
	Assets::loadTexture(renderer, "Res\\Wood3.png", "Wood3");


	// Background
	// Create the "far back" background
	/*vector<Texture*> bgTexsFar{
		&Assets::getTexture("Farback01"),
			& Assets::getTexture("Farback02")
	};
	Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpritesFar = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesFar->setScrollSpeed(-100.0f);

	// Create the closer background
	Actor* bgClose = new Actor();
	std::vector<Texture*> bgTexsClose {
		&Assets::getTexture("Stars"),
			& Assets::getTexture("Stars")
	};
	BackgroundSpriteComponent* bgSpritesClose = new BackgroundSpriteComponent(bgClose, bgTexsClose);
	bgSpritesClose->setScrollSpeed(-200.0f);*/


	// Création de la balle
	new Ball((int)Assets::getTexture("Apple").getWidth(), (int)Assets::getTexture("Apple").getHeight());
	//new Ball(10,13);
	SpriteComponent* spriteBall = new SpriteComponent(ball, Assets::getTexture("Apple"));
	ball->setPosition(Vector2{ 400, 400 });
	int lives = 5;
	ball->setLives(lives);


	// Création de la raquette
	new Paddle(128, 16);
	paddle->setPosition(Vector2{ 450, 700 });


	// Création des briques
	srand(time(NULL));
	const int horizontalBricks = 8;
	const int verticalBricks = 5;
	const int brickSizeX = 128;
	const int brickSizeY = 32;
	int offsetX = 1;
	int offsetY = 1;
	float xPos = 0;

	for (int i = 0; i < horizontalBricks; ++i)
	{
		float yPos = 70;
		for (int i = 0; i < verticalBricks; ++i) {
			Brick* brick = new Brick(Assets::getTexture("Brique").getWidth(), (int)Assets::getTexture("Brique").getHeight());
			brick->setPosition(Vector2{ xPos, yPos });

			int randWood = rand() % 3 + 1;
			if (randWood == 1) SpriteComponent* spriteBrick = new SpriteComponent(brick, Assets::getTexture("Wood"));
			else if (randWood == 2) SpriteComponent* spriteBrick = new SpriteComponent(brick, Assets::getTexture("Wood2"));
			else SpriteComponent* spriteBrick = new SpriteComponent(brick, Assets::getTexture("Wood3"));
			yPos += brickSizeY + offsetY;
		}
		xPos += brickSizeX + offsetX;
	}


	// Création des vies

	float liveSizeX = Assets::getTexture("Apple").getWidth();
	float liveSizeY = Assets::getTexture("Apple").getHeight();
	xPos = 20;
	float yPos = 730;
	offsetX = 10;

	for (int i = 0; i < lives; ++i) {
		Live* live = new Live(Assets::getTexture("Apple").getWidth(), (int)Assets::getTexture("Apple").getHeight());
		live->setPosition(Vector2{ xPos, yPos });
		SpriteComponent* spriteBrick = new SpriteComponent(live, Assets::getTexture("Apple"));
		xPos += liveSizeX + offsetX;
	}

	// Animated sprite
	/*
	vector<Texture*> animTextures {
		&Assets::getTexture("Ship01"),
		&Assets::getTexture("Ship02"),
		&Assets::getTexture("Ship03"),
		&Assets::getTexture("Ship04"),
	};
	Actor* ship = new Actor();
	AnimSpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animTextures);
	ship->setPosition(Vector2{ 100, 300 });
	*/
}

vector<Brick*>& Game::getBricks()
{
	return bricks;
}

void Game::addBrick(Brick* brick)
{
	bricks.emplace_back(brick);
}

void Game::removeBrick(Brick* brick)
{
	auto iter = std::find(begin(bricks), end(bricks), brick);
	if (iter != bricks.end())
	{
		bricks.erase(iter);
	}
}

Paddle* Game::getPaddle()
{
	return paddle;
}

void Game::setPaddle(Paddle* paddleP)
{
	paddle = paddleP;
}

Ball* Game::getBall()
{
	return ball;
}

void Game::setBall(Ball* ballP)
{
	ball = ballP;
}

vector<Live*>& Game::getLives()
{
	return lives;
}

void Game::addLive(Live* live)
{
	lives.emplace_back(live);
}

void Game::removeLive(Live* live)
{
	auto iter = std::find(begin(lives), end(lives), live);
	if (iter != lives.end())
	{
		lives.erase(iter);
	}
}

void Game::endGame()
{
	isRunning = false;
	close();
}

void Game::processInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::update(float dt)
{
	// Update actors 
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}