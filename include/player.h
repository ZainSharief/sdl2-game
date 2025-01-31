#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "object.h"
#include "vec2.h"

class Player: public Object
{
    private:
        int health;
        int maxHealth;
        vec2 velocity;
        float maxSpeed;

    public:
        Player(const char*, SDL_Renderer*, int, vec2);

        void incHealth(int);
        bool decHealth(int);
        void setHealth(int);
        int getHealth();
    
        void setVelocity(vec2);

        float getMaxSpeed();
        vec2 getVelocity();
};

#endif