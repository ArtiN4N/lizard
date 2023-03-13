#include "../include/raylib.h"
#include "../include/raymath.h"

#include "../include/lizard.h"

#include <stdbool.h>
#include <math.h>


Lizard create_lizard(Color color) {

    Lizard lizard;

    lizard.cellPosition = Vector2Zero();

    lizard.score = 0;

    lizard.color = color;

    lizard.direction = START;

    return lizard;

}


void move_lizard(Lizard* lizard, MoveDirection direction) {

    if (lizard->direction != START) {
        if (lizard->direction == NORTH && direction == SOUTH) return;
        if (lizard->direction == SOUTH && direction == NORTH) return;

        if (lizard->direction == EAST && direction == WEST) return;
        if (lizard->direction == WEST && direction == EAST) return;

    }

    lizard->direction = direction;

}


bool hit_wall(Lizard lizard) {

    if (lizard.cellPosition.x < 0) return true;
    if (lizard.cellPosition.y < 0) return true;
    if (lizard.cellPosition.x > cells_x - 1) return true;
    if (lizard.cellPosition.y > cells_y - 1) return true;

    return false;
}


void update_lizard(Lizard* lizard) {

    switch(lizard->direction) {

    case NORTH:
        lizard->cellPosition.y--;
        return;
    case SOUTH:
        lizard->cellPosition.y++;
        return;
    case WEST:
        lizard->cellPosition.x--;
        return;
    case EAST:
        lizard->cellPosition.x++;
        return;
    default:
        return;

    }

}

void draw_lizard(Lizard lizard, Rectangle play_area) {

    const float pos_x = play_area.x + lizard.cellPosition.x * cell_size;
    const float pos_y = play_area.y + lizard.cellPosition.y * cell_size;

    DrawRectangle(pos_x, pos_y, cell_size, cell_size, lizard.color);
}

void draw_lizard_score(int score, Color score_color, Color start_color) {
    float score_factor = score / 50.0f; // The closer the score is to 50, the more colorful the text is
    if (score_factor >= 1.0f) score_factor = 1.0f;

    const int inverse_r = 255 - score_color.r;
    const int inverse_g = 255 - score_color.g;
    const int inverse_b = 255 - score_color.b;
    const int inverse_a = 255 - score_color.a;

    score_color.r = start_color.r - inverse_r * score_factor; 
    score_color.g = start_color.g - inverse_g * score_factor; 
    score_color.b = start_color.b - inverse_b * score_factor;
    score_color.a = start_color.a - inverse_a * score_factor; // The higher the score, the closer the score text is to player color


    //-----------------------------------------------------------------------


    const char* text = TextFormat("%d", score);

    const int font_size = 60;

    const float text_width = MeasureText(text, font_size);

    const float text_x = (SCREEN_WIDTH - text_width) / 2.0f;
    const float text_y = 50.0f;


    //-----------------------------------------------------------------------


    DrawText(text, text_x, text_y, font_size, score_color);
}

void lizard_unload_resources(Lizard* lizard) {

}

