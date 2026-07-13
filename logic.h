/*
 * logic.h
 *
 *  Created on: Jul 12, 2026
 *      Author: progra
 */

#ifndef LOGIC_H_
#define LOGIC_H_

#include "entities.h"
//INIT
void brick_init(brick_t bricks[]);
void pad_ball_init (ball_t *pball, paddle_t *ppaddle, level_t *plevel);
void level_init (level_t *level);

//LOOPS
void game_loop(ball_t *pball, paddle_t *ppaddle, brick_t bricks[], level_t *plevel);

//MOVEMENT
void update_paddle(paddle_t *ppaddle, char key);
void update_ball(ball_t *pball);

//COLLISIONS
void check_paddle_collision(ball_t *pball, paddle_t *ppaddle);

void render(paddle_t *ppaddle, ball_t *pball, brick_t bricks[]);

//LEVEL GENERATION
void init_new_level (level_t *level_info, brick_t bricks[]);
void init_level_1 (brick_t bricks[]);
void init_level_2 (brick_t bricks[]);
void init_level_n (brick_t bricks[]);


#endif /* LOGIC_H_ */
