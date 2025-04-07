#ifndef _PARAMERTERS_H
#define _PARAMERTERS_H

// Window_play
const int screen_width = 1200; // The width of the screen
const int screen_height = 600; // The height of the screen
const char* NAME_OF_GAME = "Dinosaur Runner";


// Window restart
const int restart_width = 600;
const int restart_height = 400;

// Ground
const int ground_level = 490; // Position of the ground in the window
int background_pos = 0 ; // Position of the background to transit screen

// Score
int score = 0; // Points after each game
int high_score = 0; // Records from previous games

// Speed
int game_speed = 1; // Speed of the game increases while you play longer

// Help the dinosaur and the bird move
int check_dino = 1; // Check the order of the dinosaur images to be displayed next
int check_bird = 1; // Check the order of the bird images to be displayed next
int frame_count = 1; // Count gameloop

// Movement characteristics of cactus
const int cactus_speed = 5;
const int min_cactus_distance = 300;
const int max_cactus_distance = 600;

// Font of word
const int font_word = 28;

// Characterists of the bird
const int bird_width = 60;
const int bird_height = 60;



#endif

