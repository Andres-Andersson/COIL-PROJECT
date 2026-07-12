/*
 * entities.h
 *
 *  Created on: May 20, 2026
 *      Author: progra
 */

#ifndef ENTITIES_H_
#define ENTITIES_H_

#include <stdlib.h>
#include <time.h>

typedef struct 
{
	int x;
	int y;
	int hp;
	int type;
}brick_t;
//TYPE 1= COMMON

typedef struct 
{
	int x;
	int y;
	int dx;
	int dy;
	int hp; //LIFE_MBALL for the main, LIFE_E_BALL for the extras.
	float speed;
	
}ball_t;

typedef struct
{
	int x;
	int dx;
	int size; //An ODD number
	
}paddle_t;

typedef struct
{
	int type; //Each type will lead to an if condition, create #define for each power type
	int duration; // Power-up time duration
}powers_t;

typedef struct
{
	int level;
	int lives;
	int speed_mult;
}level_t;

//CONSTANTS
#define ROWS 16
#define COLS 16
#define gameboard (ROWS * COLS)
#define BR_ROWS 5
#define BR_BOARD (COLS * BR_ROWS)
#define LIFE_MBALL -10 //So that it never disapears if touches many blocks in the same time, condition <=0 && >-10
#define LIFE_EBALL 1

#endif /* ENTITIES_H_ */

