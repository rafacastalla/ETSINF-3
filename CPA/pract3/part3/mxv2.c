#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10000
#define NITER 50

/* Valor double aleatorio entre 0 y 1 */
#define D01  (rand() / (double)RAND_MAX)

/* NOTA: Se trabaja con matrices almacenadas por columnas */
#define M(i,j) M[(i) + (j)*n]
#define Mloc(i,j) Mloc[(i) + (j)*n]

void inventa(int m, int n, double *A)
{
  for (m *= n; m > 0; m--)
    *A++ = D01;
}
/* Se asume que todos los elementos son no negativos,
 * lo que es cierto si se ha generado con la función inventa */
double uno_norma(int m, int n, double *A)
{
  double max, aux;
  int i;

  max = 0;
  for (; n > 0; n--) {
    aux = 0;
    for (i = 0; i < m; i++)
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
      ncolus, ncoluscalculo, tama;
  char opcion;
  double t;
  int yo, num_procs, proc;
  double *M, *Mloc, *x, *xloc1, *xloc2, *v, norma, aux;
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
      fprintf(stderr, "Uso: mxv2 [-s semilla] [-n tamanyo] [-i iteraciones]\n");
      return 1;
    }
  }

  /* Calculamos n2, un tamaño múltiplo de num_procs en el que quepa n */
  ncolus = n / num_procs;
  if (num_procs * ncolus < n) ncolus++;
  n2 = num_procs * ncolus;

  /* Todos los procesos almacenarán unas columnas de M (Mloc), las mismas filas
   * de x de la iteración anterior (xloc1) y toda x recién calculada (xloc2)
   * (cada uno tiene una parte de la x, la global se obtiene sumando todas) */
  if (yo == 0)   /* El proceso 0 almacenará toda la M, toda la x y toda la v */
    tama = n * n2 + n2 + n;
  else
    tama = 0;
  tama += n * ncolus + ncolus + n; /* Mloc, xloc1, xloc2 */

  M = malloc(tama*sizeof(double));
  if (M == NULL) {
    fprintf(stderr, "ERROR: Falta memoria\n");
    return 1;
  }

  tama = n * ncolus;
  if (yo == 0) {
    x = M + n * n2;
    v = x + n2;
    Mloc = v + n;
  } else {
    Mloc = M;
  }
  xloc1 = Mloc + tama;
  xloc2 = xloc1 + ncolus;

  if (yo == 0) {
    srand(semilla);
    inventa(n, n, M);
    inventa(n, 1, v);
    inventa(n, 1, x);
    /* Ya que es inventado, hacer que el sistema sea convergente
     * (la norma de la matriz de iteración M debe ser menor que 1) */
    escala(n, n, M, 0.9 / uno_norma(n, n, M));
  }

  t = MPI_Wtime();

  /* COMUNICACIONES */
  /* Repartir la M por columnas y la x por filas (ncolus a cada proceso) */
  /*if (yo == 0) {
    // Para el 0, no enviamos sino que copiamos 
    for (j = 0; j < ncolus; j++) {
      for (i = 0; i < n; i++)
        Mloc(i, j) = M(i, j);
      xloc1[j] = x[j];
    }
    // Para el resto, enviamos
    for (proc = 1; proc < num_procs; proc++) {
      MPI_Send(&M[proc*tama], tama, MPI_DOUBLE, proc, 13, MPI_COMM_WORLD);
      MPI_Send(&x[proc*ncolus], ncolus, MPI_DOUBLE, proc, 25, MPI_COMM_WORLD);
    }
  } else {
    MPI_Recv(Mloc, tama, MPI_DOUBLE, 0, 13, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(xloc1, ncolus, MPI_DOUBLE, 0, 25, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }*/

  MPI_Scatter(M, tama, MPI_DOUBLE, Mloc, tama, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Scatter(x, ncolus, MPI_DOUBLE, xloc1, ncolus, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  

  ncoluscalculo = n - yo * ncolus;
  if (ncoluscalculo > ncolus)
    ncoluscalculo = ncolus;

  for (iter = 1; iter <= num_iter; iter++) {
    /* Calcular Mloc*xloc1 en xloc2 */
    for (i = 0; i < n; i++) {
      aux = 0;
      for (j = 0; j < ncoluscalculo; j++)
        aux += Mloc(i, j) * xloc1[j];
      xloc2[i] = aux;
    }

    /* COMUNICACIONES */
    /* Terminar el cálculo de la x: calcular la suma de todas las xloc2
     * y añadirle la v, dejando el resultado en el procesador 0.
     * Y luego repartirlo entre los procesadores, para la siguiente iteración */
    /*if (yo == 0) {
      // La xloc2 que tiene el 0 no hay que recibirla sino operar con ella 
      for (i = 0; i < n; i++)
        x[i] = xloc2[i] + v[i];
      // El resto de xloc2 hay que recibirla de los otros procesos
      // e ir añadiéndola a la x. Reusamos xloc2 como buffer de recepción 
      for (proc = 1; proc < num_procs; proc++) {
        MPI_Recv(xloc2, n, MPI_DOUBLE, proc, 49, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < n; i++)
          x[i] += xloc2[i];
      }
      // Para el 0, no enviamos sino que copiamos 
      for (j = 0; j < ncolus; j++)
        xloc1[j] = x[j];
      // Para el resto, enviamos
      for (proc = 1; proc < num_procs; proc++)
        MPI_Send(&x[proc*ncolus], ncolus, MPI_DOUBLE, proc, 53, MPI_COMM_WORLD);

    } else {
      // Enviar xloc2, recibir xloc1
      MPI_Send(xloc2, n, MPI_DOUBLE, 0, 49, MPI_COMM_WORLD);
      MPI_Recv(xloc1, ncolus, MPI_DOUBLE, 0, 53, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }*/

    MPI_Reduce(xloc2, x, n, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(yo == 0) {
      for (i = 0; i < n; i++) x[i] += v[i];
    }

    MPI_Scatter(x, ncolus, MPI_DOUBLE, xloc1, ncolus, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  } /* fin del bucle iter */

#define ABS(a) ((a) >= 0 ? (a) : -(a))
  /* Calcular la 1-norma de la parte de x que tiene cada uno (xloc1) */
  norma = 0;
  for (i = 0; i < ncoluscalculo; i++)
    norma += ABS(xloc1[i]);

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
