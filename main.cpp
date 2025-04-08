#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include <ctime>
#include <vector>

#include "cactus.h"
#include "parameters.h"
#include "graphic.h"
#include "bird_animation.h"
#include "dino_animation.h"
#include "cactus_animation.h"
#include "check_touch.h"


using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));

    // 1. Declare SDL, window, renderer
    SDL_Window* window = init_SDL(screen_width, screen_height, NAME_OF_GAME);
    SDL_Renderer* renderer = create_renderer(window);

    // 2. Load textures, fonts, sounds
        // 2.1.Load textures
            // 2.1.1 Dino textures
            SDL_Texture* dino_texture1 = load_texture("dino1.png", renderer);
            SDL_Texture* dino_texture2 = load_texture("dino2.png", renderer);
            SDL_Texture* dino_texture3 = load_texture("dino3.png", renderer);
            SDL_Texture* dino_texture4 = load_texture("dino4.png", renderer);
            SDL_Texture* dino_texture5 = load_texture("dino5.png", renderer);
            SDL_Texture* dino_texture6 = load_texture("dino6.png", renderer);

            // 2.1.2 Bird textures
            SDL_Texture* bird_texture1 = load_texture("bird1.png", renderer);
            SDL_Texture* bird_texture2 = load_texture("bird2.png", renderer);
            SDL_Texture* bird_texture3 = load_texture("bird3.png", renderer);

            // 2.1.3 Cactus textures
            SDL_Texture* cactus_texture = load_texture("cactus.png", renderer);

            // 2.1.4 Screen textures
            SDL_Texture* background_texture = load_texture("background.png", renderer);
            SDL_Texture* start_game_texture = load_texture("start_game.png", renderer);
            SDL_Texture* restart_game_texture = load_texture("restart.png", renderer);

        // 2.2 Load music and sounds
        Mix_Music* music = load_music("music.mp3");
        Mix_Chunk* jump_sound = load_sound("jump.mp3");
        Mix_Chunk* gameover_sound = load_sound("gameover.mp3");

        // 2.3 Load font for rendering text
        TTF_Font* font = TTF_OpenFont("FONT1.ttf", font_size);
        SDL_Color text_color = { 101, 67, 33 };

    // 3. Show start screen
    SDL_RenderCopy(renderer, start_game_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // 4. Wait for user to start the game
    bool quit = false;
    bool gameover = false;
    bool waiting_for_start = true;
    SDL_Event event;

    while (waiting_for_start)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                waiting_for_start = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                waiting_for_start = false;
                play(music);
            }
        }
    }

    // 5. Update animation of bird, cactus, dinosaus
        // 5.1 Update dino animation
        Dino dino;
        dino.y = ground_level - dino_height;
        dino.v = 0;


        dino_animation dino_data;
        dino_data.renderer = renderer;
        dino_data.dino_is_jumping = false;
        dino_data.check_dino = check_dino;
        dino_data.dino_textures[0] = dino_texture1;
        dino_data.dino_textures[1] = dino_texture2;
        dino_data.dino_textures[2] = dino_texture3;
        dino_data.dino_textures[3] = dino_texture4;
        dino_data.dino_textures[4] = dino_texture5;
        dino_data.dino_textures[5] = dino_texture6;

        // 5.2 Update bird animation
        bird_animation bird_data;
        bird_data.renderer = renderer;
        bird_data.screen_width = screen_width;
        bird_data.ground_level = ground_level;
        bird_data.dino_height = dino_height;
        bird_data.check_bird = check_bird;
        bird_data.bird_textures[0] = bird_texture1;
        bird_data.bird_textures[1] = bird_texture2;
        bird_data.bird_textures[2] = bird_texture3;
        bird_data.bird_width = bird_width;
        bird_data.bird_height = bird_height;

        // 5.3 Update cactus animation
        cactus_animation cactus_data;
        cactus_data.renderer = renderer;
        cactus_data.cactus_texture = cactus_texture;
        cactus_data.ground_level = ground_level;
        // Store cactuses
        vector<Cactus> cactuses;
        // Random next distance between two cactuses
        int next_distance_cactus = min_cactus_distance + rand() % (max_cactus_distance - min_cactus_distance);


    // 6. Gameloop
    while (!quit)
    {
        // 6.1 Handle input and events
        while (SDL_PollEvent(&event))
        {
            // 6.1.1 Quit game if click 'x' button
            if (event.type == SDL_QUIT) quit = true;

            // 6.1.2 Handle key press events when the game is running
            if (event.type == SDL_KEYDOWN && !gameover)
            {
                if (!dino_data.dino_is_jumping)
                {
                    dino.v = jump;
                    dino_data.dino_is_jumping = true;
                    play(jump_sound);
                }
            }

            // 6.1.3 Restart game after game over
            if (gameover && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            {
                playing_gameover_sound = false;

                Mix_HaltChannel(-1);
                play(music);

                dino_data.dino_is_jumping = false;
                dino.v = 0;
                dino.y = ground_level - dino_height;

                cactuses.clear();
                next_distance_cactus = min_cactus_distance + rand() % (max_cactus_distance - min_cactus_distance);

                if (score > high_score) high_score = score;
                score = 0;
                game_speed = 1;
                gameover = false;
            }
        }

        // 6.2 Game handling without collision
        if (!gameover)
        {
            // 6.2.1 Update dino animation
            if (dino_data.dino_is_jumping)
            {
                dino.v += gravity;
                dino.y += dino.v;

                if (dino.y >= ground_level - dino_height)
                {
                    dino.y = ground_level - dino_height;
                    dino_data.dino_is_jumping = false;
                }
            }

            // 6.2.2 Random new cactus if need
            next_distance_cactus -= cactus_speed * game_speed;
            if (next_distance_cactus <= 0)
            {
                next_distance_cactus = min_cactus_distance + rand() % (max_cactus_distance - min_cactus_distance + 1);
                Cactus new_cactus;
                new_cactus.type = rand() % 2;
                new_cactus.x = screen_width;
                cactuses.push_back(new_cactus);
            }

            // 6.2.3 Move cactuses and check touch with dino
            for (int i = 0; i < cactuses.size(); i++)
            {
                cactuses[i].x -= cactus_speed * game_speed;

                // Create a box smaller than dino to check touch with the cactus
                int box_dino_x = dino_x * 1.1;
                int box_dino_y = dino.y ;
                int box_dino_width = dino_width * 0.8;
                int box_dino_height = dino_height * 0.8;
                SDL_Rect dino_rect = { box_dino_x, box_dino_y, box_dino_width, box_dino_height };

                // Determine the cactus is large or small
                int cactus_height;
                if (cactuses[i].type == 0) { cactus_height = small_cactus_height; }
                else { cactus_height = big_cactus_height; }
                SDL_Rect cactus_rect = { cactuses[i].x, ground_level - cactus_height, cactus_width, cactus_height };

                if (check_touch_two_rect(dino_rect, cactus_rect))
                   { gameover = true; }

                if (cactuses[i].x + cactus_width < 0)
                {
                    cactuses.erase(cactuses.begin() + i);
                    i--;
                }
            }

            // 6.2.4 Update score and difficulty
            score ++;
            if (score % 100 == 0) game_speed += add_game_speed;

            // 6.2.5 Scroll and render background
            background_pos -= cactus_speed * game_speed;
            if (background_pos <= -screen_width) background_pos = 0;

            SDL_RenderClear(renderer);
            SDL_Rect bg_rect1 = { background_pos, 0, screen_width, screen_height };
            SDL_Rect bg_rect2 = { background_pos + screen_width, 0, screen_width, screen_height };
            SDL_RenderCopy(renderer, background_texture, NULL, &bg_rect1);
            SDL_RenderCopy(renderer, background_texture, NULL, &bg_rect2);

            // 6.2.6 Update and render all animated objects

                // Cycle through animation frames (reset to 1 after reaching 14 for looping effect)
                frame_count++;
                if (frame_count == 15) frame_count = 1;

                // Update dino animation data and render it
                dino_data.frame_count = frame_count;
                dino_data.dino_rect = { dino_x, dino.y, dino_width, dino_height };
                render_dino_animation(dino_data);

                // Update bird animation frame and render flying birds
                bird_data.frame_count = frame_count;
                render_bird_animation(bird_data);

                // Update cactus list animation frame and render it
                cactus_data.cactuses = cactuses;
                render_cactus_animation(cactus_data);

            // 6.2.7 Show score when game is running
            stringstream ss;
            ss << "Score:  " << score;
            string temp = ss.str();
            SDL_Texture* score_texture = load_text_texture(renderer, font, temp.c_str(), text_color);
            SDL_Rect score_rect;
            SDL_QueryTexture(score_texture, NULL, NULL, &score_rect.w, &score_rect.h);
            score_rect.x = 10;
            score_rect.y = 10;
            SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
            SDL_DestroyTexture(score_texture);
        }
        // 6.3 Handle game when dino touch cactus
        if (gameover && !playing_gameover_sound)
        {
            // 6.3.1 Play gameover sound
            Mix_HaltMusic();
            play(gameover_sound);
            playing_gameover_sound = true;

            // 6.3.2 Show gameover
            SDL_Rect restart_rect = { (screen_width - restart_width) / 2, (screen_height - restart_height) / 2, restart_width, restart_height };
            SDL_RenderCopy(renderer, restart_game_texture, NULL, &restart_rect);

            // 6.3.3 Show score and high score
            stringstream ss;
            ss << "Score:  " << score << "     High score:  " << high_score;
            string temp = ss.str();
            SDL_Texture* score_texture = load_text_texture(renderer, font, temp.c_str(), text_color);
            SDL_Rect score_rect;
            SDL_QueryTexture(score_texture, NULL, NULL, &score_rect.w, &score_rect.h);
            score_rect.x = (screen_width - score_rect.w) / 2;
            score_rect.y = 100;
            SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
            SDL_DestroyTexture(score_texture);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);

    }

    // 7. Delete and quit
    SDL_DestroyTexture(dino_texture1);
    SDL_DestroyTexture(dino_texture2);
    SDL_DestroyTexture(dino_texture3);
    SDL_DestroyTexture(dino_texture4);
    SDL_DestroyTexture(dino_texture5);
    SDL_DestroyTexture(dino_texture6);
    SDL_DestroyTexture(bird_texture1);
    SDL_DestroyTexture(bird_texture2);
    SDL_DestroyTexture(bird_texture3);
    SDL_DestroyTexture(cactus_texture);
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(start_game_texture);
    SDL_DestroyTexture(restart_game_texture);

    TTF_CloseFont(font);
    quit_SDL(window, renderer);
    return 0;
}

