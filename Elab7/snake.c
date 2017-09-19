#include "snake.h"

static void trasla(struct snake s[],unsigned int length){
	unsigned int i;
	for(i = length; i > 0; i--){
		s[i] = s[i-1];
	}
}

static void move_head(struct snake s[], enum direction dir){
	switch (dir){
		/*UP*/
		case 0:
			s[0].x--;
			break;
		/*DOWN*/
		case 1:
			s[0].x++;
			break;
		/*LEFT*/
		case 2:
			s[0].y--;
			break;
		/*RIGTH*/
		case 3:
			s[0].y++;
			break;
	}
}

struct snake snake_head(struct snake s[], unsigned int length){
	return s[0];
}

int snake_knotted(struct snake s[], unsigned int length){
	unsigned int i;
	for (i = 1; i < length; ++i) 
		if (s[0].x == s[i].x && s[0].y == s[i].y) 
			return 1;
	
	return 0;
}

void snake_move(struct snake s[], unsigned int length, enum direction dir){
	trasla(s, length-1);
	move_head(s, dir);	
}


void snake_decrease(struct snake s[], unsigned int length){}

void snake_increase(struct snake s[], unsigned int length, enum direction dir){
	/*funziona anche da vuoto*/
	//force_move_opposite(s, length, dir);
	//trasla(s, length);
	//move_head(s, dir);
	switch (dir){
		/*UP*/
		case 0:
			s[length].x = s[length-1].x - 1; 
			s[length].y = s[length-1].y;
			break;
		/*DOWN*/
		case 1:
			s[length].x = s[length-1].x - 1;
			s[length].y = s[length-1].y;
 			break;
		/*LEFT*/
		case 2:
			s[length].x = s[length-1].x;
			s[length].y = s[length-1].y - 1;
			break;
		/*RIGTH*/
		case 3:
			s[length].x = s[length-1].x;
			s[length].y = s[length-1].y + 1;
			break;
	}
		
}