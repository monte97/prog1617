//Montelli Francesco
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    //caratteri, sarebbero interi
    char c = 'a'; //
    signed char sc = 'b'; 
    unsigned char usc = 'c'; 


    //interi
    short sh = 123; 
    unsigned short ush = 1444;
    int i = 145; 
    unsigned u = 144;
    long l = 5;
    unsigned long ul = 1;


    //virgola mobile
    float f = -1.1e+3; 
    double d = 1.2e-2; 
    long double ld = 1.12345678; 


    printf("CHAR          \n nome var  :\tc   \n v. attuale:\t%c [%d] \n v. minimo :\t%c [%d]  \n v. massimo:\t%c [%d]   \n dimensione:\t%ld\n\n", c, c, CHAR_MIN, CHAR_MIN, CHAR_MAX, CHAR_MAX, sizeof(c));
    printf("SIGNED CHAR   \n nome var  :\tsc  \n v. attuale:\t%c [%d] \n v. minimo :\t%c [%d]  \n v. massimo:\t%c [%d]   \n dimensione:\t%ld\n\n", sc, sc, SCHAR_MIN, SCHAR_MIN, SCHAR_MAX, SCHAR_MAX, sizeof(sc));
    printf("UNSIGNED CHAR \n nome var  :\tusc \n v. attuale:\t%c [%d] \n v. minimo :\t%c [%d]  \n v. massimo:\t%c [%d]   \n dimensione:\t%ld\n\n", usc, usc, 0, 0, UCHAR_MAX, UCHAR_MAX, sizeof(usc)); 
    printf("SHORT         \n nome var  :\tsh  \n v. attuale:\t%d  \n v. minimo :\t%d   \n v. massimo:\t%d    \n dimensione:\t%ld\n\n", sh, SHRT_MIN, SHRT_MAX, sizeof(sh));
    printf("UNSIGNED SHORT\n nome var  :\tush \n v. attuale:\t%d  \n v. minimo :\t%d   \n v. massimo:\t%d    \n dimensione:\t%ld\n\n", ush, 0, USHRT_MAX, sizeof(ush));
    printf("INT           \n nome var  :\ti   \n v. attuale:\t%d  \n v. minimo :\t%d   \n v. massimo:\t%d    \n dimensione:\t%ld\n\n", i, INT_MIN, INT_MAX, sizeof(i));
    printf("UNSIGNED      \n nome var  :\tu   \n v. attuale:\t%u  \n v. minimo :\t%u   \n v. massimo:\t%u    \n dimensione:\t%ld\n\n", u, 0, UINT_MAX, sizeof(u));
    printf("LONG          \n nome var  :\tl   \n v. attuale:\t%ld \n v. minimo :\t%ld  \n v. massimo:\t%ld   \n dimensione:\t%ld\n\n", l, LONG_MIN, LONG_MAX, sizeof(l));
    printf("UNSIGNED LONG \n nome var  :\tul  \n v. attuale:\t%lu \n v. minimo :\t%d   \n v. massimo:\t%lu   \n dimensione:\t%ld\n\n", ul, 0, ULONG_MAX, sizeof(ul));
    printf("FLOAT         \n nome var  :\tf   \n v. attuale:\t%e  \n v. minimo :\t%e   \n v. massimo:\t%e    \n dimensione:\t%ld\n\n", f, FLT_MIN, FLT_MAX, sizeof(f));
    printf("DOUBLE        \n nome var  :\td   \n v. attuale:\t%e  \n v. minimo :\t%e   \n v. massimo:\t%e    \n dimensione:\t%ld\n\n", d, DBL_MIN, DBL_MAX, sizeof(d));
    printf("LONG DOUBLE   \n nome var  :\tld  \n v. attuale:\t%Le \n v. minimo :\t%Le  \n v. massimo:\t%Le   \n dimensione:\t%ld\n\n", ld, LDBL_MIN, LDBL_MAX, sizeof(ld));


    return 0;

}
