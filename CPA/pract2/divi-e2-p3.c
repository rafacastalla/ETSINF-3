
#include <stdio.h>
#include <omp.h>

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
  
  double tmp = omp_get_wtime();
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
        
        // 3a paralelitzacio, cambiar el bucle de dalt
        omp_set_num_threads(2);
        int auxV = vn[N/2], auxC = vc[N/2], j; 
        
        #pragma omp parallel //schedule(runtime)
        {

          //omp_get_thread_num();
          #pragma omp single nowait
          for ( i = N - 1 ; i >= N/2 && MEJOR(n,c,i-1) ; i-- ) {
            vc[i] = vc[i-1]; vn[i] = vn[i-1];
          }

          #pragma omp single nowait
          for ( j = (N/2) - 1 ; j > 0 && MEJOR(n,c,j-1) ; j-- ) {

            //if( j == (N/2) - 1 ) auxV = vn[j]; auxC = vc[j];
            
            vc[j] = vc[j-1]; vn[j] = vn[j-1];
          }
          
          //#pragma omp barrier
        }

        if (i < N/2){ 
          vc[N/2 +1] = auxC;
          vn[N/2 +1] = auxV;
          vc[j] = c; vn[j] = n;
        
        }else { vc[i] = c; vn[i] = n; }
        
      }

    }

  tmp = omp_get_wtime() - tmp;
  printf("Time on parallel: %5.5f\n", tmp);

  /* Imprimir los N con más divisores */
  printf("Los %d enteros con más divisores hasta %d son:\n",N,M);
  for ( k = 0 ; k < N ; k++ ) {
    printf(" %d, con %d divisores\n",vn[k],vc[k]);
  }

  return 0;
}

