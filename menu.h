#ifndef MENU_H_
#define MENU_H_

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "entities.h"

typedef struct termios Terminal;

int display_menu(Terminal*);

void print_Menu(void);

void Raw_mode(Terminal*);

void Canonical_mode(Terminal*);

int animate_menu(Terminal*);




#endif /* MENU_H_ */
