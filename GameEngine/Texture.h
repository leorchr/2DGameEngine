#pragma once
#include "Renderer.h"
#include <SDL_render.h>
#include <string>
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool load(Renderer& rendererP, const string& filenameP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	string filename;
	SDL_Texture* SDLTexture;
	int width;
	int height;
};