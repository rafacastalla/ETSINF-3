
/**************************************************************************
 * 
 * Departamento de Informatica de Sistemas y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author:	Sergio Sáez (ssaez@disca.upv.es)
 *			Pedro López (plopez@disca.upv.es)
 * 
 * File: instrucciones.c
 *  
 * Description: Contiene las funciones necesarias para la imprimir las
 *    instrucciones
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

/***** Includes ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/***** Definiciones Externas **********************************/

#include "main.h"
#include "instrucciones.h"
#include "etiquetas.h"
#include "memoria.h"

/***** Funciones Exportables **********************************/

/***************************************************************
 *
 * Func: color_instruccion
 *
 * Desc: Devuelve un color
 *
 **************************************************************/

void color_instruccion(
        char *color,
        dword PC
) {
    static char *paleta[15] = {
            "red", "darkcyan", "orange", "limegreen", "deeppink", "royalblue", "brown", "seagreen",
            "lightcoral", "magenta", "salmon", "steelblue", "mediumseagreen", "darkorange", "orchid"
    };

    if (PC == -1) {
        sprintf(color, "lightgray");
        return;
    } /* endif */

    int index = te_busca(PC, m_instruc);

    strcpy(color, paleta[index % 15]);

} /* end color_instruccion */

/***************************************************************
 *
 * Func: imprime_instruccion
 *
 * Parametros:
 *	instruc  (char *) ;
 *
 * Descripción:
 *   Imprime la intrucción localizada en el PC sobre la
 *   cadena de caracteres 'instruc'
 *
 **************************************************************/

void imprime_instruccion_color(
        char *instruc,
        dword PC,
        boolean encolor
) {

    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char aux[128];
    char color[128];

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    if (PC == -1) {
        sprintf(instruc, "-nop-");
    } else {
        instruccion_t instruccion = lee_mem_instruc(PC);
        switch (instruccion.codop) {
            case OP_NOP:
                sprintf(instruc, "nop");
                break;
            case OP_TRAP:
                sprintf(instruc, "trap %d",
                        instruccion.inmediato);
                break;
            case OP_SYSCALL:
                sprintf(instruc, "syscall");
                break;
            case OP_LB:
                sprintf(instruc, "lb r%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_LBU:
                sprintf(instruc, "lbu r%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_SB:
                sprintf(instruc, "sb r%d,%d(r%d)",
                        instruccion.Rfuente2,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_LH:
                sprintf(instruc, "lh r%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_LHU:
                sprintf(instruc, "lhu r%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_SH:
                sprintf(instruc, "sw r%d,%d(r%d)",
                        instruccion.Rfuente2,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_LW:
                sprintf(instruc, "lw r%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_LWU:
                sprintf(instruc, "lwu r%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_SW:
                sprintf(instruc, "sw r%d,%d(r%d)",
                        instruccion.Rfuente2,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_LD:
                sprintf(instruc, "ld r%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_SD:
                sprintf(instruc, "sd r%d,%d(r%d)",
                        instruccion.Rfuente2,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_DADD:
                sprintf(instruc, "dadd r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_DSUB:
                sprintf(instruc, "dsub r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_DMUL:
                sprintf(instruc, "dmul r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_DDIV:
                sprintf(instruc, "ddiv r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_LUI:
                sprintf(instruc, "lui r%d, #%d",
                        instruccion.Rdestino,
                        instruccion.inmediato
                );
                break;
            case OP_AND:
                sprintf(instruc, "and r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_OR:
                sprintf(instruc, "or r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_XOR:
                sprintf(instruc, "xor r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_DSRA:
                sprintf(instruc, "dsrav r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_DSRL:
                sprintf(instruc, "dsrlv r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_DSLL:
                sprintf(instruc, "dsllv r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_SEQ:
                sprintf(instruc, "seq r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_SNE:
                sprintf(instruc, "sne r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_SGT:
                sprintf(instruc, "sgt r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_SGE:
                sprintf(instruc, "sge r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_SLT:
                sprintf(instruc, "slt r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_SLE:
                sprintf(instruc, "sle r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_DADDI:
                sprintf(instruc, "dadd r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_DSUBI:
                sprintf(instruc, "dsub r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_ANDI:
                sprintf(instruc, "and r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_ORI:
                sprintf(instruc, "or r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_XORI:
                sprintf(instruc, "xor r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_DSRAI:
                sprintf(instruc, "dsra r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_DSRLI:
                sprintf(instruc, "dsrl r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_DSLLI:
                sprintf(instruc, "dsll r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_SEQI:
                sprintf(instruc, "seq r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_SNEI:
                sprintf(instruc, "sne r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_SGTI:
                sprintf(instruc, "sgt r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_SGEI:
                sprintf(instruc, "sge r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_SLTI:
                sprintf(instruc, "slt r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_SLEI:
                sprintf(instruc, "sle r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.inmediato
                );
                break;
            case OP_BNEZ:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "bnez r%d,%s",
                        instruccion.Rfuente1,
                        aux);
                break;
            case OP_BEQZ:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "beqz r%d,%s",
                        instruccion.Rfuente1,
                        aux);
                break;
            case OP_BNE:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "bne r%d,r%d,%s",
                        instruccion.Rfuente1,
                        instruccion.Rfuente2,
                        aux);
                break;
            case OP_BEQ:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "beq  r%d,r%d,%s",
                        instruccion.Rfuente1,
                        instruccion.Rfuente2,
                        aux);
                break;
            case OP_BC1T:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "bc1t %s",
                        aux);
                break;
            case OP_BC1F:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "bc1f %s",
                        aux);
                break;
            case OP_MOVZ:
                sprintf(instruc, "movz r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2);
                break;
            case OP_MOVN:
                sprintf(instruc, "movn r%d,r%d,r%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_J:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "j %s",
                        aux);
                break;
            case OP_JAL:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "jal %s",
                        aux);
                break;
            case OP_JR:
                sprintf(instruc, "jr r%d",
                        instruccion.Rfuente1);
                break;
            case OP_JALR:
                te_etiqueta(aux, PC + 4 + instruccion.inmediato, m_instruc);
                sprintf(instruc, "jalr R%d,%s",
                        instruccion.Rfuente1,
                        aux);
                break;

            case OP_FP_ADD_D:
                sprintf(instruc, "add.d f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_SUB_D:
                sprintf(instruc, "sub.d f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_MUL_D:
                sprintf(instruc, "mul.d f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_DIV_D:
                sprintf(instruc, "div.d f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_ADD_S:
                sprintf(instruc, "add.s f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_SUB_S:
                sprintf(instruc, "sub.s f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_MUL_S:
                sprintf(instruc, "mul.s f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_DIV_S:
                sprintf(instruc, "div.s f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_ADD_PS:
                sprintf(instruc, "add.ps f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_SUB_PS:
                sprintf(instruc, "sub.ps f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_MUL_PS:
                sprintf(instruc, "mul.ps f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_DIV_PS:
                sprintf(instruc, "div.ps f%d,f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_L_D:
                sprintf(instruc, "l.d f%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_FP_S_D:
                sprintf(instruc, "s.d f%d,%d(r%d)",
                        instruccion.Rfuente2,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_FP_L_S:
                sprintf(instruc, "l.s f%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_FP_S_S:
                sprintf(instruc, "s.s f%d,%d(r%d)",
                        instruccion.Rfuente2,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_FP_L_PS:
                sprintf(instruc, "l.ps f%d,%d(r%d)",
                        instruccion.Rdestino,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_FP_S_PS:
                sprintf(instruc, "s.ps f%d,%d(r%d)",
                        instruccion.Rfuente2,
                        instruccion.inmediato,
                        instruccion.Rfuente1
                );
                break;
            case OP_FP_EQ_D:
                sprintf(instruc, "c.eq.d fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_NE_D:
                sprintf(instruc, "c.ne.d fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_LT_D:
                sprintf(instruc, "c.eq.d fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_LE_D:
                sprintf(instruc, "c.le.d fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_GT_D:
                sprintf(instruc, "c.gt.d fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_GE_D:
                sprintf(instruc, "c.ge.d fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_EQ_S:
                sprintf(instruc, "c.eq.s fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_NE_S:
                sprintf(instruc, "c.ne.s fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_LT_S:
                sprintf(instruc, "c.eq.s fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_LE_S:
                sprintf(instruc, "c.le.s fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_GT_S:
                sprintf(instruc, "c.gt.s fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_GE_S:
                sprintf(instruc, "c.ge.s fpsr,f%d,f%d",
                        //                instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2
                );
                break;
            case OP_FP_MOV_D:
                sprintf(instruc, "mov.d f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1
                );
                break;
            case OP_FP_MOV_S:
                sprintf(instruc, "mov.s f%d,f%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1
                );
                break;
                /*
               case OP_MFC1:
                    sprintf(instruc, "mfc1 r%d,f%d",
                            instruccion.Rdestino,
                            instruccion.Rfuente1
                            );
                    break;
               case OP_MTC1:
                    sprintf(instruc, "mtc1 f%d,r%d",
                            instruccion.Rdestino,
                            instruccion.Rfuente1
                            );
                    break;
                 */
            default:
                sprintf(instruc, "Inst desconocida r%d,r%d,r%d,#%d",
                        instruccion.Rdestino,
                        instruccion.Rfuente1,
                        instruccion.Rfuente2,
                        instruccion.inmediato
                );
                break;
        } /* endswitch */
    } /* endif */

    sprintf(aux, "%s", instruc);
    if (encolor == SI) {
        color_instruccion(color, PC);
        sprintf(instruc, "<font color=\"%s\">%s</font>", color, aux);
    } else {
        sprintf(instruc, "%s", aux);
    }

} /* end imprime_instruccion */
