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
	char key;
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
	int active;
	
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
    int x;
    int y;
    int type;
    int active;
} capsule_t;

typedef struct
{
	int level;
	int lives;
	float speed_mult;
	int score;
	float score_mult;
	int ball_count;
}level_t;

//CONSTANTS

//GAMEBOARD
#define ROWS 30 //LOSES IN THE N, Arrays from 0to ROWS-1
#define COLS 15 //ODD NUMBER TO CENTER PADDLE
#define gameboard (ROWS * COLS)
#define BR_ROWS 10
#define BR_BOARD (COLS * BR_ROWS)

//GAME
#define INITIAL_LIVES 3
#define BASE_SPEED 4
#define MAX_LEVEL 10
#define MAX_BALLS 5

//BALL & PADDLE
#define LIFE_BALL 1 //So that it never disapears if touches many blocks in the same time, condition <=0 && >-10

#define PADDLE_ROW (ROWS-1)
#define INIT_SIZE_PADDLE 5

//KEYS
#define LEFT 'a'
#define RIGHT 'd'
#define CHEAT_CLEAR_BRICKS 'c'
#define CHEAT_SPAWN_POWERS 'p'

//CAPSULES
#define MAX_CAPSULES 5
#define MAX_PADDLE_SIZE 11
#define POWER_DURATION 600   // FRAMES (15 SECONDS AT 40FPS)
#define CAPSULE_SPEED 3      // CAPSULE FALLS EVERY N FRAMES

// BRICK TYPES
#define BR_TYPE_1 1   // COMMON
#define BR_TYPE_2 2   // MEDIUM
#define BR_TYPE_3 3   // HARD
#define BR_TYPE_4 4   // power-up A
#define BR_TYPE_5 5   // power-up B
#define BR_TYPE_6 6   // power-up C
#define BR_TYPE_7 7   // power-up D

// BRICK VISUAL KEYS
#define BR_KEY_1 '-'
#define BR_KEY_2 '='
#define BR_KEY_3 '#'
#define BR_KEY_4 '$'
#define BR_KEY_5 '&'
#define BR_KEY_6 '%'
#define BR_KEY_7 '?'

// Brick scores
#define BR_SCORE_1 100
#define BR_SCORE_2 250
#define BR_SCORE_3 500
#define BR_SCORE_4 150
#define BR_SCORE_5 150
#define BR_SCORE_6 150
#define BR_SCORE_7 150




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

