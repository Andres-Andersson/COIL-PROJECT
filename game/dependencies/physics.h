/*
 * physics.h
 *
 *  Created on: Jul 19, 2026
 *      Author: progra
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

//MOVEMENT
void update_paddle(paddle_t *ppaddle, char key);
void update_ball(ball_t *pball);

//COLLISIONS
void check_paddle_collision(ball_t *pball, paddle_t *ppaddle);
int  check_ball_lost(ball_t balls[], paddle_t *ppaddle, level_t *plevel);
void check_brick_collision(ball_t *pball, brick_t bricks[], level_t *plevel, capsule_t capsules[]);

#endif /* PHYSICS_H_ */
