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
#include "memoria.h"

#include "f_ejecucion.hi"
#include "tipos.h"

/***************************************************************
 *
 * Func: fase_EX_1
 *
 * Desc: Implementa la fase de ejecucion de los operadores
 * multiciclo. Comienza la ejecución de las operaciones que tienen
 * todos los operandos, y el operador libre.
 *
 **************************************************************/

void fase_EX_1() {
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    unsigned int oper;
    unsigned int oper_iniciadas[NUM_TIPOS_OPERADORES];

    boolean iniciada;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    for (oper = 0; oper < NUM_TIPOS_OPERADORES; oper++) {
        oper_iniciadas[oper] = 0;
    }

    for (oper = 0; oper < NUM_OPERADORES; oper++) {
        iniciada = NO;
        if (!Op[oper].ocupado) { /* Si el operador está libre */
            switch (Op[oper].tipo) {
                case OPER_ENTEROS:
                    if (oper_iniciadas[OPER_ENTEROS] >= NUM_INICIO_ENTEROS)
                        break;
                    iniciada = fase_EX_1_ENTEROS(oper);
                    break;
                case OPER_SUMREST:
                    if (oper_iniciadas[OPER_SUMREST] >= NUM_INICIO_SUMREST)
                        break;
                    iniciada = fase_EX_1_SUMREST(oper);
                    break;
                case OPER_MULTDIV:
                    if (oper_iniciadas[OPER_MULTDIV] >= NUM_INICIO_MULTDIV)
                        break;
                    iniciada = fase_EX_1_MULTDIV(oper);
                    break;
                case OPER_DIRECCIONES:
                    if (oper_iniciadas[OPER_DIRECCIONES] >= NUM_INICIO_DIRECCIONES)
                        break;
                    iniciada = fase_EX_1_DIRECCIONES(oper);
                    break;
                case OPER_MEMDATOS:
                    if (oper_iniciadas[OPER_MEMDATOS] >= NUM_INICIO_MEMDATOS)
                        break;
                    iniciada = fase_EX_1_MEMDATOS(oper);
                    break;
                default:
                    fprintf(stderr, "ERROR (%s:%d): Operador no implementado\n",
                            __FILE__, __LINE__);
                    exit(1);
                    break;
            }

            if (iniciada)
                oper_iniciadas[Op[oper].tipo]++;
        }
    }
}

boolean fase_EX_1_ENTEROS(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s, r;

    ciclo_t siguiente;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    s = TAM_ESTACIONES;
    siguiente = MAX_ORDEN;

    /*** Busca la instrucción más antigua que este preparada */

    for (r = INICIO_RS_ENTEROS;
         r <= FIN_RS_ENTEROS; r++) {
        if (!RS[r].ocupado || RS[r].estado != PENDIENTE)
            continue;

        if (RS[r].Qj == MARCA_NULA &&
            RS[r].Qk == MARCA_NULA &&
            /* Tiene todos los operandos disponibles */
            RS[r].orden < siguiente) {
            siguiente = RS[r].orden;
            s = r;
        } /* endif */
    } /* endfor */

    /*** Entra en ejecución la operación más antigua, si existe */

    if (s < TAM_ESTACIONES) {
        Op[oper].ocupado = SI;
        Op[oper].ciclo = 0;
        Op[oper].codigo = RS[s].rob;
        Op[oper].estacion = s;
        RS[s].estado = EN_CURSO;
        RS[s].operador = oper;

        return SI;
    } /* endif */

    return NO;

} /* end fase_EX_1_ENTEROS */

boolean fase_EX_1_SUMREST(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s, r;

    ciclo_t siguiente;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    s = TAM_ESTACIONES;
    siguiente = MAX_ORDEN;

    /*** Busca la instrucción más antigua que este preparada */

    for (r = INICIO_RS_SUMA_RESTA;
         r <= FIN_RS_SUMA_RESTA; r++) {
        if (!RS[r].ocupado || RS[r].estado != PENDIENTE)
            continue;

        if (RS[r].Qj == MARCA_NULA &&
            RS[r].Qk == MARCA_NULA &&
            /* Tiene todos los operandos disponibles */
            RS[r].orden < siguiente) {
            siguiente = RS[r].orden;
            s = r;
        } /* endif */
    } /* endfor */

    /*** Entra en ejecución la operación más antigua, si existe */

    if (s < TAM_ESTACIONES) {
        Op[oper].ocupado = SI;
        Op[oper].ciclo = 0;
        Op[oper].codigo = RS[s].rob;
        Op[oper].estacion = s;
        RS[s].estado = EN_CURSO;
        RS[s].operador = oper;

        return SI;
    } /* endif */

    return NO;

} /* end fase_EX_1_SUMREST */

boolean fase_EX_1_MULTDIV(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s, r;

    ciclo_t siguiente;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    s = TAM_ESTACIONES;
    siguiente = MAX_ORDEN;

    /*** Busca la instrucción más antigua que este preparada */

    for (r = INICIO_RS_MULT_DIV;
         r <= FIN_RS_MULT_DIV; r++) {
        if (!RS[r].ocupado || RS[r].estado != PENDIENTE)
            continue;

        if (RS[r].Qj == MARCA_NULA &&
            RS[r].Qk == MARCA_NULA &&
            /* Tiene todos los operandos disponibles */
            RS[r].orden < siguiente) {

            siguiente = RS[r].orden;
            s = r;
        } /* endif */
    } /* endfor */

    /*** Entra en ejecución la operación más antigua, si existe */

    if (s < TAM_ESTACIONES) {
        Op[oper].ocupado = SI;
        Op[oper].ciclo = 0;
        Op[oper].codigo = RS[s].rob;
        Op[oper].estacion = s;
        RS[s].estado = EN_CURSO;
        RS[s].operador = oper;

        return SI;
    } /* endif */

    return NO;

} /* end fase_EX_1_MULTDIV */

boolean fase_EX_1_DIRECCIONES(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s, r;

    ciclo_t siguiente;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    s = TAM_ESTACIONES;
    siguiente = MAX_ORDEN;

    /*** Busca la instrucción más antigua que este preparada */

    for (r = INICIO_TAMPONES;
         r <= FIN_TAMPONES; r++) {
        if (!RS[r].ocupado || RS[r].estado != PENDIENTE)
            continue;

        if (RS[r].Qj == MARCA_NULA &&
            /* Tiene todos los operandos disponibles */
            RS[r].orden < siguiente) {
            siguiente = RS[r].orden;
            s = r;
        } /* endif */
    } /* endfor */

    /*** Entra en ejecución la operación más antigua, si existe */

    if (s < TAM_ESTACIONES) {
        Op[oper].ocupado = SI;
        Op[oper].ciclo = 0;
        Op[oper].codigo = RS[s].rob; // Se utiliza para las excepciones
        Op[oper].estacion = s;
        RS[s].estado = EN_CURSO;
        RS[s].operador = oper;

        return SI;
    } /* endif */

    return NO;

} /* end fase_EX_1_DIRECCIONES */

boolean fase_EX_1_MEMDATOS(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s, r, t;

    ciclo_t siguiente;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    s = TAM_ESTACIONES;
    siguiente = MAX_ORDEN;

    /*** Busca la instrucción más antigua que este preparada */

    for (r = INICIO_TAMPON_LECT;
         r <= FIN_TAMPON_LECT; r++) {
        if (!TL[r].ocupado || TL[r].estado != PREPARADA)
            continue;

        /* Comprueba que no haya ninguna escritura pendiente en la misma
         * dirección */
        /* No comprueba si las escrituras sin la dirección
           calculada porque como las direcciones se calculan en
           orden esa escritura será posterior a la lectura. REVISAR
         */
        for (t = INICIO_TAMPON_ESCR;
             t <= FIN_TAMPON_ESCR; t++) {
            if (TE[t].ocupado && TE[t].estado != PENDIENTE &&
                TE[t].direccion == TL[r].direccion &&
                TE[t].orden < TL[r].orden) {
                if (dep_mem == l_forwarding &&
                    TE[t].Qk == MARCA_NULA) {
                    /* Load forwarding */
                    TL[r].estado = FINALIZADA;
                    TL[r].resultado = TE[t].Vk;
                } /* endif */
                break;
            } /* endif */
        } /* endfor */

        if (t > FIN_TAMPON_ESCR) { /* No hay conflictos con ninguna escritura */
            if (TL[r].orden < siguiente) {
                siguiente = TL[r].orden;
                s = r;
            } /* endif */
        }
    } /* endfor */

    for (r = INICIO_TAMPON_ESCR;
         r <= FIN_TAMPON_ESCR; r++) {
        if (!TE[r].ocupado || !TE[r].confirm || TE[r].estado == EN_CURSO)
            continue;

        if (TE[r].Qj == MARCA_NULA &&
            TE[r].orden < siguiente) {
            siguiente = TE[r].orden;
            s = r;
        } /* endif */
    } /* endfor */

    /*** Entra en ejecución la operación más antigua, si existe */

    if (s < TAM_ESTACIONES) {
        Op[oper].ocupado = SI;
        Op[oper].ciclo = 0;
        Op[oper].codigo = RS[s].rob; /* RS = TL = TE */
        Op[oper].estacion = s;
        RS[s].estado = EN_CURSO;
        RS[s].operador = oper;

        return SI;
    } /* endif */

    return NO;

} /* end fase_EX_1_MEMDATOS */

/***************************************************************
 *
 * Func: fase_EX_2
 *
 * Desc: Implementa la fase de ejecucion de los operadores
 * multiciclo. Avanza la ejecución de las operaciones que se están
 * ejecutando en cada operador.
 *
 **************************************************************/

void fase_EX_2() {
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    unsigned int oper;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    for (oper = 0; oper < NUM_OPERADORES; oper++) {
        if (Op[oper].ocupado) { /* Si el operador está ocupado */
            switch (Op[oper].tipo) {
                case OPER_ENTEROS:
                    fase_EX_2_ENTEROS(oper);
                    break;
                case OPER_SUMREST:
                    fase_EX_2_SUMREST(oper);
                    break;
                case OPER_MULTDIV:
                    fase_EX_2_MULTDIV(oper);
                    break;
                case OPER_DIRECCIONES:
                    fase_EX_2_DIRECCIONES(oper);
                    break;
                case OPER_MEMDATOS:
                    fase_EX_2_MEMDATOS(oper);
                    break;
                default:
                    fprintf(stderr, "ERROR (%s:%d): Operador no implementado\n",
                            __FILE__, __LINE__);
                    exit(1);
                    break;
            }
        }
    }
}

void fase_EX_2_ENTEROS(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    if (Op[oper].ciclo < Op[oper].Teval)
        Op[oper].ciclo++; /* Si quedan ciclos por realizar */

    s = Op[oper].estacion;

    /*** VISUALIZACIÓN ****/
    sprintf(p_str, "E%d", Op[oper].ciclo);
    muestra_fase(p_str, RS[s].orden);
    /**********************/

    if (Op[oper].ciclo == Op[oper].Teval) {
        RS[s].estado = FINALIZADA;
        Op[oper].ocupado = NO;

        /* Cálculo del resultado */
        switch (RS[s].OP) {
            case OP_DADD:
            case OP_DADDI:
                RS[s].resultado.int_d = RS[s].Vj.int_d + RS[s].Vk.int_d;
                break;
            case OP_DSUB:
            case OP_DSUBI:
                RS[s].resultado.int_d = RS[s].Vj.int_d - RS[s].Vk.int_d;
                break;
            case OP_BC1F:
            case OP_BEQZ:
            case OP_BEQ:
                RS[s].resultado.int_d = (RS[s].Vj.int_d == RS[s].Vk.int_d);
                break;
            case OP_BC1T:
            case OP_BNEZ:
            case OP_BNE:
                RS[s].resultado.int_d = (RS[s].Vj.int_d != RS[s].Vk.int_d);
                break;
            default:
                fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n",
                        __FILE__, __LINE__);
                exit(1);
        } /* endswitch */
    } /* endif */

}

void fase_EX_2_SUMREST(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    if (Op[oper].ciclo < Op[oper].Teval)
        Op[oper].ciclo++; /* Si quedan ciclos por realizar */

    s = Op[oper].estacion;

    /*** VISUALIZACIÓN ****/
    sprintf(p_str, "A%d", Op[oper].ciclo);
    muestra_fase(p_str, RS[s].orden);
    /**********************/

    if (Op[oper].ciclo == Op[oper].Teval) {
        RS[s].estado = FINALIZADA;
        Op[oper].ocupado = NO;

        /*** Estadisticas ***/
        estat.flops++;

        /* Cálculo del resultado */
        switch (RS[s].OP) {
            case OP_FP_ADD_D:
                RS[s].resultado.fp_d = RS[s].Vj.fp_d + RS[s].Vk.fp_d;
                break;
            case OP_FP_SUB_D:
                RS[s].resultado.fp_d = RS[s].Vj.fp_d - RS[s].Vk.fp_d;
                break;
            case OP_FP_GT_D:
                RS[s].resultado.int_d = (RS[s].Vj.fp_d > RS[s].Vk.fp_d);
                break;
            case OP_FP_LT_D:
                RS[s].resultado.int_d = (RS[s].Vj.fp_d < RS[s].Vk.fp_d);
                break;
            default:
                fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n",
                        __FILE__, __LINE__);
                exit(1);
        } /* endswitch */
    } /* endif */

}

void fase_EX_2_MULTDIV(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    if (Op[oper].ciclo < Op[oper].Teval)
        Op[oper].ciclo++; /* Si quedan ciclos por realizar */

    s = Op[oper].estacion;

    /*** VISUALIZACIÓN ****/
    sprintf(p_str, "M%d", Op[oper].ciclo);
    muestra_fase(p_str, RS[s].orden);
    /**********************/

    if (Op[oper].ciclo == Op[oper].Teval) {
        RS[s].estado = FINALIZADA;
        Op[oper].ocupado = NO;

        /*** Estadisticas ***/
        estat.flops++;

        /* Cálculo del resultado */
        switch (RS[s].OP) {
            case OP_FP_MUL_D:
                RS[s].resultado.fp_d = RS[s].Vj.fp_d * RS[s].Vk.fp_d;
                break;
            case OP_FP_DIV_D:
                RS[s].resultado.fp_d = RS[s].Vj.fp_d / RS[s].Vk.fp_d;
                break;
            default:
                fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n",
                        __FILE__, __LINE__);
                exit(1);
        } /* endswitch */
    } /* endif */

}

void fase_EX_2_DIRECCIONES(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /*** Cálculo de la dirección efectiva */

    if (Op[oper].ciclo < Op[oper].Teval)
        Op[oper].ciclo++; /* Si quedan ciclos por realizar */

    s = Op[oper].estacion;

    /*** VISUALIZACIÓN ****/
    if (Op[oper].Teval > 1) {
        sprintf(p_str, "AC%d", Op[oper].ciclo);
    } else {
        sprintf(p_str, "AC");
    }
    muestra_fase(p_str, RS[s].orden);
    /**********************/

    if (Op[oper].ciclo == Op[oper].Teval) {
        Op[oper].ocupado = NO;

        RS[s].direccion = RS[s].Vj.int_d + RS[s].desplazamiento;

        if (ES_ESTACION(s, TAMPON_LECT)) {
            TL[s].estado = PREPARADA;
            if (!esta_alineada_dir_dword(TL[s].direccion)) {
                TL[s].excepcion = EXC_UNALIGN_MEM_DAT;
                TL[s].estado = FINALIZADA;
            } else if (!EN_MEMORIA(TL[s].direccion, SegDatos)) {
                TL[s].excepcion = EXC_OUT_MEM_DAT;
                TL[s].estado = FINALIZADA;
            }
        } else {
            TE[s].estado = PREPARADA;
            if (!esta_alineada_dir_dword(TE[s].direccion)) {
                TE[s].excepcion = EXC_UNALIGN_MEM_DAT;
            } else if (!EN_MEMORIA(TE[s].direccion, SegDatos)) {
                TE[s].excepcion = EXC_OUT_MEM_DAT;
            }
        }

    } /* endif */

}

void fase_EX_2_MEMDATOS(unsigned int oper) {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    marca_t s;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    if (Op[oper].ciclo < Op[oper].Teval)
        Op[oper].ciclo++; /* Si quedan ciclos por realizar */

    s = Op[oper].estacion;

    /*** VISUALIZACIÓN ****/
/*
    if (ES_ESTACION(s, TAMPON_LECT)) {
        sprintf(p_str, "L%d", Op[oper].ciclo);
    } else {
        sprintf(p_str, "S%d", Op[oper].ciclo);
    }
*/
    sprintf(p_str, "L%d", Op[oper].ciclo);
    muestra_fase(p_str, RS[s].orden);
    /**********************/

    if (Op[oper].ciclo == Op[oper].Teval) {

        if (ES_ESTACION(s, TAMPON_LECT)) {

            TL[s].estado = FINALIZADA;
            Op[oper].ocupado = NO;

            /* Cálculo del resultado */
            switch (RS[s].OP) {
                case OP_LD:
                    TL[s].resultado = lee_mem_datos(TL[s].direccion, t_dword);
                    break;
                case OP_FP_L_D:
                    TL[s].resultado = lee_mem_datos(TL[s].direccion, t_double);
                    break;
                default:
                    fprintf(stderr, "ERROR (%s:%d): Operacion no implementada\n",
                            __FILE__, __LINE__);
                    exit(1);
            } /* endswitch */

        } else {
            Op[oper].ocupado = NO;

            TE[s].ocupado = NO; /* El operador libera la estación de reserva */

            /* Escritura al final del último ciclo */

            switch (RS[s].OP) {
                case OP_SD:
                    escribe_mem_datos(TE[s].direccion, TE[s].Vk, t_dword);
                    break;
                case OP_FP_S_D:
                    escribe_mem_datos(TE[s].direccion, TE[s].Vk, t_double);
                    break;
            } /* endswitch */
        } /* endif */
    } /* endif */

}

