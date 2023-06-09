#include "../include/timer.h"


#include <stdio.h>


Timer create_timer(float length, bool loop) {

    const float elapsed = 0.0f;

    const bool paused = false;

    const bool finished = false;


    //--------------------------------------------------------


    Timer timer = { elapsed, length, paused, loop, finished };


    //--------------------------------------------------------


    return timer;

}


void pause_unpause_timer(Timer* timer) { timer->paused = !timer->paused; }


void reset_timer(Timer* timer) {

    timer->finished = false;
    timer->elapsed = 0.0f;

}


void step_timer(Timer* timer, float dt) {

    if (timer->paused) return;


    //-------------------------------------------


    if (!timer->finished) timer->elapsed += dt;
    if (timer->elapsed < timer->length) return;


    //-------------------------------------------


    if (timer->loop) {
        if (timer->finished) {
            reset_timer(timer); // Let timer be flagged as finished for one frame before looping
            return;
        }
        timer->finished = true;
    } else { // Update timer to be finished
        timer->elapsed = timer->length;
        timer->finished = true;
    }
}
