#include "entities.h"
#include "menu.h"
#include "logic.h"
#include "data.h"


int main(void){
	srand (time(NULL));
	int program_running=1;

	char username[MAX_USERNAME+1]; //We include the terminating character
	int score;

	score = get_username(username);

	int selection = open_menu(username, score);

	while (program_running){
		if (selection == QUIT)
			{
				program_running = 0;
			}
			else if (selection == PLAY){

			}

			else if (selection == LEADERBOARD){
				open_leaderboard();
				selection = open_menu(username, score);
			}

	}
	end_program();



	/*
		level_t level_stats;
		level_init (&level_stats);

		brick_t bricks[BR_BOARD]={0};
		brick_init (bricks);
		init_new_level (&level_stats, bricks);

		ball_t balls[MAX_BALLS] = {0};
		paddle_t paddle;
		pad_ball_init (balls, &paddle, &level_stats);

		capsule_t capsules[MAX_CAPSULES] = {0};
		powers_t  active_powers[2]       = {0};  // [0]=TYPE4, [1]=TYPE6



		game_loop(balls, &paddle, bricks, &level_stats, capsules, active_powers);
		*/



	return 0;
}


