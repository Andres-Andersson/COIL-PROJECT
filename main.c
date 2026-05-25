#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "menu.h"


#define MIN_USERNAME 2
#define MAX_USERNAME 10

#define INVALID_USER 0
#define VALID_USER 1

int validate_username(const char*);

int main(void){

	char username[MAX_USERNAME+2]; //We make sure that nor the enter nor the terminating character get clipped
	int valid_user;
	//int level = 1;
	int mode;


	Terminal original_termios; //termios struct with the default settings
	tcgetattr(STDIN_FILENO, &original_termios);


	printf("\nHi there!\nPlease enter your username to start playing!\n");

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
	CLEAR_SCREEN;

	if (mode == PLAY){
		printf("Get ready\n");

		//Call a function to initilize the game.
	}
	else if (mode==QUIT){
		printf("Thank you for playing\n");
	}


	return 0;
}

int validate_username(const char*username){
	int length = strlen(username);
	if (length<MIN_USERNAME||length>MAX_USERNAME){
		return INVALID_USER; //If the username is longer or shorter it will be assumed invalid
	}

	for (int i=0; i<length;i++){
		char letter = username[i];
		if (!isalpha(letter) || isspace(letter)){
			return INVALID_USER;
		}
	}
	 //If the username passed the filter, we know is valid.
	return VALID_USER;

}

