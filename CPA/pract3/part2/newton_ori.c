#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define W 1000
#define H 1000

typedef unsigned char Byte;
typedef struct {
  double a; /* parte real*/
  double b; /* parte imaginaria */
} Complejo;

Complejo multiplica(Complejo x, Complejo y)
{
  Complejo r;

  r.a = x.a*y.a - x.b*y.b;
  r.b = x.a*y.b + x.b*y.a;
  return r;
}

Complejo eleva(Complejo z, unsigned int exponente)
{
  Complejo r = { 1, 0 };
  int i;

  for (i = 0; i < exponente; i++)
    r = multiplica(r, z);
  return r;
}

/* Función: F(z) = z^3 - 1 */
Complejo F1(Complejo z)
{
  Complejo f;

  f = eleva(z, 3);
  f.a -= 1;
  return f;
}
/* Derivada: F'(z) = 3*z^2 */
Complejo D1(Complejo z)
{
  Complejo d;

  d = eleva(z, 2);
  d.a *= 3;
  d.b *= 3;
  return d;
}

/* Función: F(z) = z^4 - 1 */
Complejo F2(Complejo z)
{
  Complejo f;

  f = eleva(z, 4);
  f.a -= 1;
  return f;
}
/* Derivada: F'(z) = 4*z^3 */
Complejo D2(Complejo z)
{
  Complejo d;

  d = eleva(z, 3);
  d.a *= 4;
  d.b *= 4;
  return d;
}

/* Función: F(z) = z^6 + z^3 - 1 */
Complejo F3(Complejo z)
{
  Complejo f, z3, z6;

  z3 = eleva(z, 3);
  z6 = eleva(z, 6);
  f.a = z6.a + z3.a - 1;
  f.b = z6.b + z3.b;
  return f;
}
/* Derivada: F'(z) = 6*z^5 + 3*z^2 */
Complejo D3(Complejo z)
{
  Complejo d, z2, z5;

  z2 = eleva(z, 2);
  z5 = eleva(z, 5);
  d.a = 6*z5.a + 3*z2.a;
  d.b = 6*z5.b + 3*z2.b;
  return d;
}

/* Función: F(z) = z^11 - 1 */
Complejo F4(Complejo z)
{
  Complejo f;

  f = eleva(z, 11);
  f.a -= 1;
  return f;
}
/* Derivada: F'(z) = 11*z^10 */
Complejo D4(Complejo z)
{
  Complejo d;

  d = eleva(z, 10);
  d.a *= 11;
  d.b *= 11;
  return d;
}

Complejo (*fs[])(Complejo) = { F1, F2, F3, F4 };
Complejo (*ds[])(Complejo) = { D1, D2, D3, D4 };
#define CASOS (sizeof(fs)/sizeof(*fs))

void escribe_pgm(char nom[], int ancho, int alto, Byte *imagen, int max, int col)
{
  FILE *F;
  char nombre[100];
  Byte pal[256][3];
  int i, j, c;

  if (strlen(nom) > 80) nom[80] = '\0';
  sprintf(nombre, "%s.p%cm", nom, col?'p':'g');
  F = fopen(nombre, "w");
  if (F == NULL) {
    fprintf(stderr, "ERROR: No se ha podido crear el archivo \"%s\".\n", nombre);
  } else {
    if (max > 255 || col) max = 255;
    fprintf(F, "P%c %d %d %d\n", col?'6':'5', ancho, alto, max);
    if (!col) {
      fwrite(imagen, 1, ancho*alto, F);
    } else { 
      if (col < 0) { /* Se utiliza col como semilla para una paleta aleatoria */
        srand(col);
        for (i = 0; i < 256; i++)
          for (j = 0; j < 3; j++)
            pal[i][j] = rand() & 255;
      } else {
        c = 0; /* Se utiliza col como incremento para crear una paleta */
        for (i = 0; i < 768; i++) {
          ((Byte *)pal)[i] = c;
          c = (c + col) & 255;
        }
      }
      for (i = ancho*alto; i > 0; i--)
        fwrite(pal[*imagen++], 1, 3, F);
    }
    fclose(F);
  }
}

#define ABS(a) ((a) >= 0 ? (a) : -(a))

int caso;
#define F (*fs[caso])
#define D (*ds[caso])

/* Newton: z(i+1) = z(i) - f(z(i))/f'(z(i))     */
/* Devuelve el número de iteraciones realizadas */
int newton(Complejo z0, double tol, int maxiter)
{
  int i;
  Complejo f, d;
  double m;

  for (i = 0; (f = F(z0), ABS(f.a) > tol || ABS(f.b) > tol) && i < maxiter; i++) {
    d = D(z0);
    m = d.a*d.a + d.b * d.b;
    if (m == 0.0) {
      return maxiter;
    } else {
      /* (fa+fb*i)/(da+db*i) * (da-db*i)/(da-db*i) =
          = ( fa*da+fb*db + i*( fb*da - fa*db ) )/m */
      z0.a -= (f.a*d.a + f.b*d.b) / m;
      z0.b -= (f.b*d.a - f.a*d.b) / m;
    }
  }
  return i;
}

#define A(i, j) A[(i)*w + (j)]
int fractal_newton(double x1, double x2, double y1, double y2,
                   int w, int h, Byte *A, double tol, int maxiter,
                   int yo, int np)
{
  int j, ni, max;
  Complejo z0;
  double ix, iy;
  int siguiente_fila, num_fila, filas_hechas, proc;
  Byte B[W]; /* buffer para una fila de la imagen */
  MPI_Status status;

  ix = (x2-x1)/(w-1);
  iy = (y2-y1)/(h-1);
  max = 0;

  if(yo == 0) {

    /* CÓDIGO DEL MAESTRO */

    /* Reparto inicial de faena */
    siguiente_fila = 0;
    for ( proc = 1 ; proc < np ; proc++ ) {
      MPI_Send(&siguiente_fila, 1, MPI_INT, proc, 0, MPI_COMM_WORLD);
      siguiente_fila++;
    }

    /* Mientras queden filas por recibir */
    for ( filas_hechas = 0 ; filas_hechas < h ; filas_hechas++ ) {
      /* Recibimos una fila ya calculada de cualquier proceso */
      MPI_Recv(B, w, MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
               &status);
      /* Sacamos el identificador del proceso y el número de fila */
      proc = status.MPI_SOURCE;
      /*
        Para ahorrarnos un mensaje extra, el trabajador pone el número de fila
        en el TAG del mensaje.
        También podríamos habernos apuntado en el maestro qué fila procesa cada
        trabajador.
      */
      num_fila = status.MPI_TAG;
      /* Le pedimos a ese proceso que procese otra fila */
      MPI_Send(&siguiente_fila, 1, MPI_INT, proc, 0, MPI_COMM_WORLD);
      siguiente_fila++;
      /* Copiamos la fila procesada a su lugar en la imagen */
      memcpy(&A(num_fila, 0), B, w);
    }

  }else{

    /* CÓDIGO DE LOS TRABAJADORES */

    /* Recibe número de fila con la que trabajar, fuera de rango para acabar */
    MPI_Recv(&num_fila, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    while ( num_fila < h ) {
      /* Calcula esa fila */
      z0.b = y1 + iy*num_fila;
      for ( j = 0 ; j < w ; j++ ) {
        z0.a = x1 + ix*j;
        ni = newton(z0, tol, maxiter);
        if ( ni > max ) max = ni;
        B[j] = ni;
      }
      /* Envía fila recién calculada */
      MPI_Send(B, w, MPI_BYTE, 0, num_fila, MPI_COMM_WORLD);
      /* Recibe número de la siguiente fila a procesar */
      MPI_Recv(&num_fila, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

  }

  /* Queda calcular el máximo de todos los máximos */
  ni = max;
  MPI_Reduce(&ni, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
  return max;
}

int main(int argc, char *argv[])
{
  int max, maxiter=50, debug=0, col=0;
  Byte *A;
  double x=0, y=0, rango=1, tol=0.1;
  char *salida = "newton";
  int yo, np, *max_tag, flag;
  double t;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &yo);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  /* Lo que sigue es para sacar el máximo valor permitido como TAG */
  MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_TAG_UB, &max_tag, &flag);

  if (np < 2 || (flag && H - 1 > *max_tag)) {
    if (np < 2) {
      fprintf(stderr,
        "Al menos tiene que haber un trabajador al que mandar. :P\n");
    } else {
      fprintf(stderr,
        "No se puede usar el TAG para indicar el número de fila (no cabe).\n");
    }
    MPI_Finalize();
    return 1;
  }

  while (argc > 1) {
    if (argv[1][0] == '-') {
      switch (argv[1][1]) {
      case 'c':
        caso = atoi(&argv[1][2]) - 1;
        if (caso < 0 || caso > CASOS) {
          caso = 0;
        } else if (caso == 3) {
          maxiter = 200;
        } else if (caso == CASOS) {
          caso = 3;  maxiter = 255;  y = 0.128;  rango = 0.1;
        }
        break;
      case 'i':
        maxiter = atoi(&argv[1][2]);
        /* ¡Ojo! maxiter no debe valer más de 255 */
        if (maxiter > 255) maxiter = 255;
        break;
      case 'r':
        rango = atof(&argv[1][2]);
        if (rango <= 0) rango = 1;
        break;
      case 't':
        tol = atof(&argv[1][2]);
        break;
      case 'd':
        debug = 1;
        break;
      case 'o':
        salida = &argv[1][2];
        break;
      case 'x':
        x = atof(&argv[1][2]);
        break;
      case 'y':
        y = atof(&argv[1][2]);
        break;
      case 'p':
        col = atoi(&argv[1][2]);
        break;
      case 'h':
      default:
        fprintf(stderr, "Uso: newton -cCASO -iMAXITER -rRANGO -tTOL"
                " -oSALIDA -xX -yY -pPALETA -d -h\n");
        return 1;
      }
    }
    argc--; argv++;
  }

  /*
   Pedimos memoria.
   El maestro (yo=0) tiene que almacenar toda la imagen.
   (Asumimos que malloc no falla, al ser poca memoria).
  */
  if (yo == 0) {
    A = malloc(W*H*sizeof(Byte));
  }

  t = MPI_Wtime();
  max = fractal_newton(x-rango, x+rango, y+rango, y-rango,
                       W, H, A, tol, maxiter, yo, np);
  t = MPI_Wtime() - t;
  if (yo == 0) {
    printf("Tiempo: %.2f (%d procesos)\n", t, np);

    if (debug) {
      fprintf(stderr, "(max: %d)\n",max);
    }

    escribe_pgm(salida, W, H, A, max, col);

    /* Liberamos memoria */
    free(A);
  }

  MPI_Finalize();
  return 0;
}
