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
	plevel->speed_mult=BASE_SPEED;
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
void init_level_1 (brick_t bricks[])
{
	int i=0;
	for (;i<(BR_BOARD);i++)
	{
		bricks[i].hp=1;
		bricks[i].type=1;
		bricks[i].score=1;
	}
}

void init_level_2 (brick_t bricks[])
{
	//MODIFICAR
	int i=0;
		for (;i<(BR_BOARD);i++)
		{
			bricks[i].hp=1;
			bricks[i].type=1;
			bricks[i].score=1;
		}
}

void init_level_n (brick_t bricks[])
{
	//SEE LOGIC AND MODIFY
	int i=0;
		for (;i<(BR_BOARD);i++)
		{
			bricks[i].hp=1;
			bricks[i].type=1;
			bricks[i].score=1;
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

    // DOWN, NOW BOUNCES, THEN LOSES LIFE
    if (pball->y >= ROWS - 1) { pball->y = ROWS - 1;  pball->dy = -1; }
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

void check_brick_collision(ball_t *pball, brick_t bricks[])
{
    for (int i = 0; i < BR_BOARD; i++)
    {
        if (bricks[i].hp <= 0) continue; //Hole, no brick

        if (pball->x == bricks[i].x && pball->y == bricks[i].y) //BRICK
        	//SUMAR PUNTAJE
        {
            bricks[i].hp--; //-1 LIFE

            //BOUNCE: Up-Down or Left-Right
            int prev_y = pball->y - pball->dy;

            if (prev_y == bricks[i].y)
                {pball->dx = -pball->dx;}  //LEFT- RIGHT
            else
                pball->dy = -pball->dy;  //UP-DOWN

            break;
        }
    }
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
        }

        frame++;
        key = 0;

        // 3. COLISIONES (próximo paso)
        check_paddle_collision(pball, ppaddle);
        check_brick_collision(pball, bricks);
        // 4. RENDER
        render(ppaddle, pball, bricks);
        usleep(SLEEP_TIME);
    }

    Canonical_mode(&termios);
}


void render(paddle_t *ppaddle, ball_t *pball, brick_t bricks[])
{
    CLEAR_SCREEN;
    PRINT_TOP_RIGHT;

    // Ladrillos (hardcoded en las primeras BR_ROWS filas)
    for (int i = 0; i < BR_BOARD; i++)
    {
        if (bricks[i].hp > 0)
        {
            printf("\033[%d;%dH#", bricks[i].y + 1, bricks[i].x + 1);
        }
    }

    // Pelota
    printf("\033[%d;%dHO", pball->y + 1, pball->x + 1);

    // Paddle
    int half = ppaddle->size / 2;
    for (int i = -half; i <= half; i++)
    {
        printf("\033[%d;%dH=", ppaddle->y + 1, ppaddle->x + i + 1);
    }

    fflush(stdout);
}
