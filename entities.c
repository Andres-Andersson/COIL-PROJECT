/*
 * entities.h
 *
 *  Created on: May 20, 2026
 *      Author: progra
 */

#ifndef ENTITIES_H_
#define ENTITIES_H_

#define LIFE_MBALL -10
#define LIFE_EBALL 100
typedef struct 
{
	int x;
	int y;
	int hp;
	int type;
}bloque_t;

typedef struct 
{
	int x;
	int y;
	int dx;
	int dy;
	int hp; //LIFE_MBALL for the main, LIFE_E_BALL for the extras.
	float speed;
	
}bola_t;

typedef struct
{
	int x;
	int dx;
	int size; //An ODD number
	
}paddle_t;

typedef struct
{
	int type; //Each type will lead to an if condition, create #define for each power type
	int duration; // Power-up time duration
}powers_t;

#endif /* ENTITIES_H_ */
