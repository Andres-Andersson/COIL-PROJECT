#include <time.h>
#include <stdlib.h>

#include "menu/menu.h"
#include "data/data.h"
#include "game/gamemanager.h"


int main(void){
	srand (time(NULL));
	int program_running=1;

	char username[MAX_USERNAME+1]; //We include the terminating character
	int score;
	int round_score;

	score = get_username(username);

	int selection = open_menu(username, score);

	while (program_running){
		if (selection == QUIT)
			{
				program_running = 0;
			}
			else if (selection == PLAY){
				round_score = play_game(score);
				selection = open_menu(username, score);

			}

			else if (selection == LEADERBOARD){
				open_leaderboard();
				selection = open_menu(username, score);
			}

	}
	end_program();

	return 0;
}


