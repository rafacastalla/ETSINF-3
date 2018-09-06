#include <stdio.h>
#include <math.h>
#include <limits.h>

typedef unsigned long long Entero_grande;
#define ENTERO_MAS_GRANDE  ULLONG_MAX

int primo(Entero_grande n)
{
  volatile int p;
  Entero_grande i, s;

  p = (n % 2 != 0 || n == 2);

  if (p) {
    s = sqrt(n);

#pragma omp parallel private(i)
{
    int ifil = omp_get_thread_num();
    int nfils = omp_get_num_threads();

    for (i = 3+2*ifil; p && i <= s; i += 2*nfils)
      if (n % i == 0) p = 0;
  }
}//fin pragma omp

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
