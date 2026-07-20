#include "datarender.h"
#include "../../render/render.h"


void init_leaderboard(){
	render_create_win(WIN_LEADERBOARD, L_BOARD_HEIGHT, L_BOARD_WIDTH, SCREEN_START_Y, SCREEN_START_X);

	print_str(WIN_LEADERBOARD, L1, GET_CENTER_TEXT(L_BOARD_WIDTH, "ALL-TIME HIGH SCORES"), GREEN,"ALL-TIME HIGH SCORES");

	render_refresh_win(WIN_LEADERBOARD);


}

void show_top_scores(Player_t* topscores, int player_count){
	if (player_count> NTOP){
		player_count = NTOP;
	}

	char* username;
	int score;
	int offset = L2;

	for (int j = 1; j<(L_BOARD_WIDTH-2);j++){
		print_char(WIN_LEADERBOARD, offset, j, WHITE, '_');
	}
	offset++;

	for (int i =0; i<player_count;i++){

		username = topscores[i].username;
		score = topscores[i].score;

		switch(i){

		case 0:
			print_str(WIN_LEADERBOARD, offset, L_LEFT, YELLOW, "%d. %s:			%d",i+1,username, score);
			break;
		case 1:
			print_str(WIN_LEADERBOARD, offset, L_LEFT, CYAN, "%d. %s:			%d",i+1,username, score);
			break;
		case 2:
			print_str(WIN_LEADERBOARD, offset, L_LEFT, RED, "%d. %s:			%d",i+1,username, score);

			break;

		default:
			print_str(WIN_LEADERBOARD, offset, L_LEFT, GREEN, "%d. %s:			%d",i+1,username, score);
			break;
		}

		offset++;
		if (i != NTOP-1){
			for (int j = 1; j<(L_BOARD_WIDTH-2);j++){
				print_char(WIN_LEADERBOARD, offset, j, WHITE, '_');
			}
		}

		offset++;
	}

	render_refresh_win(WIN_LEADERBOARD);
}


void close_leaderboard(){
	render_destroy_win(WIN_LEADERBOARD);
}
