#ifndef _GRAPHIC__H
#define _GRAPHIC__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

void log_error_and_exit(const char* msg, const char* error);

SDL_Window* init_SDL(int screen_width, int screen_height, const char* name_of_game);

SDL_Renderer* create_renderer(SDL_Window* window);

SDL_Texture* load_texture(const char* filename, SDL_Renderer* renderer);

SDL_Texture* load_text_texture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);

Mix_Music *load_music(const char* path);

void play(Mix_Music *gMusic);

Mix_Chunk* load_sound(const char* path);

void play(Mix_Chunk* gChunk);

void quit_SDL(SDL_Window* window, SDL_Renderer* renderer);

#endif
