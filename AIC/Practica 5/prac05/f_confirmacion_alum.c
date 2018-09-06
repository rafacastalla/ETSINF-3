/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: f_confirmacion.c
 *  
 * Description: 
 *    Contiene la fase de confirmación del algoritmo de Tomasulo con especulación
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#define f_confirmacion_alum_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "instrucciones.h"
#include "prediccion.h"
#include "presentacion.h"
#include "algoritmo.h"
#include "tipos.h"

/***************************************************************
 *
 * Func: fase_COM
 *
 **************************************************************/

void fase_COM_alum() {
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int i;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /*************************************/
    RB_cab = RB_inicio; /* Información administrativa */
    /*************************************/

    if (!terminando && RB[RB_inicio].ocupado
        &&
        (RB[RB_inicio].estado == WB
         ||
         ((RB[RB_inicio].OP == OP_SD || RB[RB_inicio].OP == OP_FP_S_D)
          &&
          TE[RB[RB_inicio].dest].estado == PREPARADA))) {

        /*** VISUALIZACIÓN ****/
        muestra_fase("C", RB[RB_inicio].orden);
        /**********************/

        /*** Estadisticas ***/
        estat.instrucciones++;

        /*** Atención de las excepciones */

        if (RB[RB_inicio].OP == OP_SD || RB[RB_inicio].OP == OP_FP_S_D) {
            /* En caso de los stores la excepción se mira en la estación de reserva */
            RB[RB_inicio].excepcion = TE[RB[RB_inicio].dest].excepcion;
        }

        switch (RB[RB_inicio].excepcion) {
            case EXC_NONE:
                break;
            case EXC_OUT_MEM_INST:
                fprintf(stderr, "Ciclo %lu: Acceso a memoria de instrucciones ilegal\n",
                        Ciclo);
                break;
            case EXC_OUT_MEM_DAT:
                fprintf(stderr, "Ciclo %lu: Acceso a memoria de datos ilegal\n",
                        Ciclo);
                break;
            case EXC_UNALIGN_MEM_DAT:
                fprintf(stderr, "Ciclo %lu: Acceso desalineado a la memoria de datos\n",
                        Ciclo);
                break;
            case EXC_TRAP(0):
                fprintf(stderr, "Ciclo %lu: El programa está terminando normalmente\n",
                        Ciclo);
                break;
            default:
                fprintf(stderr, "Excepción no manejada\n");
                exit(1); /* Sale del simulador */
                break;
        } /* endswitch */

        if (RB[RB_inicio].excepcion != EXC_NONE) {
            RB[RB_inicio].OP = OP_TRAP;

            terminando = SI;

            /*** VISUALIZACIÓN ****/
            muestra_fase("<font color=\"red\">C</font>", RB[RB_inicio].orden);
            /**********************/
        }

        /*** Confirmación de la intrucción */

        switch (RB[RB_inicio].OP) {
            case OP_NOP:
                /*** No hace nada ***/
                break;
            case OP_TRAP:
                /*** No hace nada ***/
                RB[RB_inicio].valor.int_d = !RB[RB_inicio].prediccion; /* Truco para forzar la cancelación */
                /*** SALTOS ***/
            case OP_BC1T:
            case OP_BC1F:
            case OP_BNEZ:
            case OP_BEQZ:
            case OP_BNE:
            case OP_BEQ:
                /* Actualizar las predicción (haya o no haya habido fallo) */

                if (RB[RB_inicio].excepcion == EXC_NONE) {
                    actualizar_prediccion(RB[RB_inicio].PC, RB[RB_inicio].orden,
                                          RB[RB_inicio].valor.int_d, RB[RB_inicio].dest);
                }

                if (RB[RB_inicio].valor.int_d == RB[RB_inicio].prediccion) {
                    /*** Estadisticas ***/
                    estat.saltos_acertados++;
                } else {
                    /*** Predicción incorrecta ***/

                    /*** VISUALIZACIÓN ****/
                    for (i = 0; i < TAM_REORDER; i++) {
                        if (RB[i].ocupado && i != RB_inicio)
                            muestra_fase("x", RB[i].orden);
                    } /* endfor */

                    for (i = 0; i < TAM_ESTACIONES; i++) {
                        if (RS[i].ocupado && RS[i].estado == FINALIZADA && !ES_ESTACION(i, TAMPON_ESCR))
                            muestra_fase("X", RS[i].orden);
                    } /* endfor */

                    for (i = 0; i < NUM_OPERADORES; i++) {
                        if (Op[i].ocupado && !ES_ESTACION(Op[i].estacion, TAMPON_ESCR))
                            muestra_fase("X", RS[Op[i].estacion].orden);
                    } /* endfor */

                    /**********************/

                    /* Liberar los registros */
                    for(i = 0; i < TAM_REGISTROS; i++){
                        if (Rfp[i].rob != MARCA_NULA)
                            Rfp[i].rob = MARCA_NULA;
                        
                        if (Rint[i].rob != MARCA_NULA)
                            Rint[i].rob = MARCA_NULA;
                    }

                    /* Liberar las estaciones de reserva */

                    for (i = 0; i < TAM_ESTACIONES; i++) {
                        if (RS[i].ocupado &&  RS[i].confirm == NO )
                            RS[i].ocupado = NO;
                    }

                    /* Liberar los operadores */

                    for (i = 0; i < NUM_OPERADORES; i++) {
                        if (Op[i].ocupado && RS[Op[i].estacion].confirm == NO)
                            Op[i].ocupado = NO;
                    }

                    /* Preparar la búsqueda de la dirección correcta */
                    
                    if( RB[RB_inicio].valor.int_d == 1){
                        Control_1.NPC = RB[RB_inicio].dest;
                    }else {
                        Control_1.NPC = RB[RB_inicio].PC + 4;
                    }

                    /* Liberar el reorder buffer e inicializarlo */

                    for (i = 0; i < TAM_REORDER; i++) {
                            RB[i].ocupado = NO;
                    }

                    /* Inicializar la cola circular del reorder buffer */

                    RB_long = 0;
                    RB_inicio = 0;
                    RB_fin = 0;

                    /* Resetea las señales de control y el FPSR */
                    
                    Control_1.Cancelar = SI;
                    Control_1.Excepcion = NO;
                    Rint[REG_FPSR].rob = MARCA_NULA;

                    return;

                } /* endif */
                break;
                /*** ALMACENAMIENTOS EN MEMORIA ***/
            case OP_SD:
            case OP_FP_S_D:
                /*** Confirma la intrucción de escritura */

                TE[RB[RB_inicio].dest].confirm = SI;

                break;
                /*** OPERACIONES ENTERAS CON ESCRITURA EN REGISTROS */
            case OP_LD:
            case OP_DADD:
            case OP_DSUB:
            case OP_DADDI:
            case OP_DSUBI:
            case OP_FP_LT_D: /* Escriben en un registro entero que usamos como */
            case OP_FP_GT_D: /* registro de estado del coprocesador de C.F. */

                /* El registro R0 no se debería modificar */
                
                Rint[RB[RB_inicio].dest].valor = RB[RB_inicio].valor;
                
                if(Rint[RB[RB_inicio].dest].rob == RB_inicio){
                    Rint[RB[RB_inicio].dest].rob = MARCA_NULA;
                }

                break;
                /*** OPERACIONES DE COMA FLOTANTE CON ESCRITURA EN REGISTROS */
            case OP_FP_L_D:
            case OP_FP_ADD_D:
            case OP_FP_SUB_D:
            case OP_FP_MUL_D:
            case OP_FP_DIV_D:

                Rfp[RB[RB_inicio].dest].valor = RB[RB_inicio].valor;
                
                if(Rfp[RB[RB_inicio].dest].rob == RB_inicio){
                    Rfp[RB[RB_inicio].dest].rob = MARCA_NULA;
                }
                    
                break;
            default:
                fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n",
                        __FILE__, __LINE__);
                exit(1);
        } /* endswitch */

        /* Actualizar el reorder buffer */
        RB[RB_inicio].ocupado = NO;
        RB_inicio = (RB_inicio + 1) % TAM_REORDER;
        RB_long--;

    } /* endif */

    return;

} /* end fase_COM */
