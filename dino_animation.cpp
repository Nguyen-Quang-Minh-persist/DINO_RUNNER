#include "dino_animation.h"

void render_dino_animation(dino_animation& data)
{
   if(data.dino_is_jumping == false)
    {
        if (data.frame_count % 5 == 0)
        {
            switch (data.check_dino)
            {
            case 1:
                SDL_RenderCopy(data.renderer, data.dino_textures[0], NULL, &data.dino_rect);
                data.check_dino ++;
                break;
            case 2:
                SDL_RenderCopy(data.renderer, data.dino_textures[1], NULL, &data.dino_rect);
                data.check_dino ++;
                break;
            case 3:
                SDL_RenderCopy(data.renderer, data.dino_textures[2], NULL, &data.dino_rect);
                data.check_dino ++;
                break;
            case 4:
                SDL_RenderCopy(data.renderer, data.dino_textures[3], NULL, &data.dino_rect);
                data.check_dino ++;
                break;
            case 5:
                SDL_RenderCopy(data.renderer, data.dino_textures[4], NULL, &data.dino_rect);
                data.check_dino = 1;
                break;
            }
        } else
          {
            switch (data.check_dino)
            {
            case 1:
                SDL_RenderCopy(data.renderer, data.dino_textures[0], NULL, &data.dino_rect);
                break;
            case 2:
                SDL_RenderCopy(data.renderer, data.dino_textures[1], NULL, &data.dino_rect);
                break;
            case 3:
                SDL_RenderCopy(data.renderer, data.dino_textures[2], NULL, &data.dino_rect);
                break;
            case 4:
                SDL_RenderCopy(data.renderer, data.dino_textures[3], NULL, &data.dino_rect);
                break;
            case 5:
                SDL_RenderCopy(data.renderer, data.dino_textures[4], NULL, &data.dino_rect);
                break;
            }
          }
    }  else SDL_RenderCopy(data.renderer, data.dino_textures[5], NULL, &data.dino_rect);

}

