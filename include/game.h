#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#include "lizard.h"
#include "food.h"
#include "timer.h"

//-- SCREEN DIMENSIONS --
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define cells_x 15
#define cells_y 15
#define cell_size 40
//-----------------------

// Enum to designate menu, win, and play screens.
typedef enum ScreenEvent { MENU = 0, PLAY, GAMEOVER, YOUWIN } ScreenEvent;

// Enum for color palette colors.
typedef enum PaletteColors { BACKGROUND = 0, FOREGROUND, PRIMARY, SECONDARY, BASICBLACK, BASICWHITE } PaletteColors;

// The game state stores all relevant data to how to program can adapt and change.
typedef struct {
    Lizard lizard;

    Food food;

    float time;

    Timer move_timer;

    Timer death_timer;

    bool death_flag;

    MoveDirection input_buffer[2];

    bool close;

    ScreenEvent screen_event;

    Sound menuSelect;

    Color palette[6];

    Rectangle play_area;
} Game;

// Creates a default game state. Returns a Game struct.
Game initial_game_state();

void reset_game(Game* game);

void handle_input(Game* game, float dt);

void step_physics(Game* game, float dt);

Color get_gradient_in_time(Color start_color, Color end_color, float elapsed, float length);

void draw_player_score(Color start_color, Color end_color, int score);

// Draws game clock
void draw_time(Color start_color, Color end_color, float time);

void draw_board(Color foreground, Color background, Rectangle play_area);

void draw_gameover(Game game);

void draw_youwin(Game game);

void draw_play(Game game);

void draw_menu(Game game);

void draw_game(Game game);

// Unloads all allocated resources in game
void unload_resources(Game* game);

#endif