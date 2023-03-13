#include "../include/raylib.h"
#include "../include/raymath.h"

#include "../include/food.h"


Food create_food(Color color) {

    Food food;

    const float start_x = 5;
    const float start_y = 5;


    //-------------------------------------------------


    food.cellPosition = (Vector2) { start_x, start_y };

    food.color = color;


    //-------------------------------------------------


    return food;

}

void regenerate_food(Food* food, Lizard lizard) {

    const float start_x = 5;
    const float start_y = 5;


    //-------------------------------------------------
    

    food->cellPosition = (Vector2) { start_x, start_y };

}


void draw_food(Food food, Rectangle play_area) {

    const float pos_x = play_area.x + food.cellPosition.x * cell_size;
    const float pos_y = play_area.y + food.cellPosition.y * cell_size;

    DrawRectangle(pos_x, pos_y, cell_size, cell_size, food.color);
}