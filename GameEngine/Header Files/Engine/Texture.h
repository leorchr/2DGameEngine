#pragma once
#include "Renderer.h"
#include <SDL_render.h>
#include <SDL_surface.h>
#include <string>
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool load(Renderer& rendererP, const string& , int widthP, int heightP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);
	void createFromSurface(Renderer& renderer, struct SDL_Surface* surface);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	string filename;
	SDL_Texture* SDLTexture;
	int width;
	int height;
};