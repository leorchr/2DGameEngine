#include "Assets.h"
#include "Log.h"
#include <sstream>

std::map<std::string, Texture> Assets::textures;
std::map<std::string, Font> Assets::fonts;

Texture Assets::loadTexture(Renderer& renderer, const string& filename, const string& name, int width, int height)
{
    textures[name] = loadTextureFromFile(renderer, filename.c_str(), width, height);
    return textures[name];
}

Texture& Assets::getTexture(const string& name)
{
    if (textures.find(name) == end(textures))
    {
        std::ostringstream loadError;
        loadError << "Texture " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return textures[name];
}

Font Assets::loadFont(const string& filename, const string& name)
{
    fonts[name] = loadFontFromFile(filename);
    return fonts[name];
}

Font& Assets::getFont(const std::string& name)
{
    if (fonts.find(name) == end(fonts))
    {
        std::ostringstream loadError;
        loadError << "Font " << name << " does not exist in assets manager.";
            Log::error(LogCategory::Application, loadError.str());
    }
    return fonts[name];
}

void Assets::clear()
{
    // (Properly) delete all textures
    for (auto iter : textures)
        iter.second.unload();
    textures.clear();
    for (auto iter : fonts)
        iter.second.unload();
    fonts.clear();
}

Texture Assets::loadTextureFromFile(Renderer& renderer, const string& filename, int width, int height)
{
    Texture texture;
    texture.load(renderer, filename, width, height);
    return texture;
}

Font Assets::loadFontFromFile(const string& filename)
{
    vector<int> fontSizes = {
    8, 9,
    10, 11, 12, 14, 16, 18,
    20, 22, 24, 26, 28,
    30, 32, 34, 36, 38,
    40, 42, 44, 46, 48,
    52, 56,
    60, 64, 68,
    72
    };
    Font font;
    for (auto& size : fontSizes)

    {
        TTF_Font* ttfFont = TTF_OpenFont(filename.c_str(), size);
        if (ttfFont == nullptr)
        {
            std::ostringstream s;
            s << "Failed to load Font " << filename << " in size "
                << size;
            Log::error(LogCategory::Application, s.str());
        }
        font.addFontData(size, ttfFont);
    }
    Log::info("Loaded font " + filename);
    return font;
}
