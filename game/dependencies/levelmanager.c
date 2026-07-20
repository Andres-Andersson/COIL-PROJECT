#include "entities.h"
#include "levelmanager.h"

void brick_init (brick_t bricks[])
{
	int i=0, j=0, k=0;
	for (;i<BR_BOARD;k++)
	{
		for (j=0;j<COLS;j++,i++) //SETS EACH BLOCK WITH ITS POSITION (X,Y), ONLY ONCE
		{
			bricks[i].y=k;
			bricks[i].x=j;
		}
	}
}

void pad_ball_init(ball_t balls[], paddle_t *ppaddle, level_t *plevel)
{
    int i; //DEACTIVATE ALL BALLS
    for (i = 1; i < MAX_BALLS; i++) { balls[i].active = 0; }

    ppaddle->x   = (COLS/2+1); //SETS PADDLE
    ppaddle->y   = PADDLE_ROW;
    ppaddle->size = INIT_SIZE_PADDLE;
    ppaddle->dx  = 0;

    balls[0].x      = ppaddle->x;	//SETS MAIN BALL
    balls[0].y      = ppaddle->y - 1;
    balls[0].dx     = 0;
    balls[0].dy     = 0;
    balls[0].hp     = LIFE_BALL;
    balls[0].speed  = plevel->speed_mult;
    balls[0].active = 1;
}

void level_init (level_t *plevel)
{
	plevel->level=1;
	plevel->lives= INITIAL_LIVES; //SETS LEVEL INFO, ONLY ONCE
	plevel->speed_mult=1;
	plevel->score=0;
	plevel->ball_count=1;
	plevel->score_mult=1;
}

void init_new_level (level_t *level_info, brick_t bricks[])
{
	switch (level_info->level)
	{
		case 1: init_level_1 (bricks);break; //EACH NEW LEVEL, CHOOSES WHICH FUNCTION TO CALL
		case 2: init_level_2 (bricks);break;
		case 3: init_level_3 (bricks);break;
		case 4: init_level_4(bricks); break;
		default: init_level_n (bricks);break;
	}

}
void init_level_1(brick_t bricks[])
{
    int i, row, col;	//FIRST LEVEL, FIXED, EASY

    for (row = 0; row < BR_ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            i = row * COLS + col;
            bricks[i].hp = 0; // EMPTY BY DEFAULT

            if (row == 0 || row == 2 || row == 6 || row == 8)
            {
                set_brick(&bricks[i], BR_TYPE_1);
            }
            else if (row == 3 || row == 5)
            {
                set_brick(&bricks[i], BR_TYPE_2);
            }
            else if (row == 4)
            {
                if      (col == 4)  { set_brick(&bricks[i], BR_TYPE_4); }
                else if (col == 10) { set_brick(&bricks[i], BR_TYPE_5); }
                else                { set_brick(&bricks[i], BR_TYPE_2); }
            }
            // ROWS 1, 7, 9 EMPTY
        }
    }
}

void init_level_2(brick_t bricks[])
{
    int i, row, col;	//LEVEL 2, AN INVERSE PYRAMID WITH SUPERPOWERS
    int center = COLS / 2;  // FINDS THE MIDDLE

    // CLEARS ALL, TO PREVENT ERRORS
    for (i = 0; i < BR_BOARD; i++)
    {
        bricks[i].hp = 0;
    }

    for (row = 0; row < BR_ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            i = row * COLS + col;

            if (row <= 7)
            {
                int left  = center - row;
                int right = center + row;

                if (col >= left && col <= right)
                {
                    // POWER-UPS
                    if (row == 3 && col == center)
                    {
                        set_brick(&bricks[i], BR_TYPE_4);
                    }
                    else if (row == 5 && (col == center - 2 || col == center + 2))
                    {
                        set_brick(&bricks[i], BR_TYPE_5);
                    }
                    else if (row == 7 && (col == center - 4 || col == center + 4))
                    {
                        set_brick(&bricks[i], BR_TYPE_6);
                    }
                    // PYRAMID BORDER
                    else if (col == left || col == right)
                    {
                        set_brick(&bricks[i], BR_TYPE_3);
                    }
                    // INSIDE
                    else
                    {
                        set_brick(&bricks[i], BR_TYPE_2);
                    }
                }
            }
            else if (row == 8)
            {
                set_brick(&bricks[i], BR_TYPE_3);
            }
            // ROW 9 EMPTY
        }
    }
}

void init_level_3(brick_t bricks[])
{
    int i, row, col;	//LEVEL 3, CONCENTRIC CRICLES

    for (i = 0; i < BR_BOARD; i++)
    {
        bricks[i].hp = 0;	//CLEARS ALL
    }

    for (row = 0; row < BR_ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            i = row * COLS + col;

            int row_layer = row < (BR_ROWS - row - 1) ? row : (BR_ROWS - row - 1);
            int col_layer = col < (COLS  - col  - 1) ? col : (COLS  - col  - 1);
            int min_layer = row_layer < col_layer ? row_layer : col_layer;

            if (min_layer == 0 || min_layer == 2)
            {
                set_brick(&bricks[i], BR_TYPE_3); // HARD RINGS
            }
            else if (min_layer == 1)
            {
                set_brick(&bricks[i], BR_TYPE_2); // MEDIUM RINGS
            }
            else
            {
                if      (row == 4 && col == 5) { set_brick(&bricks[i], BR_TYPE_4); }
                else if (row == 4 && col == 7) { set_brick(&bricks[i], BR_TYPE_7); }
                else if (row == 4 && col == 9) { set_brick(&bricks[i], BR_TYPE_5); }
                else if (row == 5 && col == 5) { set_brick(&bricks[i], BR_TYPE_5); }
                else if (row == 5 && col == 7) { set_brick(&bricks[i], BR_TYPE_6); }
                else if (row == 5 && col == 9) { set_brick(&bricks[i], BR_TYPE_4); }
                else                           { set_brick(&bricks[i], BR_TYPE_2); }
            }
        }
    }
}

void init_level_4(brick_t bricks[])
{
    int i, row, col;	//LEVEL 4, COIL

    for (i = 0; i < BR_BOARD; i++)
    {
        bricks[i].hp = 0;
    }

    for (row = 0; row < BR_ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            i = row * COLS + col;

            // ROWS 0 AND 9 ALTERNATE BRICK TYPE 3
            if (row == 0 || row == 9)
            {
                if (col % 2 == 0) { set_brick(&bricks[i], BR_TYPE_3); }
            }
            // ROW 1 DECORATED WITH POWER-UPS
            else if (row == 1)
            {
                if      (col == 2)  { set_brick(&bricks[i], BR_TYPE_4); }
                else if (col == 7)  { set_brick(&bricks[i], BR_TYPE_5); }
                else if (col == 12) { set_brick(&bricks[i], BR_TYPE_4); }
            }
            // ROWS 2 AND 8 DECORATED WITH TYPE 2
            else if (row == 2 || row == 8)
            {
                if (col >= 3 && col <= 11) { set_brick(&bricks[i], BR_TYPE_2); }
            }
            // ROWS 3-7: COIL
            else if (row >= 3 && row <= 7)
            {
                // C
                if (col <= 2)
                {
                    if (row == 3 || row == 7)  { set_brick(&bricks[i], BR_TYPE_3); }
                    else if (col == 0)          { set_brick(&bricks[i], BR_TYPE_3); }
                }
                // O
                else if (col >= 4 && col <= 6)
                {
                    if (row == 3 || row == 7)       { set_brick(&bricks[i], BR_TYPE_3); }
                    else if (col == 4 || col == 6)  { set_brick(&bricks[i], BR_TYPE_3); }
                }
                // I
                else if (col >= 8 && col <= 10)
                {
                    if (row == 3 || row == 7)  { set_brick(&bricks[i], BR_TYPE_3); }
                    else if (col == 9)          { set_brick(&bricks[i], BR_TYPE_3); }
                }
                // L
                else if (col >= 12 && col <= 14)
                {
                    if (row == 7)      { set_brick(&bricks[i], BR_TYPE_3); }
                    else if (col == 12){ set_brick(&bricks[i], BR_TYPE_3); }
                }
            }
        }
    }
}

void init_level_n(brick_t bricks[])
{
    int i;
    int power_count = 0;

    for (i = 0; i < BR_BOARD; i++)
    {
        bricks[i].hp = 0;

        // 1/4 EMPTY CELL
        if (rand() % 4 == 0) { continue; }

        // RANDOM BRICK TYPE WEIGHTED TOWARD HARDER BRICKS
        int roll = rand() % 10;
        int type;

        if      (roll < 3) { type = BR_TYPE_1; }  // 30% TYPE 1
        else if (roll < 6) { type = BR_TYPE_2; }  // 30% TYPE 2
        else               { type = BR_TYPE_3; }  // 40% TYPE 3

        // OCCASIONAL POWER-UPS (MAX 4 PER LEVEL)
        if (power_count < 4 && rand() % 15 == 0)
        {
            type = (rand() % 4) + BR_TYPE_4;  // TYPE 4-7 RANDOM
            power_count++;
        }

        set_brick(&bricks[i], type);
    }
}

void set_brick(brick_t *brick, int type)
{
    brick->type = type;	//SWITCH TO AUTOFILL THE INFO OF EACH BRICK DEPENDING OF ITS TYPE
    switch(type)
    {
        case BR_TYPE_1: brick->hp=1; brick->score=BR_SCORE_1; brick->key=BR_KEY_1; break;
        case BR_TYPE_2: brick->hp=2; brick->score=BR_SCORE_2; brick->key=BR_KEY_2; break;
        case BR_TYPE_3: brick->hp=3; brick->score=BR_SCORE_3; brick->key=BR_KEY_3; break;
        case BR_TYPE_4: brick->hp=1; brick->score=BR_SCORE_4; brick->key=BR_KEY_4; break;
        case BR_TYPE_5: brick->hp=1; brick->score=BR_SCORE_5; brick->key=BR_KEY_5; break;
        case BR_TYPE_6: brick->hp=1; brick->score=BR_SCORE_6; brick->key=BR_KEY_6; break;
        case BR_TYPE_7: brick->hp=1; brick->score=BR_SCORE_7; brick->key=BR_KEY_7; break;
        default:        brick->hp=1; brick->score=BR_SCORE_1; brick->key=BR_KEY_1; break;
    }
}

void update_brick_key(brick_t *brick) //TO REPRESENT THE DAMAGE IN BLOCKS: # -> = -> -
{
    if (brick->type > BR_TYPE_3)
    {
    	return; // DON´T DO ANYTHING TO POWER-UPS
    }

    if      (brick->hp == 2)
    {
    	brick->key = BR_KEY_2;
    }
    else if (brick->hp == 1)
    {
    	brick->key = BR_KEY_1;
    }
}

void update_paddle(paddle_t *ppaddle, char key)
{
    if (key==LEFT)		//ALLOWS TO MOVE THE PADDLE
        {ppaddle->dx = -1;}
    else if (key == RIGHT)
    	{ppaddle->dx = 1;}
    else
        {ppaddle->dx = 0;}

    ppaddle->x += ppaddle->dx;

    int half = ppaddle->size / 2; //LIMIT IN BORDERS
    if (ppaddle->x - half < 0)
    {
    	ppaddle->x = half;
    }

    if (ppaddle->x + half >= COLS)
    {
    	ppaddle->x = COLS - 1 - half;
    }
}

void update_ball(ball_t *pball)
{
    pball->x += pball->dx;	//MOVEMENT
    pball->y += pball->dy;

    //LEFT AND RIGHT BOUNCE WITH WALLS
    if (pball->x <= 0)
    {
    	pball->x = 0;
    	pball->dx =  1;
    }
    if (pball->x >= COLS - 1)
    {
    	pball->x = COLS - 1;
    	pball->dx = -1;
    }

    // UP BOUNCE WITH WALLS
    if (pball->y <= 0)        { pball->y = 0;         pball->dy =  1; }

}
