#include "map.h"

#include <iostream>

Map::Map(const unsigned seed, const unsigned chunkSize, const unsigned blockSize, const unsigned octaves, SDL_Renderer* renderer)
{
    PerlinNoise noise(seed, chunkSize, blockSize, octaves);
    std::vector<std::vector<float> > map = noise.generateChunk(0, 0);

    std::vector<Uint32> pixelBuffer(800 * 800);

    for (int y = 0; y < blockSize * chunkSize; y++){
        for (int x = 0; x < blockSize * chunkSize; x++){
            Uint8 color = static_cast<Uint8>(map[x][y]); // Ensure pixel value is in [0, 255]
            Uint32 pixel = (color << 16) | (color << 8) | color; // RGB format (grayscale)
            pixelBuffer[y * 800 + x] = pixel;
        }
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 800, 800);
    SDL_UpdateTexture(texture, nullptr, pixelBuffer.data(), 800 * sizeof(Uint32));
    
}

void Map::render(SDL_Renderer* renderer) 
{
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

PerlinNoise::PerlinNoise(const unsigned seed, const unsigned chunkSize, const unsigned blockSize, const unsigned octaves)
    :seed(seed), chunkSize(chunkSize), blockSize(blockSize), octaves(octaves)
{

}

std::vector<std::vector<float> > PerlinNoise::generateChunk(int chunk_x, int chunk_y) 
{
    // chunk_x and chunk_y are the coordinates of each chunk, ie. starting coordinates are (0, 0)
    int chunkOffset_x = chunk_x * chunkSize;
    int chunkOffset_y = chunk_y * chunkSize;

    std::vector<std::vector<vec2> > grid((chunkSize + 1), std::vector<vec2>(chunkSize + 1));
    std::vector<std::vector<float> > map(blockSize * chunkSize, std::vector<float>(blockSize * chunkSize));

    // Generates a random gradient for each chunk border
    for (int y = 0; y < chunkSize + 1; y++) {
        for (int x = 0; x < chunkSize + 1; x++) {
            grid[x][y] = randomGradient(chunkOffset_x+x, chunkOffset_y+y);
        }
    }

    for (int y = 0; y < blockSize * chunkSize; y++) {
        for (int x = 0; x < blockSize * chunkSize; x++) {

            float amplitude = 1.0f;
            float frequency = 1.0f;

            for (int o = 0; o < octaves; o++){

                // Normalises the point so chunk x starts at x 
                vec2 point_norm = vec2(x, y) / (blockSize * frequency);

                // Finds surrounding chunk borders
                int x0 = (int) point_norm.x;
                int y0 = (int) point_norm.y;
                int x1 = x0 + 1;
                int y1 = y0 + 1;

                // Cubic interpolation horizontally 
                float ix0 = interpolate(
                    (point_norm - vec2(x0, y0)).dot(grid[x0][y0]),
                    (point_norm - vec2(x1, y0)).dot(grid[x1][y0]),
                    point_norm.x - x0
                );
                float ix1 = interpolate(
                    (point_norm - vec2(x0, y1)).dot(grid[x0][y1]),
                    (point_norm - vec2(x1, y1)).dot(grid[x1][y1]),
                    point_norm.x - x0
                );

                // Cubic interpolation vertically
                float value = interpolate(ix0, ix1, point_norm.y - y0);

                map[x][y] += (value * amplitude);

                // Reduces the amplitude + increases the frequency for the next octave
                amplitude /= 2;
                frequency *= 2;
            }

            // Clamps the value between -1 and 1
            if (map[x][y] > 1.0f) map[x][y] = 1.0f;
            else if (map[x][y] < -1.0f) map[x][y] = -1.0f;

            map[x][y] = (map[x][y] + 1) * (255.0f / 2.0f);  // [-1, 1] -> [0, 255]
        }
    }

    return map;
}

float PerlinNoise::interpolate(float a0, float a1, float w) 
{
    // Cubic interpolation to avoid "block" shapes in the noise
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

vec2 PerlinNoise::randomGradient(int ix, int iy) 
{
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;

    // Bunch of magic with primes to hash to a unique value
    a ^= seed;              
    a *= 3284157443;

    b ^= seed;               
    b ^= a << s | a >> (w - s);
    b *= 1911520717;

    a ^= b << s | b >> (w - s);
    a *= 2048419325;

    // Converts value to range [0, 2*Pi]
    float random = a * (3.14159265 / ~(~0u >> 1)); 

    // Converts the input into a unit vector
    vec2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}