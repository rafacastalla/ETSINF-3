/**************************************************************************
 *
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.
 *
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 *
 * File: memoria.c
 *
 * Description:
 *      Contiene las funciones de acceso a la memoria de datos e instrucciones.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "main.h"

#include "memoria.h"

/***************************************************************
 *
 * Func: mem_rango
 *
 ***************************************************************/
void mem_rango(dword dir, tipo_t tipo, dword *m_from, dword *m_to) {

    switch (tipo) {
        case t_byte:
            *m_from = dir_byte(dir) * sizeof(byte);
            *m_to = (*m_from) + sizeof(byte);
            break;
        case t_half:
            *m_from = dir_half(dir) * sizeof(half);
            *m_to = (*m_from) + sizeof(half);
            break;
        case t_word:
            *m_from = dir_word(dir) * sizeof(word);
            *m_to = (*m_from) + sizeof(word);
            break;
        case t_dword:
            *m_from = dir_dword(dir) * sizeof(dword);
            *m_to = (*m_from) + sizeof(dword);
            break;
        case t_float:
            *m_from = dir_float(dir) * sizeof(float);
            *m_to = (*m_from) + sizeof(float);
            break;
        case t_double:
            *m_from = dir_double(dir) * sizeof(double);
            *m_to = (*m_from) + sizeof(double);
            break;
        default:
            *m_from = (dir);
            *m_to = (*m_from) + 1;
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
    for (i = old_from; i < old_to; i++)
        md_tipo[i] = t_ninguno;

    mem_rango(dir, tipo, &new_from, &new_to);
    for (i = new_from; i < new_to; i++)
        md_tipo[i] = tipo;

} /* end mem_etiqueta */

valor_t lee_mem_datos(
        dword direccion,
        tipo_t tipo_dato
) {
    valor_t resultado;

    bzero(&resultado, sizeof(valor_t));

    switch (tipo_dato) {
        case t_byte:
            resultado.int_b = MD.m_byte[dir_byte(direccion)];
            break;
        case t_half:
            resultado.int_h = MD.m_half[dir_half(direccion)];
            break;
        case t_word:
            resultado.int_w = MD.m_word[dir_word(direccion)];
            break;
        case t_dword:
            resultado.int_d = MD.m_dword[dir_dword(direccion)];
            break;
        case t_float:
            resultado.fp_s = MD.m_float[dir_float(direccion)];
            break;
        case t_double:
            resultado.fp_d = MD.m_double[dir_double(direccion)];
            break;
        default:
	    fprintf(stderr, "ERROR: Tipo de datos incorrecto para lectura en memoria");
	    exit(1);	    
    }

    return resultado;
}

void escribe_mem_datos(
        dword direccion,
        valor_t valor,
        tipo_t tipo_dato
) {
    switch (tipo_dato) {
        case t_byte:
            MD.m_byte[dir_byte(direccion)] = valor.int_b;
            break;
        case t_half:
            MD.m_half[dir_half(direccion)] = valor.int_h;
            break;
        case t_word:
            MD.m_word[dir_word(direccion)] = valor.int_w;
            break;
        case t_dword:
            MD.m_dword[dir_dword(direccion)] = valor.int_d;
            break;
        case t_float:
            MD.m_float[dir_float(direccion)] = valor.fp_s;
            break;
        case t_double:
            MD.m_double[dir_double(direccion)] = valor.fp_d;
            break;
        default:
	    fprintf(stderr, "ERROR: Tipo de datos incorrecto para escritura en memoria");
	    exit(1);	    
    }

    mem_etiqueta(direccion, tipo_dato);
}

instruccion_t lee_mem_instruc(
        dword direccion
) {
    if (direccion % 4 != 0) {
        fprintf(stderr, "ERROR: Lectura desalineada en memoria de instrucciones (" F_DWORD ")\n", direccion);
        exit(1);
    }
    return MI[direccion / 4];
}

void escribe_mem_instruc(
        dword direccion,
        instruccion_t instruccion
) {
    if (direccion % 4 != 0) {
        fprintf(stderr, "ERROR: Escritura desalineada en memoria de instrucciones (" F_DWORD ")\n", direccion);
        exit(1);
    }
    MI[direccion / 4] = instruccion;
}
