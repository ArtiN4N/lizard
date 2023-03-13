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


void draw_food(Food food) {
    DrawRectangle(food.cellPosition.x * cell_size, food.cellPosition.y * cell_size, cell_size, cell_size, food.color);
}