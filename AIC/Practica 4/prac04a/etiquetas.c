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
#include <math.h>
#include "etiquetas.h"
#include "memoria.h"

/***** Definiciones Externas **********************************/

#include "tipos.h"
#include "main.h"

extern int yyerror(char *);

extern int linenumber;

/***** Variables Globales *************************************/

/***** Variables Locales **************************************/

static etiqueta_t LE[MAX_ETIQUETAS]; /* Lista de etiquetas */

static short num_etiq = 0;

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

void te_inserta(
        char *texto,
        dword direccion,
        modo_t tipo_memoria
) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int i;            /* Indice con el que recorreremos el
				   array de etiq. */
    instruccion_t instruccion;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

/*   fprintf(stderr, "INS ETIQ: %s\n", texto); */

    for (i = 0; i < num_etiq; i++) {   /* Busca la existencia de alguna referencia previa */
        if (!strcmp(LE[i].texto, texto)) {            /* Existe una referencia */
            if (LE[i].sin_resolver == NULL) {            /* Redefinición */
                yyerror("Redefinición de una etiqueta");
            } else {           /* Referencias sin resolver */

                referencia_t *ref_iter;
                referencia_t *ref_next;

                /*** Establece los valores de la etiqueta */

                LE[i].direccion = direccion;
                LE[i].tipo_memoria = tipo_memoria;

                /*** Resuelve los valores pendientes */

                for (ref_iter = LE[i].sin_resolver;
                     ref_iter != NULL;
                     ref_iter = ref_next) {
                    if (ref_iter->tipo_memoria != tipo_memoria) {
                        linenumber = ref_iter->linea;
                        yyerror("Etiqueta de tipo incompatible");
                    } else {
                        instruccion = lee_mem_instruc(ref_iter->direccion);
                        switch (ref_iter->tipo_memoria) {
                            case m_datos:
                                /* Relativo al comienzo del segmento de datos. DESACTIVADO */
                                // MI[ref_iter->direccion].inmediato = (half) (direccion - SegDatos.inicio);
                                instruccion.inmediato = (half) direccion;
                                break;
                            case m_instruc:
                                /* Relativo a la propia dirección de la instrucción + 1 */
                                instruccion.inmediato = direccion - ref_iter->direccion - 1;
                                break;
                            default:
                                yyerror("PÁNICO");
                        } /* endswitch */
                        escribe_mem_instruc(ref_iter->direccion, instruccion);
                    } /* endif */

                    ref_next = ref_iter->next;

                    free(ref_iter); /* Libera la referencia ya resuelta */

                } /* endfor */

                LE[i].sin_resolver = NULL;

            } /* endif */

            break;

        } else if (LE[i].direccion == direccion && LE[i].tipo_memoria == tipo_memoria) {
            strcpy(LE[i].texto, texto);
            break;
        } /* endif */
    } /* endfor */

    if (i == num_etiq)        /* Añadimos una nueva etiqueta */
    {
        if (i == MAX_ETIQUETAS) {
            yyerror("Tabla de etiquetas llena. "
                            "Cambie MAX_ETIQUETAS en etiquetas.h");
        } /* endif */

        strcpy(LE[i].texto, texto);
        LE[i].direccion = direccion;
        LE[i].tipo_memoria = tipo_memoria;
        LE[i].sin_resolver = NULL;

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
                char *texto,
                word linea,
                dword puntero,
                modo_t tipo_memoria
        ) {
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int i;            /* Indice con el que recorremos LE */

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

/*   fprintf(stderr, "RES ETIQ: %s\n", texto); */

    for (i = 0; i < num_etiq; i++)    /* Mira si la etiqueta existe */
    {
        if (!strcmp(LE[i].texto, texto)) {            /* Existe una referencia */
            if (LE[i].sin_resolver == NULL) {
                return LE[i].direccion; /* Devuelve la dirección */
            } else            /* Referencias sin resolver */
            {
                referencia_t *ref_nueva;

                /*** Crea un referencia sin resolver */

                ref_nueva = malloc(sizeof(referencia_t));
                if (ref_nueva == NULL)
                    yyerror("Falta memoria");

                ref_nueva->direccion = puntero;
                ref_nueva->linea = linea;
                ref_nueva->tipo_memoria = tipo_memoria;

                ref_nueva->next = LE[i].sin_resolver;

                LE[i].sin_resolver = ref_nueva;

            } /* endif */

            break;

        } /* endif */
    } /* endfor */

    if (i == num_etiq)        /* Añadimos una nueva etiqueta sin resolver */
    {
        referencia_t *ref_nueva;

        if (i == MAX_ETIQUETAS) {
            yyerror("Tabla de etiquetas llena. "
                            "Cambie MAX_ETIQUETAS en etiquetas.h");
        } /* endif */

        strcpy(LE[i].texto, texto);
        LE[i].direccion = 0;        /* sin resolver */

        /*** Crea una referencia sin resolver */

        ref_nueva = malloc(sizeof(referencia_t));
        if (ref_nueva == NULL)
            yyerror("Falta memoria");

        ref_nueva->direccion = puntero;
        ref_nueva->linea = linea;
        ref_nueva->tipo_memoria = tipo_memoria;
        ref_nueva->next = NULL;

        LE[i].sin_resolver = ref_nueva;

        num_etiq++;

    } /* endif */

    return 0;            /* Referencia sin resolver */

} /* end te_resuelve */

/***************************************************************
 *
 * Func: te_confirma
 *
 * Descripción:
 *   Mira si hay referencias sin resolver
 *
 **************************************************************/

void te_confirma() {
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int i;            /* Indice con el que recorremos LE */

    for (i = 0; i < num_etiq; i++)    /* Mira si la etiqueta existe */
    {
        if (LE[i].sin_resolver != NULL) {
            /* Existe una referencia sin resolver */
            char mensaje[128];

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

void te_etiqueta(
        char *texto,
        dword direccion,
        modo_t tipo_memoria
) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int i;            /* Indice con el que recorremos LE */

    dword limit = 0;
    int size = 0;
    char format[20];

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    switch (tipo_memoria) {
        case m_instruc:
            limit = SegInstruc.final;
            break;
        case m_datos:
            limit = SegDatos.final;
            break;
        default:
	    fprintf(stderr, "ERROR: No se debería usar el valor 'm_ninguno' en la función 'te_etiqueta'");
	    exit(1);
            break;
    }
    size = (int) ceil(log10((double) limit));

    if (f_etiquetas) {
        dword base = 0;
        int etiqueta = -1;

        for (i = 0; i < num_etiq; i++) {    /* Mira si la dirección existe */
            if (LE[i].tipo_memoria == tipo_memoria) {
//                if (LE[i].direccion == direccion) {
//                    strcpy(texto, LE[i].texto);
//                    return;
//                } else
                if (LE[i].direccion >= base && LE[i].direccion <= direccion) {
                    etiqueta = i;
                    base = LE[i].direccion;
                }
            } /* endif */
        } /* endfor */

        if (etiqueta >= 0) {
            sprintf(format, "%%s + %%0%d" PRId64, size);
            sprintf(texto, format, LE[etiqueta].texto, direccion - LE[etiqueta].direccion);
        } else {
            /* Etiqueta no encontrada */
            sprintf(texto, F_DWORD, direccion);
        }
    } else {
        for (i = 0; i < num_etiq; i++) {    /* Mira si la dirección existe */
            if (LE[i].direccion == direccion && LE[i].tipo_memoria == tipo_memoria) {
                strcpy(texto, LE[i].texto);
                return;
            } /* endif */
        } /* endfor */

        /* Etiqueta no encontrada */
        sprintf(texto, F_DWORD, direccion);
    }

} /* end te_etiqueta */


/***************************************************************
 *
 * Func: te_busca
 *
 * Descripción:
 *   Busca la etiqueta más cercana a la direccion.
 *   Devuelve el índice de la etiqueta + 1.
 *
 **************************************************************/

int te_busca(
        dword direccion,
        modo_t tipo_memoria
) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int i;            /* Indice con el que recorremos LE */

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    dword base = 0;
    int etiqueta = -1;

    for (i = 0; i < num_etiq; i++) {    /* Mira si la dirección existe */
        if (LE[i].tipo_memoria == tipo_memoria) {
            if (LE[i].direccion == direccion) {
                return i + 1;
            } else if (LE[i].direccion >= base && LE[i].direccion < direccion) {
                etiqueta = i;
                base = LE[i].direccion;
            }
        } /* endif */
    } /* endfor */

    return etiqueta + 1;

} /* end te_etiqueta */

