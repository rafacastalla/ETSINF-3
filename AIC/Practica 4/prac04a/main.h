/*********************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: main.h
 * 
 * Description: Contiene las definiciones de constantes y de variables
 *    globales a todo el simulador
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *********************************************************************/

#ifndef main_H
#define main_H

/*** Includes ********************************************************/

#include "tipos.h"

/*** Defines *********************************************************/

/*** Tamaño de las estructuras de datos */

#define MAX_VIAS_SUPERESCALAR   16

#define _NUM_VIAS_ISSUE  1 /* Valor por omisión */
#define _NUM_VIAS_BUS  1 /* Valor por omisión */
#define _NUM_VIAS_COMMIT 1 /* Valor por omisión */

#define MAX_BUFFER_PREDIC       16
#define _TAM_BUFFER_PREDIC      2

#define _TAM_RS_ENTEROS  5
#define _TAM_RS_SUMA_RESTA 3
#define _TAM_RS_MULT_DIV 2
#define _TAM_TAMPON_LECT 3 /* 1 */
#define _TAM_TAMPON_ESCR 3 /* 1 */

#define _TAM_ESTACIONES (_TAM_RS_ENTEROS + \
                        _TAM_RS_SUMA_RESTA + \
                        _TAM_RS_MULT_DIV + \
                        _TAM_TAMPON_LECT + \
                        _TAM_TAMPON_ESCR)

#define MAX_ESTACIONES  64

#define _TAM_REGISTROS  8

#define MAX_REORDER    128
#define _TAM_REORDER    20 /* Valor por omisión */

#define MAX_OPERADORES  100 /* Número de operadores * latencia máxima */

#define _NUM_OPER_ENTEROS 1
#define _NUM_OPER_SUMREST 1
#define _NUM_OPER_MULTDIV 1
#define _NUM_OPER_DIRECCIONES 1
#define _NUM_OPER_MEMDATOS 1

#define _NUM_INICIO_ENTEROS _NUM_OPER_ENTEROS
#define _NUM_INICIO_SUMREST _NUM_OPER_SUMREST
#define _NUM_INICIO_MULTDIV _NUM_OPER_MULTDIV
#define _NUM_INICIO_DIRECCIONES _NUM_OPER_DIRECCIONES
#define _NUM_INICIO_MEMDATOS _NUM_OPER_MEMDATOS

/*** Tiempos de evaluacion */

#define _TEVAL_ENTEROS  1
#define _TEVAL_MEMDATOS  2 /* + 1 ciclo del cálculo de la dirección efectiva */
#define _TEVAL_SUMREST  4
#define _TEVAL_MULTDIV  7
#define _TEVAL_DIRECCIONES 1


#define CHECK_DEFAULT_VALUE(v) \
do { \
   if ((v) == 0) { \
      (v) = _##v; \
   } \
} while (0)

// Lo siguiente es necesario para que los ficheros .o que no se compilan
// vean los cambios planificados en la practica y para la modificación línea de ordenes


#ifdef main_C

int NUM_VIAS_ISSUE = _NUM_VIAS_ISSUE;
int NUM_VIAS_BUS = _NUM_VIAS_BUS;
int NUM_VIAS_COMMIT = _NUM_VIAS_COMMIT;

int TAM_REORDER = _TAM_REORDER;
int TAM_BUFFER_PREDIC = _TAM_BUFFER_PREDIC;

int TAM_RS_ENTEROS = _TAM_RS_ENTEROS;
int TAM_RS_SUMA_RESTA = _TAM_RS_SUMA_RESTA;
int TAM_RS_MULT_DIV = _TAM_RS_MULT_DIV;
int TAM_TAMPON_LECT = _TAM_TAMPON_LECT;
int TAM_TAMPON_ESCR = _TAM_TAMPON_ESCR;
int TAM_ESTACIONES = _TAM_ESTACIONES;

const int TAM_REGISTROS = _TAM_REGISTROS;

int NUM_OPER_ENTEROS = _NUM_OPER_ENTEROS;
int NUM_OPER_SUMREST = _NUM_OPER_SUMREST;
int NUM_OPER_MULTDIV = _NUM_OPER_MULTDIV;
int NUM_OPER_DIRECCIONES = _NUM_OPER_DIRECCIONES;
int NUM_OPER_MEMDATOS = _NUM_OPER_MEMDATOS;

int NUM_INICIO_ENTEROS = _NUM_OPER_ENTEROS;
int NUM_INICIO_SUMREST = _NUM_OPER_SUMREST;
int NUM_INICIO_MULTDIV = _NUM_OPER_MULTDIV;
int NUM_INICIO_DIRECCIONES = _NUM_OPER_DIRECCIONES;
int NUM_INICIO_MEMDATOS = _NUM_OPER_MEMDATOS;

int NUM_OPERADORES = 0;

int TEVAL_ENTEROS = _TEVAL_ENTEROS;
int TEVAL_SUMREST = _TEVAL_SUMREST;
int TEVAL_MULTDIV = _TEVAL_MULTDIV;
int TEVAL_DIRECCIONES = _TEVAL_DIRECCIONES;
int TEVAL_MEMDATOS = _TEVAL_MEMDATOS;

#else

extern int NUM_VIAS_ISSUE;
extern int NUM_VIAS_BUS;
extern int NUM_VIAS_COMMIT;

extern int TAM_REORDER;
extern int TAM_BUFFER_PREDIC;

extern int TAM_RS_ENTEROS;
extern int TAM_RS_SUMA_RESTA;
extern int TAM_RS_MULT_DIV;
extern int TAM_TAMPON_LECT;
extern int TAM_TAMPON_ESCR;
extern int TAM_ESTACIONES;
extern int TAM_REGISTROS;

extern int NUM_OPER_ENTEROS;
extern int NUM_OPER_SUMREST;
extern int NUM_OPER_MULTDIV;
extern int NUM_OPER_DIRECCIONES;
extern int NUM_OPER_MEMDATOS;

extern int NUM_INICIO_ENTEROS;
extern int NUM_INICIO_SUMREST;
extern int NUM_INICIO_MULTDIV;
extern int NUM_INICIO_DIRECCIONES;
extern int NUM_INICIO_MEMDATOS;

extern int NUM_OPERADORES;

extern int TEVAL_ENTEROS;
extern int TEVAL_SUMREST;
extern int TEVAL_MULTDIV;
extern int TEVAL_DIRECCIONES;
extern int TEVAL_MEMDATOS;

#endif

/*** Contantes */

#define MARCA_NULA    (MAX_REORDER)
#define MAX_ORDEN     10000

/*** Excepciones */

#define EXC_NONE                0

#define EXC_OUT_MEM_INST        1
#define EXC_OUT_MEM_DAT         2
#define EXC_UNALIGN_MEM_INST    3
#define EXC_UNALIGN_MEM_DAT     4

#define EXC_USER                32
#define EXC_TRAP(t)  (EXC_USER+(t))


/*** Inicios y finales de las estaciones de reserva */

#define INICIO_RS_ENTEROS (0)
#define FIN_RS_ENTEROS  (INICIO_RS_ENTEROS + TAM_RS_ENTEROS -1)

#define INICIO_RS_SUMA_RESTA (FIN_RS_ENTEROS + 1)
#define FIN_RS_SUMA_RESTA (INICIO_RS_SUMA_RESTA + TAM_RS_SUMA_RESTA -1)

#define INICIO_RS_MULT_DIV (FIN_RS_SUMA_RESTA + 1)
#define FIN_RS_MULT_DIV  (INICIO_RS_MULT_DIV + TAM_RS_MULT_DIV -1)

#define INICIO_TAMPON_LECT (FIN_RS_MULT_DIV + 1)
#define FIN_TAMPON_LECT  (INICIO_TAMPON_LECT + TAM_TAMPON_LECT -1)

#define INICIO_TAMPON_ESCR (FIN_TAMPON_LECT + 1)
#define FIN_TAMPON_ESCR  (INICIO_TAMPON_ESCR + TAM_TAMPON_ESCR -1)

#define INICIO_TAMPONES         INICIO_TAMPON_LECT
#define FIN_TAMPONES            FIN_TAMPON_ESCR

#define PRIMERA_ESTACION_RESERVA (INICIO_RS_ENTEROS)
#define ULTIMA_ESTACION_RESERVA  (FIN_TAMPON_ESCR)

#define ES_ESTACION(s, tipo)  ((s) >= INICIO_##tipo && (s) <= FIN_##tipo)

/*** IDENTIFICADORES */

#define REG_FPSR        TAM_REGISTROS

/*** Inclusion condicional *************************************************/

/***************************************************************************/
/***************************************************************************/

#ifdef main_C   /* Privado para el fichero main.c */

/*** Opciones de Ejecución */

boolean f_etiquetas = NO;

/*** Variables internas  */

ciclo_t Ciclo;
boolean terminando;
char nombre_fich[128];
dword PC_ISS = -1;
int RB_cab = -1;
estadisticas_t estat;

dep_mem_t dep_mem = l_bypassing;

/*** Estructuras visibles al programador */

segmento_t SegDatos;
memoria_datos_t MD;
segmento_t SegInstruc;
memoria_intrucciones_t MI;

tipo_t md_tipo[TAM_MEMO_DATOS]; /* Tipos de la memoria de datos */

//reg_fp_t Rfp[_TAM_REGISTROS];
reg_t Rfp[_TAM_REGISTROS];
//reg_int_t Rint[_TAM_REGISTROS + 1]; /* El último simula el 'fpsr' */
reg_t Rint[_TAM_REGISTROS + 1]; /* El último simula el 'fpsr' */

/*** Registros inter-etapa para la segmentación */

/* Representan a los registros inter-etapa que contienen los valores
   para el siguiente ciclo, los valores futuros */
/* DEBEN ESTAR SIEMPRE A LA IZQUIERDA DE UNA ASIGNACION */

reg_if_iss_t M_IF_ISS_1[MAX_VIAS_SUPERESCALAR];

reg_if_iss_t IF_ISS_1;
reg_control_t Control_1;

/* Representan a los registros inter-etapa que contienen los valores
   del presente ciclo. Serán estables hasta que se vuelvan escribir al
   final del ciclo con los nuevos valores */
/* DEBEN ESTAR SIEMPRE A LA DERECHA DE UNA ASIGNACION O EN LAS
   COMPARACIONES */

reg_if_iss_t M_IF_ISS_2[MAX_VIAS_SUPERESCALAR];

reg_if_iss_t IF_ISS_2;
reg_control_t Control_2;

/*** Estructuras internas de la ruta de datos de coma flotante */

/* Todas las estaciones están en el mismo array, pero se puede usar
   RS, TL o TE */
estacion_t RS[MAX_ESTACIONES];
#define TL RS
#define TE RS

int RB_inicio, RB_fin, RB_long;
reorder_t RB[MAX_REORDER];

bus_comun_t BUS;

operador_t Op[MAX_OPERADORES];

/*** Estructuras para el predictor */

entrada_btb_t BTB[MAX_BUFFER_PREDIC];

#endif

/***************************************************************************/
/***************************************************************************/

#ifndef main_C  /* Publico (excepto main.c) */

/*** Opciones de Ejecución */

extern boolean f_etiquetas;

/*** Variables internas  */

extern ciclo_t Ciclo;
extern boolean terminando;
extern char nombre_fich[128];
extern dword PC_ISS;
extern int RB_cab;
extern estadisticas_t estat;

extern dep_mem_t dep_mem;

/*** Estructuras visibles al programador */
extern segmento_t SegDatos;
extern memoria_datos_t MD;
extern segmento_t SegInstruc;
extern memoria_intrucciones_t MI;

extern tipo_t md_tipo[TAM_MEMO_DATOS]; /* Tipos de la memoria de datos */

//extern reg_fp_t Rfp[_TAM_REGISTROS];
extern reg_t Rfp[_TAM_REGISTROS];
//extern reg_int_t Rint[_TAM_REGISTROS + 1]; /* El último simula el 'fpsr' */
extern reg_t Rint[_TAM_REGISTROS + 1]; /* El último simula el 'fpsr' */

/*** Registros inter-etapa para la segmentación */

/* Representan a los registros inter-etapa que contienen los valores
   para el siguiente ciclo, los valores futuros */
/* DEBEN ESTAR SIEMPRE A LA IZQUIERDA DE UNA ASIGNACION */
extern reg_if_iss_t IF_ISS_1;
extern reg_control_t Control_1;

/* Representan a los registros inter-etapa que contienen los valores
   del presente ciclo. Serán estables hasta que se vuelvan escribir al
   final del ciclo con los nuevos valores */
/* DEBEN ESTAR SIEMPRE A LA DERECHA DE UNA ASIGNACION O EN LAS
   COMPARACIONES */
extern reg_if_iss_t IF_ISS_2;
extern reg_control_t Control_2;

/*** Estructuras internas de la ruta de datos de coma flotante */

/* Todas las estaciones están en el mismo array, pero se puede usar
   RS, TL o TE */
extern estacion_t RS[MAX_ESTACIONES];
#define TL RS   
#define TE RS

extern int RB_inicio, RB_fin, RB_long;
extern reorder_t RB[MAX_REORDER];

extern bus_comun_t BUS;

extern operador_t Op[MAX_OPERADORES];

/*** Estructuras para el predictor */

extern entrada_btb_t BTB[MAX_BUFFER_PREDIC];

#endif

#endif /* Include main.h */


