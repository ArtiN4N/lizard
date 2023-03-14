#include "../include/raylib.h"
#include "../include/raymath.h"

#include "../include/lizard.h"

#include <stdbool.h>
#include <math.h>


Lizard create_lizard(Color color) {

    Lizard lizard;

    Vector2 start_nub = { cells_x / 2, cells_y / 2 };
    Vector2 nub_2 = { start_nub.x, start_nub.y };
    Vector2 nub_3 = { start_nub.x, start_nub.y };


    //-------------------------------------------------


    lizard.nubs[0] = create_nub(start_nub);
    lizard.nubs[1] = create_nub(nub_2);
    lizard.nubs[2] = create_nub(nub_3);

    lizard.score = 0;

    lizard.color = color;

    lizard.direction = START;
    lizard.last_direction = START;
    lizard.next_direction = START;


    //-------------------------------------------------


    lizard.death = LoadSound("resources/sfx/death.wav");

    lizard.eat = LoadSound("resources/sfx/eat.wav");

    lizard.moveup = LoadSound("resources/sfx/moveup.wav");
    SetSoundVolume(lizard.moveup, 0.5f);
    
    lizard.moveright = LoadSound("resources/sfx/moveright.wav");
    SetSoundVolume(lizard.moveright, 0.5f);

    lizard.movedown = LoadSound("resources/sfx/movedown.wav");
    SetSoundVolume(lizard.movedown, 0.5f);

    lizard.moveleft = LoadSound("resources/sfx/moveleft.wav");
    SetSoundVolume(lizard.moveleft, 0.5f);

    return lizard;

}


void move_lizard(Lizard* lizard, MoveDirection* move_buffer) {

    if (move_buffer[0] == START) return;

    if (lizard->direction == NORTH && move_buffer[0] == SOUTH) return;
    if (lizard->direction == SOUTH && move_buffer[0] == NORTH) return;

    if (lizard->direction == EAST && move_buffer[0] == WEST) return;
    if (lizard->direction == WEST && move_buffer[0] == EAST) return;

    switch(move_buffer[0]) {

    case NORTH:
        PlaySound(lizard->moveup); // move sfx        
        break;
    case SOUTH:
        PlaySound(lizard->movedown); // move sfx        
        break;
    case WEST:
        PlaySound(lizard->moveleft); // move sfx        
        break;
    case EAST:
        PlaySound(lizard->moveright); // move sfx
        break;
    default:
        break;
    }

    lizard->direction = move_buffer[0];
    move_buffer[0] = move_buffer[1];
    move_buffer[1] = START;
}


bool hit_wall(Lizard lizard) {

    if (lizard.nubs[0].cellPosition.x < 0) return true;
    if (lizard.nubs[0].cellPosition.y < 0) return true;
    if (lizard.nubs[0].cellPosition.x > cells_x - 1) return true;
    if (lizard.nubs[0].cellPosition.y > cells_y - 1) return true;

    return false;
}

bool hit_self(Lizard lizard) {
    if (lizard.direction == START) return false;

    const int num_nubs = lizard.score + 3;

    for (int i = 1; i < num_nubs; i++) if (Vector2Equals(lizard.nubs[0].cellPosition, lizard.nubs[i].cellPosition)) return true;

    return false;
}


void update_lizard(Lizard* lizard) {

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


void lizard_unload_resources(Lizard* lizard) {

    UnloadSound(lizard->death);
    UnloadSound(lizard->eat);
    UnloadSound(lizard->moveup);
    UnloadSound(lizard->moveright);
    UnloadSound(lizard->movedown);
    UnloadSound(lizard->moveleft);

}

