/*
 * gamerender.h
 *
 *  Created on: Jul 19, 2026
 *      Author: progra
 */

#ifndef GAMERENDER_H_
#define GAMERENDER_H_

//Text coordinates
#define PLAYFLEID_X 0
#define PLAYFLEID_Y 0

#define TEXT_X 2
#define OFFSET_INSTRUCT 5

#define I1 5
#define I2 (I1+OFFSET_INSTRUCT)
#define I3 (I2+OFFSET_INSTRUCT)

#define INIT_WAIT 2500000 //Wait times
#define WAIT_ACTION_PAUSE 1000
#define RESUME_WAIT 500000

#define SECOND 1000000

#define COUNTDOWN 3


#include "../../game/dependencies/entities.h"

int game_paused();

void resume_game(int selection, paddle_t *ppaddle, ball_t balls[], brick_t bricks[], level_t *plevel, capsule_t capsules[]);

void render_game(paddle_t *ppaddle, ball_t balls[], brick_t bricks[], level_t *plevel, capsule_t capsules[]);

void init_game_render();
void end_game_render();

void instructions();

char get_key();

#endif /* GAMERENDER_H_ */
