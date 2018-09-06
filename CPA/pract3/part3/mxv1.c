#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10000
#define NITER 50

/* Valor double aleatorio entre 0 y 1 */
#define D01  (rand() / (double)RAND_MAX)

/* NOTA: Se trabaja con matrices almacenadas por filas */
#define M(i,j) M[(i)*n + (j)]
#define Mloc(i,j) Mloc[(i)*n + (j)]

void inventa(int m, int n, double *A)
{
  for (m *= n; m > 0; m--)
    *A++ = D01;
}
/* Se asume que todos los elementos son no negativos,
 * lo que es cierto si se ha generado con la función inventa */
double inf_norma(int m, int n, double *A)
{
  double max, aux;
  int j;

  max = 0;
  for (; m > 0; m--) {
    aux = 0;
    for (j = 0; j < n; j++)
      aux += *A++;
    if (aux > max) max = aux;
  }
  return max;
}
void escala(int m, int n, double *A, double e)
{
  for (m *= n; m > 0; m--)
    *A++ *= e;
}

/*
 * (Resolución de un sistema de ecuaciones por un método iterativo)
 * Dadas una matriz de iteración M de nxn y dos vectores x,v de nx1, calcular:
 * Repetir num_iteraciones veces:
 *   x <- M * x + v
 * Al final, se tendrá en x una aproximación a la solución del sistema.
 * Se desea visualizar su 1-norma.
 * (La 1-norma de un vector es la suma de los valores absolutos de sus elementos)
 */
int main(int argc, char *argv[])
{
  int num_iter = NITER, semilla = 0, n = N, n2,
      nfilas, nfilascalculo, tama;
  char opcion;
  double t;
  int yo, num_procs, proc;
  double *M, *Mloc, *x, *xloc, *v, *vloc, norma, aux;
  int i, j, iter;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &yo);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  while (argc > 1) {
    argc--; argv++;
    if (argv[0][0] != '-') {
      opcion = '?';
    } else {
      opcion = *++argv[0];
      if (opcion != '\0' && *++argv[0] == '\0' && argc > 1) {
        argc--; argv++;
      }
    }
    switch (opcion) {
    case 's':
      semilla = atoi(argv[0]);
      break;
    case 'n':
      n = atoi(argv[0]); if (n < 0) n = N;
      break;
    case 'i':
      num_iter = atoi(argv[0]); if (num_iter < 0) num_iter = NITER;
      break;
    default:
      fprintf(stderr, "Uso: mxv1 [-s semilla] [-n tamanyo] [-i iteraciones]\n");
      return 1;
    }
  }

  /* Calculamos n2, un tamaño múltiplo de num_procs en el que quepa n */
  nfilas = n / num_procs;
  if (num_procs * nfilas < n) nfilas++;
  n2 = num_procs * nfilas;

  /* Todos los procesos almacenarán un bloque de filas de M (Mloc), de v (vloc)
   * y del vector x recien calculado (xloc), ademas del vector x de la
   * iteracion anterior completo (x) */
  if (yo == 0)   /* El proceso 0 almacenará toda la M y toda la v */
    tama = n2 * n + n2;
  else
    tama = 0;
  tama += nfilas * n + 2 * nfilas + n2;   /* Mloc, vloc, xloc, x */

  M = malloc(tama * sizeof(double));
  if (M == NULL) {
    fprintf(stderr, "ERROR: Falta memoria\n");
    return 1;
  }

  tama = nfilas * n;
  if (yo == 0) {
    v = M + n2 * n;
    Mloc = v + n2;
  } else {
    Mloc = M;
  }
  vloc = Mloc + tama;
  xloc = vloc + nfilas;
  x = xloc + nfilas;

  if (yo == 0) {
    srand(semilla);
    inventa(n, n, M);
    inventa(n, 1, v);
    inventa(n, 1, x);
    /* Ya que es inventado, hacer que el sistema sea convergente
     * (la norma de la matriz de iteración M debe ser menor que 1) */
    escala(n, n, M, 0.9 / inf_norma(n, n, M));
  }

  t = MPI_Wtime();

  /* COMUNICACIONES */
  /* Repartir la M y la v por filas (nfilas a cada proceso)
   * y enviar la x inicial a todos */
  /*if (yo == 0) {
    // Para el 0, no enviamos sino que copiamos
    for (i = 0; i < nfilas; i++) {
      for (j = 0; j < n; j++)
        Mloc(i, j) = M(i, j);
      vloc[i] = v[i];
    }
    // Para el resto, enviamos 
    for (proc = 1; proc < num_procs; proc++) {
      MPI_Send(&M[proc*tama], tama, MPI_DOUBLE, proc, 13, MPI_COMM_WORLD);
      MPI_Send(&v[proc*nfilas], nfilas, MPI_DOUBLE, proc, 89, MPI_COMM_WORLD);
      MPI_Send(x, n, MPI_DOUBLE, proc, 25, MPI_COMM_WORLD);
    }
    
  } else {
    MPI_Recv(Mloc, tama, MPI_DOUBLE, 0, 13, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(vloc, nfilas, MPI_DOUBLE, 0, 89, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(x, n, MPI_DOUBLE, 0, 25, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }*/

  MPI_Scatter(M, tama, MPI_DOUBLE, Mloc, tama, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Scatter(v, nfilas, MPI_DOUBLE, vloc, nfilas, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  nfilascalculo = n - yo * nfilas;
  if (nfilascalculo > nfilas)
    nfilascalculo = nfilas;

  for (iter = 1; iter <= num_iter; iter++) {
    /* Calcular M*x + v en la parte local de x (xloc) de cada proceso */
    for (i = 0; i < nfilascalculo; i++) {
      aux = vloc[i];
      for (j = 0; j < n; j++)
        aux += Mloc(i, j) * x[j];
      xloc[i] = aux;
    }

    /* COMUNICACIONES */
    /* Preparar la siguiente iteración. Esto es formar la x completa (x)
     * a partir de los fragmentos de x (xloc) que tiene cada proceso
     * y dejarla replicada en todos */
    /*if (yo == 0) {
      // Poner todos los fragmentos de x cada uno en su sitio
      // El primer fragmento lo tengo yo -> copiarlo
      for (i = 0; i < nfilas; i++)
        x[i] = xloc[i];
      // El resto de fragmentos hay que recibirlos de los otros procesos
      for (proc = 1; proc < num_procs; proc++)
        MPI_Recv(&x[proc*nfilas], nfilas, MPI_DOUBLE, proc, 49,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      // Enviar la x ya completa a todos
      for (proc = 1; proc < num_procs; proc++)
        MPI_Send(x, n, MPI_DOUBLE, proc, 53, MPI_COMM_WORLD);
    } else {
      // Enviar mi fragmento de x 
      MPI_Send(xloc, nfilas, MPI_DOUBLE, 0, 49, MPI_COMM_WORLD);
      // Recibir toda la x 
      MPI_Recv(x, n, MPI_DOUBLE, 0, 53, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }*/

    MPI_Gather(xloc, nfilas, MPI_DOUBLE, x, nfilas, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  } // fin del bucle iter 

#define ABS(a) ((a) >= 0 ? (a) : -(a))
  /* Calcular la 1-norma de la parte de x que tiene cada uno */
  norma = 0;
  for (i = 0; i < nfilascalculo; i++)
    norma += ABS(xloc[i]);

  /* COMUNICACIONES */
  /* Calcular la 1-norma de toda la x a partir de la 1-norma de cada fragmento.
   * Esto es calcular la suma de todas dejándola en el proceso 0. */
  /*if (yo == 0) {
    for (proc = 1; proc < num_procs; proc++) {
      MPI_Recv(&aux, 1, MPI_DOUBLE, proc, 65, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      norma += aux;
    }
  } else {
    MPI_Send(&norma, 1, MPI_DOUBLE, 0, 65, MPI_COMM_WORLD);
  }*/
  MPI_Reduce(&norma, &aux, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  norma = aux;

  t = MPI_Wtime() - t;

  if (yo == 0) {
    printf("1-norma (%d iteraciones): %.10g\n", num_iter, norma);
    printf("Tiempo con %d procesos: %.2f\n", num_procs, t);
  }

  free(M);

  MPI_Finalize();

  return 0;
}
