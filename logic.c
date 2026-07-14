/*
 * logic.c
 *
 *  Created on: Jul 12, 2026
 *      Author: progra
 */

#include <stdio.h>
#include <unistd.h>
#include "entities.h"
#include "logic.h"
#include "menu.h"

void brick_init (brick_t bricks[])
{
	int i=0, j=0, k=0;
	for (;i<BR_BOARD;k++)
	{
		for (j=0;j<COLS;j++,i++)
		{
			bricks[i].y=k;
			bricks[i].x=j;
		}
	}
}

void pad_ball_init (ball_t *pball, paddle_t *ppaddle, level_t *plevel)
{
	ppaddle->x= (COLS/2+1);
	ppaddle->y= PADDLE_ROW;
	ppaddle->size= INIT_SIZE_PADDLE;
	ppaddle->dx=0;

	pball->x= (COLS/2+1);
	pball->y= (PADDLE_ROW-1);
	pball->hp= LIFE_BALL;
	pball->speed= plevel->speed_mult;
	pball->dx=0;
	pball->dy=0;
}

void level_init (level_t *plevel)
{
	plevel->level=1;
	plevel->lives= INITIAL_LIVES;
	plevel->speed_mult=1;
	plevel->score=0;
	plevel->ball_count=1;
	plevel->score_mult=1;
}

void init_new_level (level_t *level_info, brick_t bricks[])
{
	switch (level_info->level)
	{
		case 1: init_level_1 (bricks);break;
		case 2: init_level_2 (bricks);break;
		default: init_level_n (bricks);break;
	}

}
void init_level_1(brick_t bricks[])
{
    int i, row, col;

    for (row = 0; row < BR_ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            i = row * COLS + col;
            bricks[i].hp = 0; // empty by default

            if (row == 0 || row == 2 || row == 6 || row == 8)
            {
                set_brick(&bricks[i], BR_TYPE_1);
            }
            else if (row == 3 || row == 5)
            {
                set_brick(&bricks[i], BR_TYPE_2);
            }
            else if (row == 4)
            {
                if      (col == 4)  { set_brick(&bricks[i], BR_TYPE_4); }
                else if (col == 10) { set_brick(&bricks[i], BR_TYPE_5); }
                else                { set_brick(&bricks[i], BR_TYPE_2); }
            }
            // rows 1, 7, 9 → stay empty (hp=0)
        }
    }
}

void init_level_2(brick_t bricks[])
{
    int i = 0;
    for (; i < BR_BOARD; i++)
    {
        set_brick(&bricks[i], BR_TYPE_1); // modify later
    }
}

void init_level_n(brick_t bricks[])
{
    int i = 0;
    for (; i < BR_BOARD; i++)
    {
        set_brick(&bricks[i], BR_TYPE_1); // randomize later
    }
}

void set_brick(brick_t *brick, int type)
{
    brick->type = type;
    switch(type)
    {
        case BR_TYPE_1: brick->hp=1; brick->score=BR_SCORE_1; brick->key=BR_KEY_1; break;
        case BR_TYPE_2: brick->hp=2; brick->score=BR_SCORE_2; brick->key=BR_KEY_2; break;
        case BR_TYPE_3: brick->hp=3; brick->score=BR_SCORE_3; brick->key=BR_KEY_3; break;
        case BR_TYPE_4: brick->hp=1; brick->score=BR_SCORE_4; brick->key=BR_KEY_4; break;
        case BR_TYPE_5: brick->hp=1; brick->score=BR_SCORE_5; brick->key=BR_KEY_5; break;
        case BR_TYPE_6: brick->hp=1; brick->score=BR_SCORE_6; brick->key=BR_KEY_6; break;
        case BR_TYPE_7: brick->hp=1; brick->score=BR_SCORE_7; brick->key=BR_KEY_7; break;
        default:        brick->hp=1; brick->score=BR_SCORE_1; brick->key=BR_KEY_1; break;
    }
}

void update_brick_key(brick_t *brick)
{
    if (brick->type > BR_TYPE_3)
    {
    	return; // power-ups keep their key
    }

    if      (brick->hp == 2)
    {
    	brick->key = BR_KEY_2;
    }
    else if (brick->hp == 1)
    {
    	brick->key = BR_KEY_1;
    }
}

void update_paddle(paddle_t *ppaddle, char key)
{
    if (key==LEFT)
        {ppaddle->dx = -1;}
    else if (key == RIGHT)
    	{ppaddle->dx = 1;}
    else
        {ppaddle->dx = 0;}

    ppaddle->x += ppaddle->dx;

    int half = ppaddle->size / 2; //LIMITS
    if (ppaddle->x - half < 0)
    {
    	ppaddle->x = half;
    }

    if (ppaddle->x + half >= COLS)
    {
    	ppaddle->x = COLS - 1 - half;
    }
}

void update_ball(ball_t *pball)
{
    pball->x += pball->dx;
    pball->y += pball->dy;

    //LEFT AND RIGHT BOUNCE WITH WALLS
    if (pball->x <= 0)
    {
    	pball->x = 0;
    	pball->dx =  1;
    }
    if (pball->x >= COLS - 1)
    {
    	pball->x = COLS - 1;
    	pball->dx = -1;
    }

    // UP BOUNCE WITH WALLS
    if (pball->y <= 0)        { pball->y = 0;         pball->dy =  1; }

}

void check_paddle_collision(ball_t *pball, paddle_t *ppaddle)
{
    int half = ppaddle->size / 2;

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

void check_brick_collision(ball_t *pball, brick_t bricks[], level_t *plevel)
{
    int mid_x = pball->x - (pball->dx / 2);
    int mid_y = pball->y;

    for (int i = 0; i < BR_BOARD; i++)
    {
        if (bricks[i].hp <= 0) { continue; }

        int hit     = (pball->x == bricks[i].x && pball->y == bricks[i].y);
        int hit_mid = ((pball->dx == 2 || pball->dx == -2) &&
                        mid_x == bricks[i].x && mid_y == bricks[i].y);

        if (hit || hit_mid)
        {
            bricks[i].hp--;

            if (bricks[i].hp <= 0)
            {
                plevel->score += bricks[i].score * plevel->score_mult;
            }
            else
            {
                update_brick_key(&bricks[i]); // Update visual damage
            }

            // Bounce
            int prev_y = pball->y - pball->dy;

            if (prev_y == bricks[i].y)
            {
                pball->dx = -pball->dx; // lateral impact
            }
            else
            {
                pball->dy = -pball->dy; // top/bottom impact
            }

            return; // one brick per frame
        }
    }
}

int check_ball_lost(ball_t *pball, paddle_t *ppaddle, level_t *plevel)
{
    if (pball->y >= ROWS)
    {
        plevel->lives--;
        if (plevel->lives <= 0) { return -1; } // game over

        pad_ball_init(pball, ppaddle, plevel); // reset ball and paddle
        return 1; // lost a life, continue
    }
    return 0; // normal
}

int check_level_complete(brick_t bricks[])
{
    for (int i = 0; i < BR_BOARD; i++)
    {
        if (bricks[i].hp > 0) { return 0; }
    }
    return 1; // all bricks destroyed
}

void game_loop(ball_t *pball, paddle_t *ppaddle, brick_t bricks[], level_t *plevel)
{
    Terminal termios;
    Raw_mode(&termios);  // ya la tienes en menu.h

    char key = 0;
    int running = 1;
    int launched = 0;
    int frame = 0;

    while (running)
    {
        int bytes = read(STDIN_FILENO, &key, 1);
        if (bytes <= 0) key = 0;

        // INPUT
        update_paddle(ppaddle, key);

        // BALL
        if (!launched)
        {
            if (key == ' ')
            	{
            	launched = 1;
            	pball->dx = 1;
            	pball->dy = -1;
            	}
            pball->x = ppaddle->x;
            pball->y = ppaddle->y - 1;
        }
        else if (frame % (int)(BASE_SPEED / pball->speed) == 0)
        {
            update_ball(pball);


			// COLLISIONS
			check_paddle_collision(pball, ppaddle);
			check_brick_collision(pball, bricks, plevel);

			int lost = check_ball_lost(pball, ppaddle, plevel);
			if (lost == -1) { running = 0; } // game over
			if (lost >= 1)  { launched = 0; } // reset launch

			// NEW LEVEL
			if (check_level_complete(bricks))
			{
				plevel->level++;

				if (plevel->level > MAX_LEVEL)
				{
					running = 0; // you win
				}
				else
				{
					// increase speed and score_mult each level
					plevel->speed_mult += 0.5f;
					plevel->score_mult +=0.5f;

					// reset bricks and ball
					brick_init(bricks);
					init_new_level(plevel, bricks);
					pad_ball_init(pball, ppaddle, plevel);
					launched = 0;
				}
			}

        }

        frame++;
        key = 0;

        // RENDER
        render(ppaddle, pball, bricks, plevel);
        usleep(SLEEP_TIME);
    }

    Canonical_mode(&termios);
}


void render(paddle_t *ppaddle, ball_t *pball, brick_t bricks[], level_t *plevel)
{
    CLEAR_SCREEN;
    PRINT_TOP_RIGHT;

    // Bricks
    for (int i = 0; i < BR_BOARD; i++)
    {
        if (bricks[i].hp > 0)
        {
        	printf("\033[%d;%dH%c", bricks[i].y + 1, bricks[i].x + 1, bricks[i].key);
        }
    }

    // Ball
    printf("\033[%d;%dHO", pball->y + 1, pball->x + 1);

    // Paddle
    int half = ppaddle->size / 2;
    for (int i = -half; i <= half; i++)
    {
        printf("\033[%d;%dH=", ppaddle->y + 1, ppaddle->x + i + 1);
    }
    // Life and Score
    printf("\033[%d;1H Lives: %d   Score: %d", ROWS + 1, plevel->lives, plevel->score);

    fflush(stdout);
}
