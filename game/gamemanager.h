#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

int play_game(int score);

#define SPEED_MULT 0.05f
#define SCORE_MULT 0.5f

#define PADDLE_DISPLACEMENT 1

typedef enum{
	ACTION_NONE,
	PLAY_ACTION,
	QUIT_PAUSE,
	LEADERBOARD_ACTION,
	LEFT,
	RIGHT,
	CHEAT_CLEAR_BRICKS,
	CHEAT_SPAWN_POWERS,

}GameAction; //Keys (game manager interpretation)

#endif /* GAMEMANAGER_H_ */
