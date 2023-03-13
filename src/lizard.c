#include "../include/raylib.h"
#include "../include/raymath.h"

#include "../include/lizard.h"

#include <stdbool.h>
#include <math.h>


Lizard create_lizard(Color color) {

    Lizard lizard;

    Vector2 start_nub = { cells_x / 2, cells_y / 2 };
    Vector2 nub_2 = { start_nub.x + 1, start_nub.y };
    Vector2 nub_3 = { start_nub.x + 2, start_nub.y };


    //-------------------------------------------------


    lizard.nubs[0] = create_nub(start_nub);
    lizard.nubs[1] = create_nub(nub_2);
    lizard.nubs[2] = create_nub(nub_3);

    lizard.score = 0;

    lizard.color = color;

    lizard.direction = START;
    lizard.last_direction = START;
    lizard.next_direction = START;

    return lizard;

}


void move_lizard(Lizard* lizard, MoveDirection direction) {

    if (lizard->direction != START) {
        if (lizard->direction == NORTH && direction == SOUTH) return;
        if (lizard->direction == SOUTH && direction == NORTH) return;

        if (lizard->direction == EAST && direction == WEST) return;
        if (lizard->direction == WEST && direction == EAST) return;

    }

    lizard->next_direction = direction;

    if (lizard->direction != direction) lizard->last_direction = direction;

}


bool hit_wall(Lizard lizard) {

    if (lizard.nubs[0].cellPosition.x < 0) return true;
    if (lizard.nubs[0].cellPosition.y < 0) return true;
    if (lizard.nubs[0].cellPosition.x > cells_x - 1) return true;
    if (lizard.nubs[0].cellPosition.y > cells_y - 1) return true;

    return false;
}


void update_lizard(Lizard* lizard) {


    if (lizard->direction == NORTH && lizard->next_direction == SOUTH) lizard->direction = lizard->last_direction;
    else if (lizard->direction == SOUTH && lizard->next_direction == NORTH) lizard->direction = lizard->last_direction;

    else if (lizard->direction == EAST && lizard->next_direction == WEST) lizard->direction = lizard->last_direction;
    else if (lizard->direction == WEST && lizard->next_direction == EAST) lizard->direction = lizard->last_direction;
    else {
        lizard->last_direction = lizard->direction;
        lizard->direction = lizard->next_direction;
    }

    if (lizard->direction == START) return;

    const int num_nubs = lizard->score + 3;

    for (int i = num_nubs - 1; i > 0; i--) {
        lizard->nubs[i].cellPosition.x = lizard->nubs[i - 1].cellPosition.x;
        lizard->nubs[i].cellPosition.y = lizard->nubs[i - 1].cellPosition.y;
    }
    

    switch(lizard->direction) {

    case NORTH:
        lizard->nubs[0].cellPosition.y--;
        return;
    case SOUTH:
        lizard->nubs[0].cellPosition.y++;
        return;
    case WEST:
        lizard->nubs[0].cellPosition.x--;
        return;
    case EAST:
        lizard->nubs[0].cellPosition.x++;
        return;
    default:
        return;

    }

}


void add_nub(Lizard* lizard) {
    const int num_nubs = lizard->score + 3;

    Vector2 new_nub = { lizard->nubs[num_nubs - 1].cellPosition.x, lizard->nubs[num_nubs - 1].cellPosition.y };

    lizard->nubs[num_nubs] = create_nub(new_nub);

    lizard->score++;
}


void draw_lizard(Lizard lizard, Rectangle play_area) {

    const int num_nubs = lizard.score + 3;

    for (int i = 0; i < num_nubs; i++) draw_nub(lizard.nubs[i], lizard.color, play_area);

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

