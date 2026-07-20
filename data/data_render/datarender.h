/*
 * datarender.h
 *
 *  Created on: Jul 18, 2026
 *      Author: progra
 */

#ifndef DATARENDER_H_
#define DATARENDER_H_

#define MAX_USER 10

#include <string.h>

typedef struct{
	char username[MAX_USER+2];
	int score;
}Player_t;

void init_leaderboard();
void show_top_scores(Player_t*, int player_count);
void close_leaderboard();

#define L_BOARD_HEIGHT 23
#define L_BOARD_WIDTH 79

#define NTOP 10

#define L1 1
#define L2 (L1+1)
#define L_LEFT 1


#endif /* DATARENDER_H_ */
