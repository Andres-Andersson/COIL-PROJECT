/*
 * render.h
 *
 *  Created on: Jul 15, 2026
 *      Author: progra
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <ncurses.h>
#include <stdarg.h>

void init_ncurses();
void end_ncurses();

typedef enum {
    WIN_MENU,
    WIN_GAME_BORDER,
    WIN_GAME_PLAYFIELD,
    WIN_LEADERBOARD
} WindowID;

#define W_MAX 4

typedef enum{
	ACTION_NONE,
	PLAY_ACTION,
	QUIT_PAUSE,
	LEADERBOARD_ACTION,
}MenuAction;

MenuAction render_get_action(WindowID win_id);

void render_create_win(WindowID, int height, int width, int i, int j);
void render_destroy_win(WindowID);

void print_str(WindowID win_id, int i, int j, int color_id, const char* format,...);
void print_char(WindowID win_id, int i, int j, int color_id, char character);

void render_refresh_win(WindowID win_id);
void render_clear_win(WindowID win_id);

#define GET_CENTER_TEXT(win_width, text) (((win_width) - strlen(text)) / 2)

#define SCREEN_START_Y 0
#define SCREEN_START_X 0

typedef enum{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE,
	SELECTION,
}colors;



#endif /* RENDER_H_ */
