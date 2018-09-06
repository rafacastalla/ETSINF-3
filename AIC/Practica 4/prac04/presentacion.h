/*********************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: presentacion.h
 *  
 * Description: 
 *    Definiciones para el módulo de presentación
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

#ifndef presentacion_H
#define presentacion_H

/***** Includes ***********************************************/


/***** Constants **********************************************/

#define MAX_INSTRUC	25	/* Número máximo de instrucciones visibles */
#define MAX_CICLOS_INIC	25	/* Número máximo de ciclos visibles
                                   inicialmente */
#define MAX_CICLOS	35	/* Número máximo de ciclos visibles */

/***** Types **************************************************/

typedef char n_fase_t[64];	  /* Nombre de la fase */
typedef char n_instruccion_t[64]; /* Instrucción */

typedef struct {
  n_instruccion_t	inst;	/* Instrucción */
  n_fase_t		fase[MAX_CICLOS]; 
				/* Fases de la instrucción */
} linea_crono_t;		/* Una linea del cronograma */


/***** Macros *************************************************/


/***** Prototypes *********************************************/

#include "presentacion.hi"

#ifdef presentacion_C		/*** Privado ***/

char		p_str[256];	/* Cadena auxiliar */

linea_crono_t		crono[MAX_INSTRUC];
				/* Instrucciones visibles en el
                                   cronograma */
#else				/*** Público ***/

extern char		p_str[256]; /* Cadena auxiliar */

extern linea_crono_t	crono[MAX_INSTRUC];
				/* Instrucciones visibles en el
                                   cronograma */
#endif

#endif /* end presentacion.h */

