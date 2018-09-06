/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: main.c
 *  
 * Description: 
 *    Módulo principal del simulador
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *************************************************************************/

#define main_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/*** Definiciones Externas *************************************************/

#include "tipos.h"
#include "prediccion.h"
#include "presentacion.h"
#include "instrucciones.h"
#include "algoritmo.h"

extern void ensamblador (FILE*);

/*** Variables Globales ****************************************************/

extern int pos_datos;

/*** Variables Locales *****************************************************/

static boolean          f_depuracion;

/*** Funciones Locales *****************************************************/

/***************************************************************
 *
 * Func: inicializa_estructuras
 *
 * Desc: Inicializa las estructuras de la unidad de gestión de
 * instrucciones
 *
 **************************************************************/

static void inicializa_estructuras 
(  
 )
{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int		i;

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/

  /* Estadisticas */

  estat.ciclos= 0;
  estat.instrucciones= 0;
  estat.flops= 0;
  estat.saltos_accedidos= 0;
  estat.saltos_encontrados= 0;
  estat.saltos_ejecutados= 0;
  estat.saltos_acertados= 0;

  /* Registros inter-etapas */

  IF_ISS_1.IR.codop= OP_NOP;
  IF_ISS_1.PC= -1;
  IF_ISS_1.orden= 0;
  IF_ISS_1.excepcion= EXC_NONE;

  IF_ISS_2= IF_ISS_1;

  Control_1.Parar= NO;
  Control_1.Cancelar= NO;
  Control_1.NPC= 0;
  
  Control_2= Control_1;

  /* Registros */

  for (i=0; i<TAM_REGISTROS; i++)
    {
      Rfp[i].valor= 0.0;
      Rfp[i].rob= MARCA_NULA;
      Rint[i].valor= 0;
      Rint[i].rob= MARCA_NULA;
    } /* endfor */

  Rint[REG_FPSR].rob= MARCA_NULA; /* FPSR */
  Rint[REG_FPSR].valor= 0;    /* FPSR */

  /* Memoria de datos */

  for (i=0; i< TAM_MEMO_DATOS; i+= sizeof(dword))
    {
      MD.m_dword[dir_dword(i)]= 0;
    } /* endfor */

  for (i=0; i< TAM_MEMO_DATOS; i++) {
      md_tipo[i]= t_ninguno;
  } /* endfor */

  /* Memoria de instrucciones */

  for (i=0; i<TAM_MEMO_INSTRUC; i++)
    {
      MI[i].codop= OP_NOP;
      MI[i].tipo= FormatoI;
      MI[i].Rdestino= 0;
      MI[i].Rfuente1= 0;
      MI[i].Rfuente2= 0;
      MI[i].inmediato= 0;
    } /* endfor */

  /* Predictor */

  inicializa_prediccion_sol();

  /* Estaciones de reserva */

  for (i=1; i<TAM_ESTACIONES; i++)
    {
      RS[i].OP= OP_NOP;
      RS[i].ocupado= NO;
      RS[i].Qj= MARCA_NULA;
      RS[i].Vj.i= 0;
      RS[i].Qk= MARCA_NULA;
      RS[i].Vk.i= 0;
      RS[i].direccion= 0;
      RS[i].confirm= NO;
      RS[i].rob= MARCA_NULA;
      RS[i].orden= 0;
    } /* endfor */

  /* Reorder Buffer */

  RB_inicio= 0;
  RB_fin= 0;
  RB_long= 0;

  for (i=1; i<TAM_REORDER; i++)
    {
      RB[i].OP= OP_NOP;
      RB[i].ocupado= NO;
      RB[i].estado= NONE;
      RB[i].dest= MARCA_NULA;
      RB[i].valor.i= 0;
      RB[i].orden= 0;
    } /* endfor */

  /* Operadores */
  
  Enteros.ocupado= NO;
  Enteros.codigo= 0;
  Enteros.ciclo= 0;
  Enteros.Teval= TEVAL_ENTEROS;

  RegEnteros.ocupado= NO;
  RegEnteros.codigo= 0;
  RegEnteros.valor.i= 0;

  SumRest.ocupado= NO;
  SumRest.codigo= 0;
  SumRest.ciclo= 0;
  SumRest.Teval= TEVAL_SUMREST;

  RegSumRest.ocupado= NO;
  RegSumRest.codigo= 0;
  RegSumRest.valor.f= 0.0;

  MultDiv.ocupado= NO;
  MultDiv.codigo= 0;
  MultDiv.ciclo= 0;
  MultDiv.Teval= TEVAL_MULTDIV;

  RegMultDiv.ocupado= NO;
  RegMultDiv.codigo= 0;
  RegMultDiv.valor.f= 0.0;

  MemDatos.ocupado= NO;
  MemDatos.codigo= 0;
  MemDatos.ciclo= 0;
  MemDatos.Teval= TEVAL_MEMORIA;

  RegMemDatos.ocupado= NO;
  RegMemDatos.codigo= 0;
  RegMemDatos.valor.i= 0;

  /* Bus común */

  BUS.ocupado= NO;
  BUS.codigo= MARCA_NULA;
  BUS.valor.i= 0;
  
} /* end inicializa_estructuras */

/***************************************************************
 *
 * Func: mira_si_todo_vacio
 *
 * Retorna:  (boolean) 
 *
 * Desc: Mira si queda alguna operación por acabar
 *
 **************************************************************/

static boolean mira_si_todo_vacio (  
   )

{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int		i;

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/

  for (i=INICIO_TAMPON_ESCR; i<=FIN_TAMPON_ESCR; i++)
    {
      if (TE[i].ocupado)
	return (NO);
    } /* endfor */

  return (SI);

} /* end mira_si_todo_vacio */

/***************************************************************
 *
 * Func: ejecutar_codigo
 *
 *
 * Retorna:  RC  (int) 
 *
 * Descripción: 
 *   Ejecuta el bucle principal del computador
 *
 **************************************************************/

static void ejecutar_codigo 
(  
 )
{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  boolean final;

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/

  /*** Inicializacion del computador */

  Ciclo= 0;
  terminando= NO;
  final= NO;

  imprime_inicio();

  /*** Bucle principal */

  while (!final)
    {
      Control_1.Parar= NO;
      Control_1.Cancelar= NO;

      Ciclo++;			/* Incrementa el número de ciclos
				   ejecutados */

      /*** Fase: EX (1) **********/

      fase_EX_1 ();

      /*** Fase: COMMIT ***********/

      fase_COM_sol ();

      /*** Fase: WB **************/

      fase_WB ();

      /*** Fase: ISSUE ***********/

      fase_ISS_sol ();

      /*** Fase: EX (2) **********/

      fase_EX_2 ();

      /*** Fase: IF **************/

      fase_IF ();

      /*** Estadisticas ***/
      
      estat.ciclos++;

      /*** Control del simulador ****************/

      if (terminando)
        {
          if (mira_si_todo_vacio())
            final= SI;		/* Termina */
          else
            Control_1.Parar= SI;	/* Bloquea la búsqueda */
        } /* endif */

      if (!Control_1.Parar && !Control_1.Cancelar)
	{			/* Ejecución normal */
	  IF_ISS_2= IF_ISS_1;
	  Control_2= Control_1;
	}
      else if (Control_1.Parar)
	{			/* Búsqueda parada */
	  Control_2.Parar= SI;
	}
      else			/* Búsqueda cancelada */
	{
	  Control_2= Control_1;
	  IF_ISS_2.orden= IF_ISS_1.orden; 
	  IF_ISS_2.PC= IF_ISS_1.PC; 
	} /* endif */

      /*** Imprime el estado del los operadores, etc.  */

      if (f_depuracion) {
          imprime_crono ();
          imprime_estado ();
          imprime_predictor ();
      } /* endif */

    } /* endwhile */
    
    imprime_final();

} /* end ejecutar_codigo */

/***************************************************************
 *
 * Func: error_fatal
 *
 * Descripción: 
 *   Muestra el mensaje y sale
 *
 **************************************************************/

static void error_fatal 
(  
 char * msg_format,
 char * msg_value
 )
{
  fprintf(stderr, msg_format, msg_value);
  exit(1);
} /* end error_fatal */

/*** Funciones Exportables *************************************************/

/***************************************************************
 *
 * Func: main
 *
 * Parametros:
 *	argc  (int) ; Número de parametros en linea
 *	argv[]  (char*) ; Texto de los parametros en linea
 *
 * Retorna:  RC  (int) 
 *
 * Descripción: 
 *   Función principal
 *
 **************************************************************/

int main 
(  
 int	argc,
 char*	argv[]
 )
{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int		RC= 0;	/* Valor de retorno */

  int           argn;
  char *	uso= 
    "\n%s [-{t|g} <fichero.sign>] [-s] -f <fichero.s>\n"    
    "\t-t	Comprueba que la ejecución corresponde con la que hay en el fichero de firmas.\n"
    "\t-g	Genera un fichero de firmas correspondiente a la ejecución actual.\n"
    "\t   <fichero.sign>\n"	
    "\t         Nombre del fichero de firmas\n"
    "\t-s       Ejecuta sin imprimir los ficheros de estado y los cronogramas.\n"
    "\t         Se deshabilita la comprobación de firmas.\n"
    "\t-f <fichero.s>\n"
    "\t         Nombre del fichero en ensamblador\n"
    "";

  FILE*		f_entrada= NULL;
  boolean       f_firmas= NO;

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/

  /*** Lectura de parametros */

  f_depuracion= SI;

  argn= 1;
  if (argc < 3)
    {
      fprintf(stderr, uso, argv[0]);
      exit(1);
    } /* endif */

  while (argn < argc)
    {
      if (!strncmp(argv[argn],"-f", 2))
        {
          argn++;
          strcpy(nombre_fich, argv[argn]);
          f_entrada= fopen(nombre_fich, "r");
          if (f_entrada == NULL)
            {
              fprintf(stderr, "%s: Error abriendo fichero '%s'.", 
                      argv[0], nombre_fich);
              error_fatal(uso, argv[0]);
            } /* endif */
        }
      else if (!strncmp(argv[argn],"-t", 2)) 
        {
          argn++;
          if (argn == argc)
            error_fatal(uso, argv[0]);
          abre_firma(argv[argn]);
          f_firmas= SI;
        }
      else if (!strncmp(argv[argn],"-g", 2)) 
        {
          argn++;
          if (argn == argc)
            error_fatal(uso, argv[0]);
          crea_firma(argv[argn]);
          f_firmas= SI;
        }
      else if (!strncmp(argv[argn],"-s", 2)) 
        {
          f_depuracion= NO;
        }
      else
        {
          error_fatal(uso, argv[0]);
        } /* endif */

      argn ++;
    } /* endwhile */

  if (f_entrada == NULL)
    {
      fprintf(stderr, "%s: Falta el fichero de entrada.", argv[0]);
      error_fatal(uso, argv[0]);
    } /* endif */

  /*** Inicializacion de estructuras */

  inicializa_estructuras ();

  /*** Carga el codigo en lenguaje ensamblador */

  ensamblador (f_entrada);

  /*** Llama al bucle principal */

  ejecutar_codigo ();

  if (f_firmas)
    cierra_firma();

  /*** Imprime estadisticas */

  imprime_estadisticas();

  return RC;

} /* end main */

