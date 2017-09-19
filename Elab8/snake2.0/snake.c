#include "snake.h"
#include <stdlib.h>
#include <math.h>

static void trasla(struct snake *s,unsigned int length){
	unsigned int i;
	for(i = length; i > 0; i--){
		s->coord[i] = s->coord[i-1];
	}
}

static void move_head(struct snake *s, enum direction dir){
	switch (dir){
		/*UP*/
		case 0:
			s->coord[0].x--;
			break;
		/*DOWN*/
		case 1:
			s->coord[0].x++;
			break;
		/*LEFT*/
		case 2:
			s->coord[0].y--;
			break;
		/*RIGTH*/
		case 3:
			s->coord[0].y++;
			break;
	}
}

static void updateSnake(struct snake *s, struct coord *c, unsigned int l){
	s->coord = c;
	s->max_length = l;
}



/*
 * Destroys the snake data structure.
 */
void snake_kill(struct snake *s){
	int i;
	for (i = 0; i < s-> max_length; i++){
		free(s->coord[i]);
	}
	free(s);
}


/*
 * Returns the (coordinates of the) snake's head.
 */
struct coord snake_head(struct snake *s, unsigned int length){
	return s->coord[0];
}

/*
 * Returns 1 if the snake crosses himself, 0 otherwise.
 */ 
int snake_knotted(struct snake *s, unsigned int length){
	unsigned int i;
	struct coord headCord = s->coord[0];

	for (i = 1; i < length; i++)
		if (headCord.x == s->coord[i].x && headCord.y == s->coord[i].y)
			return 1;
	
	return 0;

}

void snake_move(struct snake *s, unsigned int length, enum direction dir){
	trasla(s, length);
	move_head(s, dir);	
}

/*
 * Increases the snake length.
 *
 * This is equivalent to:
 * - add a new head in the dir direction wrt the old head.
 */
void snake_increase(struct snake *s, unsigned int length, enum direction dir){
	struct coord *c = s->coord;

	if (length+1 >= s->max_length){
		c = (struct coord *) realloc(c, (s->max_length*2) * (sizeof(struct coord)));
		updateSnake(s, c, s->max_length*2); //aggiorno le info sullo snake
	}
	
	//aggiorno le posizioni
	trasla(s, length);
	move_head(s, dir);
}

/*
 * Decreases the snake length by half.
 *
 * This is equivalent to:
 * - remove ceil(length/2) coordinates from the tail of the snake.
 */
void snake_decrease(struct snake *s, unsigned int length){
	struct coord *c = s->coord;

	c = (struct coord*) realloc(c, sizeof(struct coord) * length); //rialloco la memoria in modo da avere solo metà degli elementi nell'array delle coordinate

	//update delle dimensione del serpente
	updateSnake(s, c, length);
}

/*
 * Creates a snake's head at coordinates (x,y);
 */
struct snake *snake_create(unsigned int x, unsigned int y){
	static struct snake *s = 0;
	static struct coord *c = 0;

	c = (struct coord*)  calloc(10, sizeof(struct coord));
	s = (struct snake*) malloc(sizeof(struct snake));

	c -> x = x;
	c -> y = y;

	s->max_length = 10;
	s->coord = c;
	return s;
}
