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

#define TAM_BUFFER_PREDIC       2

#define _TAM_RS_ENTEROS		5
#define _TAM_RS_SUMA_RESTA	3
#define _TAM_RS_MULT_DIV	2

#define _TAM_TAMPON_LECT	3
#define _TAM_TAMPON_ESCR	3

// #define _TAM_RS_ENTEROS	5
// #define _TAM_RS_SUMA_RESTA	3
// #define _TAM_RS_MULT_DIV	3
//
// #define _TAM_TAMPON_LECT	2
// #define _TAM_TAMPON_ESCR	2

#define _TAM_ESTACIONES (_TAM_RS_ENTEROS + \
			_TAM_RS_SUMA_RESTA + \
			_TAM_RS_MULT_DIV + \
			_TAM_TAMPON_LECT + \
			_TAM_TAMPON_ESCR)

// Lo siguiente es necesario para que los ficheros .o que no se compilan
// vean los cambios planificados en la practica
#ifdef main_C
const int TAM_RS_ENTEROS=_TAM_RS_ENTEROS;
const int TAM_RS_SUMA_RESTA=_TAM_RS_SUMA_RESTA;
const int TAM_RS_MULT_DIV=_TAM_RS_MULT_DIV;
const int TAM_TAMPON_LECT=_TAM_TAMPON_LECT;
const int TAM_TAMPON_ESCR=_TAM_TAMPON_ESCR;
const int TAM_ESTACIONES=_TAM_ESTACIONES;
#else
extern int TAM_RS_ENTEROS;
extern int TAM_RS_SUMA_RESTA;
extern int TAM_RS_MULT_DIV;
extern int TAM_TAMPON_LECT;
extern int TAM_TAMPON_ESCR;
extern int TAM_ESTACIONES;
#endif

#define TAM_REGISTROS		8
#define TAM_REORDER		20

/*** Contante */

#define MARCA_NULA		(TAM_REORDER) 

/*** Excepciones */

#define EXC_NONE	        0

#define EXC_OUT_MEM_INST	1
#define EXC_OUT_MEM_DAT		2
#define EXC_UNALIGN_MEM_DAT     3

#define EXC_TRAP(t)		(32+(t))


/*** Inicios y finales de las estaciones de reserva */

#define INICIO_RS_ENTEROS	(0)
#define FIN_RS_ENTEROS		(INICIO_RS_ENTEROS + TAM_RS_ENTEROS -1)

#define INICIO_RS_SUMA_RESTA	(FIN_RS_ENTEROS + 1)
#define FIN_RS_SUMA_RESTA	(INICIO_RS_SUMA_RESTA + TAM_RS_SUMA_RESTA -1)

#define INICIO_RS_MULT_DIV	(FIN_RS_SUMA_RESTA + 1)
#define FIN_RS_MULT_DIV		(INICIO_RS_MULT_DIV + TAM_RS_MULT_DIV -1)

#define INICIO_TAMPON_LECT	(FIN_RS_MULT_DIV + 1)
#define FIN_TAMPON_LECT		(INICIO_TAMPON_LECT + TAM_TAMPON_LECT -1)

#define INICIO_TAMPON_ESCR	(FIN_TAMPON_LECT + 1)
#define FIN_TAMPON_ESCR		(INICIO_TAMPON_ESCR + TAM_TAMPON_ESCR -1)

#define PRIMERA_ESTACION_RESERVA	(INICIO_RS_ENTEROS)
#define ULTIMA_ESTACION_RESERVA		(FIN_TAMPON_ESCR)

/*** Tiempos de evaluacion */

#define TEVAL_ENTEROS		1
#define TEVAL_MEMORIA		3
#define TEVAL_SUMREST		4
#define TEVAL_MULTDIV		7

/*** IDENTIFICADORES */

#define REG_FPSR        TAM_REGISTROS

#define OPER_ENTEROS		0
#define OPER_SUMREST		1
#define OPER_MULTDIV		2
#define OPER_MEMDATOS		3

#define OPERADORES		4

#define SumRest Op[OPER_SUMREST]
#define RegSumRest RegOp[OPER_SUMREST]

#define MultDiv Op[OPER_MULTDIV]
#define RegMultDiv RegOp[OPER_MULTDIV]

#define Enteros Op[OPER_ENTEROS]
#define RegEnteros RegOp[OPER_ENTEROS]

#define MemDatos Op[OPER_MEMDATOS]
#define RegMemDatos RegOp[OPER_MEMDATOS]

/*** Inclusion condicional *************************************************/

/***************************************************************************/
/***************************************************************************/

#ifdef main_C   /* Privado para el fichero main.c */

ciclo_t			Ciclo;
boolean			terminando;
char			nombre_fich[128];
dword			PC_ISS= -1;
int			RB_cab= -1;
estadisticas_t          estat;

/*** Estructuras visibles al programador */

segmento_t		SegDatos;
memoria_datos_t		MD;
segmento_t		SegInstruc;
memoria_intrucciones_t	MI;

tipo_t                  md_tipo[TAM_MEMO_DATOS]; /* Tipos de la memoria de datos */

reg_fp_t                Rfp[TAM_REGISTROS];
reg_int_t               Rint[TAM_REGISTROS+1]; /* El último simula el 'fpsr' */

/*** Registros inter-etapa para la segmentación */

/* Representan a los registros inter-etapa que contienen los valores
   para el siguiente ciclo, los valores futuros */
/* DEBEN ESTAR SIEMPRE A LA IZQUIERDA DE UNA ASIGNACION */
reg_if_iss_t		IF_ISS_1;
reg_control_t		Control_1;

/* Representan a los registros inter-etapa que contienen los valores
   del presente ciclo. Serán estables hasta que se vuelvan escribir al
   final del ciclo con los nuevos valores */
/* DEBEN ESTAR SIEMPRE A LA DERECHA DE UNA ASIGNACION O EN LAS
   COMPARACIONES */
reg_if_iss_t		IF_ISS_2;
reg_control_t		Control_2;

/*** Estructuras internas de la ruta de datos de coma flotante */

/* Todas las estaciones están en el mismo array, pero se puede usar
   RS, TL o TE */
estacion_t		RS[_TAM_ESTACIONES];
#define TL RS			
#define TE RS

int                     RB_inicio, RB_fin, RB_long;
reorder_t		RB[TAM_REORDER];

bus_comun_t		BUS;

operador_t		Op[OPERADORES];
reg_operador_t		RegOp[OPERADORES];

/*** Estructuras para el predictor */

entrada_btb_t           BTB[TAM_BUFFER_PREDIC];

#endif 

/***************************************************************************/
/***************************************************************************/

#ifndef main_C  /* Publico (excepto main.c) */

extern ciclo_t      Ciclo;
extern boolean			terminando;
extern char			nombre_fich[128];
extern dword			PC_ISS;
extern int			RB_cab;
extern estadisticas_t           estat;

/*** Estructuras visibles al programador */
extern segmento_t		SegDatos;
extern memoria_datos_t		MD;
extern segmento_t		SegInstruc;
extern memoria_intrucciones_t	MI;

extern tipo_t                   md_tipo[TAM_MEMO_DATOS]; /* Tipos de la memoria de datos */

extern reg_fp_t                 Rfp[TAM_REGISTROS]; 
extern reg_int_t                Rint[TAM_REGISTROS+1];/* El último simula el 'fpsr' */

/*** Registros inter-etapa para la segmentación */

/* Representan a los registros inter-etapa que contienen los valores
   para el siguiente ciclo, los valores futuros */
/* DEBEN ESTAR SIEMPRE A LA IZQUIERDA DE UNA ASIGNACION */
extern reg_if_iss_t	IF_ISS_1;
extern reg_control_t	Control_1;

/* Representan a los registros inter-etapa que contienen los valores
   del presente ciclo. Serán estables hasta que se vuelvan escribir al
   final del ciclo con los nuevos valores */
/* DEBEN ESTAR SIEMPRE A LA DERECHA DE UNA ASIGNACION O EN LAS
   COMPARACIONES */
extern reg_if_iss_t	IF_ISS_2;
extern reg_control_t	Control_2;

/*** Estructuras internas de la ruta de datos de coma flotante */

/* Todas las estaciones están en el mismo array, pero se puede usar
   RS, TL o TE */
extern estacion_t	RS[_TAM_ESTACIONES];
#define TL RS			
#define TE RS

extern int              RB_inicio, RB_fin, RB_long;
extern reorder_t	RB[TAM_REORDER];

extern bus_comun_t	BUS;

extern operador_t	Op[OPERADORES];
extern reg_operador_t	RegOp[OPERADORES];

/*** Estructuras para el predictor */

extern entrada_btb_t    BTB[TAM_BUFFER_PREDIC];

#endif

#endif /* Include main.h */


