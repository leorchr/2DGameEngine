#include "Actor.h"
#include "Assets.h"
#include "Boids.h"
#include "Font.h"
#include "Game.h"
#include "InputSystem.h"
#include "Timer.h"
#include "UIScreen.h"
#include "Vector2.h"
#include "Window.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_scancode.h>
#include <vector>

bool Game::initialize()
{
	srand(time(NULL));
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isInputInit = inputSystem.initialize();
	bool isFontInit = Font::initialize();
	return isWindowInit && isRendererInit && isInputInit && isFontInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	Assets::loadTexture(renderer, "Resource Files\\Textures\\WhiteFish.png", "RedFish", 50, 50);
	SDL_SetTextureColorMod(Assets::getTexture("RedFish").toSDLTexture(),246,249,58);
	Assets::loadTexture(renderer, "Resource Files\\Textures\\WhiteFish.png", "GreenFish", 50, 50);
	SDL_SetTextureColorMod(Assets::getTexture("GreenFish").toSDLTexture(),178,248,152);
	Assets::loadTexture(renderer, "Resource Files\\Textures\\WhiteFish.png", "BlueFish", 50, 50);
	SDL_SetTextureColorMod(Assets::getTexture("BlueFish").toSDLTexture(),252,230,252);
	
	srand (time(NULL));

	// Actor* rectangle = new Actor();
	// RectangleComponent* rectComp = new RectangleComponent(rectangle, 350, 120, 150, 600, Vector3(59,13,17));
	// rectangles.emplace_back(rectComp);
	// Actor* rectangle2 = new Actor();
	// RectangleComponent* rectComp2 = new RectangleComponent(rectangle2, 1000, 750, 450, 150, Vector3(59,13,17));
	// rectangles.emplace_back(rectComp2);
	
	for(int i = 0; i < 80; i++)
	{
		Boids* temp = new Boids(Group::RED);
		Vector2 pos = Vector2(rand() % (WINDOW_WIDTH-25) + 25,rand() % (WINDOW_HEIGHT-25) + 25);
		temp->setPosition(pos);
		boids.emplace_back(temp->getBoidsMoveComponent());
	}

	for(int i = 0; i < 80; i++)
	{
		Boids* temp = new Boids(Group::GREEN);
		Vector2 pos = Vector2(rand() % (WINDOW_WIDTH-25) + 25,rand() % (WINDOW_HEIGHT-25) + 25);
		temp->setPosition(pos);
		boids.emplace_back(temp->getBoidsMoveComponent());
	}

	for(int i = 0; i < 80; i++)
	{
		Boids* temp = new Boids(Group::BLUE);
		Vector2 pos = Vector2(rand() % (WINDOW_WIDTH-25) + 25,rand() % (WINDOW_HEIGHT-25) + 25);
		temp->setPosition(pos);
		boids.emplace_back(temp->getBoidsMoveComponent());
	}
}

void Game::processInput()
{
	inputSystem.preUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		isRunning = inputSystem.processEvent(event);
	}

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	// Escape: quit game
	if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		isRunning = false;
	}

	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(input);
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

	// Update UI screens
	for (auto ui : UIStack)
	{
		if (ui->getState() == UIState::Active)
		{
			ui->update(dt);
		}
	}

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

	// Delete any UIScreens that are closed
	auto iter = UIStack.begin();
	while (iter != UIStack.end())
	{
		if ((*iter)->getState() == UIState::Closing)
		{
			delete* iter;
			iter = UIStack.erase(iter);
		}
		else
		{
			++iter;
		}
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
	inputSystem.close();
	renderer.close();
	window.close();
	Font::close();
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

void Game::pushUI(UIScreen* screen)
{
	UIStack.emplace_back(screen);
}