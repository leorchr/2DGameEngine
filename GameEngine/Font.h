#pragma once
#include "SDL_ttf.h"
#include "Texture.h"
#include "Vector3.h"
#include <string>
#include <unordered_map> 
using std::string;

class Font
{
public:
	Font();
	~Font();

	static bool initialize();
	static void close();

	void unload();
	class Texture* renderText(const string& text, const Vector3& color = Vector3(255,255,255), int pointSize = 10);
	void addFontData(int size, TTF_Font* fontSize);

private:
	std::unordered_map <int, TTF_Font*> fontData;
};