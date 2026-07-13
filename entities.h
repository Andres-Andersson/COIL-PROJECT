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
	int score;
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
	int y; //Constant, PADDLE_ROW
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
	int score;
	int score_mult;
	int ball_count;
}level_t;

//CONSTANTS
//GAMEBOARD
#define ROWS 41 //LOSES IN THE 17TH, Arrays from 0to ROWS-1
#define COLS 41 //ODD NUMBER TO CENTER PADDLE
#define gameboard (ROWS * COLS)
#define BR_ROWS 25
#define BR_BOARD (COLS * BR_ROWS)

//GAME
#define INITIAL_LIVES 3
#define BASE_SPEED 50

//BALL & PADDLE
#define LIFE_BALL 1 //So that it never disapears if touches many blocks in the same time, condition <=0 && >-10

#define PADDLE_ROW (ROWS-1)
#define INIT_SIZE_PADDLE 5

//KEYS
#define LEFT 'a'
#define RIGHT 'd'

// MENU DISPLAY (GAUSS WILL CHECK)
#define US_SECOND 1000000

#define FPS 40

#define MENU_WAIT US_SECOND
#define SLEEP_TIME (US_SECOND/(FPS))

#define ANIMATION_FREQ 12 //The higher the number the less frequent it will change
#define ANIMATION_TIME ((SLEEP_TIME)*ANIMATION_FREQ)

#define MENU_HEIGHT 20
#define MENU_WIDTH 40

#define MENU_SPACING 2

#define ROW_CENTER(text) (((MENU_WIDTH-((int)sizeof(text)-1))/2)+1) //Center of the row

#define PRINT_CENTER(row, text) printf("\033[%d;%dH%s", (row), (ROW_CENTER(text)), (text))

#define PRINT_TOP_RIGHT printf("\033[1;1H")

#define CLEAR_SCREEN printf("\033[H\033[2J\033[3J")

//#define CENTER_CURSOR not needed for now

#define HIDE_CURSOR printf("\033[?25l")
#define SHOW_CURSOR printf("\033[?25h")

#define QUIT 0
#define PLAY 1

#define M1 3
#define M2 4
#define M3 5
#define M4 10
#define M5 15

#define ENTER_ALT_SCREEN printf("\033[?1049h")
#define EXIT_ALT_SCREEN printf("\033[?1049l")

#endif /* ENTITIES_H_ */

