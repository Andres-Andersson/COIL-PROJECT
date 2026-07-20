#include "menu.h"

#include "render.h"

static void draw_menu(char*username, int score, int selection);
static void animate_rocket(int rocket_y, int rocket_x, int frame_count);
static void animate_stars(Star_t* sky, int frame_count);


int open_menu(char*username, int score){

	int menu_running = TRUE;
	int frames = 0;
	int selection = -1;

	init_ncurses();
	render_create_win(WIN_MENU, MENU_HEIGHT, MENU_WIDTH, 0, 0);



	int rocket_y = ROCKET_Y; //The rocket changes x spawn location
	int rocket_x = ROCKET_X+rand()%OFFSET;

	Star_t sky[MAX_STARS];
	for(int i = 0; i < MAX_STARS; i++) //Different speeds, x and y positions for each star
	{
		sky[i].x =1+(rand()%(MENU_WIDTH-OFFSET));
		sky[i].y =1+(rand()%(MENU_HEIGHT-OFFSET));
		sky[i].speed =1+(rand()%MAX_SPEED);
	}


	while(menu_running){

		GameAction action = render_get_action(WIN_MENU);

		switch(action){
			case QUIT_PAUSE:
				selection = QUIT;
				break;
			case PLAY_ACTION:
				selection = PLAY;
				break;
			case LEADERBOARD_ACTION:
				selection = LEADERBOARD;
				break;
			default:
				break;
		}

		if (frames>=ROCKET_ANIM_FREQ){
			rocket_y--;
			if (rocket_y == 0){
				rocket_y = ROCKET_Y;
				rocket_x = ROCKET_X+rand()%(MENU_WIDTH-OFFSET);
			}

			frames=0;
		}

		render_clear_win(WIN_MENU);

		animate_stars(sky,frames);
		animate_rocket(rocket_y,rocket_x, frames);
		draw_menu(username, score, selection);

		usleep(MENU_WAIT1);
		frames++;

		render_refresh_win(WIN_MENU);

		if ((QUIT<=selection) && (selection<=LEADERBOARD)){
			usleep(MENU_WAIT2);
			menu_running = FALSE;
		}
	}

	render_destroy_win(WIN_MENU);
	return selection;
}

void end_program(){
	end_ncurses();
}


static void draw_menu(char*username, int score, int selection){

		print_str(WIN_MENU, M1, GET_CENTER_TEXT(MENU_WIDTH, "ARKANOID"), GREEN, "ARKANOID");
		print_str(WIN_MENU, M5, MLEFT, CYAN, "Username: %s", username);
		print_str(WIN_MENU, M6, MLEFT, RED, "Top score: %d", score);


        if (selection == PLAY){
       	 print_str(WIN_MENU, M2, MLEFT, SELECTION, "PLAY [SPACE]");
       	 print_str(WIN_MENU, M3, MLEFT, WHITE, "VIEW LEADERBOARD [L]");
       	 print_str(WIN_MENU, M4, MLEFT, WHITE, "QUIT [Q]");

		}
        else if (selection == QUIT){
       	 print_str(WIN_MENU, M2, MLEFT, WHITE, "PLAY [SPACE]");
       	 print_str(WIN_MENU, M3, MLEFT, WHITE, "VIEW LEADERBOARD [L]");
       	 print_str(WIN_MENU, M4, MLEFT, SELECTION, "QUIT [Q]");

        }

        else if (selection == LEADERBOARD){
       	 print_str(WIN_MENU, M2, MLEFT, WHITE, "PLAY [SPACE]");
       	 print_str(WIN_MENU, M3, MLEFT, SELECTION, "VIEW LEADERBOARD [L]");
       	 print_str(WIN_MENU, M4, MLEFT, WHITE, "QUIT [Q]");
        }

        else{
        	 print_str(WIN_MENU, M2, MLEFT, WHITE, "PLAY [SPACE]");
        	 print_str(WIN_MENU, M3, MLEFT, WHITE, "VIEW LEADERBOARD [L]");
        	 print_str(WIN_MENU, M4, MLEFT, WHITE, "QUIT [Q]");
        }

}

static void animate_rocket(int rocket_y, int rocket_x, int frame_count){
	print_str(WIN_MENU, rocket_y,	rocket_x, CYAN, " /^\\ ");
	print_str(WIN_MENU, rocket_y+1,	rocket_x, CYAN, " |X| ");

	print_str(WIN_MENU, rocket_y+2,	rocket_x, CYAN, "/|X|\\");
	print_str(WIN_MENU, rocket_y+3,	rocket_x, CYAN, "|---|");


	if ((frame_count / 4) % 2 == 0)
	{
		print_str(WIN_MENU, rocket_y+4, rocket_x, RED, "v v v");
	}

	else
	{
		print_str(WIN_MENU, rocket_y+4,rocket_x, YELLOW, "w w w");
	}
}

static void animate_stars(Star_t* sky, int frame_count){
    for (int i = 0; i < MAX_STARS; i++){
        if (frame_count % STAR_ANIM_FREQ == 0) {
            sky[i].y += sky[i].speed; //Stars fall at different speeds
        }
        if (sky[i].y >= MENU_HEIGHT-1) { //Resets the star at random y location
            sky[i].y = 1;
            sky[i].x = 1 + (rand() % (MENU_WIDTH - 2));
        }
        if (sky[i].speed == 2) { //Different looks for each star
            print_char(WIN_MENU, sky[i].y, sky[i].x, MAGENTA, '*');
        }
        else if (sky[i].speed == 3){
        	print_char(WIN_MENU, sky[i].y, sky[i].x, WHITE, '#');
        }
        else {
            print_char(WIN_MENU, sky[i].y, sky[i].x, CYAN, '.');
        }
    }
}
