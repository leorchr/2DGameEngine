#pragma once
#include <SDL.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT= 768;

class Window
{
    SDL_Window* window{ nullptr };
    int width{ WINDOW_WIDTH };
    int height{ WINDOW_HEIGHT };

public:
    Window() = default;

};