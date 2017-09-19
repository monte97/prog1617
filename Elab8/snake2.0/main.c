#include <stdio.h>
#include <stdlib.h>
#include "world.h"
#include "snake.h"
#include "display.h"

#define MIN(x,y) ((x)<(y)?(x):(y))

#define WORLD_ROWS       30
#define WORLD_COLS       (2*WORLD_ROWS) 
#define FOOD_AMOUNT      20

int main() {
	enum direction dir = RIGHT; // The snake starts sliding to the right
	struct world *W;
	int max_row, max_col;

	display_open();

	display_width(&max_row,&max_col);

	// Creates a board that fits into the display
	W = world_create(MIN(WORLD_ROWS,max_row-3),MIN(WORLD_COLS,max_col),FOOD_AMOUNT);

	if(W == NULL) { // Allocation error
		display_close();
		fprintf(stderr,"Error: cannot initialize the game\n");
		return 1;
	}

	do {
		display_plot(W);
		dir = display_input(dir);
	} while(world_update(W,dir) == CONTINUE);

	display_gameover(W);
	world_destroy(W);

	display_close();

  return 0;
}
