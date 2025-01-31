#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <algorithm>

#include "vec2.h"

class Screen
{
    private:
        SDL_Event event;
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Screen(int, int);
        ~Screen();

        void display();
        void render();
        void adjustSize(int, int);
        SDL_Renderer* getRenderer();

        int getWidth();
        int getHeight();
};

#endif