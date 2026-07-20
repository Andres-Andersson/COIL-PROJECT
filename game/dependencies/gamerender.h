/*
 * gamerender.h
 *
 *  Created on: Jul 19, 2026
 *      Author: progra
 */

#ifndef GAMERENDER_H_
#define GAMERENDER_H_

#define PLAYFLEID_X 0
#define PLAYFLEID_Y 0



void render_game(paddle_t *ppaddle, ball_t *pball, brick_t bricks[], level_t *plevel, capsule_t capsules[]);

void init_game_render();
void end_game_render();

char get_key();

#endif /* GAMERENDER_H_ */
