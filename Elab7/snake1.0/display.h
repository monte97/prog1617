#ifndef DISPLAY_H
#define DISPLAY_H

#include "world.h"

// Waiting time for input
#define STARTING_TIMEOUT    256 //256ms

#define SNAKE_SYMBOL       '@'
#define GOOD_FOOD_SYMBOL   ACS_DIAMOND
#define BAD_FOOD_SYMBOL    ACS_DEGREE

/*
 * Gets the display's number of rows and columns
 */
void display_width(int *max_row, int *max_col);

/*
 * Opens the graphical display.
 */
void display_open(void);

/*
 * Closes the graphical display.
 */
void display_close(void);

/*
 * Plots the current world into the graphical display.
 */
void display_plot(struct world *W);

/*
 * Plots the final world into the graphical display.
 */
void display_gameover(struct world *W);

/*
 * Gets the next input from keyboard.
 */
enum direction display_input(enum direction dir);

#endif
