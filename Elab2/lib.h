#include <math.h>

#define DELTA(a,b,c) ((b)*(b)-4*((a)*(c)))
#define Y_EXTREME(a,b,c) ((a)*EXTREME_POINT((a),(b),(c))*EXTREME_POINT((a),(b),(c)) + (b)*EXTREME_POINT((a),(b),(c)) + (c))

#define NUM_OF_ROOTS(a, b, c) (DELTA((a),(b),(c)) == 0 ? 1 : (DELTA((a),(b),(c)) < 0 ? 0 : 2) )
#define ROOT1(a,b,c) ( (-(b)+sqrt(DELTA((a),(b),(c))))/(2*(a)) )
#define ROOT2(a,b,c) ( (-(b)-sqrt(DELTA((a),(b),(c))))/(2*(a)) )
#define MAXIMUM_POINT(a,b,c) ((a) < 0 ? 1 : 0)
#define EXTREME_POINT(a,b,c) (-(b)/(2*(a)))