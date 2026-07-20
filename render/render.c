#include "render.h"

static int initialized = FALSE;

static WINDOW* windows[W_MAX];

void init_ncurses(){

	if (initialized){
		return;

	}
	else{

		initscr();
		raw();
		noecho();
		curs_set(0);

		if (has_colors()) { //Init colors
			start_color();

			init_pair(BLACK, COLOR_BLACK,COLOR_BLACK);
			init_pair(BLUE, COLOR_BLUE,COLOR_BLACK);
			init_pair(GREEN, COLOR_GREEN,COLOR_BLACK);
			init_pair(CYAN, COLOR_CYAN,COLOR_BLACK);
			init_pair(RED, COLOR_RED,COLOR_BLACK);
			init_pair(MAGENTA, COLOR_MAGENTA,COLOR_BLACK);
			init_pair(YELLOW, COLOR_YELLOW,COLOR_BLACK);
			init_pair(WHITE, COLOR_WHITE,COLOR_BLACK);
			init_pair(SELECTION, COLOR_BLACK,COLOR_WHITE);

		}

		initialized = TRUE;
	}

}

void render_create_win(WindowID win_id, int height, int width, int i, int j){
	if ((win_id >= W_MAX) || (win_id<0)){ //Window creation validation
		return;
	}

	if ((height<0) || (height <0)){
		return;
	}

	if (windows[win_id] != NULL){ //Updates the window.
		delwin(windows[win_id]);
	}

	windows[win_id] = newwin(height, width, i, j);
	nodelay(windows[win_id], TRUE); //activates non freezing when getting the output from the user
	keypad(windows[win_id], TRUE); //allows keypad input
	box(windows[win_id],0,0);
}

void render_destroy_win(WindowID win_id){

	if ((win_id >= W_MAX) || (win_id<0)){
			return;
		}

	if (windows[win_id] != NULL){ //Checks if the window exists before trying to close it.

		delwin(windows[win_id]);
		windows[win_id] = NULL;

	}


}

void end_ncurses(){ //Safely shutdowns ncurses and deletes every active window.
    if (initialized == FALSE) {
        return;
    }
    for(int i=0;i<W_MAX;i++){
    	if (windows[i] != NULL){
    		delwin(windows[i]);
    	}
    }

    endwin();
    initialized = FALSE;
}


void print_str(WindowID win_id, int i, int j, int color_id, const char* format,...){

		if ((win_id>=W_MAX) || (win_id<0) || (windows[win_id] == NULL)){ //Window validation
			return;
		}

		WINDOW* win = windows[win_id];


		wattron(win,COLOR_PAIR(color_id));
	    move(i, j);

	    va_list args; //Receives the list with the formats
	    va_start(args, format);

	    wmove(win,i,j);
	    vw_printw(win, format, args);
	    va_end(args);

	    wattroff(win,COLOR_PAIR(color_id));
}

void print_char(WindowID win_id, int i, int j, int color_id, char character) {

	if ((win_id>=W_MAX) || (win_id<0) || (windows[win_id] == NULL)){ //Window validation
				return;
			}

	WINDOW* win = windows[win_id];

    wattron(win,COLOR_PAIR(color_id));
    mvwaddch(win, i, j, character);
    wattroff(win, COLOR_PAIR(color_id));
}

void render_refresh_win(WindowID win_id) {
    if ((win_id >= W_MAX) || (win_id < 0) || (windows[win_id] == NULL)) return;
    wrefresh(windows[win_id]);
}

void render_clear_win(WindowID win_id) {
    if ((win_id >= W_MAX) || (win_id < 0) || (windows[win_id] == NULL)){
    	return;
    }
    wclear(windows[win_id]);
    box(windows[win_id],0,0);
}


MenuAction render_get_action(WindowID win_id){
	if ((win_id >= W_MAX) || (win_id < 0) || (windows[win_id] == NULL)) {
	        return ACTION_NONE;
	    }

	int ch = wgetch(windows[win_id]);

	if (ch == ERR) {
	        return ACTION_NONE;
	    }

	switch(ch){

	case '\n':
	case KEY_ENTER:
	case ' ':
		return PLAY_ACTION;

	case 'q':
	case 'Q':
		return QUIT_PAUSE;

	case 'l':
	case 'L':
		return LEADERBOARD_ACTION;
	default:
		return ACTION_NONE;
	}
}


