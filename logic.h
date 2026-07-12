/*
 * logic.h
 *
 *  Created on: Jul 12, 2026
 *      Author: progra
 */

#ifndef LOGIC_H_
#define LOGIC_H_

void init_level (level_t level_info, brick_t bricks[]);
void init_level_1 (brick_t bricks[]);
void init_level_2 (brick_t bricks[]);
void init_level_n (brick_t bricks[]);
void brick_init(brick_t bricks[]);
void pad_ball_init (ball_t *pball, paddle_t *ppaddle);
void level_init (level_t *level);

#endif /* LOGIC_H_ */
