#include "../include/raylib.h"

#include "../include/nub.h"

#include <stdlib.h>

Nub create_nub(Vector2 cellPosition) {

    Nub nub;

    nub.cellPosition = cellPosition;

    return nub;

}


void explode_nub(Nub* nub, Rectangle play_area) {

    const int y_range = 1000;
    const int y_max = 1500;

    const int x_range = 200;
    const int x_max = 250;

    int x_sign = 1;
    if (rand() % 2 == 1) x_sign = -1;

    const int rand_x = (x_max - rand() % x_range) * x_sign;
    const int rand_y = (y_max - rand() % y_range) * -1;

    nub->explodeVelocity = (Vector2) { rand_x, rand_y };

    nub->explodePosition.x = play_area.y + nub->cellPosition.x * cell_size;
    nub->explodePosition.y = play_area.y + nub->cellPosition.y * cell_size;
}


void kill_nub(Nub* nub, float dt) {
    const float gravity = 1500.0f;

    nub->explodePosition.x += nub->explodeVelocity.x * dt;
    nub->explodePosition.y += nub->explodeVelocity.y * dt;

    nub->explodeVelocity.y += gravity * dt;
}


void move_nub(Nub* nub, Vector2 cellPosition) {
    nub->cellPosition = cellPosition;
}


void draw_nub(Nub nub, Color color, Rectangle play_area) {

    if (nub.explodeVelocity.x != 0) {
        DrawRectangle(nub.explodePosition.x, nub.explodePosition.y, cell_size, cell_size, color);

        return;
    }

    const float pos_x = play_area.x + nub.cellPosition.x * cell_size;
    const float pos_y = play_area.y + nub.cellPosition.y * cell_size;

    DrawRectangle(pos_x, pos_y, cell_size, cell_size, color);

}