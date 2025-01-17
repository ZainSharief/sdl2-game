#include "object.h"

#include <iostream>

Object::Object(const char* path, SDL_Renderer* renderer, vec2 position)
    : position(position)
{
    texture = IMG_LoadTexture(renderer, path);
    SDL_QueryTexture(texture, NULL, NULL, &xsize, &ysize);
}

void Object::render(SDL_Renderer* renderer)
{
    SDL_Rect dstRect = {position.x, position.y, xsize, ysize}; 
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

void Object::incPosition(vec2 velocity, float deltaTime)
{
    position = addVec2(position, multVec2(velocity, vec2(deltaTime, deltaTime)));
    bindPosition();
}

void Object::decPosition(vec2 pos)
{
    position = subVec2(position, pos);
    bindPosition();
}

void Object::setPosition(vec2 pos)
{
    position = pos;
    bindPosition();
}

void Object::bindPosition()
{
    // TEMPORARY FUNCTION - > binds the player to the screen
    if (position.x > 800 - xsize) {
        position.x = 800 - xsize;
    } else if (position.x < 0) {
        position.x = 0;
    }

    if (position.y > 600 - ysize) {
        position.y = 600 - ysize;
    } else if (position.y < 0) {
        position.y = 0;
    }
}

vec2 Object::getPosition()
{
    return position;
}