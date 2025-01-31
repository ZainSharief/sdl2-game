#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include <cmath>

#include "vec2.h"

class Map
{
    private:
        SDL_Texture* texture;

    public:
        Map(const unsigned, const unsigned, const unsigned, const unsigned);
};

class PerlinNoise
{
    private:
        const unsigned seed;
        const unsigned chunkSize;
        const unsigned blockSize;
        const unsigned octaves;
        vec2 randomGradient(int, int);
        float interpolate(float, float, float);

    public:
        PerlinNoise(const unsigned, const unsigned, const unsigned, const unsigned);
        std::vector<std::vector<float> > generateChunk(int, int);

};

#endif