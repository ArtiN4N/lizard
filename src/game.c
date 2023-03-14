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

    const float move_timer_length = 0.1f;
    const bool move_loop = true;


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

    game.move_timer = create_timer(move_timer_length, move_loop);
    game.move_timer.elapsed = move_timer_length;
    game.move_timer.finished = true;
    pause_unpause_timer(&game.move_timer);

    game.input_buffer[0] = START;
    game.input_buffer[1] = START;

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

    game->input_buffer[0] = START;
    game->input_buffer[1] = START;

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


    int insert_index = 0;

    if (game->input_buffer[0] != START) insert_index = 1;
    if (game->input_buffer[1] != START) return;

    switch(GetKeyPressed()) {

    case KEY_W:
        game->input_buffer[insert_index] = NORTH;
        break;
    case KEY_A:
        game->input_buffer[insert_index] = WEST;
        break;
    case KEY_S:
        game->input_buffer[insert_index] = SOUTH;
        break;
    case KEY_D:
        game->input_buffer[insert_index] = EAST;
        break;
    default:
        return;
    
    }

    game->move_timer.paused = false;
    //move_lizard(&game->lizard, game->input_buffer[1]);

}


void step_physics(Game* game, float dt) {

    if (game->screen_event != PLAY) return;

    step_timer(&game->move_timer, dt);

    game->time += dt;

    if (game->move_timer.finished) {
        move_lizard(&game->lizard, game->input_buffer);
        update_lizard(&game->lizard);
    }

    if (Vector2Equals(game->lizard.nubs[0].cellPosition, game->food.cellPosition)) {
        add_nub(&game->lizard);
        regenerate_food(&game->food, game->lizard);
    }

    if (hit_wall(game->lizard) || hit_self(game->lizard)) {
        game->screen_event = GAMEOVER;
    }

}


Color get_gradient_in_time(Color start_color, Color end_color, float elapsed, float length) {

    float completion_level = elapsed / length;

    if (completion_level > 1.0f) completion_level = 1.0f;

    Color ret = start_color;

    ret.r = start_color.r * ( 1 - completion_level ) + end_color.r * completion_level;
    ret.g = start_color.g * ( 1 - completion_level ) + end_color.g * completion_level;
    ret.b = start_color.b * ( 1 - completion_level ) + end_color.b * completion_level;

    return ret;

}


void draw_player_score(Color start_color, Color end_color, int score) {


    const char* text = TextFormat("score = %d", score);

    const int font_size = 40;

    const float text_width = MeasureText(text, font_size);

    const float text_x = (SCREEN_WIDTH + cell_size * cells_x) / 2.0f - text_width; 
    const float text_y = (SCREEN_HEIGHT - cell_size * cells_y) / 4.0f - font_size / 2.0f;

    const Color score_color = get_gradient_in_time(start_color, end_color, score, 64.0f);


    //-----------------------------------------------------------------------


    DrawText(text, text_x, text_y, font_size, score_color);

}



void draw_time(Color start_color, Color end_color, float time) {


    const char* text = TextFormat("time = %.1f", time);
    const int font_size = 40;

    const float text_x = (SCREEN_WIDTH - cell_size * cells_x) / 2.0f;
    const float text_y = (SCREEN_HEIGHT - cell_size * cells_y) / 4.0f - font_size / 2.0f;
    // 


    //-----------------------------------------------------------------------------


    Color time_color = get_gradient_in_time(start_color, end_color, time, 90.0f);

    DrawText(text, text_x, text_y, font_size, time_color);

}

void draw_board(Color foreground, Color background, Rectangle play_area) {
    for (int x = 0; x < cells_x; x++) {
        for (int y = 0; y < cells_y; y++) {

            Color color = foreground;

            if ((x + y) % 2 == 0) color = background;
            else color.a *= 0.3f;

            DrawRectangle(play_area.x + x * cell_size, play_area.y + y * cell_size, cell_size, cell_size, color);
        }
    }
}


void draw_play(Game game) {

    draw_board(game.palette[FOREGROUND], game.palette[BACKGROUND], game.play_area);

    draw_lizard(game.lizard, game.play_area);
    draw_food(game.food, game.play_area);

    draw_time(game.palette[SECONDARY], game.palette[PRIMARY], game.time);

    draw_player_score(game.palette[SECONDARY], game.palette[PRIMARY], game.lizard.score);

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

    font_size = 30;
    const char* play_text = "Press R to play";
    float play_text_x = (SCREEN_WIDTH - MeasureText(play_text, font_size)) / 2.0f;
    float play_text_y = ((SCREEN_HEIGHT - font_size) / 2.0f);
    DrawText(play_text, play_text_x, play_text_y, font_size, game.palette[PRIMARY]);


    //--------------------------------------------------------------------------------------------------


    font_size = 20;
    const char* multi_paddle1_text = "Use W A S D to move";
    float multi_paddle1_text_x = ( SCREEN_WIDTH - MeasureText(multi_paddle1_text, font_size)) / 2.0f;
    float multi_paddle1_text_y = play_text_y + 50.0f;
    DrawText(multi_paddle1_text, multi_paddle1_text_x, multi_paddle1_text_y, font_size, game.palette[FOREGROUND]);


    //--------------------------------------------------------------------------------------------------


    font_size = 30;
    const char* exit_text = "Press BACKSPACE to exit";
    float exit_text_x = (SCREEN_WIDTH - MeasureText(exit_text, font_size)) / 2.0f;
    float exit_text_y = multi_paddle1_text_y + 100.0f;
    DrawText(exit_text, exit_text_x, exit_text_y, font_size, game.palette[SECONDARY]);
    
}


void draw_gameover(Game game) {

    const float margin = (SCREEN_HEIGHT - cells_y * cell_size) / 2.0f;

    const float background_height = cell_size * 5;

    Rectangle background = { 0, margin + cell_size * 5, SCREEN_WIDTH, background_height };

    DrawRectangleRec(background, game.palette[BACKGROUND]);

    DrawRectangleLinesEx(background, 5, game.palette[FOREGROUND]);


    //--------------------------------------------------------------------------------------------------


    int font_size = 100;
    const char* title_text = "YOU DIED!";
    const float title_text_x = (SCREEN_WIDTH - MeasureText(title_text, font_size)) / 2.0f;
    const float title_text_y = (SCREEN_HEIGHT - font_size) / 2.0f - 10;

    DrawText(title_text, title_text_x, title_text_y, font_size, game.palette[SECONDARY]);


    //--------------------------------------------------------------------------------------------------


    const float author_text_y = title_text_y + font_size;
    font_size = 20;
    const char* author_text = "Press R to restart";
    const float author_text_x = (SCREEN_WIDTH - MeasureText(author_text, font_size)) / 2.0f;
    
    DrawText(author_text, author_text_x, author_text_y, font_size, game.palette[FOREGROUND]);

}


void draw_game(Game game) {

    BeginDrawing();

        ClearBackground(game.palette[BACKGROUND]);

        if (game.screen_event == MENU) draw_menu(game);
        else draw_play(game);

        if (game.screen_event == GAMEOVER) draw_gameover(game);

    EndDrawing();

}


void unload_resources(Game* game) {

    lizard_unload_resources(&game->lizard);

    UnloadSound(game->menuSelect);

}