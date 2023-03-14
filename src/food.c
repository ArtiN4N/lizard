#include "../include/raylib.h"
#include "../include/raymath.h"

#include "../include/food.h"

#include <stdlib.h>


Food create_food(Color color) {

    Food food;

    const int start_x = rand() % cells_x;
    const int start_y = rand() % cells_y;


    //-------------------------------------------------


    food.cellPosition = (Vector2) { start_x, start_y };

    food.color = color;


    //-------------------------------------------------


    return food;

}

void regenerate_food(Food* food, Lizard lizard) {


    Vector2 start = food->cellPosition;

    bool in_lizard = false;

    const int num_nubs = lizard.score + 3;

    do {
        start.x = rand() % cells_x;
        start.y = rand() % cells_y;

        in_lizard = false;

        for (int i = 0; i < num_nubs; i++) if (Vector2Equals(start, lizard.nubs[i].cellPosition)) in_lizard = true;
    } while (in_lizard);
    


    //-------------------------------------------------
    

    food->cellPosition = start;

}


void draw_food(Food food, Rectangle play_area) {

    const float pos_x = play_area.x + food.cellPosition.x * cell_size;
    const float pos_y = play_area.y + food.cellPosition.y * cell_size;

    DrawRectangle(pos_x, pos_y, cell_size, cell_size, food.color);
}