#include <math.h>
#include <limits.h>

static int suc = 0;
unsigned short int is_prime ( unsigned short int n ){
	
	int i;

	if (n<2){
		return 0;
	}else{
		i = 2;
		while (i <= (floor(sqrt(n))+1)){
			if (n!= i && n%i == 0){/*ho trovato un divisore, non è primo, ritorno subito*/
				return 0;
			}
			i++;
		}
			
	}

	return 1;
	
}

unsigned short int nth_prime (unsigned short int n ){
	unsigned short int i = 2; /*2 è lo 0-esimo numero primo*/
	unsigned short int primeCont = 0; /*a che numero primo sono arrivato*/

	/*finchè non ho raggiunto l'n-esimo numero primo*/
	while (primeCont != n+1){ /*PERCHÈ FUNZIONA*/
		/*se è primo incremento contatore dei numeri primi*/
		if (is_prime(i)){
			primeCont++;
		}

		if (i == USHRT_MAX){
			return 0;
		}else{
			i++;
		}
	
		
	}
	return --i;
	
}

unsigned short int succ_prime ( int reset ){
	int res;
	if (reset==0){
		suc++;
		res = nth_prime(suc-1);
		/*
		*se è andato in overflow resetto il contatore della successioni e ritorno 0
		*/
		if (res == 0){
			suc = 0; /*in questo modo ritorna 2 alla prossima chiamata*/
			return 0;
		}else{
			return res;
		}
		
	}else{
		/*dato che ritorna due dopo devo dare 3*/
		suc = 1;
		return 2;
	}
}

static unsigned short int mcd(unsigned short int x ,unsigned short int y){
	do{
		if (x>y){
			x-=y;
		}else if(x<y){
			y-=x;
		}else{
			return x;
		}
    }
    while(x!=y);
    return x;
}

unsigned short int co_prime(unsigned short int m ,unsigned short int n){
	
	return (mcd(m,n)==1) ? 1:  0;
	
	/*
	if (mcd(m,n) == 1){
		return 1;
	}else{
		return 0;
	}
	*/
}