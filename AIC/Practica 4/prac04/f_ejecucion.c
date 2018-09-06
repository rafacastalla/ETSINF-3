/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: f_ejecucion.c
 *  
 * Description: 
 *    Contiene la fase de ejecución de los operadores multiciclo
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#define f_ejecucion_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "etiquetas.h"
#include "instrucciones.h"
#include "prediccion.h"
#include "presentacion.h"

/***************************************************************
 *
 * Func: fase_EX_1
 *
 * Desc: Implementa la fase de ejecucion de los operadores
 * multiciclo. Comienza la ejecución de las operaciones que tienen
 * todos los operandos, y el operador libre.
 *
 **************************************************************/

void fase_EX_1 ()
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t	s, r, t;
  
    ciclo_t		siguiente;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/
    if (!Op[OPER_ENTEROS].ocupado) {		/* Si el operador está libre */
        s= TAM_ESTACIONES;
        siguiente= Ciclo+1;

        /*** Busca la instrucción más antigua que este preparada */

        for (r= INICIO_RS_ENTEROS; 
             r <= FIN_RS_ENTEROS; r++) {
            if (RegOp[OPER_ENTEROS].ocupado && 
                RegOp[OPER_ENTEROS].estacion == r)
                continue;

            if (RS[r].ocupado && /* Hay una operación pendiente */
                RS[r].Qj == MARCA_NULA &&
                RS[r].Qk == MARCA_NULA &&
                /* Tiene todos los operandos disponibles */
                RS[r].orden < siguiente) {
                siguiente= RS[r].orden;
                s= r;
            } /* endif */
        } /* endfor */

        /*** Entra en ejecución la operación más antigua, si existe */

        if (s < TAM_ESTACIONES)	{
            Op[OPER_ENTEROS].ocupado= SI;
            Op[OPER_ENTEROS].ciclo= 0;
            Op[OPER_ENTEROS].codigo= RS[s].rob;
            Op[OPER_ENTEROS].estacion= s;
        } /* endif */
    } /* endif */

    /*** Operador Suma/resta */

    if (!Op[OPER_SUMREST].ocupado) {		/* Si el operador está libre */
        s= TAM_ESTACIONES;
        siguiente= Ciclo+1;

        /*** Busca la instrucción más antigua que este preparada */

        for (r= INICIO_RS_SUMA_RESTA; 
             r <= FIN_RS_SUMA_RESTA; r++) {
            if (RegOp[OPER_SUMREST].ocupado && 
                RegOp[OPER_SUMREST].estacion == r)
                continue;

            if (RS[r].ocupado && /* Hay una operación pendiente */
                RS[r].Qj == MARCA_NULA &&
                RS[r].Qk == MARCA_NULA &&
                /* Tiene todos los operandos disponibles */
                RS[r].orden < siguiente) {
                siguiente= RS[r].orden;
                s= r;
            } /* endif */
        } /* endfor */

        /*** Entra en ejecución la operación más antigua, si existe */

        if (s < TAM_ESTACIONES)	{
            Op[OPER_SUMREST].ocupado= SI;
            Op[OPER_SUMREST].ciclo= 0;
            Op[OPER_SUMREST].codigo= RS[s].rob;
            Op[OPER_SUMREST].estacion= s;
        } /* endif */
    } /* endif */

    /*** Operador Multiplicación/división */

    if (!Op[OPER_MULTDIV].ocupado) {		/* Si el operador está libre */
        s= TAM_ESTACIONES;
        siguiente= Ciclo+1;

        /*** Busca la instrucción más antigua que este preparada */

        for (r= INICIO_RS_MULT_DIV; 
             r <= FIN_RS_MULT_DIV; r++) {
            if (RegOp[OPER_MULTDIV].ocupado && 
                RegOp[OPER_MULTDIV].estacion == r)
                continue;

            if (RS[r].ocupado && /* Hay una operación pendiente */
                RS[r].Qj == MARCA_NULA &&
                RS[r].Qk == MARCA_NULA &&
                /* Tiene todos los operandos disponibles */
                RS[r].orden < siguiente) {

                siguiente= RS[r].orden;
                s= r;
            } /* endif */
        } /* endfor */

        /*** Entra en ejecución la operación más antigua, si existe */

        if (s < TAM_ESTACIONES)	{
            Op[OPER_MULTDIV].ocupado= SI;
            Op[OPER_MULTDIV].ciclo= 0;
            Op[OPER_MULTDIV].codigo= RS[s].rob;
            Op[OPER_MULTDIV].estacion= s;
        } /* endif */
    } /* endif */

    /*** Tampones de lectura/escritura */
  
    if (!Op[OPER_MEMDATOS].ocupado) {	/* Si el operador está libre */
        s= TAM_ESTACIONES;
        siguiente= Ciclo + 1;

        /*** Busca la instrucción más antigua que este preparada */

        for (r= INICIO_TAMPON_LECT; 
             r <= FIN_TAMPON_LECT; r++)	{
            if (RegOp[OPER_MEMDATOS].ocupado && 
                RegOp[OPER_MEMDATOS].estacion == r)
                continue;

            if (!TL[r].ocupado) /* Si no hay operaciones pendientes continua */
                continue;

            /* Comprueba que no haya ninguna escritura pendiente en la misma
             * dirección */
            for (t= INICIO_TAMPON_ESCR; 
                 t <= FIN_TAMPON_ESCR; t++) 
                if (TE[t].ocupado &&
                    TE[t].direccion == TL[r].direccion &&
                    TE[t].orden < TL[r].orden)
                    break;   
         
            if (t>FIN_TAMPON_ESCR) /* No hay conflictos con ninguna escritura */
                if (TL[r].orden < siguiente) {
                    siguiente= TL[r].orden;
                    s= r;
                } /* endif */
        } /* endfor */

        for (r= INICIO_TAMPON_ESCR; 
             r <= FIN_TAMPON_ESCR; r++) {
            if (TE[r].ocupado && /* Hay una operación pendiente */	
                TE[r].Qj == MARCA_NULA &&
                TE[r].confirm &&	/* Ha llegado a 'Commit' */
                TE[r].orden < siguiente) {
                siguiente= TE[r].orden;
                s= r;
            } /* endif */
        } /* endfor */

        /*** Entra en ejecución la operación más antigua, si existe */

        if (s < TAM_ESTACIONES)	{
            Op[OPER_MEMDATOS].ocupado= SI;
            Op[OPER_MEMDATOS].ciclo= 0;
            Op[OPER_MEMDATOS].codigo= RS[s].rob; /* RS = TL = TE */
            Op[OPER_MEMDATOS].estacion= s;
        } /* endif */

    } /* endif */

} /* end fase_EX_1 */


/***************************************************************
 *
 * Func: fase_EX_2
 *
 * Desc: Implementa la fase de ejecucion de los operadores
 * multiciclo. Avanza la ejecución de las operaciones que se están
 * ejecutando en cada operador.
 *
 **************************************************************/

void fase_EX_2 ()
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t	s;
  
    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /*** Operador Op[OPER_ENTEROS] */

    if (Op[OPER_ENTEROS].ocupado) {	/* Hay una operación pendiente */
        if (Op[OPER_ENTEROS].ciclo < Op[OPER_ENTEROS].Teval)
            Op[OPER_ENTEROS].ciclo++;	/* Si quedan ciclos por realizar */

        /*** VISUALIZACIÓN ****/
        sprintf(p_str, "E%d", Op[OPER_ENTEROS].ciclo);
        muestra_fase(p_str, RS[Op[OPER_ENTEROS].estacion].orden);
        /**********************/

        if (Op[OPER_ENTEROS].ciclo == Op[OPER_ENTEROS].Teval)
            if (!RegOp[OPER_ENTEROS].ocupado) {
                /* Sino hay pendiente un resultado anterior */
                RegOp[OPER_ENTEROS].ocupado= SI;
                RegOp[OPER_ENTEROS].codigo= Op[OPER_ENTEROS].codigo;
                RegOp[OPER_ENTEROS].estacion= Op[OPER_ENTEROS].estacion;
                RegOp[OPER_ENTEROS].orden= 
                    RS[Op[OPER_ENTEROS].estacion].orden;

                Op[OPER_ENTEROS].ocupado= NO;

                s= RegOp[OPER_ENTEROS].estacion;

                /* Cálculo del resultado */
                switch (RS[s].OP) {
                case OP_DADD:
                case OP_DADDI:
                    RegOp[OPER_ENTEROS].valor.i= RS[s].Vj.i + RS[s].Vk.i;
                    break;
                case OP_DSUB:
                case OP_DSUBI:
                    RegOp[OPER_ENTEROS].valor.i= RS[s].Vj.i - RS[s].Vk.i;
                    break;
                case OP_BC1F:
                case OP_BEQZ:
                case OP_BEQ:
                    RegOp[OPER_ENTEROS].valor.i= (RS[s].Vj.i == RS[s].Vk.i);
                    break;
                case OP_BC1T:
                case OP_BNEZ:
                case OP_BNE:
                    RegOp[OPER_ENTEROS].valor.i= (RS[s].Vj.i != RS[s].Vk.i);
                    break;
                default:
                    fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n", 
                            __FILE__, __LINE__);
                    exit(1);
                } /* endswitch */
            } /* endif */
    } /* endif */

    /*** Operador Suma/resta */

    if (Op[OPER_SUMREST].ocupado) {	/* Hay una operación pendiente */
        if (Op[OPER_SUMREST].ciclo < Op[OPER_SUMREST].Teval)
            Op[OPER_SUMREST].ciclo++;	/* Si quedan ciclos por realizar */

        /*** VISUALIZACIÓN ****/
        sprintf(p_str, "A%d", Op[OPER_SUMREST].ciclo);
        muestra_fase(p_str, RS[Op[OPER_SUMREST].estacion].orden);
        /**********************/

        if (Op[OPER_SUMREST].ciclo == Op[OPER_SUMREST].Teval)
            if (!RegOp[OPER_SUMREST].ocupado) {
                /* Sino hay pendiente un resultado anterior */
                RegOp[OPER_SUMREST].ocupado= SI;
                RegOp[OPER_SUMREST].codigo= Op[OPER_SUMREST].codigo;
                RegOp[OPER_SUMREST].estacion= Op[OPER_SUMREST].estacion;
                RegOp[OPER_SUMREST].orden= 
                    RS[Op[OPER_SUMREST].estacion].orden;

                Op[OPER_SUMREST].ocupado= NO;

                s= RegOp[OPER_SUMREST].estacion;

                /*** Estadisticas ***/
                estat.flops++;

                /* Cálculo del resultado */
                switch (RS[s].OP) {
                case OP_ADD_D:
                    RegOp[OPER_SUMREST].valor.f= RS[s].Vj.f + RS[s].Vk.f;
                    break;
                case OP_SUB_D:
                    RegOp[OPER_SUMREST].valor.f= RS[s].Vj.f - RS[s].Vk.f;
                    break;
                case OP_C_GT_D:
                    RegOp[OPER_SUMREST].valor.i= (RS[s].Vj.f > RS[s].Vk.f);
                    break;
                case OP_C_LT_D:
                    RegOp[OPER_SUMREST].valor.i= (RS[s].Vj.f < RS[s].Vk.f);
                    break;
                default:
                    fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n", 
                            __FILE__, __LINE__);
                    exit(1);
                } /* endswitch */
            } /* endif */
    } /* endif */

    /*** Operador Multiplicación/división */

    if (Op[OPER_MULTDIV].ocupado) {	/* Hay una operación pendiente */
        if (Op[OPER_MULTDIV].ciclo < Op[OPER_MULTDIV].Teval)
            Op[OPER_MULTDIV].ciclo++;	/* Si quedan ciclos por realizar */

        /*** VISUALIZACIÓN ****/
        sprintf(p_str, "M%d", Op[OPER_MULTDIV].ciclo);
        muestra_fase(p_str, RS[Op[OPER_MULTDIV].estacion].orden);
        /**********************/

        if (Op[OPER_MULTDIV].ciclo == Op[OPER_MULTDIV].Teval)
            if (!RegOp[OPER_MULTDIV].ocupado) {
                /* Sino hay pendiente un resultado anterior */            
                RegOp[OPER_MULTDIV].ocupado= SI;
                RegOp[OPER_MULTDIV].codigo= Op[OPER_MULTDIV].codigo;
                RegOp[OPER_MULTDIV].estacion= Op[OPER_MULTDIV].estacion;
                RegOp[OPER_MULTDIV].orden= 
                    RS[Op[OPER_MULTDIV].estacion].orden;

                Op[OPER_MULTDIV].ocupado= NO;

                s= RegOp[OPER_MULTDIV].estacion;

                /*** Estadisticas ***/
                estat.flops++;

                /* Cálculo del resultado */
                switch (RS[s].OP) {
                case OP_MUL_D:
                    RegOp[OPER_MULTDIV].valor.f= RS[s].Vj.f * RS[s].Vk.f;
                    break;
                case OP_DIV_D:
                    RegOp[OPER_MULTDIV].valor.f= RS[s].Vj.f / RS[s].Vk.f;
                    break;
                default:
                    fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n", 
                            __FILE__, __LINE__);
                    exit(1);
                } /* endswitch */
            } /* endif */
    } /* endif */

    /*** Tampones de lectura/escritura */

    if (Op[OPER_MEMDATOS].ocupado) {	/* Hay una operación de memoria pendiente */
        if (Op[OPER_MEMDATOS].ciclo < Op[OPER_MEMDATOS].Teval)
            Op[OPER_MEMDATOS].ciclo++;	/* Si quedan ciclos por realizar */

        /*** VISUALIZACIÓN ****/
        if (Op[OPER_MEMDATOS].estacion >= INICIO_TAMPON_LECT &&
            Op[OPER_MEMDATOS].estacion <= FIN_TAMPON_LECT)
            sprintf(p_str, "L%d", Op[OPER_MEMDATOS].ciclo);
        else
            sprintf(p_str, "S%d", Op[OPER_MEMDATOS].ciclo);
        muestra_fase(p_str, RS[Op[OPER_MEMDATOS].estacion].orden);
        /**********************/

        if (Op[OPER_MEMDATOS].ciclo == Op[OPER_MEMDATOS].Teval) {
            if (Op[OPER_MEMDATOS].estacion >= INICIO_TAMPON_LECT &&
                Op[OPER_MEMDATOS].estacion <= FIN_TAMPON_LECT) {
                if (!RegOp[OPER_MEMDATOS].ocupado) {
                    /* Sino hay pendiente un resultado anterior */
                    RegOp[OPER_MEMDATOS].ocupado= SI;
                    RegOp[OPER_MEMDATOS].codigo= Op[OPER_MEMDATOS].codigo;
                    RegOp[OPER_MEMDATOS].estacion= Op[OPER_MEMDATOS].estacion;
                    RegOp[OPER_MEMDATOS].orden= 
                        RS[Op[OPER_MEMDATOS].estacion].orden;

                    Op[OPER_MEMDATOS].ocupado= NO;

                    s= RegOp[OPER_MEMDATOS].estacion;
                  
                    /* Cálculo del resultado */                  
                    switch (RS[s].OP) {
                    case OP_LD:
                        if (!esta_alineada_dir_dword(TL[s].direccion))
                            RB[RegOp[OPER_MEMDATOS].codigo].excepcion= EXC_UNALIGN_MEM_DAT;
                        else
                            RegOp[OPER_MEMDATOS].valor.i= 
                                MD.m_dword[dir_dword(TL[s].direccion)];
                        break;
                    case OP_L_D:                        
                        if (!esta_alineada_dir_double(TL[s].direccion))
                            RB[RegOp[OPER_MEMDATOS].codigo].excepcion= EXC_UNALIGN_MEM_DAT;
                        else
                            RegOp[OPER_MEMDATOS].valor.f= 
                                MD.m_double[dir_double(TL[s].direccion)];
                        break;
                    default:
                        fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n", 
                                __FILE__, __LINE__);
                        exit(1);
                    } /* endswitch */
                  
                } /* endif */
            }
            else {
                Op[OPER_MEMDATOS].ocupado= NO;
                TE[Op[OPER_MEMDATOS].estacion].ocupado= NO;
            } /* endif */
        } /* endif */

        /* Escritura al final del último ciclo */

        if (Op[OPER_MEMDATOS].ciclo == Op[OPER_MEMDATOS].Teval &&
            Op[OPER_MEMDATOS].estacion >= INICIO_TAMPON_ESCR &&
            Op[OPER_MEMDATOS].estacion <= FIN_TAMPON_ESCR) {
            switch (RS[Op[OPER_MEMDATOS].estacion].OP) {
            case OP_SD:
                MD.m_dword[dir_dword(TE[Op[OPER_MEMDATOS].estacion].direccion)]= 
                    TE[Op[OPER_MEMDATOS].estacion].Vk.i; 
                mem_etiqueta(TE[Op[OPER_MEMDATOS].estacion].direccion, t_dword);
                break;
            case OP_S_D:
                MD.m_double[dir_double(TE[Op[OPER_MEMDATOS].estacion].direccion)]= 
                    TE[Op[OPER_MEMDATOS].estacion].Vk.f; 
                mem_etiqueta(TE[Op[OPER_MEMDATOS].estacion].direccion, t_double);
                break;
            } /* endswitch */
        } /* endif */
    } /* endif */
  
} /* end fase_EX_2 */

