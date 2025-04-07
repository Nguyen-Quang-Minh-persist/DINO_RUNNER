#ifndef _CACTUS_ANIMATION_H
#define _CACTUS_ANIMATION_H

#include <SDL.h>
#include <vector>

using namespace std;

// Fixed characterists
const int cactus_width = 60;
const int big_cactus_height = 100;
const int small_cactus_height = 70;

// Changing characterists
struct Cactus
{
    int x; // x is coordinate of the cactus
    int type; // 0 for small cactus and 1 for big cactus
};

struct cactus_animation
{
    SDL_Renderer* renderer;
    vector<Cactus> cactuses;
    SDL_Texture* cactus_texture;
    int ground_level;
};

void render_cactus_animation(cactus_animation& data);

#endif

