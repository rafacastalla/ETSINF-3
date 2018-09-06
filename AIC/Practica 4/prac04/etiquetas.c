/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: etiquetas.c
 *  
 * Description: 
 *    Contiene el código de gestión de etiquetas y etiquetado de la memoria
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

#define etiquetas_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etiquetas.h"

/***** Definiciones Externas **********************************/

#include "tipos.h"
#include "main.h"

extern int yyerror (char*);
extern int linenumber;

/***** Variables Globales *************************************/

/***** Variables Locales **************************************/

static etiqueta_t LE[MAX_ETIQUETAS]; /* Lista de etiquetas */

static short	num_etiq= 0;

/***** Funciones Locales **************************************/

/***** Funciones Exportables **********************************/

/***************************************************************
 *
 * Func: te_inserta
 *
 * Descripción:
 *   Inserta el valor de una etiqueta en la tabla de simbolos
 *
 **************************************************************/

void te_inserta 
(
 char*	texto,
 int	linea,
 word	puntero,
 modo_t tipo_memoria
 )
{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int i;			/* Indice con el que recorreremos el
				   array de etiq. */

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/

/*   fprintf(stderr, "INS ETIQ: %s\n", texto); */

  for (i=0; i < num_etiq; i++)	/* Busca la existencia de alguna
				   referencia previa */
    {
      if (!strcmp(LE[i].texto, texto))
	{			/* Existe una referencia */
	  if (LE[i].sin_resolver == NULL)
	    {			/* Redefinición */
	      yyerror("Redefinición de una etiqueta");
	    }
	  else			/* Referencias sin resolver */
	    {
	      referencia_t *	ref_iter;
	      referencia_t *	ref_next;
	      
	      /*** Establece los valores de la etiqueta */

	      LE[i].puntero= puntero;
	      LE[i].tipo_memoria= tipo_memoria;

	      /*** Resuelve los valores pendientes */

	      for (ref_iter= LE[i].sin_resolver;
		   ref_iter != NULL;
		   ref_iter= ref_next)
		{
		  if (ref_iter->tipo_memoria != tipo_memoria)
		    {
		      linenumber= ref_iter->linea;
		      yyerror("Etiqueta de tipo incompatible");
		    }
		  else 
		    {
		      switch (ref_iter->tipo_memoria)
			{
			case m_datos:
			  MI[ref_iter->puntero].inmediato= puntero;
			  break;
			case m_instruc:
			  MI[ref_iter->puntero].inmediato= 
			    puntero - ref_iter->puntero -1;
				/* Relativo a la propia dirección de la
                                   instrucción + 1 */
			  break;
			default:
			  yyerror("PÁNICO");
			} /* endswitch */
		    } /* endif */

		  ref_next= ref_iter->next;

		  free(ref_iter); /* Libera la referencia ya resuelta */
		  
		} /* endfor */
	      
	      LE[i].sin_resolver= NULL;
	      
	    } /* endif */

	  break;

	} /* endif */
    } /* endfor */

  if (i == num_etiq)		/* Añadimos una nueva etiqueta */
    {
      if (i == MAX_ETIQUETAS)
	{
	  yyerror("Tabla de etiquetas llena. "
		  "Cambie MAX_ETIQUETAS en etiquetas.h");
	} /* endif */

      strcpy(LE[i].texto, texto);
      LE[i].puntero= puntero;
      LE[i].tipo_memoria= tipo_memoria;
      LE[i].sin_resolver= NULL;

      num_etiq++;
      
    } /* endif */

} /* end te_inserta */


/***************************************************************
 *
 * Func: te_resuelve
 *
 * Descripción:
 *   Resuelve el valor de las etiquetas o lo deja pendiente.
 *
 **************************************************************/

word te_resuelve 
( 
 char*	texto,
 word	linea,
 word	puntero,
 modo_t tipo_memoria
 )
{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int i;			/* Indice con el que recorremos LE */

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/

/*   fprintf(stderr, "RES ETIQ: %s\n", texto); */

  for (i=0; i < num_etiq; i++)	/* Mira si la etiqueta existe */
    {
      if (!strcmp(LE[i].texto, texto))
	{			/* Existe una referencia */
	  if (LE[i].sin_resolver == NULL)
	    {			
	      return LE[i].puntero; /* Devuelve la dirección */
	    }
	  else			/* Referencias sin resolver */
	    {
	      referencia_t *	ref_nueva;
	      
	      /*** Crea un referencia sin resolver */
	      
	      ref_nueva= malloc(sizeof(referencia_t));
	      if (ref_nueva == NULL)
		yyerror("Falta memoria");
	      
	      ref_nueva->puntero= puntero;
	      ref_nueva->linea= linea;
	      ref_nueva->tipo_memoria= tipo_memoria;

	      ref_nueva->next= LE[i].sin_resolver;

	      LE[i].sin_resolver= ref_nueva;

	    } /* endif */

	  break;

	} /* endif */
    } /* endfor */

  if (i == num_etiq)		/* Añadimos una nueva etiqueta sin
				   resolver */
    {
      referencia_t *	ref_nueva;
	      
      if (i == MAX_ETIQUETAS)
	{
	  yyerror("Tabla de etiquetas llena. "
		  "Cambie MAX_ETIQUETAS en etiquetas.h");
	} /* endif */

      strcpy(LE[i].texto, texto);
      LE[i].puntero= 0;		/* sin resolver */

      /*** Crea una referencia sin resolver */
      
      ref_nueva= malloc(sizeof(referencia_t));
      if (ref_nueva == NULL)
	yyerror("Falta memoria");
      
      ref_nueva->puntero= puntero;
      ref_nueva->linea= linea;
      ref_nueva->tipo_memoria= tipo_memoria;
      ref_nueva->next= NULL;
      
      LE[i].sin_resolver= ref_nueva;

      num_etiq++;

    } /* endif */

  return 0;			/* Referencia sin resolver */

} /* end te_resuelve */

/***************************************************************
 *
 * Func: te_confirma
 *
 * Descripción:
 *   Mira si hay referencias sin resolver
 *
 **************************************************************/

void te_confirma ()
{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int i;			/* Indice con el que recorremos LE */

  for (i=0; i < num_etiq; i++)	/* Mira si la etiqueta existe */
    {
      if (LE[i].sin_resolver != NULL)
	{			
	  /* Existe una referencia sin resolver */
	  char	mensaje[128];

	  sprintf(mensaje, "La referencia %s está sin resolver",
		  LE[i].texto);
	  yyerror(mensaje);
	} /* endif */
    } /* endfor */

} /* end te_confirma */

/***************************************************************
 *
 * Func: te_etiqueta
 *
 * Descripción:
 *   Resuelve el nombre de la etiqueta a partir de la direccion
 *
 **************************************************************/

int te_etiqueta 
( 
 char*	texto,
 word	puntero,
 modo_t tipo_memoria
 )
{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int i;			/* Indice con el que recorremos LE */

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/

  for (i=0; i< num_etiq; i++) {	/* Mira si la dirección existe */
      if (LE[i].puntero == puntero && LE[i].tipo_memoria  == tipo_memoria) {
          strcpy(texto, LE[i].texto);
          return 1;
      } /* endif */
  } /* endfor */

  /* Etiqueta no encontrada */
  sprintf(texto, "???");

  return 0;

} /* end te_etiqueta */


/***************************************************************
 *
 * Func: mem_rango
 *
 ***************************************************************/
void mem_rango(dword dir, tipo_t tipo, dword * m_from, dword * m_to) {

    switch (tipo) {
    case t_byte:
        *m_from= dir_byte(dir)*sizeof(byte);
        *m_to= (*m_from) + sizeof(byte);
        break;
    case t_half:
        *m_from= dir_half(dir)*sizeof(half);
        *m_to= (*m_from) + sizeof(half);
        break;
    case t_word:
        *m_from= dir_word(dir)*sizeof(word);
        *m_to= (*m_from) + sizeof(word);
        break;
    case t_dword:
        *m_from= dir_dword(dir)*sizeof(dword);
        *m_to= (*m_from) + sizeof(dword);
        break;
    case t_float:
        *m_from= dir_float(dir)*sizeof(float);
        *m_to= (*m_from) + sizeof(float);
        break;
    case t_double:
        *m_from= dir_double(dir)*sizeof(double);
        *m_to= (*m_from) + sizeof(double);
        break;
    default:
        *m_from= (dir);
        *m_to= (*m_from) + 1;
    } /* endswitch */

} /* end mem_rango */

/***************************************************************
 *
 * Func: mem_etiqueta
 *
 ***************************************************************/

void mem_etiqueta(dword dir, tipo_t tipo) {
    
    dword i; 
    dword old_from, old_to;
    dword new_from, new_to;

    mem_rango(dir, md_tipo[dir], &old_from, &old_to);
    for(i= old_from; i<old_to; i++) 
        md_tipo[i]= t_ninguno;

    mem_rango(dir, tipo, &new_from, &new_to);
    for(i= new_from; i<new_to; i++) 
        md_tipo[i]= tipo;

} /* end mem_etiqueta */
