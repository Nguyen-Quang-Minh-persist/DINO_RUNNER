#include "bird_animation.h"
#include "dino_animation.h"

void render_bird_animation(bird_animation& data)
{
    SDL_Rect bird_rect = {data.screen_width / 2, data.ground_level - data.dino_height - 70, data.bird_width, data.bird_height};

    if (data.frame_count % 3 == 0)
    {
    switch (data.check_bird)
        {
         case 1:
            SDL_RenderCopy(data.renderer, data.bird_textures[0], NULL, &bird_rect);
            data.check_bird ++;
            break;
         case 2:
            SDL_RenderCopy(data.renderer, data.bird_textures[1], NULL, &bird_rect);
            data.check_bird ++;
            break;
         case 3:
            SDL_RenderCopy(data.renderer, data.bird_textures[2], NULL, &bird_rect);
            data.check_bird = 1;
            break;
        }
    } else
    {
    switch (data.check_bird)
        {
         case 1:
            SDL_RenderCopy(data.renderer, data.bird_textures[0], NULL, &bird_rect);
            break;
         case 2:
            SDL_RenderCopy(data.renderer, data.bird_textures[1], NULL, &bird_rect);
            break;
         case 3:
            SDL_RenderCopy(data.renderer, data.bird_textures[2], NULL, &bird_rect);
            break;
        }
    }

}

