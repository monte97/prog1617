#include <math.h>
#include "complex.h"

static complex create_complex(double a, double b){
	complex c;
	c.re = a;
	c.im = b;
	return c;
}

double creal(complex x){
    return x.re;    
}

double cimg(complex x){
    return x.im;
}

double cmod(complex x){
    return sqrt(pow(x.re,2)+pow(x.im,2));
}

double carg(complex x){
	if (x.re && x.im) return atan2(x.im,x.re);
	else return 0;
}

complex cadd(complex x, complex y){
    double re, im;
    re = x.re + y.re;
    im = x.im + y.im;
    return create_complex(re, im);
}

complex csub(complex x, complex y){
    double re, im;
    re = x.re - y.re;
    im = x.im - y.im;
    return create_complex(re, im);
}

complex cdiv(complex x, complex y){
    double re, im;
    re = (( (x.re*y.re) + (x.im*y.im) ) / (pow(y.re,2) + pow(y.im,2)));
    im = (( (y.re*x.im) - (x.re*y.im) ) / (pow(y.re,2) + pow(y.im,2)));
    return create_complex(re, im);
}

complex cmul(complex x, complex y){
    double re, im;
    re = (x.re*y.re) - (x.im*y.im);
    im = (x.im*y.re) + (x.re*y.im);
    return create_complex(re, im);
}

/* Returns the inverse 1/x of the complex number x */
complex cinv(complex x){
    double re, im;
    re =  x.re / (pow(x.re,2)+pow(x.im,2));
    im = -x.im / (pow(x.re,2)+pow(x.im,2));
    return create_complex(re, im);
}

/* Returns the negative -x of the complex number x */
complex cneg(complex x){
    double re, im;
    re = -x.re;
    im = -x.im;
    return create_complex(re, im);
}
    

/* Returns the conjugate of the complex number x */
complex cconj(complex x){
    double re, im;
    re = x.re;
    im = -x.im;
    return create_complex(re, im);
}



