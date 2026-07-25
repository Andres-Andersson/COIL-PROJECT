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
		if (selection == QUIT_PAUSE) //Ends the program
			{
				program_running = 0;
			}
			else if (selection == PLAY_ACTION){
				round_score = play_game(score); //Starts a new run and waits for the user's round score
				check_score(username, round_score, score); //Compares the round score to the high score

				if (round_score>score){
					score = round_score; //The player beat its previous record
				}
				selection = open_menu(username, score); //Opens the main menu an waits for a new selection

			}

			else if (selection == LEADERBOARD_ACTION){ //Displays the highest scores and then shows the main menu again.
				open_leaderboard();
				selection = open_menu(username, score);
			}

	}
	end_program();

	return 0;
}


