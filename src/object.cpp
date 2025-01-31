#include "object.h"

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
    position = position + (velocity * deltaTime);
}

void Object::setPosition(vec2 pos)
{
    position = pos;
}

vec2 Object::getPosition()
{
    return position;
}