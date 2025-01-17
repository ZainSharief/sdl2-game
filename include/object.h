#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "vec2.h"

class Object
{
    private:
        vec2 position;
        int xsize;
        int ysize;

    public:
        SDL_Texture* texture;
        vec2 size;

        Object(const char*, SDL_Renderer*, vec2);
        void render(SDL_Renderer*);

        void incPosition(vec2, float);
        void decPosition(vec2);
        void setPosition(vec2);
        void bindPosition();
        vec2 getPosition();
};

#endif