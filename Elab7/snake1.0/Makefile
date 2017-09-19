CFLAG = -Wall -pedantic-errors -O3 
CFLAG2 = -lncurses
 
all: snake

snake.o: snake.h snake.c
	gcc $(CFLAG) -c snake.c $(CFLAG2)

world.o: world.h world.c
	gcc $(CFLAG) -c world.c $(CFLAG2)

display.o: world.h display.h display.c
	gcc $(CFLAG) -c display.c $(CFLAG2)

snake: snake.h world.h display.h snake.o world.o display.o main.c
	gcc $(CFLAG) -lcurses snake.o world.o display.o main.c -o snake $(CFLAG2)

clean:
	rm -rf *.o snake 
