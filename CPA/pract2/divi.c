
#include <stdio.h>

#define M 100000
#define N 10

/*
 Macro para determinar si el número n, que tiene c divisores,
 tiene más divisores que el número almacenado en la posición p de los vectores.
 A igual número de divisores, se considera mejor si es un número más pequeño.
 ---
 Macro that returns TRUE if number n, which has c divisors, is "BETTER" (i.e. it has
 more divisors) than the number stored at position p of the vectors.
 If both have the same number of divisors, the smallest number is considered better
*/
#define MEJOR(n,c,p) ( c > vc[p] || (c == vc[p] && n < vn[p]) )

int main()
{
	int c,n,vc[N],vn[N],i,ini,inc,k;

	/* Inicializar las cuentas máximas */
	for ( i = 0 ; i < N ; i++ ) {
	vc[i] = 0; vn[i] = 0;
	}

  	/* Bucle principal: contar divisores para los números desde 1 hasta M */
	for ( n = 1 ; n <= M ; n++ ) {
	  c = 1; /* por el 1, que siempre es divisor */
	  if ( n % 2 == 0 ) {
	    ini = 2; inc = 1;
	  } else { /* no mirar pares, que seguro que no son divisores */
	    ini = 3; inc = 2;
	  }

	  /* Contar divisores */
	  for ( i = ini ; i <= n ; i += inc ) {
	    if ( n % i == 0 ) c++;
	  }    

	  /* Insertar en vector si es de los N con más divisores */
	  if ( MEJOR(n,c,N-1) ) {
	    for ( i = N - 1 ; i > 0 && MEJOR(n,c,i-1) ; i-- ) {
	      vc[i] = vc[i-1]; vn[i] = vn[i-1];
	    }
	    vc[i] = c; vn[i] = n;
	  }

	}

	/* Imprimir los N con más divisores */
	printf("Los %d enteros con más divisores hasta %d son:\n",N,M);
	for ( k = 0 ; k < N ; k++ ) {
	printf(" %d, con %d divisores\n",vn[k],vc[k]);
	}

	return 0;
}

