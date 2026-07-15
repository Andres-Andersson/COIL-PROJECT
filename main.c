#include "entities.h"
#include "menu.h"
#include "logic.h"


#define MIN_USERNAME 2
#define MAX_USERNAME 10

#define INVALID_USER 0
#define VALID_USER 1

int validate_username(const char*);

int main(void){
	srand (time(NULL));

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
	return 0;
}

int validate_username(const char*username){
	int length = strlen(username);
	if (length<MIN_USERNAME||length>MAX_USERNAME){
		return INVALID_USER; //If the username is longer or shorter it will be assumed invalid
	}

	for (int i=0; i<length;i++){
		char letter = username[i];
		if (!isalpha(letter)){
			return INVALID_USER;
		}
	}
	 //If the username passed the filter, we know is valid.
	return VALID_USER;

}

void gauss (void)
{
	char username[MAX_USERNAME+2]; //We make sure that nor the enter nor the terminating character get clipped
		int valid_user;
		//int level = 1;
		int mode;
		Terminal original_termios;

		printf("Hi there!\nPlease enter your username to start playing!\n");

		do //We save and verify the username
		{
			if(fgets(username, sizeof(username), stdin) != NULL){
				username[strcspn(username, "\n")] = 0; //We replace the \n by a terminating character
			}
			valid_user = validate_username(username);
			if (!valid_user){
				printf("Invalid username, please try again\n");
			}
			usleep(SLEEP_TIME);
		}

		while(!valid_user); //We will prompt the user again until the username becomes valid

		printf("Welcome to Arkanoid in C, %s!\n", username);

		mode = display_menu(&original_termios);

		if (mode == PLAY){
			printf("Get ready\n");

			//Call a function to initilize the game.
		}
		else if (mode==QUIT){
			printf("Thank you for playing\n");
		}
}
