#include "gamerender.h"
#include "../ncurses/render.h"
#include "../../game/dependencies/entities.h"


void init_game_render(){ //Creates a new window
	render_create_win(WIN_GAME_PLAYFIELD, GAME_ROWS+3, GAME_COLS+2, PLAYFLEID_Y, PLAYFLEID_X);
}

void end_game_render(){ //Destroy the created window
	render_destroy_win(WIN_GAME_PLAYFIELD);
}

char get_key(){ //Reads the key pressed
	return render_get_action(WIN_GAME_PLAYFIELD);;
}

void instructions(){ //Displays the game controls to the user

	render_create_win(WIN_PAUSED, GAME_ROWS+4, GAME_COLS+2, PLAYFLEID_Y, PLAYFLEID_X);

	print_str(WIN_PAUSED, I1, GET_CENTER_TEXT(GAME_COLS+2, "HOW TO PLAY"), GREEN, "HOW TO PLAY");

	print_str(WIN_PAUSED, I2, GET_CENTER_TEXT(GAME_COLS+2, "[SPACE]"), YELLOW, "[SPACE]");
	print_str(WIN_PAUSED, I2+1, GET_CENTER_TEXT(GAME_COLS+2, "TO START/PAUSE THE GAME"), RED, "TO START/PAUSE THE GAME");

	print_str(WIN_PAUSED, I3, GET_CENTER_TEXT(GAME_COLS+2, "[A-D]"), YELLOW, "[A-D]");
	print_str(WIN_PAUSED, I3+1, GET_CENTER_TEXT(GAME_COLS+2, "TO MOVE THE PADDLE"), CYAN, "TO MOVE THE PADDLE");

	render_refresh_win(WIN_PAUSED);
	usleep(INIT_WAIT);

	render_destroy_win(WIN_PAUSED);
}

void render_game(paddle_t *ppaddle, ball_t balls[], brick_t bricks[], level_t *plevel, capsule_t capsules[]) //Renders the entire grid
{
	render_clear_win(WIN_GAME_PLAYFIELD);
    // Bricks
    for (int i = 0; i < BR_BOARD; i++) //Goes brick by brick and it displays them if their health is greater than zero
    {
        if (bricks[i].hp > 0)
        {
        	print_char(WIN_GAME_PLAYFIELD, bricks[i].y + 1, bricks[i].x + 1, ((bricks[i].type)+1), bricks[i].key);

        }
    }

    // BALLS
    int b;
    for (b = 0; b < MAX_BALLS; b++) //Only displays active balls (consider the power ups)
    {
        if (balls[b].active)
        {
        	print_char(WIN_GAME_PLAYFIELD, balls[b].y + 1, balls[b].x + 1, CYAN, 'O');
        }
    }

    // Paddle
    int half = ppaddle->size / 2;
    for (int i = -half; i <= half; i++)
    {
    	print_char(WIN_GAME_PLAYFIELD, ppaddle->y + 1, ppaddle->x + i + 1, RED, '=');
    }
    // Life and Score
    print_str(WIN_GAME_PLAYFIELD, GAME_ROWS, TEXT_X, GREEN, "Lives: %d   Score: %d", plevel->lives, plevel->score);
    print_str(WIN_GAME_PLAYFIELD, GAME_ROWS + 1, TEXT_X, YELLOW, "Level: %d", plevel->level);

    // CAPSULES
       int i;
       for (i = 0; i < MAX_CAPSULES; i++)
       {
           if (capsules[i].active)
           {
        	   print_char(WIN_GAME_PLAYFIELD, capsules[i].y + 1, capsules[i].x + 1, ((capsules[i].type)+1), capsules[i].key);

           }
       }
       render_refresh_win(WIN_GAME_PLAYFIELD);
       clean_buffer();
}

int game_paused(){ //Pauses the game a shows a paused window in front of the game's window
	render_create_win(WIN_PAUSED, GAME_ROWS+4, GAME_COLS+2, PLAYFLEID_Y, PLAYFLEID_X);

	print_str(WIN_PAUSED, I1, GET_CENTER_TEXT(GAME_COLS+2, "GAME PAUSED"), GREEN, "GAME PAUSED");

	print_str(WIN_PAUSED, I2, GET_CENTER_TEXT(GAME_COLS+2, "RESUME [SPACE]"), RED, "RESUME [SPACE]");

	print_str(WIN_PAUSED, I3, GET_CENTER_TEXT(GAME_COLS+2, "QUIT [Q]"), BLUE, "QUIT [Q]");

	render_refresh_win(WIN_PAUSED);

	int selection = 0;

	while((selection!=PLAY_ACTION)&&(selection!=QUIT_PAUSE)){ //Depending on the selection, game manager will either resume or quit the run.
		selection = render_get_action(WIN_PAUSED);
		usleep(WAIT_ACTION_PAUSE);
	}
	clean_buffer();

	return selection;
}

void resume_game(int selection, paddle_t *ppaddle, ball_t balls[], brick_t bricks[], level_t *plevel, capsule_t capsules[]){ //Gives the user feedback
	print_str(WIN_PAUSED, I1, GET_CENTER_TEXT(GAME_COLS+2, "GAME PAUSED"), GREEN, "GAME PAUSED");

	if (selection==PLAY_ACTION){ //Resumes the game

		int i;

		print_str(WIN_PAUSED, I2, GET_CENTER_TEXT(GAME_COLS+2, "RESUME [SPACE]"), YELLOW, "RESUME [SPACE]");
		print_str(WIN_PAUSED, I3, GET_CENTER_TEXT(GAME_COLS+2, "QUIT [Q]"), BLUE, "QUIT [Q]");
		render_refresh_win(WIN_PAUSED);
		usleep(RESUME_WAIT);
		render_destroy_win(WIN_PAUSED);

			for (i=0;i<COUNTDOWN;i++){ //Brief count down

				render_game(ppaddle, balls, bricks, plevel, capsules);
				print_str(WIN_GAME_PLAYFIELD, (GAME_ROWS/2)+5, GAME_COLS/2,YELLOW,"%d",(COUNTDOWN-i));
				render_refresh_win(WIN_GAME_PLAYFIELD);
				usleep(SECOND);
			}
	}
	else{ //The user quitted the game
		print_str(WIN_PAUSED, I2, GET_CENTER_TEXT(GAME_COLS+2, "RESUME [SPACE]"), RED, "RESUME [SPACE]");
		print_str(WIN_PAUSED, I3, GET_CENTER_TEXT(GAME_COLS+2, "QUIT [Q]"), YELLOW, "QUIT [Q]");
		render_refresh_win(WIN_PAUSED);
		usleep(RESUME_WAIT);
		render_destroy_win(WIN_PAUSED);
	}
	clean_buffer(); //Avoids any wrong keys interpretations if the user pressed anything during the game pause.
}
