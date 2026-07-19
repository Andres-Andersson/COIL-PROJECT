/*
 * init.h
 *
 *  Created on: Jul 15, 2026
 *      Author: progra
 */

#ifndef DATA_H_
#define DATA_H_

#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define INVALID_USER 0
#define VALID_USER 1

#define MULT 2

#define MIN_USERNAME 4
#define MAX_USERNAME 10
#define MAX_BUFFER 50

#define USER_DOES_NOT_EXIST -1

#define LINE_SIZE 20

#define DEFAULT_SCORE 0

#define SLEEP_TIME 1000000 //1 SECOND

#define LEADERBOARD_WAIT_TIME SLEEP_TIME*5

int get_username(char*);

void open_leaderboard();

#endif /* DATA_H_ */
