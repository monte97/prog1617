#include <stdlib.h>
#include <time.h>
#include "world.h"
#include "snake.h"

// Allocates the world structure
static struct world *world_alloc(unsigned int rows, unsigned int cols);

// Allocates a row*col matrix
static enum cell **board_alloc(unsigned int row, unsigned int col);

// Frees the row*col matrix
static void board_free(enum cell **board);

// Initializes the world structure
static void world_init(struct world *W, unsigned int food_amount);

// Creates random food that does not overlap snake and world borders.
// The food variable should be either GOOD_FOOD or BAD_FOOD
static void random_food(struct world *W, enum cell food);

// Checks whether the snake opverlaps world borders or food.
// In the latter case, it removes the food from the board.
// It returns the type of overlap or EMPTY if there is no overlap.
static enum cell check_overlap(struct world *W);

// Updates the status of the world.
enum status update(struct world *W, enum direction dir);


struct world *world_create(unsigned int rows, unsigned int cols, unsigned int food_amount) {
	struct world *w = NULL;

	if((w = world_alloc(rows,cols)) != NULL)
		world_init(w,food_amount);

	return w;
}

void world_destroy(struct world *W) {
	if(W != NULL) {
		board_free(W->board);
		snake_kill(W->snake);
		free(W);
	}
}

enum status world_update(struct world *W, enum direction dir) {
	// First, move the snake
	snake_move(W->snake,W->snake_length,dir);	
	// Second, update the world and return whether to continue or not
	return update(W,dir);
}


static enum cell **board_alloc(unsigned int row, unsigned int col) {
	enum cell **board = (enum cell **)calloc(row,sizeof(enum cell *));
	
	if(board != NULL) {
		board[0] = (enum cell *)calloc(row*col,sizeof(enum cell));
		if(board[0] == NULL) {
			free(board);
			board = NULL;
		} else {
			unsigned int i;

			for(i = 1; i < row; i++)
				board[i] = &board[0][i*col];
		}
	}
	return board;
}

static void board_free(enum cell **board) {
	if(board != NULL) {
		free(board[0]);
		free(board);
	}
}

static struct world *world_alloc(unsigned int rows, unsigned int cols) {
	struct world *W = NULL;

	
	if((W = (struct world *)calloc(1,sizeof(struct world))) != NULL) {
		W->rows = rows;
		W->cols = cols;
		if((W->board = board_alloc(rows,cols)) == NULL) 
			free(W);
	}
	
	return W;
}

static void random_food(struct world *W, enum cell food) {
	unsigned int i, j;
	int tries = (W->rows-1)*(W->cols-1)-W->snake_length;
	struct coord head = snake_head(W->snake,W->snake_length);

	do {
		i = rand() % (W->rows-2)+1;
		j = rand() % (W->cols-2)+1;
	} while(--tries > 0 && (W->board[i][j] != EMPTY || (head.x == i && head.y == j)));
	// The search stops when an empty cell is found.
	// The tries > 0 condition prevents eventual infinite loops if the board is full. 

	if(tries > 0)
		W->board[i][j] = food;
}


static enum cell check_overlap(struct world *W) {
	struct coord head = snake_head(W->snake,W->snake_length);
	enum cell type;

	switch(type = W->board[head.x][head.y]) {
		case BAD_FOOD: case GOOD_FOOD: // Food overlap
			// Removes food from the cell
			W->board[head.x][head.y] = EMPTY;
			return type; 
		case BORDER:                  // Border overlap
			return type; 
		default: break;
	}
  return EMPTY;                     // No overlap 
}

static void world_init(struct world *W, unsigned int food_amount) {
	unsigned int i, j;

	srand(time(0));

	for(i = 0; i < W->rows; i++)
		for(j = 0; j < W->cols; j++)
			if(i == 0 || i == W->rows-1 || j == 0 || j == W->cols-1)
				W->board[i][j] = BORDER;
			else
				W->board[i][j] = EMPTY;
	
	// Puts the snake in the middle of the board
	W->snake_length = 1;
	W->snake = snake_create(W->rows/2,W->cols/2);

	// Adds the same amunt of bad and good food
	for(i = 0; i < food_amount; i++) {
		random_food(W,GOOD_FOOD);
		random_food(W,BAD_FOOD);
	}
}


enum status update(struct world *W, enum direction dir) {
	// If the snake is knotted, the game is over
	if(snake_knotted(W->snake,W->snake_length))
		return GAMEOVER;

	switch(check_overlap(W)) {
		case BORDER:       // the snake hit the border: game over
			return GAMEOVER;
		case GOOD_FOOD:    // the snake ate good food: add a new head
			snake_increase(W->snake,W->snake_length,dir);
			W->snake_length++;
			// We need to check whether the snake reached the maximim possible
			// length or whether the new head hits something else
			if(W->snake_length == (W->rows-1)*(W->cols-1) || update(W,dir) == GAMEOVER) {
				return GAMEOVER;
			} else {
				// If the game continues we need to add new good food
				random_food(W,GOOD_FOOD);
				return CONTINUE;
			} 
		case BAD_FOOD:    // the snake ate bad food: remove its tail 
			snake_decrease(W->snake,W->snake_length);
			W->snake_length /= 2;
			// We need to check whether the length of the snake is zero: dead
			if(W->snake_length == 0) {
				return GAMEOVER; 
			} else {
				// If the game continues we need to add new good food
				random_food(W,BAD_FOOD);
				return CONTINUE;
			}
		default:         // no overalp: continue the game
				return CONTINUE;
	}
}
