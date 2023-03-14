#ifndef NUB_H
#define NUB_H

#include "raylib.h"

//-- SCREEN DIMENSIONS --
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define cells_x 15
#define cells_y 15
#define cell_size 40
//-----------------------

// Nub is a single cell.
// A lizard is made of multiple nubs
typedef struct { 
    Vector2 cellPosition;

    Vector2 explodePosition;
    Vector2 explodeVelocity;
} Nub;


// Creates a default nub. Returns a nub struct.
Nub create_nub(Vector2 cellPosition);

void explode_nub(Nub* nub, Rectangle play_area);

void kill_nub(Nub* nub, float dt);

void move_nub(Nub* nub, Vector2 cellPosition);

void draw_nub(Nub nub, Color color, Rectangle play_area);

#endif