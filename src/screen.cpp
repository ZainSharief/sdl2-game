#include "screen.h"

#include <iostream>

Screen::Screen(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow(
        "Insane Game",                 
        SDL_WINDOWPOS_CENTERED,        
        SDL_WINDOWPOS_CENTERED,        
        width,                           
        height,                           
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE              
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

void Screen::adjustSize(int newWidth, int newHeight)
{
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float scaleX = (float)newWidth / windowWidth;
    float scaleY = (float)newHeight / windowHeight;

    float scale = std::min(scaleX, scaleY);

    int viewportWidth = newWidth * scale;
    int viewportHeight = newHeight * scale;

    int offsetX = (newWidth - viewportWidth) / 2;
    int offsetY = (newHeight - viewportHeight) / 2;

    SDL_Rect viewport = {offsetX, offsetY, viewportWidth, viewportHeight};
    SDL_RenderSetViewport(renderer, &viewport);
}


SDL_Renderer* Screen::getRenderer()
{
    return renderer;
}

int Screen::getWidth()
{
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, NULL);
    return windowWidth;
}

int Screen::getHeight()
{
    int windowHeight;
    SDL_GetWindowSize(window, NULL, &windowHeight);
    return windowHeight;
}