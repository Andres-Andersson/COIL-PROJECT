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
void pad_ball_init(ball_t balls[], paddle_t *ppaddle, level_t *plevel);
void level_init (level_t *level);
void set_brick(brick_t *brick, int type);
void update_brick_key(brick_t *brick);

//LOOPS
void game_loop(ball_t balls[], paddle_t *ppaddle, brick_t bricks[], level_t *plevel, capsule_t capsules[], powers_t active_powers[]);
void render(paddle_t *ppaddle, ball_t *pball, brick_t bricks[], level_t *plevel, capsule_t capsules[]);


//MOVEMENT
void update_paddle(paddle_t *ppaddle, char key);
void update_ball(ball_t *pball);

//COLLISIONS
void check_paddle_collision(ball_t *pball, paddle_t *ppaddle);
int  check_ball_lost(ball_t balls[], paddle_t *ppaddle, level_t *plevel);
void check_brick_collision(ball_t *pball, brick_t bricks[], level_t *plevel, capsule_t capsules[]);

//LEVEL GENERATION
void init_new_level (level_t *level_info, brick_t bricks[]);
void init_level_1 (brick_t bricks[]);
void init_level_2 (brick_t bricks[]);
void init_level_3(brick_t bricks[]);
void init_level_4(brick_t bricks[]);
void init_level_n (brick_t bricks[]);

//NEW BALL
void spawn_ball(ball_t balls[], int x, int y, float speed);


//CAPSULES
void spawn_capsule(capsule_t capsules[], int x, int y, int type);
void update_capsules(capsule_t capsules[], paddle_t *ppaddle, ball_t balls[], powers_t active_powers[]);
void activate_power(int type, paddle_t *ppaddle, ball_t balls[], powers_t active_powers[]);
void update_powers(powers_t active_powers[], paddle_t *ppaddle, ball_t balls[]);



#endif /* LOGIC_H_ */
