/*********************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio S‡ez (ssaez@disca.upv.es)
 *	   Pedro L—pez (plopez@disca.upv.es)
 * 
 * File: tipos.h
 *  
 * Description: 
 *    Contiene las definiciones de tipos comunes
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
 *********************************************************************/

#ifndef tipos_H
#define tipos_H

/***** Includes ***********************************************/

#include <sys/types.h>
#include <stdint.h>

/***** Constants **********************************************/

#define KB			(1024)

#define TAM_MEMO_DATOS		(16*KB)
#define TAM_MEMO_INSTRUC	(1*KB)

/*** Excepciones */

#define EXC_NONE		0

#define EXC_MEM_INST		1
#define EXC_MEM_DAT		2

#define EXC_TRAP(t)		(32+(t))

/***** Types **************************************************/

typedef unsigned char	byte;	/* Un byte: 8 bits */
typedef short		half;	/* Media palabra: 16 bits */
// typedef long		word;	/* Una palabra: 32 bits */
typedef int32_t		word;	/* Una palabra: 32 bits */
typedef int64_t		dword;	/* Una doble palabra: 64 bits */

//typedef unsigned long 	ciclo_t;
typedef long 	ciclo_t;

#define MAX_BYTE (0xFF)
#define MAX_HALF (0xFFFF)
#define MAX_WORD (0xFFFFFFFF)
#define MAX_DWORD (0xFFFFFFFFFFFFFFFF)

typedef enum
{
  NO=0, 
  SI=1
} boolean;			/* Valor lógico */

typedef enum
{
    t_ninguno,
    t_word,
    t_dword,
    t_double
} tipo_t;			/* Tipo de dato utilizado */

typedef enum 
{
  m_ninguno, 
  m_datos, 
  m_instruc
} modo_t;			/* Segmento de memoria accedido */

/*** Estructuras espécificas ****/

typedef byte	codop_t;	/* Código de operación */

typedef enum 
{
  FormatoR, 
  FormatoI, 
  FormatoJ
} formato_t;			/* El formato J no esta implementado */

typedef enum {
  parada, 
  cortocircuito, 
  ninguno
} riesgos_d_t;

typedef enum {
  stall, 
  pnt, 
  ds3,
  ds2,
  ds1
} riesgos_c_t;

typedef enum {
  html,
  html_final, 
  res_ciclo, 
  res_final,
  res_tiempo
} sal_t;
 
/*** Formato de instruccion ****/

typedef struct {
  codop_t	codop;
  formato_t	tipo;

  byte		Rfuente1,	/* Índice del registro fuente 1 */
            Rfuente2;    /* Índice del registro fuente 2 */
  byte		Rdestino;	/* Índice del registro destino */
  half		inmediato;	/* Valor Inmediato */
} instruccion_t;

/*** Banco de registros ********/

typedef struct {
  dword		valor;		/* Valor del registro */
} reg_int_t;

/*** Registros inter-etapas ************************************************/

/*** Registros intermedios *******************/


typedef struct {
  instruccion_t	IR;		/* IR */
  dword		NPC;       	/* PC+4 */

  dword		iPC;		
  ciclo_t		orden;		/* Información de visualización */
} IF_ID_t;

typedef struct {
  instruccion_t	IR;		/* IR */
  dword		NPC;       	/* PC+4 */
  dword		Ra,		/* Valores de los registros*/
  		Rb;
  dword		Imm;		/* Inmediato con signo extendido */

  dword		iPC;		
  ciclo_t		orden;		/* Información de visualización */
} ID_EX_t;

typedef struct {
  instruccion_t	IR;		/* IR */
  dword		ALUout;		/* Resultado */
  dword	        data;	        /* Dato a escribir */
  boolean	cond;		/* Resultado condicion de salto */

  dword		iPC;		
  ciclo_t		orden;		/* Información de visualización */
} EX_MEM_t;

typedef struct {
  instruccion_t	IR;		/* IR */
  dword		ALUout;		/* Resultado */
  dword		MEMout;		/* Resultado */

  dword		iPC;		
  ciclo_t		orden;		/* Información de visualización */
} MEM_WB_t;

/*** Estructuras internas de la ruta de datos de coma flotante *************/

/*** Segmento de memoria ********/

typedef struct {
  dword	inicio;
  dword	final;
} segmento_t;

/*** Memoria de datos ***********/

typedef union {
  word		mword[TAM_MEMO_DATOS/sizeof(word)];
  dword		mdword[TAM_MEMO_DATOS/sizeof(dword)];
  double	mdouble[TAM_MEMO_DATOS/sizeof(double)];
} memoria_datos_t;

/*** Memoria de instrucciones ***/

typedef instruccion_t	memoria_intrucciones_t[TAM_MEMO_INSTRUC];

/*** Estadisticas ***/

typedef struct {
    long  ciclos;
    long  instrucciones;
    long  enteras;
    long  multiciclo;
    long  flops;
	
} estadisticas_t;

/***** Macros *************************************************/

#define dir_word(d) (dword)((d) / sizeof(word))
#define dir_dword(d) (dword)((d) / sizeof(dword))
//#define dir_float(d) (dword)((d) / sizeof(float))
#define dir_double(d) (dword)((d) / sizeof(double))

#define esta_alineada_dir_word(d) (((d) % sizeof(word)) == 0 )
#define esta_alineada_dir_dword(d) (((d) % sizeof(dword)) == 0 )
//#define esta_alineada_dir_float(d) (((d) % sizeof(float)) == 0 )
#define esta_alineada_dir_double(d) (((d) % sizeof(double)) == 0 )


#endif /* end tipos.h */
