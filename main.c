#include "entities.h"
#include "menu.h"
#include "logic.h"
#include "data.h"


int main(void){
	srand (time(NULL));

	char username[MAX_USERNAME+2]; //We make sure that nor the enter nor the terminating character get clipped
	int score;

	score = get_username(username);


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


