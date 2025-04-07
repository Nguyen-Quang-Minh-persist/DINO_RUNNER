#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "graphic.h"

using namespace std;

const int screen_width = 1200; // The width of the screen
const int screen_height = 600; // The height of the screen

void log_error_and_exit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* init_SDL(int screen_width, int screen_height, const char* name_of_game)
{
    SDL_Window* window = SDL_CreateWindow(name_of_game, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height,SDL_WINDOW_SHOWN);

    if(window == nullptr)log_error_and_exit("SDL_image error:", IMG_GetError());

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) log_error_and_exit("SDL_Init", SDL_GetError());

    if (TTF_Init() == -1) {log_error_and_exit("SDL_ttf could not initialize! SDL_ttf Error: ",TTF_GetError());}

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {log_error_and_exit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",Mix_GetError() );}

    return window;
}
SDL_Renderer* create_renderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == nullptr) log_error_and_exit("create_rendere", SDL_GetError());

    SDL_SetHint("linear", SDL_HINT_RENDER_SCALE_QUALITY);
    SDL_RenderSetLogicalSize(renderer, screen_width, screen_height);

    return renderer;
}

SDL_Texture* load_texture(const char* filename, SDL_Renderer* renderer)
{
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading", filename);

  SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
  if(texture == NULL) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Loading texture...", IMG_GetError());

  return texture;
}

SDL_Texture* load_text_texture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

Mix_Music *load_music(const char* path)
{
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"Could not load music! SDL_mixer Error: %s", Mix_GetError());}
    return gMusic;
}

void play(Mix_Music *gMusic)
{
    if (gMusic == nullptr) return;

    Mix_VolumeMusic(60);
    if (Mix_PlayingMusic() == 0) Mix_PlayMusic( gMusic, -1 );
    else if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
}

Mix_Chunk* load_sound(const char* path)
{
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr) {SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"Could not load sound! SDL_mixer Error: %s", Mix_GetError());}

    return gChunk;
}

void play(Mix_Chunk* gChunk)
{
    if (gChunk != nullptr)
    {
        Mix_VolumeChunk(gChunk, 200);

        Mix_PlayChannel( -1, gChunk, 0 );
    }
}

void quit_SDL(SDL_Window* window, SDL_Renderer* renderer)
{
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


