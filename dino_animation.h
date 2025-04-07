#ifndef _DINO_ANIMATION_H
#define _DINO_ANIMATION_H

#include <SDL.h>

// Characterists of moving
const double gravity = 0.6;
const double jump = -15;

// Fixed characterists
const int dino_width = 90;
const int dino_height = 90;
const int dino_x = 100;

// Changing characterists
struct Dino
{
    double y; // y is coordinate of the dino
    double v; // v is velocity
   // bool is_jumping;
};

struct dino_animation
{
    SDL_Renderer* renderer;
    SDL_Rect dino_rect;
    bool dino_is_jumping;
    int frame_count;
    int check_dino;
    SDL_Texture* dino_textures[6];
};

void render_dino_animation(dino_animation& data);

#endif

