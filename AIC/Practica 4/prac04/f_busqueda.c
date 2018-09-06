/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: f_busqueda.c
 *  
 * Description: 
 *    Contiene la fase de búsqueda
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#define f_busqueda_C

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
 * Func: fase_IF
 *
 **************************************************************/

void fase_IF () 
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    boolean     salto;
    boolean     prediccion;
    dword       destino;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    if (!Control_2.Parar) {
        IF_ISS_1.PC= Control_2.NPC;

        if (Control_2.NPC >= SegInstruc.inicio && 
            Control_2.NPC < SegInstruc.final) {
            IF_ISS_1.IR= MI[Control_2.NPC]; /* Busca la siguiente instrucción */
            IF_ISS_1.orden= IF_ISS_2.orden + 1;	
            /* Incrementa el número de instrucciones leidas */
            IF_ISS_1.excepcion= EXC_NONE;
	}
        else {
            /*** Excepción en el acceso a la memoria de instrucciones */

            IF_ISS_1.IR.codop= OP_NOP; /* Cancela la instrucción */
            IF_ISS_1.orden= IF_ISS_2.orden + 1;	
            /* Incrementa el número de instrucciones leidas */
            IF_ISS_1.excepcion= EXC_OUT_MEM_INST;
	} /* endif */

        /*** PREDICCIÓN ************/

        if (!Control_1.Cancelar) {
            salto= obtener_prediccion_sol(IF_ISS_1.PC, IF_ISS_1.orden, &prediccion, &destino); 
            if (salto && prediccion) { 
                /*** Es un salto y predice que salta */
                IF_ISS_1.prediccion= SI;
                Control_1.NPC= destino;

                /*** Estadisticas ***/
                estat.saltos_accedidos++;
            }
            else {  
                /*** O no es un salto, o es un salto y predice que no salta */
                IF_ISS_1.prediccion= NO;
                Control_1.NPC= Control_2.NPC + 1;

                /*** Estadisticas ***/
                if (inst_branch(IF_ISS_1.IR.codop))
                    estat.saltos_accedidos++;
            } /* endif */
        } /* endif */

    } /* endif */

    /*** VISUALIZACIÓN ****/
    init_instruc(IF_ISS_1.PC, IF_ISS_1.orden);
    if (!Control_1.Cancelar)
        muestra_fase("IF", IF_ISS_1.orden);
    else
        muestra_fase("X", IF_ISS_1.orden); 
    /**********************/

} /* end fase_IF */

