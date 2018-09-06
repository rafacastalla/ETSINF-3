/*********************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 *	   Pedro López (plopez@disca.upv.es)
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

#ifndef main_H
#define main_H

/***** Includes ***********************************************/

#include "tipos.h"

/*** Defines ***************************************************************/

#define TAM_REGISTROS		32
#define NUM_REG_VISIBLES    16
#define MAX_CICLOS_HTML		100
#define MAX_CICLOS_TXT		1000
#define MAX_CICLOS_TOTAL    1000

/*** Inclusion condicional *************************************************/

#ifdef main_C   /* Privado para el fichero main.c */

long                    orden;
ciclo_t			Ciclo;
estadisticas_t  estat;
ciclo_t         Instrucciones;
char			nombre_fich[128];
// byte			ins_count;
int				w3css_flag=1;


/*** Estructuras visibles al programador */

segmento_t		SegDatos;
memoria_datos_t		MD;
segmento_t		SegInstruc;
memoria_intrucciones_t	MI;

reg_int_t		Rint[TAM_REGISTROS];

/*** Registros inter-etapa para la segmentación */

word			PCn,PC;

IF_ID_t			IF_IDn, IF_ID;
ID_EX_t			ID_EXn, ID_EX;
EX_MEM_t		EX_MEMn, EX_MEM;
MEM_WB_t		MEM_WBn, MEM_WB;

riesgos_d_t		solucion_riesgos_datos;
riesgos_c_t		solucion_riesgos_control;
sal_t			salida;

boolean			MEMaEXalu_s,
			MEMaEXalu_i,
			MEMaEXcomp,
			WBaEXalu_s,
			WBaEXalu_i,
			WBaEXcomp,
			WBaEXmem,
			WBaMEM,
			MEMaID,
			WBaID,
            		SaltoEfectivo;

boolean			IFstall,
			IDstall,
			EXstall,
			IFnop,
			IDnop,
			EXnop,
			MEMnop;

word			IDcompin,
			IDdir,
			ALUout,
			WBdata;

boolean 		CONDout;


#endif 

/***************************************************************************/
/***************************************************************************/

#ifndef main_C  /* Publico (excepto main.c) */

extern long                     orden;
extern ciclo_t      Ciclo;
extern ciclo_t      Instrucciones;
extern estadisticas_t  estat;
extern char			nombre_fich[128];
// extern byte			ins_count;

/*** Estructuras visibles al programador */
extern segmento_t		SegDatos;
extern memoria_datos_t		MD;
extern segmento_t		SegInstruc;
extern memoria_intrucciones_t	MI;

extern reg_int_t		Rint[TAM_REGISTROS];

/*** Registros inter-etapa para la segmentación */

extern word			PCn,PC;

extern IF_ID_t			IF_IDn, IF_ID;
extern ID_EX_t			ID_EXn, ID_EX;
extern EX_MEM_t		EX_MEMn, EX_MEM;
extern MEM_WB_t		MEM_WBn, MEM_WB;

extern riesgos_d_t		solucion_riesgos_datos;
extern riesgos_c_t		solucion_riesgos_control;
extern sal_t			salida;

boolean			MEMaEXalu_s,
			MEMaEXalu_i,
			MEMaEXcomp,
			WBaEXalu_s,
			WBaEXalu_i,
			WBaEXcomp,
			WBaEXmem,
			WBaMEM,
			MEMaID,
			WBaID,
            		SaltoEfectivo;

extern boolean			IFstall,
				IDstall,
				EXstall,
				IFnop,
				IDnop,
				EXnop,
				MEMnop;
				
extern word			IDcompin,
				IDdir,
				ALUout,
				WBdata;

extern boolean 		CONDout;


#endif

#endif /* Include main.h */


