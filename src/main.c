// <3 Made with raylib
#include "../include/raylib.h"

#include "../include/game.h"

#include <time.h>
#include <stdlib.h>


int main(void) {

    srand(time(NULL)); // Sets random seed for food generation

    SetConfigFlags(FLAG_VSYNC_HINT); // Turns on v-sync

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "classic_pong");

    SetExitKey(KEY_NULL); // Disables exiting with escape key

    InitAudioDevice(); // Initialize audio device for sfx
    SetMasterVolume(0.5f); // Set global volume for sfx

    Game game = initial_game_state();

    //------------------------------------------------------


    while (!game.close && !WindowShouldClose()) { // Main game loop
        
        float dt = GetFrameTime();


        //------------------------------------------------------


        handle_input(&game, dt);

        step_physics(&game, dt);

        draw_game(game);

    }


    //------------------------------------------------------


    unload_resources(&game);

    CloseAudioDevice();

    CloseWindow();

    return 0;

}
