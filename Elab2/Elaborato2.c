#include <stdio.h>
#include "lib.h"

int main(void){
	
	double a,b,c;
	int solNum;
	scanf("%lf %lf %lf",&a,&b,&c);
	
	printf("%e %e %e\n", a, b, c);
	solNum = NUM_OF_ROOTS(a, b, c);

	(solNum == 0) ? printf("Equation f(x) = 0 has %d roots\n", solNum ):
	(solNum == 1) ? printf("Equation f(x) = 0 has %d root \nRoot 1 = Root 2 = %e\n", solNum, ROOT1(a,b,c)):
		printf("Equation f(x) = 0 has %d roots\nRoot 1 = %e Root 2 = %e\n", solNum, ROOT1(a,b,c), ROOT2(a,b,c));
	



	MAXIMUM_POINT(a,b,c) ? 
		printf("Function f(x) has a maxium in f(%e) = %e\n", EXTREME_POINT(a,b,c), Y_EXTREME(a,b,c)) 
		:
		printf("Function f(x) has a minium in f(%e) = %e\n", EXTREME_POINT(a,b,c), Y_EXTREME(a,b,c));
		
		
	return 0;
}