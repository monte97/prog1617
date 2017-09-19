#ifndef SNAKE_H
#define SNAKE_H

enum direction {UP, DOWN, LEFT, RIGHT};

struct coord {
	unsigned int x;
	unsigned int y;
};

struct snake {
	unsigned int max_length;
	struct coord *coord;
};

/*
 * Creates a snake's head at coordinates (x,y);
 */
struct snake *snake_create(unsigned int x, unsigned int y);

/*
 * Destroys the snake data structure.
 */
void snake_kill(struct snake *s);

/*
 * Returns the (coordinates of the) snake's head.
 */
struct coord snake_head(struct snake *s, unsigned int length);

/*
 * Returns 1 if the snake crosses himself, 0 otherwise.
 */ 
int snake_knotted(struct snake *s, unsigned int length);

/*
 * Moves the snake one step forward in the dir direction.
 */
void snake_move(struct snake *s, unsigned int length, 
                                         enum direction dir);

/*
 * Increases the snake length.
 *
 * This is equivalent to:
 * - add a new head in the dir direction wrt the old head.
 */
void snake_increase(struct snake *s, unsigned int length, 
                                         enum direction dir);
/*
 * Decreases the snake length by half.
 *
 * This is equivalent to:
 * - remove ceil(length/2) coordinates from the tail of the snake.
 */
void snake_decrease(struct snake *s, unsigned int length);

#endif
