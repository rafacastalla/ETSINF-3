/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: f_transferencia.c
 *  
 * Description: 
 *      Contiene la fase de transferencia por el bus común de datos para el
 *      algoritmo de Tomasulo con especulación.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#define f_transferencia_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "instrucciones.h"
#include "prediccion.h"
#include "presentacion.h"

/***************************************************************
 *
 * Func: fase_WB
 *
 **************************************************************/

void fase_WB ()
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    short		i;
    marca_t	s;

    ciclo_t		orden;
    short		operador;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /*** Busca operadores con resultados disponibles */
  
    orden= Ciclo;
    operador= 0;
    
    for (i= 0; i < OPERADORES; i++) {
        if (RegOp[i].ocupado && RegOp[i].orden < orden) {
            operador= i;
            orden= RegOp[i].orden;
	} /* endif */
    } /* endif */

    if (orden >= Ciclo) return ;  /* No hay ningún operador con resultados disponibles */

    /*** Libera el registro de salida del operador */
    RegOp[operador].ocupado= NO;    

    /*** Volcado de resultados */

	/* INSERTAR CÓDIGO */

    /*** Lectura de resultados */

    /* Estaciones de reserva */

    for (s= INICIO_RS_ENTEROS; 
         s<= FIN_RS_ENTEROS; s++) {

	/* INSERTAR CÓDIGO */

    } /* endfor */

    for (s= INICIO_RS_SUMA_RESTA; 
         s<= FIN_RS_SUMA_RESTA; s++) {

	/* INSERTAR CÓDIGO */

    } /* endfor */

    for (s= INICIO_RS_MULT_DIV; 
         s<= FIN_RS_MULT_DIV; s++) {

	/* INSERTAR CÓDIGO */

    } /* endfor */

    /* Tampón de escritura */

    for (s= INICIO_TAMPON_ESCR; 
         s<= FIN_TAMPON_ESCR; s++) {

	/* INSERTAR CÓDIGO */

    } /* endfor */
    
    /* Reorder buffer */

	/* INSERTAR CÓDIGO */

    /*** Libera la estación de reserva */

	/* INSERTAR CÓDIGO */

    /*** VISUALIZACIÓN ****/
    muestra_fase("WB", RB[BUS.codigo].orden);
    /**********************/

} /* end fase_WB */

