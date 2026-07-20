#include "entities.h"
#include "gamemanager.h"


#include "dependencies/physics.h"
#include "dependencies/powers.h"
#include "dependencies/gamerender.h"
#include "dependencies/levelmanager.h"

static int game_loop(ball_t balls[], paddle_t *ppaddle, brick_t bricks[], level_t *plevel, capsule_t capsules[], powers_t active_powers[]);

int play_game(int score){

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

	init_game_render();

	int newscore = game_loop(balls, &paddle, bricks, &level_stats, capsules, active_powers);
	return newscore;
}



static int game_loop(ball_t balls[], paddle_t *ppaddle, brick_t bricks[], level_t *plevel, capsule_t capsules[], powers_t active_powers[]){

    char key;
    int running = 1;
    int launched = 0;
    int frame = 0;



    while (running)
    {
    	key = get_key();
        // INPUT
        update_paddle(ppaddle, key);

        // CHEATS
        if (key == CHEAT_CLEAR_BRICKS)
        {
            int i;
            for (i = 0; i < BR_BOARD; i++) { bricks[i].hp = 0; }
        }
        if (key == CHEAT_SPAWN_POWERS)
        {
            int i;
            for (i = 0; i < BR_BOARD; i++)
            {
                if (bricks[i].type >= BR_TYPE_4 && bricks[i].hp > 0)
                {
                    spawn_capsule(capsules, bricks[i].x, bricks[i].y, bricks[i].type);
                    bricks[i].hp = 0;
                }
            }
        }

        // BALL
        if (!launched)
        {
            if (key == PLAY_ACTION)
            {
                launched = 1;
                balls[0].dx = 1;
                balls[0].dy = -1;
            }
            balls[0].x = ppaddle->x;
            balls[0].y = ppaddle->y - 1;
        }
        else if (frame % (int)(BASE_SPEED / balls[0].speed) == 0)
        {
            int b;
            for (b = 0; b < MAX_BALLS; b++)
            {
                if (!balls[b].active) { continue; }
                update_ball(&balls[b]);
                check_paddle_collision(&balls[b], ppaddle);
                check_brick_collision(&balls[b], bricks, plevel, capsules);
            }

            int lost = check_ball_lost(balls, ppaddle, plevel);
            if (lost == -1) { running = 0; }
            if (lost >= 1)  { launched = 0; }

            // NEW LEVEL
            if (check_level_complete(bricks))
            {
                plevel->level++;
                if (plevel->level > MAX_LEVEL)
                {
                    running = 0;
                }
                else
                {
                    plevel->speed_mult += 0.25f;
                    plevel->score_mult  += 0.5f;
                    brick_init(bricks);
                    init_new_level(plevel, bricks);
                    pad_ball_init(balls, ppaddle, plevel);  // BALLS NOT PBALL
                    launched = 0;
                }
            }
        }

        // CAPSULES AND POWERS
        if (frame % CAPSULE_SPEED == 0)
        {
            update_capsules(capsules, ppaddle, balls, active_powers);
        }
        update_powers(active_powers, ppaddle, balls);

        frame++;
        key = ACTION_NONE;

        render_game(ppaddle, balls, bricks, plevel, capsules);
        usleep(SLEEP_TIME);
    }

    end_game_render();
}

