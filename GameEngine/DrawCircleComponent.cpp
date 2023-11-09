#include "DrawCircleComponent.h"
#include "Actor.h"
#include <SDL.h>
#include "Renderer.h"

DrawCircleComponent::DrawCircleComponent(Actor* ownerP, int radiusP) :
	Component(ownerP),
	radius{ radiusP }
{

}


void DrawCircleComponent::draw(Renderer& renderer)
{
	drawCircle(renderer);
}

void DrawCircleComponent::drawCircle(Renderer& renderer)
{
    SDL_Renderer* SDL_Renderer = renderer.toSDLRenderer();
    const int centreX = owner.getPosition().x;
    const int centreY = owner.getPosition().y;

    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    SDL_SetRenderDrawColor(SDL_Renderer, 255, 255, 255, 255);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(SDL_Renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(SDL_Renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(SDL_Renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(SDL_Renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(SDL_Renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(SDL_Renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(SDL_Renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(SDL_Renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }

    }
}