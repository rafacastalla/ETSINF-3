#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <omp.h>

typedef unsigned long long Entero_grande;
#define ENTERO_MAS_GRANDE  ULLONG_MAX
//#define _OPENMP

int primo(Entero_grande n)
{
  volatile int p;
  Entero_grande i, s;

  p = (n % 2 != 0 || n == 2);

  if (p) {
    s = sqrt(n);
	  //i = 3;

    double fils = 1;
    int fil = 1;
    
    #pragma omp parallel private(i)
    {

      //#ifdef _OPENMP
      fils = omp_get_num_threads();
      fil = omp_get_thread_num();
      //#endif

      for (i = 3+2*fil; p && i <= s; i += 2*fils)
        if (n % i == 0) p = 0;

    }

  }

  return p;
}

int main()
{
  Entero_grande n;
	
  for (n = ENTERO_MAS_GRANDE; !primo(n); n -= 2) {
    /* NADA */
  }

  printf("El mayor primo que cabe en %lu bytes es %llu.\n",
         sizeof(Entero_grande), n);

  return 0;
}
