#include <iostream>

#include "map.h"
#include "screen.h"
#include "player.h"

void eventHandler(SDL_Event event, Player* player, std::unordered_map<SDL_Keycode, bool>& keyStates, float deltaTime)
{
    while (SDL_PollEvent(&event)) {

        switch (event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
                keyStates[event.key.keysym.sym] = true;
                break;
            
            case SDL_KEYUP:
                keyStates[event.key.keysym.sym] = false;
                break;

            default:
                break; 
        }
    }

    vec2 movement = vec2(0, 0);

    if (keyStates[SDLK_w]){
        movement = movement + vec2(0, -1);
    }
    if (keyStates[SDLK_s]){
        movement = movement + vec2(0, 1);
    }
    if (keyStates[SDLK_a]){
        movement = movement + vec2(-1, 0);
    }
    if (keyStates[SDLK_d]){
        movement = movement + vec2(1, 0);
    }

    movement = movement.normalize();
    movement = movement * player->getMaxSpeed();

    player->setVelocity(movement);
    player->incPosition(player->getVelocity(), deltaTime);
}

int main(int argc, char* argv[]) 
{
    Screen screen;

    SDL_Event event;
    std::unordered_map<SDL_Keycode, bool> keyStates;

    Map map(101, 2, 400, 8, screen.getRenderer()); // seed, chunksize, blocksize, octaves renderer
    Player player("textures/sprite/sprite_stationary.png", screen.getRenderer(), 100, vec2(0, 0));

    int frameBuffer = 0;
    Uint64 currentFrame = SDL_GetPerformanceCounter();
    Uint64 previousFrame = 0;
    double deltaTime = 0.0f;

    while (true)
    {
        previousFrame = currentFrame;
        currentFrame = SDL_GetPerformanceCounter();
        deltaTime = (currentFrame - previousFrame) / (double) SDL_GetPerformanceFrequency();

        /**frameBuffer += 1;
        if (frameBuffer == 60) {
            std::cout << (int) (1 / deltaTime) << std::endl;
            frameBuffer = 0;
        }*/

        screen.display();
        
        map.render(screen.getRenderer());
        player.render(screen.getRenderer());

        screen.render();

        eventHandler(event, &player, keyStates, deltaTime);
    }  
}