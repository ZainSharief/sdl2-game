#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "vec2.h"

class Screen
{
    private:
        SDL_Event event;
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Screen();
        ~Screen();

        void display();
        void render();
        SDL_Renderer* getRenderer();
};

#endif