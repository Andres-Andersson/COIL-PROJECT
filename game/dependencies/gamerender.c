#include "gamerender.h"
#include "../../render/render.h"
#include "entities.h"

void init_game_render(){
	render_create_win(WIN_GAME_PLAYFIELD, ROWS, COLS, PLAYFLEID_Y, PLAYFLEID_X);
}

void end_game_render(){
	render_destroy_win(WIN_GAME_PLAYFIELD);
}

char get_key(){
	return render_get_action(WIN_GAME_PLAYFIELD);;
}

void render_game(paddle_t *ppaddle, ball_t balls[], brick_t bricks[], level_t *plevel, capsule_t capsules[])
{

    // Bricks
    for (int i = 0; i < BR_BOARD; i++)
    {
        if (bricks[i].hp > 0)
        {
        	print_char(WIN_GAME_PLAYFIELD, bricks[i].y + 1, bricks[i].x + 1, bricks[i].color, bricks[i].key);

        }
    }

    // BALLS
    int b;
    for (b = 0; b < MAX_BALLS; b++)
    {
        if (balls[b].active)
        {
        	print_char(WIN_GAME_PLAYFIELD, balls[b].y + 1, balls[b].x + 1 + 1, CYAN, 'O');
        }
    }

    // Paddle
    int half = ppaddle->size / 2;
    for (int i = -half; i <= half; i++)
    {
    	print_char(WIN_GAME_PLAYFIELD, ppaddle->y + 1, ppaddle->x + i + 1, bricks[i].color, '=');
    }
    // Life and Score
    print_str(WIN_GAME_PLAYFIELD, ROWS + 1, 0, RED, "Lives: %d   Score: %d", plevel->lives, plevel->score);

    // CAPSULES
       int i;
       for (i = 0; i < MAX_CAPSULES; i++)
       {
           if (capsules[i].active)
           {
        	   print_char(WIN_GAME_PLAYFIELD, capsules[i].y + 1, capsules[i].x + 1, bricks[i].color, capsules[i].key);

           }
       }
       render_refresh_win(WIN_GAME_PLAYFIELD);
}


