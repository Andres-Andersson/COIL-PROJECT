#include "datarender.h"
#include "data.h"


static int validate_username(char*);
static int user_exists(const char*);
static void register_new_user(const char*);
static void get_top_scores_list();
static int compare_players(const void*p1, const void* p2);


static int validate_username(char*username){
	int length = strlen(username);

	for (int i=0; i<length;i++){
		char letter = username[i];
		if (!isalpha(letter)){
			return FALSE;
		}
	}
	 //If the username passed the filter, we know is valid.
	return TRUE;

}

int get_username(char*username){
		int score;

		int c;
		int i;
		int long_user;
		int valid_user;

		printf("Hi there!\nPlease enter your username to start playing!\n");

		do //We save and verify the username
		{
			i=0;
			long_user = FALSE;
			valid_user = TRUE;
			while(((c=getchar())!= '\n') && (c!= EOF)){
				if (i<MAX_USERNAME){
					username[i++]=c;
				}
				else{
					long_user=1;
				}

			}
			username[i] = '\0';

			//We check that the username complies with all the requirements.

			if (i<MIN_USERNAME){
				printf("Your username must be more than %d letters long. Please try again\n", MIN_USERNAME);
				valid_user = FALSE;
			}

			if (long_user){
				printf("Your username must be less than %d letters long. Please try again\n",MAX_USERNAME);
				valid_user = FALSE;
			}



			if (valid_user){
				valid_user = validate_username(username);
				if (!valid_user){
					printf("Your username must only contain letters! Please try again\n");
				}
			}
			usleep(SLEEP_TIME);
		}

		while(!valid_user); //We will prompt the user again until the username becomes valid

		score = user_exists(username);

		if (score<DEFAULT_SCORE){
			register_new_user(username);
			return DEFAULT_SCORE;
		}
		else{
			return score;
		}



}

static int user_exists(const char*username_to_find){

	FILE * file = fopen("scores.txt", "r");

	if (file==NULL){
		return USER_DOES_NOT_EXIST;
	}
	else{

		char current_name[LINE_SIZE] = {0}; //It will check line by line if a user with the same name exists
		int current_score;

		while(fscanf(file, "%s\t%d", current_name, &current_score) == 2){
			if (strcmp(current_name,username_to_find)){
				continue;
			}
			else{
				fclose(file);
				return current_score;

			}

		}
		fclose(file);
		return USER_DOES_NOT_EXIST;

	}

}

static void register_new_user(const char*username){ //If the user does not exist it will register it with a default score

	FILE * file = fopen("scores.txt", "a");

	if (file!=NULL){

		fprintf(file,"%s\t%d\n",username,DEFAULT_SCORE);

		fclose(file);

	}
}

void open_leaderboard(){
	init_leaderboard();
	get_top_scores_list();
	usleep(LEADERBOARD_WAIT_TIME);
	close_leaderboard();

}

static void get_top_scores_list(){

	int capacity = NTOP;
	int player_count= 0;

	FILE * file = fopen("scores.txt", "r");

	if (file == NULL){
		return;
	}

	Player_t* player_list = malloc(NTOP*sizeof(Player_t));

	while(fscanf(file, "%s\t%d", player_list[player_count].username, &player_list[player_count].score) == 2){
		player_count++;

		if (player_count>=capacity){
			capacity *= MULT;

			Player_t* temp = realloc(player_list, capacity*sizeof(Player_t));

			if (temp == NULL){
				free(player_list);
				fclose(file);
				return;
			}
			player_list = temp;
		}
	}

	fclose(file);

	if (player_count>0){
		qsort(player_list, player_count, sizeof(Player_t), compare_players);
		show_top_scores(player_list, player_count);
	}
	free(player_list);
}


static int compare_players(const void*p1, const void* p2){
	return (((Player_t*)p2)->score)- (((Player_t*)p1)->score);
}

