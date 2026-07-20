#include "powers.h"
#include "entities.h"


void spawn_ball(ball_t balls[], int x, int y, float speed)
{
    int i;	//SPAWNS BALL WITH POWER-UP
    for (i = 1; i < MAX_BALLS; i++)
    {
        if (!balls[i].active)
        {
            balls[i].x      = x;
            balls[i].y      = y;
            balls[i].dx     = (i % 2 == 0) ? 1 : -1;  // ALTERNATE DIRECTIONS
            balls[i].dy     = -1;
            balls[i].hp     = LIFE_BALL;
            balls[i].speed  = speed;
            balls[i].active = 1;
            return;
        }
    }
}



void spawn_capsule(capsule_t capsules[], int x, int y, int type)
{
    int i;
    for (i = 0; i < MAX_CAPSULES; i++)
    {
        if (!capsules[i].active)
        {
            capsules[i].x      = x;
            capsules[i].y      = y;
            capsules[i].type   = type;
            capsules[i].active = 1;
            return;
        }
    }
}

void activate_power(int type, paddle_t *ppaddle, ball_t balls[], powers_t active_powers[])
{
    switch(type)
    {
        case BR_TYPE_4:  // EXPAND PADDLE
            if (ppaddle->size < MAX_PADDLE_SIZE) { ppaddle->size += 2; }
            active_powers[0].type     = BR_TYPE_4;
            active_powers[0].duration = POWER_DURATION;
            break;

        case BR_TYPE_5:  // EXTRA BALL
            spawn_ball(balls, ppaddle->x, ppaddle->y - 2, balls[0].speed);
            break;

        case BR_TYPE_6:  // SLOW BALL
            if (balls[0].speed > 1.0f) { balls[0].speed -= 0.5f; }
            active_powers[1].type     = BR_TYPE_6;
            active_powers[1].duration = POWER_DURATION;
            break;

        case BR_TYPE_7:  // MULTI-BALL
            spawn_ball(balls, ppaddle->x - 2, ppaddle->y - 2, balls[0].speed);
            spawn_ball(balls, ppaddle->x + 2, ppaddle->y - 2, balls[0].speed);
            break;
    }
}



void update_capsules(capsule_t capsules[], paddle_t *ppaddle, ball_t balls[], powers_t active_powers[])
{
    int i;
    int half = ppaddle->size / 2;

    for (i = 0; i < MAX_CAPSULES; i++)
    {
        if (!capsules[i].active) { continue; }

        capsules[i].y++;

        // CAPSULE OFF SCREEN
        if (capsules[i].y >= ROWS)
        {
            capsules[i].active = 0;
            continue;
        }

        // CAUGHT BY PADDLE
        if (capsules[i].y == ppaddle->y &&
            capsules[i].x >= ppaddle->x - half &&
            capsules[i].x <= ppaddle->x + half)
        {
            activate_power(capsules[i].type, ppaddle, balls, active_powers);
            capsules[i].active = 0;
        }
    }
}

void update_powers(powers_t active_powers[], paddle_t *ppaddle, ball_t balls[])
{
    if (active_powers[0].duration > 0)
    {
        active_powers[0].duration--;
        if (active_powers[0].duration == 0)
        {
            if (ppaddle->size > INIT_SIZE_PADDLE) { ppaddle->size -= 2; }
        }
    }
    if (active_powers[1].duration > 0)
    {
        active_powers[1].duration--;
        if (active_powers[1].duration == 0) { balls[0].speed += 0.5f; }
    }
}
