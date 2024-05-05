#include "Font.h"
#include "Game.h"
#include "Log.h"
#include "Texture.h"
#include "Vector3.h"
#include <iosfwd>
#include <list>
#include <new>
#include <ostream>
#include <SDL_pixels.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <sstream>
#include <string>
#include <utility>

Font::Font()
{
}

Font::~Font()
{
}

bool Font::initialize()
{
	if (TTF_Init() != 0)
	{
		Log::error(LogCategory::System, "Failed to initialize SDL_ttf");
		return false;
	}
	return true;
}

void Font::close()
{
	TTF_Quit();
}

void Font::unload()
{
	for (auto& font : fontData)
	{
		TTF_CloseFont(font.second);
	}
}

Texture* Font::renderText(const string& text, const Vector3& color, int pointSize)
{
	Texture* texture = nullptr;
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x);
	sdlColor.g = static_cast<Uint8>(color.y);
	sdlColor.b = static_cast<Uint8>(color.z);
	sdlColor.a = 255;

	auto iter = fontData.find(pointSize);
	if (iter != fontData.end()) {
		TTF_Font* font = iter->second;
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), sdlColor);
		if (surf != nullptr) {
			texture = new Texture();
			;
			texture->createFromSurface(Game::instance().getRenderer(), surf);
			SDL_FreeSurface(surf);
		}
	}
	else {
		std::ostringstream loadError;
		loadError << "Point size " << pointSize << " is unsupported";
		Log::error(LogCategory::Application, loadError.str());
	}

	return texture;
}

void Font::addFontData(int size, TTF_Font* fontSize) {
	fontData.emplace(size, fontSize);
}