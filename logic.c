/*
 * logic.c
 *
 *  Created on: Jul 12, 2026
 *      Author: progra
 */

#include <entities.h>
#include <logic.h>

void brick_init (brick_t bricks[]);
{
	int i=0;
}

void pad_ball_init (ball_t *pball, paddle_t *ppaddle)
{

}

void init_level (level_t level_info, brick_t bricks[])
{
	switch (level_info)
	{
		case 1: void init_level_1 (bricks[]);break;
		case 2: void init_level_2 (bricks[]);break;
		default: void init_level_n (bricks[]);break;
	}

}
void init_level_1 (brick_t bricks[])
{
	int i=0;
	for (;i<(BR_BOARD);i++)
	{
		bricks[i].hp=1;
		bricks[i].type=1;
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
		}
}
