/*
 * levelmanager.h
 *
 *  Created on: Jul 19, 2026
 *      Author: progra
 */

#ifndef LEVELMANAGER_H_
#define LEVELMANAGER_H_

//INIT
void brick_init(brick_t bricks[]);
void pad_ball_init(ball_t balls[], paddle_t *ppaddle, level_t *plevel);
void level_init (level_t *level);
void set_brick(brick_t *brick, int type);
void update_brick_key(brick_t *brick);


//LEVEL GENERATION
void init_new_level (level_t *level_info, brick_t bricks[]);
void init_level_1 (brick_t bricks[]);
void init_level_2 (brick_t bricks[]);
void init_level_3(brick_t bricks[]);
void init_level_4(brick_t bricks[]);
void init_level_n (brick_t bricks[]);

//GAME INIT
#define INITIAL_LIVES 3
#define BASE_SPEED 4
#define MAX_LEVEL 10


#endif /* LEVELMANAGER_H_ */
