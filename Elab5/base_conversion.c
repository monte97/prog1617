#include <stdio.h>
#include <math.h>

void base_conversion_it( unsigned int n , unsigned int b ){
	int cont_resti, cont_cifre = 0;
	int resto, save_n;
	if (n==0){
		printf("0\n");
	}else{
		
		cont_resti = floor(log(n)/log(b)); /*determino quante cifre mi servono per rappresentare il numero nella base specificata*/ 
		cont_resti++;
		cont_cifre = cont_resti; 
		save_n=n;
		/*il cilo interno si occupa di calcolare l'ultimo resto e "passarlo" al ciclo esterno
		che come prima cosa stampa appunto l'ultimo resto, in questo modo di fatto inverto le cifre stampate

		*/
		do{
			save_n=n;
			cont_resti=cont_cifre;
			do{
				resto = save_n%b;
				save_n/=b;
				cont_resti--;
			}while(cont_resti>0);

			/*fai stampa*/
			if (resto <= 9){
				printf("%d", resto);
			}else{
				printf("%c",65+((resto)-10)); /*converto i numero sopra al 9 in lettere come da specifica*/
			}
			cont_cifre --;
		}while(cont_cifre>0);
	}
	
}


void base_conversion_rc( unsigned int n , unsigned int b ){
	/*dato che prima effettuo la chiamata e poi "espongo" il risultato
	quando in fase di esecuzione i vari elementi vengo eliminati dallo stack le stampe dei valori sono già nell'oridine corretto
	*/
	if (n!=0){
		base_conversion_rc(n/b, b);
		if (n%b <= 9){
			printf("%d",n%b);
		}else{
			printf("%c",65+((n%b)-10));
		}
	}
}



