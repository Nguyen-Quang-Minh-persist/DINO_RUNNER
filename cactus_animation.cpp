#include "cactus_animation.h"

void render_cactus_animation(cactus_animation& data)
{
    for (int i = 0; i < data.cactuses.size(); i++)
    {
        int cactus_height;
        if (data.cactuses[i].type == 0) cactus_height = small_cactus_height; else cactus_height = big_cactus_height;

        SDL_Rect cactus_rect = { data.cactuses[i].x, data.ground_level - cactus_height, cactus_width, cactus_height };
        SDL_RenderCopy(data.renderer, data.cactus_texture, NULL, &cactus_rect);
    }
}

