#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"
#include "lizard.h"

//-- SCREEN DIMENSIONS --
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define cells_x 15
#define cells_y 15
#define cell_size 40
//-----------------------

// Food is a single cell.
// When a lizard runs over the food, it eats the food.
// When food is eaten, a new food is generated randomly
typedef struct { 
    Vector2 cellPosition;

    Color color;
} Food;


// Creates a default food. Returns a food struct.
Food create_food(Color color);

void regenerate_food(Food* food, Lizard lizard);

void draw_food(Food food, Rectangle play_area);

#endif