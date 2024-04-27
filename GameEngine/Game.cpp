#include "Actor.h"
#include "Actor.h"
#include "Assets.h"
#include "FruitActor.h"
#include "CircleComponent.h"
#include "ControllerActor.h"
#include "Font.h"
#include "Fruit.h"
#include "Game.h"
#include "InputSystem.h"
#include "Physics.h"
#include "Timer.h"
#include "UIMovementComponent.h"
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
#include "SpriteComponent.h"

vector<Fruit>Game::fruits = { Fruits::cherry, Fruits::strawberry, Fruits::dekopon, Fruits::orange, Fruits::apple };

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
	Assets::loadTexture(renderer, "Res\\Textures\\Cloud.png", "Cloud", 190, 190);
	Assets::loadTexture(renderer, "Res\\Textures\\LineTrail.png", "Line");
	Assets::loadTexture(renderer, "Res\\Textures\\Border.png", "Border");
	Assets::loadTexture(renderer, "Res\\Textures\\Cherry.png", "Cherry", Fruits::fruitList[0].getRadius() * 2, Fruits::fruitList[0].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Strawberry.png", "Strawberry", Fruits::fruitList[1].getRadius() * 2, Fruits::fruitList[1].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Grape.png", "Grape", Fruits::fruitList[2].getRadius() * 2, Fruits::fruitList[2].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Dekopon.png", "Dekopon", Fruits::fruitList[3].getRadius() * 2, Fruits::fruitList[3].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Orange.png", "Orange", Fruits::fruitList[4].getRadius() * 2, Fruits::fruitList[4].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Apple.png", "Apple", Fruits::fruitList[5].getRadius() * 2, Fruits::fruitList[5].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Pear.png", "Pear", Fruits::fruitList[6].getRadius() * 2, Fruits::fruitList[6].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Peach.png", "Peach", Fruits::fruitList[7].getRadius() * 2, Fruits::fruitList[7].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Pineapple.png", "Pineapple", Fruits::fruitList[8].getRadius() * 2, Fruits::fruitList[8].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Melon.png", "Melon", Fruits::fruitList[9].getRadius() * 2, Fruits::fruitList[9].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Watermelon.png", "Watermelon", Fruits::fruitList[10].getRadius() * 2, Fruits::fruitList[10].getRadius() * 2);
	Assets::loadTexture(renderer, "Res\\Textures\\Bubble.png", "Bubble", 350, 350);
	Assets::loadTexture(renderer, "Res\\Textures\\EvolutionCircle.png", "Evolution" , 350, 350);
	Assets::loadFont("Res\\Fonts\\Cute-Dino.ttf", "Dino");


	// Create UI
	Actor* border = new Actor();
	SpriteComponent* sc = new SpriteComponent(border, Assets::getTexture("Border"), 101);
	border->setPosition(Vector2(WINDOW_WIDTH / 2 - 350 + 700/2, 80 + 920/2));

	scoreT = new UIScreen(Vector2(200, 210));
	scoreT->setTitle("Score", Vector3(121,36,36), 60);

	score = 0;
	scorePointsT = new UIScreen(Vector2(260, 375));
	scorePointsT->setTitle(std::to_string(score), Vector3(121, 36, 36), 60);

	nextFruitT = new UIScreen(Vector2(1450, 120));
	nextFruitT->setTitle("Suivant", Vector3(121, 36, 36), 60);

	circleT = new UIScreen(Vector2(1432, 550));
	circleT->setTitle("Cercle de", Vector3(121, 36, 36), 60);

	evolutionT = new UIScreen(Vector2(1415, 620));
	evolutionT->setTitle("l'evolution", Vector3(121, 36, 36), 60);

	Actor* bubble1 = new Actor();
	new SpriteComponent(bubble1, Assets::getTexture("Bubble"), 101);
	bubble1->setPosition(Vector2(285, 400));
	new UIMovementComponent(bubble1);

	Actor* bubble2 = new Actor();
	new SpriteComponent(bubble2, Assets::getTexture("Bubble"), 101);
	bubble2->setPosition(Vector2(1565, 300));
	new UIMovementComponent(bubble2);

	Actor* bubble3 = new Actor();
	new SpriteComponent(bubble3, Assets::getTexture("Evolution"), 101);
	bubble3->setPosition(Vector2(1565, 825));
	new UIMovementComponent(bubble3);

	// Create the controller actor
	controller = new ControllerActor(200.0f, 100.0f);
	baseTimeBetweenSpawn = 1.0f;
	timeBetweenSpawn = 1.0f;
	spawnSpeed = 30.0f;

	// Set up simulation variables
	getPhysics().setLeftBorder(WINDOW_WIDTH/2 - 340);
	getPhysics().setRightBorder(WINDOW_WIDTH / 2 + 340);
	getPhysics().setBottomBorder(WINDOW_HEIGHT - 90);
	getPhysics().setTopBorder(80.0f);

	// Spawn initial fruit
	setNextFruit();
}

void Game::spawnFruit(Fruit fruitP, Vector2 posP)
{
	FruitActor* circle = new FruitActor(posP, fruitP);
	addCircle(circle);
}

void Game::gameOver()
{
	isRunning = false;
}

void Game::setNextFruit()
{
	nextFruit = fruits[rand() % fruits.size()];
	if (nextFruitDisplay != nullptr) nextFruitDisplay->setState(Actor::ActorState::Dead);
	nextFruit = fruits[rand() % fruits.size()];
	nextFruitDisplay = new Actor();
	nextFruitDisplay->setPosition(Vector2(WINDOW_WIDTH/2 + 605.0f, WINDOW_HEIGHT/2 - 240.0f));
	new SpriteComponent(nextFruitDisplay, Assets::getTexture(nextFruit.getName()));
	new UIMovementComponent(nextFruitDisplay);
}

void Game::addScore(int scoreP)
{
	score += scoreP;
	int offsetX = (std::to_string(score).length() - 1) * (-15);
	scorePointsT->setOffsetPosition(Vector2(offsetX, 0));
	scorePointsT->setTitle(std::to_string(score), Vector3(121, 36, 36), 60);
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
	physics.computePhysics(dt);

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

void Game::addCircle(FruitActor* circle)
{
	circles.emplace_back(circle);
}

void Game::removeCircle(FruitActor* circle)
{
	auto iter = std::find(begin(circles), end(circles), circle);
	circles.erase(iter);
}