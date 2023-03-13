#include "../include/raylib.h"

#include "../include/nub.h"


Nub create_nub(Vector2 cellPosition) {

    Nub nub;

    nub.cellPosition = cellPosition;

    return nub;

}


void move_nub(Nub* nub, Vector2 cellPosition) {
    nub->cellPosition = cellPosition;
}


void draw_nub(Nub nub, Color color, Rectangle play_area) {

    const float pos_x = play_area.x + nub.cellPosition.x * cell_size;
    const float pos_y = play_area.y + nub.cellPosition.y * cell_size;

    DrawRectangle(pos_x, pos_y, cell_size, cell_size, color);

}