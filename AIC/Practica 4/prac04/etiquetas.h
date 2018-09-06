/*********************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * Version 1.0
 * 
 * File: etiquetas.h
 *  
 * Date: 
 * 
 * Description: 
 *    Contiene las estructuras para la tabla de símbolos
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

#ifndef etiquetas_H
#define etiquetas_H

/***** Includes ***********************************************/

#include "tipos.h"

/***** Constants **********************************************/

#define LONG_ETIQUETA	64

#define MAX_ETIQUETAS	64

/***** Types **************************************************/

typedef struct referencia_s {
  word		puntero;	/* Dirección en la memoria de
				   instrucciones */
  word		linea;		/* Linea del código */
  modo_t	tipo_memoria;	/* Tipo de memoria de la referencia */

  struct referencia_s *	next;	/* Siguiente referencia por resolver */

} referencia_t;

typedef struct {
  char		texto[LONG_ETIQUETA];

  word		puntero;	/* Posición a la que apunta la etiqueta */
  modo_t	tipo_memoria;	/* Tipo de memoria a la que apunta la
				   etiqueta */
  referencia_t*	sin_resolver;	/* Lista de intrucciones con
				   referencias sin resolver */
} etiqueta_t;

/***** Prototypes *********************************************/

#include "etiquetas.hi"


#endif /* end etiquetas.h*/

