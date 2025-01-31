#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "vec2.h"

class Object
{
    public:
        Object(const char*, SDL_Renderer*, vec2);
        void render(SDL_Renderer*);

        void incPosition(vec2, float);
        void setPosition(vec2);
        vec2 getPosition();

    private:
        SDL_Texture* texture;

        vec2 position;
        int xsize;
        int ysize;    
};

#endif