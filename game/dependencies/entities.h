/*
 * entities.h
 *
 *  Created on: May 20, 2026
 *      Author: progra
 */

#ifndef ENTITIES_H_
#define ENTITIES_H_

#include <unistd.h>
#include <stdlib.h>

typedef enum{
	NO_ACTION,
	LEFT,
	RIGHT,
	SPACE,
	CHEAT_CLEAR_BRICKS,
	CHEAT_SPAWN_POWERS,
}GameAction;

typedef struct 
{
	int x;
	int y;
	int hp;
	int type;
	int score;
	char key;
	char color;
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
    char key;
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

#define US_SECOND 1000000

#define FPS 40

#define MENU_WAIT US_SECOND
#define SLEEP_TIME (US_SECOND/(FPS))

//GAMEBOARD
#define GAME_ROWS 30 //LOSES IN THE N, Arrays from 0to ROWS-1
#define GAME_COLS 15 //ODD NUMBER TO CENTER PADDLE
#define gameboard (GAME_ROWS * GAME_COLS)
#define BR_ROWS 10
#define BR_BOARD (GAME_COLS * BR_ROWS)

//BALL & PADDLE
#define LIFE_BALL 1 //So that it never disappears if touches many blocks in the same time, condition <=0 && >-10

#define PADDLE_ROW (GAME_ROWS-1)
#define INIT_SIZE_PADDLE 5

//DEFAULT VALUES
#define MAX_BALLS 5
#define INIT_SIZE_PADDLE 5
#define MAX_CAPSULES 5



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

// BRICK TYPES
#define BR_TYPE_1 1   // COMMON
#define BR_TYPE_2 2   // MEDIUM
#define BR_TYPE_3 3   // HARD
#define BR_TYPE_4 4   // power-up A
#define BR_TYPE_5 5   // power-up B
#define BR_TYPE_6 6   // power-up C
#define BR_TYPE_7 7   // power-up D



#endif /* ENTITIES_H_ */

