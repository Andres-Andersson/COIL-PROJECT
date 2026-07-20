#ifndef MENU_H_
#define MENU_H_

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int open_menu(char*, int score);
void end_program();

typedef enum{
	QUIT,
	PLAY,
	LEADERBOARD
}modes;

#define FPS 70
#define MENU_WAIT1 (1000000/FPS)
#define MENU_WAIT2 400000

#define ROCKET_ANIM_FREQ 9 //The higher the number the less frequent it will change
#define STAR_ANIM_FREQ 12

#define MENU_HEIGHT 23
#define MENU_WIDTH 79


#define M_SPACING 3

#define M1 1
#define M2 M1+5
#define M3 M2+M_SPACING
#define M4 M3+M_SPACING
#define M5 MENU_HEIGHT-3
#define M6 MENU_HEIGHT-2

#define ROCKET_Y 15
#define ROCKET_X 1
#define OFFSET 22

#define MLEFT 1

#define MAX_STARS 15
#define MAX_SPEED 3

typedef struct {
    int x;
    int y;
    int speed;
} Star_t;



#endif /* MENU_H_ */
