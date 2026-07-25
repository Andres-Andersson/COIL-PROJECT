/*
 * init.h
 *
 *  Created on: Jul 15, 2026
 *      Author: progra
 */

#ifndef DATA_H_
#define DATA_H_

#include <unistd.h> //Sleep
#include <stdio.h>
#include <ctype.h> //check types
#include <stdlib.h> //NULL and qsort


#define FALSE 0
#define TRUE 1



//Username specifications
#define MIN_USERNAME 4
#define MAX_USERNAME 10
#define MAX_BUFFER 50
#define USER_DOES_NOT_EXIST -1
#define DEFAULT_SCORE 0


#define MULT 2 //Realloc multi-player in case the amount of users is greater that the space saved by realloc
#define LINE_SIZE 20

//Wait times
#define SLEEP_TIME 1000000 //1 SECOND
#define LEADERBOARD_WAIT_TIME SLEEP_TIME*5

int get_username(char*);
void check_score(char* username, int round_score, int saved_score);

void open_leaderboard();

#endif /* DATA_H_ */
