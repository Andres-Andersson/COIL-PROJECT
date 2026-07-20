/*
 * powers.h
 *
 *  Created on: Jul 19, 2026
 *      Author: progra
 */

#ifndef POWERS_H_
#define POWERS_H_

#include "entities.h"

//CAPSULES
void spawn_capsule(capsule_t capsules[], int x, int y, int type);
void update_capsules(capsule_t capsules[], paddle_t *ppaddle, ball_t balls[], powers_t active_powers[]);
void activate_power(int type, paddle_t *ppaddle, ball_t balls[], powers_t active_powers[]);
void update_powers(powers_t active_powers[], paddle_t *ppaddle, ball_t balls[]);

//NEW BALL
void spawn_ball(ball_t balls[], int x, int y, float speed);
#define LIFE_BALL 1 //So that it never disappears if touches many blocks in the same time, condition <=0 && >-10

#define ROWS 30

//CAPSULES

#define MAX_PADDLE_SIZE 11
#define POWER_DURATION 600
#define CAPSULE_SPEED 3      // CAPSULE FALLS EVERY N FRAMES


#endif /* POWERS_H_ */
