#ifndef LIZARD_H
#define LIZARD_H

#include "raylib.h"

//-- SCREEN DIMENSIONS --
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800
#define cells_x 20
#define cells_y 20
#define cell_size 25
//-----------------------

// Enum to designate menu, win, and play screens.
typedef enum MoveDirection { START = 0, NORTH, EAST, SOUTH, WEST } MoveDirection;

// The lizard is a set of liard squares moving in any of the four cardinal directions
// Lizards get longer whenever they eat food.
// Lizards die when they hit a wall.
typedef struct { 
    Vector2 cellPosition;

    float speed;

    int score;

    Color color;

    MoveDirection direction;
} Lizard;


// Creates a default lizard. Returns a lizard struct.
Lizard create_lizard(Color color);

void move_lizard(Lizard* lizard, MoveDirection direction);

bool hit_wall(Lizard lizard);

void update_lizard(Lizard* lizard);

void draw_lizard(Lizard lizard);

void draw_lizard_score(int score, Color score_color, Color start_color);

void lizard_unload_resources(Lizard* lizard);

#endif