#ifndef MENU_H_
#define MENU_H_

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct termios Terminal;

int display_menu(Terminal*);

void print_Menu(void);

void Raw_mode(Terminal*);

void Canonical_mode(Terminal*);

int animate_menu(Terminal*);

#define US_SECOND 1000000

#define FPS 40

#define MENU_WAIT US_SECOND
#define SLEEP_TIME (US_SECOND/(FPS))

#define ANIMATION_FREQ 12 //The higher the number the less frequent it will change
#define ANIMATION_TIME ((SLEEP_TIME)*ANIMATION_FREQ)

#define MENU_HEIGHT 20
#define MENU_WIDTH 40

#define MENU_SPACING 2

#define ROW_CENTER(text) (((MENU_WIDTH-((int)sizeof(text)-1))/2)+1) //Center of the row

#define PRINT_CENTER(row, text) printf("\033[%d;%dH%s", (row), (ROW_CENTER(text)), (text))

#define PRINT_TOP_RIGHT printf("\033[1;1H")

#define CLEAR_SCREEN printf("\033[H\033[2J\033[3J")

//#define CENTER_CURSOR not needed for now

#define HIDE_CURSOR printf("\033[?25l")
#define SHOW_CURSOR printf("\033[?25h")

#define QUIT 0
#define PLAY 1

#define M1 3
#define M2 4
#define M3 5
#define M4 10
#define M5 15

#define ENTER_ALT_SCREEN printf("\033[?1049h")
#define EXIT_ALT_SCREEN printf("\033[?1049l")


#endif /* MENU_H_ */
