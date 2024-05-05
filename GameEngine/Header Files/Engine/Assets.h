#pragma once
#include "Font.h"
#include "Renderer.h"
#include "Texture.h"
#include <map>
#include <string>
using std::map;
using std::string;

// A static singleton Assets class that hosts several
// functions to load resources. Each loaded resource is also 
// stored for future reference by string handles. All functions 
// and resources are static and no public constructor is defined.
class Assets
{
public:
    static std::map<std::string, Texture> textures;
    static std::map<std::string, Font> fonts;

    // Loads a texture from file
    static Texture loadTexture(Renderer& renderer, const string& filename, const string& name, int width = 0, int height = 0);

    // Retrieves a stored texture
    static Texture& getTexture(const std::string& name);

    // Loads a font from file
    static Font loadFont(const string& filename, const string& name);

    // Retrieves a stored font
    static Font& getFont(const std::string& name);

    // Properly de-allocates all loaded resources
    static void clear();

private:
    Assets() {}

    // Loads a single texture from file
    static Texture loadTextureFromFile(Renderer& renderer, const string& filename, int width, int height);

    static Font loadFontFromFile(const string& filename);

};