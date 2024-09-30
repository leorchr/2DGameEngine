#pragma once
#include <SDL.h>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT= 1200;

class Window
{
    SDL_Window* SDLWindow{ nullptr };
    int width{ WINDOW_WIDTH };
    int height{ WINDOW_HEIGHT };

public:
    Window() = default;
    Window(const Window&) = delete;
    Window& operator = (const Window&) = delete;

    SDL_Window* getSDLWindow() const { return SDLWindow; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    bool initialize();
    void close();
};