/**************************************************************************
 * 
 * Departamento de Inform‡tica de Sistema y Computadores (DISCA)
 * Universidad PolitŽcnica de Valencia.
 * 
 * Author: Sergio S‡ez (ssaez@disca.upv.es)
 * 
 * File: prediccion.c
 *  
 * Description: 
 *    Implementa un predictor de tipo 'Branch Target Buffer'
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#define prediccion_alum_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "prediccion.h"

#include "limits.h" 
#include "tipos.h"
#include "main.h"
#include "instrucciones.h"
#include "presentacion.h"

/***** Definiciones Externas **********************************/

/***** Variables Globales *************************************/

/***** Variables Locales **************************************/

/***** Funciones Locales **************************************/

/***** Funciones Exportables **********************************/

/***************************************************************
 *
 * Func: inicializa_prediccion
 *
 * Desc: Inicializa las tablas de predicción
 *
 **************************************************************/

void inicializa_prediccion_alum ()
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/
    
    int		i;
    
    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/
    
    for (i=0; i<TAM_BUFFER_PREDIC; i++) {
        BTB[i].PC= -1;
        BTB[i].estado= NO_SALTA;
        BTB[i].destino= 0;
        
        BTB[i].orden= 0;        /* Entrada vacia */
    } /* endfor */
    
} /* end inicializa_prediccion */

/***************************************************************
 *
 * Func: obtener_prediccion
 *
 * Desc: Obtiene la predicci—n para una instrucci—n dada. Devuelve cierto si la
 * instrucci—n era un salto, modificando el valor del par‡metro 'prediccion'.  Si la
 * predicci—n es 'salto tomado' (prediccion == SI), se modifica el valor del par‡metro
 * 'destino' para indicar la direcci—n de destino del salto.
 *
 **************************************************************/

boolean obtener_prediccion_alum
( 
    word        PC,
    ciclo_t       orden,
    boolean *   prediccion,
    dword *      destino
 )
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int		i;
    boolean encontrado;
        
    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    encontrado= NO;
    for (i=0; i<TAM_BUFFER_PREDIC; i++) {
        if (BTB[i].PC == PC) {
            encontrado= SI;
            estat.saltos_encontrados++;
            BTB[i].orden= orden; 

            if (BTB[i].estado == SALTA || BTB[i].estado == SALTA_UN_FALLO) {
                *prediccion = SI;
                *destino = BTB[i].destino;
            }else {
                *prediccion = NO;
            } /* endif */
            
            break;
        } /* endif */
    } /* endfor */

    return (encontrado);

} /* end obtener_prediccion */

/***************************************************************
 *
 * Func: actualizar_prediccion
 *
 * Desc: Actualiza la predicci—n para una instrucci—n dada.
 *
 **************************************************************/

void actualizar_prediccion_alum
( 
    word        PC,
    ciclo_t       orden,
    boolean     condicion,
    dword        destino
 )
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int		i;
    boolean     encontrado;

    ciclo_t       antiguedad;
    int         mas_antigua;
        
    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    antiguedad= LONG_MAX;
    mas_antigua= -1;

    estat.saltos_ejecutados++;
    encontrado= NO;
    for (i=0; i<TAM_BUFFER_PREDIC; i++) {
        if (BTB[i].PC == PC) {
            encontrado= SI;
            BTB[i].destino= destino;
            
            switch (BTB[i].estado) {
                case SALTA:
                    BTB[i].estado = condicion ? SALTA : SALTA_UN_FALLO;
                    break;
                
                case SALTA_UN_FALLO:
                    BTB[i].estado = condicion ? SALTA : NO_SALTA;
                    break;
                
                case NO_SALTA_UN_FALLO:
                    BTB[i].estado = condicion ? SALTA : NO_SALTA;
                    break;
                
                case NO_SALTA:
                    BTB[i].estado = condicion ? NO_SALTA_UN_FALLO : NO_SALTA;
                    break;
                
                default:
                    break;
            }
            /* Sense histeresi
            switch (BTB[i].estado) {
                case SALTA:
                    BTB[i].estado = condicion ? SALTA : SALTA_UN_FALLO;
                    break;
                    
                case SALTA_UN_FALLO:
                    BTB[i].estado = condicion ? SALTA : NO_SALTA_UN_FALLO;
                    break;
                    
                case NO_SALTA_UN_FALLO:
                    BTB[i].estado = condicion ? SALTA_UN_FALLO : NO_SALTA;
                    break;
                    
                case NO_SALTA:
                    BTB[i].estado = condicion ? NO_SALTA_UN_FALLO : NO_SALTA;
                    break;
                    
                default:
                    break;
            }*/
            
            break;
        } /* endif */

        /* Algoritmo de remplazamiento LRU */
        if (BTB[i].orden < antiguedad) {
            mas_antigua= i;
            antiguedad= BTB[i].orden;
        } /* endif */
    } /* endfor */

    if (!encontrado) {
        BTB[mas_antigua].PC= PC;
        BTB[mas_antigua].orden= orden;
        BTB[mas_antigua].destino= destino; 

        /* Actualiza el estado. Inicialmente se supone en NO_SALTA */
        if (condicion) {
            BTB[mas_antigua].estado= SALTA;
        } 
        else {
            BTB[mas_antigua].estado= NO_SALTA;
        } /* endif */
    } /* endif */

} /* end actualizar_prediccion */
