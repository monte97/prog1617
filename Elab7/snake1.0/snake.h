#ifndef SNAKE_H
#define SNAKE_H

enum direction {UP, DOWN, LEFT, RIGHT};

struct snake {
  unsigned int x;
  unsigned int y;
};


/*
 * Returns the (coordinates of the) snake's head.
 */
struct snake snake_head(struct snake s[], unsigned int length);

/*
 * Returns 1 if the snake crosses himself, 0 otherwise.
 */
int snake_knotted(struct snake s[], unsigned int length);

/*
 * Moves the snake one step forward in the dir direction.
 */
void snake_move(struct snake s[], unsigned int length, enum direction dir);

/*
 * Increases the snake length.
 *
 * This is equivalent to:
 * - add a new head in the dir direction wrt the old head.
 */
void snake_increase(struct snake s[], unsigned int length, enum direction dir);

/*
 * Decreases the snake length.
 *
 * This is equivalent to:
 * - remove the tail of the snake.
 */
void snake_decrease(struct snake s[], unsigned int length);

#endif
