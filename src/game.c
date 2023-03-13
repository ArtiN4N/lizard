#include "../include/raylib.h"
#include "../include/raymath.h"

#include "../include/game.h"

#include <stdbool.h>


Game initial_game_state() {

    Game game;

    const float play_area_width = cells_x * cell_size;
    const float play_area_height = cells_y * cell_size;

    const float play_area_x = (SCREEN_WIDTH - play_area_width) / 2.0f;
    const float play_area_y = (SCREEN_HEIGHT - play_area_height) / 2.0f;


    //--------------------------------------------------------------------------


    game.palette[BACKGROUND] = (Color) { 15, 27, 38, 255 }; // r, g, b, a
    
    game.palette[FOREGROUND] = (Color) { 245, 232, 209, 255 };
    
    game.palette[PRIMARY]    = (Color) { 32, 165, 166, 255 };

    game.palette[SECONDARY]  = (Color) { 221, 86, 57, 255 };

    game.palette[BASICBLACK] = BLACK;

    game.palette[BASICWHITE] = WHITE;

    //--------------------------------------------------------------------------


    game.lizard = create_lizard(game.palette[PRIMARY]);
    game.food = create_food(game.palette[SECONDARY]);

    game.time = 0.0f;

    game.close = false;

    game.screen_event = MENU;

    game.play_area = (Rectangle) { play_area_x, play_area_y, play_area_width, play_area_height };


    //--------------------------------------------------------------------------


    game.menuSelect = LoadSound("resources/sfx/menu.wav");

    SetSoundVolume(game.menuSelect, 0.3f);


    //--------------------------------------------------------------------------


    return game;

}


void reset_game(Game* game) {

    game->lizard = create_lizard(game->palette[PRIMARY]);
    game->food = create_food(game->palette[SECONDARY]);

    game->screen_event = PLAY;

    game->time = 0.0f;

}


void handle_input(Game* game, float dt) {

    if (IsKeyDown(KEY_BACKSPACE)) { // Pressing backspace exits the game
        game->close = true;
        return;
    }

    if (game->screen_event == GAMEOVER && IsKeyDown(KEY_R)) { // R resets the game
        PlaySound(game->menuSelect); // menu sfx
        reset_game(game);
        return;
    }

    if (game->screen_event == MENU && IsKeyDown(KEY_R)) { // R is used to start game
        PlaySound(game->menuSelect); // menu sfx
        game->screen_event = PLAY;
        return;
    }


    //---------------------------------------------------------------------------------------------------------


    // TODO: handle player movement

}


void step_physics(Game* game, float dt) {

    if (game->screen_event != PLAY) return;

    game->time += dt;

    update_lizard(&game->lizard);

    if (Vector2Equals(game->lizard.cellPosition, game->food.cellPosition)) {
        game->lizard.score++;
        regenerate_food(&game->food, game->lizard);
    }

    if (hit_wall(game->lizard)) {
        game->screen_event = GAMEOVER;
    }

}


void draw_time(float time, Color time_color, Color start_color) {

    float timer_factor = time / 60.0f;
    if (timer_factor >= 1.0f) timer_factor = 1.0f;


    //-----------------------------------------------------------------------------


    const float r_offset = (255 - time_color.r) * timer_factor;
    const float g_offset = (255 - time_color.g) * timer_factor;
    const float b_offset = (255 - time_color.b) * timer_factor;
    const float a_offset = (255 - time_color.a) * timer_factor;
    time_color = (Color) { start_color.r - r_offset, start_color.g - g_offset, start_color.b - b_offset, start_color.a - a_offset };


    //-----------------------------------------------------------------------------


    const char* text = TextFormat("%.1f", time);
    const int font_size = 40;

    const float text_x = (SCREEN_WIDTH - MeasureText(text, font_size)) / 2.0f;
    const float text_y = SCREEN_HEIGHT - 70.0f;

    //-----------------------------------------------------------------------------


    DrawText(text, text_x, text_y, font_size, time_color);

}


void draw_play(Game game) {

    draw_time(game.time, game.palette[PRIMARY], game.palette[SECONDARY]);

    draw_lizard(game.lizard);
    draw_food(game.food);

    draw_lizard_score(game.lizard.score, game.palette[PRIMARY], game.palette[SECONDARY]);

}


void draw_menu(Game game) {

    int font_size = 100;
    const char* title_text = "lizard";
    const float title_text_x = (SCREEN_WIDTH - MeasureText(title_text, font_size)) / 2.0f;
    const float title_text_y = ((SCREEN_HEIGHT - font_size) / 2.0f) - 250.0f;
    DrawText(title_text, title_text_x, title_text_y, font_size, game.palette[PRIMARY]);


    //--------------------------------------------------------------------------------------------------


    const float author_text_y = title_text_y + font_size + 20;
    font_size = 20;
    const char* author_text = "Made by ArtiN4N";
    const float author_text_x = (SCREEN_WIDTH - MeasureText(author_text, font_size)) / 2.0f;
    
    DrawText(author_text, author_text_x, author_text_y, font_size, game.palette[FOREGROUND]);


    //--------------------------------------------------------------------------------------------------

    font_size = 40;
    const char* play_text = "Press R to play";
    float play_text_x = (SCREEN_WIDTH - MeasureText(play_text, font_size)) / 2.0f;
    float play_text_y = ((SCREEN_HEIGHT - font_size) / 2.0f) - 50.0f;
    DrawText(play_text, play_text_x, play_text_y, font_size, game.palette[PRIMARY]);


    //--------------------------------------------------------------------------------------------------


    font_size = 30;
    const char* multi_paddle1_text = "Use W A S D to move";
    float multi_paddle1_text_x = ( SCREEN_WIDTH - MeasureText(multi_paddle1_text, font_size)) / 2.0f;
    float multi_paddle1_text_y = play_text_y + 50.0f;
    DrawText(multi_paddle1_text, multi_paddle1_text_x, multi_paddle1_text_y, font_size, game.palette[FOREGROUND]);


    //--------------------------------------------------------------------------------------------------


    font_size = 40;
    const char* exit_text = "Press BACKSPACE to exit";
    float exit_text_x = (SCREEN_WIDTH - MeasureText(exit_text, font_size)) / 2.0f;
    float exit_text_y = multi_paddle1_text_y + 200.0f;
    DrawText(exit_text, exit_text_x, exit_text_y, font_size, game.palette[SECONDARY]);
    
}

void draw_game(Game game) {

    BeginDrawing();

        ClearBackground(game.palette[BACKGROUND]);

        if (game.screen_event == MENU) draw_menu(game);
        else draw_play(game);

    EndDrawing();

}


void unload_resources(Game* game) {

    lizard_unload_resources(&game->lizard);

    UnloadSound(game->menuSelect);

}