#ifndef LIZARD_H
#define LIZARD_H

#include "raylib.h"

#include "nub.h"

//-- SCREEN DIMENSIONS --
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define cells_x 15
#define cells_y 15
#define cell_size 40
//-----------------------

// Enum to designate menu, win, and play screens.
typedef enum MoveDirection { START = 0, NORTH, EAST, SOUTH, WEST } MoveDirection;

// The lizard is a set of liard squares moving in any of the four cardinal directions
// Lizards get longer whenever they eat food.
// Lizards die when they hit a wall.
typedef struct {
    Nub nubs[256];
    //Vector2 cellPosition;

    int score;

    Color color;

    MoveDirection direction;
    MoveDirection last_direction;
    MoveDirection next_direction;

    Sound death;
    Sound eat;

    Sound moveup;
    Sound moveright;
    Sound movedown;
    Sound moveleft;

} Lizard;


// Creates a default lizard. Returns a lizard struct.
Lizard create_lizard(Color color);

void explode_lizard(Lizard* lizard, Rectangle play_area);

void kill_lizard(Lizard* lizard, float dt);

void move_lizard(Lizard* lizard, MoveDirection* move_buffer);

bool hit_wall(Lizard lizard);

bool hit_self(Lizard lizard);

void update_lizard(Lizard* lizard);

void add_nub(Lizard* lizard);

void draw_lizard(Lizard lizard, Rectangle play_area);

void lizard_unload_resources(Lizard* lizard);

#endif