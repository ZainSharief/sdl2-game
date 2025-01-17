#include "screen.h"

Screen::Screen()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow(
        "Insane Game",                 
        SDL_WINDOWPOS_CENTERED,        
        SDL_WINDOWPOS_CENTERED,        
        800,                           
        600,                           
        SDL_WINDOW_SHOWN               
    );

    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );
}

Screen::~Screen()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Screen::display() 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void Screen::render()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Screen::getRenderer()
{
    return renderer;
}