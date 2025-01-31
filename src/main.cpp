#include <iostream>

#include "map.h"
#include "screen.h"
#include "player.h"

void eventHandler(Screen &screen, SDL_Event &event, Player &player, std::unordered_map<SDL_Keycode, bool> &keyStates, float deltaTime)
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

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED){
                    screen.adjustSize(event.window.data1, event.window.data2);
                }
                break;

            default:
                break; 
        }
    }

    vec2 movement = vec2(0, 0);

    if (keyStates[SDLK_w]) movement = movement + vec2(0, -1);
    if (keyStates[SDLK_s]) movement = movement + vec2(0, 1);
    if (keyStates[SDLK_a]) movement = movement + vec2(-1, 0);
    if (keyStates[SDLK_d]) movement = movement + vec2(1, 0);

    movement = movement.normalize();
    movement = movement * player.getMaxSpeed();

    if (keyStates[SDLK_LSHIFT]) movement = movement * 1.5;

    player.setVelocity(movement);
    player.incPosition(player.getVelocity(), deltaTime);
}

int main(int argc, char* argv[]) 
{
    Screen screen(1920, 1080);

    SDL_Event event;
    std::unordered_map<SDL_Keycode, bool> keyStates;

    Map map(100000, 10, 200, 8); // seed, chunksize, blocksize, octaves
    Player player("textures/sprite/sprite_stationary.png", screen.getRenderer(), 100, vec2(0, 0));

    Uint64 currentFrame = SDL_GetPerformanceCounter();
    Uint64 previousFrame = 0;
    double deltaTime = 0.0f;

    while (true)
    {
        previousFrame = currentFrame;
        currentFrame = SDL_GetPerformanceCounter();
        deltaTime = (currentFrame - previousFrame) / (double) SDL_GetPerformanceFrequency();

        screen.display();
        
        player.render(screen.getRenderer());

        screen.render();
        eventHandler(screen, event, player, keyStates, deltaTime);
    }  
}