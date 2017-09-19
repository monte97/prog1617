#include <stdio.h>
#include <math.h>

int main(void){
	int i;
	int p;
	int isPrime = 1;
	int isSumOfSq = 0;
	unsigned x;
	scanf("%u",&x);

	/*is prime*/
	switch (x){
		case 0:
		case 1:{
			printf("Integer %u is not prime\n", x);
			break;
		}
		default:{
			
			i = 2;
			/*printf("prime test until %lf\n", (floor(sqrt(x))+1));*/
			while (i <= (floor(sqrt(x))+1) && isPrime){
				if (x!= i && x%i == 0){
					isPrime = 0;
				}
				i++;
			}
			
			/*
			for (i=2; i <= x/2; i++){
				if (x%i == 0){
					isPrime = 0;
				}
			}
			*/
			isPrime ? printf("Integer %u is prime\n", x) : printf("Integer %u is not prime\n", x);
			break;
		}
	}

	/*is sum of square*/
	switch (x){
		case 0:
		case 1:{
			printf("Integer %u is not a sum of square\n", x);
			break;
		}
		default:{
			for(i = 1; i < floor(sqrt(x))+1; ++i){
				for(p = 1; p < floor(sqrt(x))+1; ++p){
					if (ceil(((pow(i,2))+(pow(p,2)))) == x){
						isSumOfSq = 1;
					}
				}
			}
			isSumOfSq ? printf("Integer %u is the sum of two squares\n", x) : printf("Integer %u is not the sum of two squares\n", x); 
			break;
		}
	}

	/*is triangular*/
	switch (x){
		case 0:{
			printf("Integer 0 is not a triangular\n");
			break;
		}
		case 1:{
			printf("Integer 1 is triangular\n");
			break;
		}
		default:{
			/*un numero è triangolare se il risultato dell'equazione (sqrt((8*n)-1)-1)/2 è intero
			se floor(x) == ceil(x) allora è intero
			floor restituisce l'intero successivo al parametro
			ceil restituisce l'intero più piccolo non minore del parametro
			se coincidono allora il numero è intero
	
			if ( floor((sqrt((8*x)+1)-1) /2) == ceil((sqrt((8*x)+1)-1) /2) ){
				printf("Integer %u is triangular number\n", x);
			}else{
				printf("Integer %u is not triangular number\n", x);
			}
			break;
			*/
			( floor((sqrt((8*x)+1)-1) /2) == ceil((sqrt((8*x)+1)-1) /2) ) ? printf("Integer %u is triangular number\n", x) : printf("Integer %u is not triangular number\n", x);

		}
	}

	return 0;
}


