#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <curses.h>
#include "display.h"

// Shared variabile: the timeout delay can be changed on request
// to make the game faster or slower
static unsigned int TIMEOUT = STARTING_TIMEOUT;


// Draws the border of the board.
static void display_border(struct world *W, unsigned int start_row, unsigned int start_col);

// Draws the food.
static void display_food(struct world *W, unsigned int start_row, unsigned int start_col);

// Draws the snake.
static void display_snake(struct world *W, unsigned int start_row, unsigned int start_col);

void display_width(int *max_row, int *max_col) {
	getmaxyx(stdscr,*max_row,*max_col);	
}

void display_print(char *s) {
	unsigned int len       = strlen(s);
	unsigned int start_row = (LINES - 1)/2;
  unsigned int start_col = (COLS - len)/2;
	mvprintw(start_row,start_col,s);
}


void display_open(void) {
	initscr();
	cbreak();
	noecho();               
	keypad(stdscr, TRUE); // make keys work
	curs_set(0);          // hide cursor
	timeout(TIMEOUT);     // Sets the waiting time for getch()
}

void display_plot(struct world *W) {
	unsigned int start_row = (LINES - W->rows)/2;
	unsigned int start_col = (COLS - W->cols)/2;

	erase();
	mvprintw(start_row-1,start_col+1,"SCORE: %u",W->snake_length);
	mvprintw(start_row+W->rows,start_col+1,"[Q]uit  [F]ast  [S]low");
	display_border(W,start_row,start_col);
	display_food(W,start_row,start_col);
	display_snake(W,start_row,start_col);
	refresh();
}

void display_gameover(struct world *W) {
	unsigned int start_row = (LINES - W->rows)/2;
	unsigned int start_col = (COLS - W->cols)/2;
	char *str = "GAME OVER";

	erase();
	mvprintw(start_row-1, start_col+1,"SCORE: %u",W->snake_length);
	display_border(W,start_row,start_col);
	display_food(W,start_row,start_col);
	display_snake(W,start_row,start_col);
	mvprintw(start_row+W->rows+1,start_col+(((int)W->cols-strlen(str))/2),str);
	refresh();
	// Wait forever for 'q' to be pressed
	timeout(-1);
	while(getch() != 'q'); 
}

void display_close(void) {
	endwin();
}

enum direction display_input(enum direction previous) {
	int ch = getch();

	switch (ch) {
		// We cannot move the snake in one direction
    // and immediately after in the opposite direction.
		case KEY_LEFT:  // Move the snake left
			if (previous != RIGHT) return LEFT;
			else break;
		case KEY_RIGHT: // Move the snake right
			if (previous != LEFT)  return RIGHT;
			else break;
		case KEY_DOWN:  // Move the snake down
			if (previous != UP)    return DOWN;
			else break;
		case KEY_UP:   // Move the snake up
			if (previous != DOWN)  return UP;
			else break;
		case 'f': // Faster snake
			TIMEOUT = TIMEOUT == 1 ? 1: TIMEOUT / 2;
			timeout(TIMEOUT);
			return display_input(previous);
		case 's': // Slower snake
			TIMEOUT = TIMEOUT > UINT_MAX/2 ? TIMEOUT : TIMEOUT * 2;
			timeout(TIMEOUT);
			return display_input(previous);
		case 'q': // Quits the game
			display_close();
			exit(0);
	}
	return previous;
}

static void display_border(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i;
	
	mvaddch(start_row,start_col,ACS_ULCORNER);
	mvaddch(start_row,start_col+W->cols-1,ACS_URCORNER);
	mvaddch(start_row+W->rows-1,start_col,ACS_LLCORNER);
	mvaddch(start_row+W->rows-1,start_col+W->cols-1,ACS_LRCORNER);

	
	for(i = 1; i < W->rows-1; i++) {
		mvaddch(start_row+i,start_col,ACS_VLINE);
    mvaddch(start_row+i,start_col+W->cols-1,ACS_VLINE);
	}

	for(i = 1; i < W->cols-1; i++) {
		mvaddch(start_row,start_col+i,ACS_HLINE);
		mvaddch(start_row+W->rows-1,start_col+i,ACS_HLINE);
	}
	
}

static void display_food(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i,j;

	for(i = 1; i < W->rows-1; i++)
		for(j = 1; j < W->cols-1; j++)
			switch(W->board[i][j]) {
				case GOOD_FOOD: mvaddch(start_row+i,start_col+j,GOOD_FOOD_SYMBOL); break;
				case BAD_FOOD:  mvaddch(start_row+i,start_col+j,BAD_FOOD_SYMBOL); break;
				default: break;
			}
}

// Ugly: we need to know how here the organization of the snake data strucure
static void display_snake(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i;
	for(i = 0; i < W->snake_length; i++) 
			mvaddch(start_row+W->snake->coord[i].x, start_col+W->snake->coord[i].y,SNAKE_SYMBOL);
		
}
