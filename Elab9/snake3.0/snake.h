#ifndef SNAKE_H
#define SNAKE_H

enum direction {UP, DOWN, LEFT, RIGHT};

struct position {
	unsigned int i;
	unsigned int j;
};

struct snake {
	unsigned int i;
	unsigned int j;
	struct snake *next;
	struct snake *prev;
};
/*
 * Creates a snake's head in a world of size rows*cols;
 */
struct snake *snake_create(unsigned int rows, unsigned int cols);
/*
 * Destroys the snake data structure.
 */
void snake_kill(struct snake *s);
/*
 * Returns the (position of the) snake's head.
 */
struct position snake_head(struct snake *s);
/*
 * Returns the (position of the) i-th part of the snake body.
 * 
 * Position 0 is equivalento the snake's head. If the snake
 * is shorter than i, the position returned is not defined. 
 */
struct position snake_body(struct snake *s, unsigned int i);
/*
 * Returns 1 if the snake crosses himself, 0 otherwise.
 */ 
int snake_knotted(struct snake *s);
/*
 * Moves the snake one step forward in the dir direction
 * into a toroidal world of size rows*cols.
 */
void snake_move(struct snake **s, enum direction dir);
/*
 * Reverses the snake.
 *
 * The tail of the snake is now the new head.
 */
void snake_reverse(struct snake **s);
/*
 * Increases the snake length.
 *
 * This is equivalent to:
 * - add a new head in the dir direction wrt the old head.
 */
void snake_increase(struct snake **s, enum direction dir);
/*
 * Removes from the tail of the snake decrease_len parts.
 */
void snake_decrease(struct snake **s, unsigned int decrease_len);

#endif
