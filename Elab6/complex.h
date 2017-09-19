# ifndef COMPLEX_H
# define COMPLEX_H

typedef struct complex {
	double re ;
	double im ;
} complex ;

/* BASIC OPERATIONS */

/* Returns the real part of the complex number x */
double creal (complex x);

/* Returns the imaginary part of the complex number x */
double cimg (complex x);

/* Returns the modulus of the complex number x */
double cmod (complex x);

/*
* Returns the argument of the complex number x .
* If x = 0 , returns 0.
*/
double carg (complex x);

/* ARITHMETIC OPERATIONS */

/* Returns the sum x + y of the complex numbers x and y */
complex cadd ( complex x , complex y );

/* Returns the difference x - y of the complex numbers x and y */
complex csub ( complex x , complex y );

/* Returns the quotient x / y of the complex numbers x and y */
complex cdiv ( complex x , complex y );

/* Returns the product x * y of the complex numbers x and y */
complex cmul ( complex x , complex y );

/* Returns the inverse 1/ x of the complex number x */
complex cinv ( complex x );

/* Returns the negative -x of the complex number x */
complex cneg ( complex x );

/* Returns the conjugate of the complex number x */
complex cconj ( complex x );
# endif