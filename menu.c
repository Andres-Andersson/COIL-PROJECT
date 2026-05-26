#include "menu.h"


int display_menu(Terminal*original_termios){

	Raw_mode(original_termios); //Enters raw mode

	usleep(MENU_WAIT);

	print_Menu(); //Prints the menu frame

	return animate_menu(original_termios); //Animates the menu and waits for user response
}

void print_Menu(void){

	ENTER_ALT_SCREEN; //Ensures that the menu will be displayed correctly

	CLEAR_SCREEN; //ELiminates previous messages

	fflush(stdout); //shows the changes

	PRINT_TOP_RIGHT; //Moves the cursor to (1,1)

	int k;

	for (k =0; k<MENU_WIDTH; k++){
		printf("#");
	}
	printf("\n");
	for (int i=2; i<MENU_HEIGHT;i++){ //Prints the specified height of the board
		for (int j=1; j<=MENU_WIDTH; j++){
			if ((j == 1)|| (j==MENU_WIDTH)){
				printf("#"); //Defines the border

			}
			else{
				printf(" "); //Empty square
			}
	}
		printf("\n");
	}

	for (k=0; k<MENU_WIDTH; k++){
			printf("#");
		}
	printf("\n");
	fflush(stdout);
}

void Canonical_mode(Terminal*original_termios){
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
	SHOW_CURSOR;
}

void Raw_mode(Terminal*original_termios){

	tcgetattr(STDIN_FILENO, original_termios); //Authorizes access to the keyboard

	Terminal raw = *original_termios; //Sets raw mode in order to process stdin without freezing the game.

	raw.c_lflag &= ~(ECHO|ICANON); //Disables character echo and canonical mode (it does not freeze the console)
	raw.c_iflag &= ~(IXON|ICRNL); //Disables ctrl+s and ctrl+q (commands that freeze the console) and the newline translation
	raw.c_cc[VMIN] = 0; //Disable wait time for x amount of input characters to be typed
	raw.c_cc[VTIME] = 0; //Disables maximum waiting time to register keyboard input

	tcsetattr(STDIN_FILENO, TCSANOW, &raw); //Sets the previously changed settings

	HIDE_CURSOR; //Hides the cursor
}

int animate_menu(Terminal*original_termios){
		char key = 0;

		int menu_running = 1;

		int readbytes;

		int frame_count = 0;

		int toggle_print = 0;


		while(menu_running){
			readbytes = read(STDIN_FILENO, &key, 1); //reads one key and saves it

			if (readbytes > 0){
				if ((key == 'q') || (key == 'Q')){
					menu_running = 0;
					EXIT_ALT_SCREEN;
					CLEAR_SCREEN;
					Canonical_mode(original_termios);
				}
				else if (key == ' '){
					EXIT_ALT_SCREEN;
					Canonical_mode(original_termios); //For now we will exit raw mode so the terminal is not left broken (in the future we should delete this line)
					CLEAR_SCREEN;
					return PLAY;
				}

				key = 0; //Resets the registered key
			}
			usleep(SLEEP_TIME);

			frame_count++;


			if (frame_count>ANIMATION_FREQ){

				frame_count = 0;
				toggle_print = !toggle_print;


				if (toggle_print){ //Animates the text

					PRINT_CENTER(M1, "=================================");
					PRINT_CENTER(M2, "========= ARKANOID IN C =========");
					PRINT_CENTER(M3, "=================================");

					PRINT_CENTER(M4, "-----> PRESS SPACE TO PLAY <-----");

					PRINT_CENTER(M5, "  -----> PRESS Q TO QUIT <-----");
				}
				else{


					PRINT_CENTER(M1, "=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=");
					PRINT_CENTER(M2, "=*=*=*=*= ARKANOID IN C =*=*=*=*=");
					PRINT_CENTER(M3, "=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=");

					PRINT_CENTER(M4, "----->                     <-----");

					PRINT_CENTER(M5, "  ----->                 <-----");

				}
				fflush(stdout); //Forces the screen to update to show the new contents
			}

		}

		return QUIT;
}
