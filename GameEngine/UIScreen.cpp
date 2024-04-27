#include "UIScreen.h"
#include "Texture.h"
#include "Font.h"
#include "Assets.h"
#include "Game.h"

UIScreen::UIScreen() :
	title(nullptr),
	titlePosition(Vector2::zero),
	state(UIState::Active),
	font(Assets::getFont("Dino"))
{
	Game::instance().pushUI(this);
	setTitle("Lorem Ipsum");
}
UIScreen::~UIScreen()
{
	if (title)
	{
		title->unload();
		delete title;
	}
}

void UIScreen::setTitle(const string& titleP, const Vector3& color,	int pointSize)
{
	if (title)
	{
		title->unload();
		delete title;
		title = nullptr;
	}
	title = font.renderText(titleP, color, pointSize);
}

void UIScreen::setTitlePosition(const Vector2& position)
{
	titlePosition = position;
}

void UIScreen::update(float dt)
{
}

void UIScreen::draw()
{
	if (title)
	{
		drawTexture(title, titlePosition);
	}
}
void UIScreen::processInput(const InputState& inputState)
{
}
void UIScreen::close()
{
	state = UIState::Closing;
}
void UIScreen::drawTexture(Texture* texture, const Vector2& offset)
{
	// Use SDL to render the texture on the screen
	SDL_Renderer* renderer = Game::instance().getRenderer().toSDLRenderer(); // Get the SDL renderer from the Game class

	// Assuming the Texture class has a member variable 'texture' of type SDL_Texture*
	SDL_Rect destRect;
	destRect.x = static_cast<int>(offset.x);
	destRect.y = static_cast<int>(offset.y);
	SDL_QueryTexture(texture->toSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);
	SDL_RenderCopy(renderer, texture->toSDLTexture(), nullptr, &destRect);

}