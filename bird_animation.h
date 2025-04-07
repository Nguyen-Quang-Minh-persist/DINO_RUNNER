#ifndef _BIRD_ANIMATION_H
#define _BIRD_ANIMATION_H

#include <SDL.h>

struct bird_animation {
    SDL_Renderer* renderer;
    int bird_width;
    int bird_height;
    int screen_width;
    int ground_level;
    int dino_height;
    int frame_count;
    int check_bird;
    SDL_Texture* bird_textures[3];
};

void render_bird_animation (bird_animation& data);

#endif

