#include "entities.h"
#include "physics.h"



void check_paddle_collision(ball_t *pball, paddle_t *ppaddle)
{
    int half = ppaddle->size / 2;	//PADDLE COLLISION WITH DIFFERENT ANGLES

    if (pball->y >= ppaddle->y && pball->x >= ppaddle->x - half
    		&& pball->x <= ppaddle->x + half)
    {
        pball->y = ppaddle->y - 1;
        pball->dy = -1;

        int hit_pos = pball->x - ppaddle->x;  // -2, -1, 0, 1, 2

        if      (hit_pos <= -2)
        	{pball->dx = -2;}  // 45 LEFT
        else if (hit_pos == -1)
        	{pball->dx = -1;}  //90 LEFT
        else if (hit_pos ==  0)
        	{pball->dx =  0;}  // 180 STRAIGHT
        else if (hit_pos ==  1)
        	{pball->dx =  1;}  // 90 RIGHT
        else
        	{pball->dx =  2;}  // 45 LEFT
    }
}

void check_brick_collision(ball_t *pball, brick_t bricks[], level_t *plevel, capsule_t capsules[])
{
    int mid_x = pball->x - (pball->dx / 2);	//CHECKS COLLISION AND THE DIRECTION OF IT
    int mid_y = pball->y;

    for (int i = 0; i < BR_BOARD; i++)
    {
        if (bricks[i].hp <= 0) { continue; }

        int hit     = (pball->x == bricks[i].x && pball->y == bricks[i].y);
        int hit_mid = ((pball->dx == 2 || pball->dx == -2) &&		//PREVENT SKIPPING BRICKS IF MOVES DIAGONALLY
                        mid_x == bricks[i].x && mid_y == bricks[i].y);

        if (hit || hit_mid)
        {
            bricks[i].hp--;

            if (bricks[i].hp <= 0)
            {
                plevel->score += bricks[i].score * plevel->score_mult;

                if (bricks[i].type >= BR_TYPE_4) //SPAWN CAPSULE IF WAS A SPECIAL BLOCK
                      {
                          spawn_capsule(capsules, bricks[i].x, bricks[i].y, bricks[i].type);
                      }
            }
            else
            {
                update_brick_key(&bricks[i]); // UPDATES DAMAGE
            }

            // BOUNCES
            int prev_y = pball->y - pball->dy;

            if (prev_y == bricks[i].y)
            {
                pball->dx = -pball->dx; // LATERAL IMPACT
            }
            else
            {
                pball->dy = -pball->dy; // TOP/BOTTOM IMPACT
            }

            return; // ONE BRICK PER FRAME, NO DOUBLE HITS
        }
    }
}

int check_ball_lost(ball_t balls[], paddle_t *ppaddle, level_t *plevel)
{
    int i, active_count = 0;

    for (i = 0; i < MAX_BALLS; i++)
    {
        if (!balls[i].active)
        {
        	continue;
        }
        if (balls[i].y >= ROWS)
        {
        	balls[i].active = 0;
        }  // DEACTIVATE LOST BALL
        else
        {
        	active_count++;
        }
    }

    if (active_count == 0)
    {
        plevel->lives--;
        if (plevel->lives <= 0) { return -1; }  // GAME OVER
        pad_ball_init(balls, ppaddle, plevel);
        return 1;
    }
    return 0;
}

int check_level_complete(brick_t bricks[])
{
    for (int i = 0; i < BR_BOARD; i++)
    {
        if (bricks[i].hp > 0) { return 0; }
    }
    return 1; // ALL BRICKS DESTROYED
}
