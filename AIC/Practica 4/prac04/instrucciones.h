/*********************************************************************
 *
 * Arquitectura de Computadores.
 * Departamento de Informática de Sistemas y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 *
 * Autor: Sergio Sáez (ssaez@disca.upv.es)
 *
 * Fichero: instrucciones.h
 * 
 * Descripción: 
 *   Contiene los códigos de las instrucciones implementadas
 *
 ***********************************************************************/

#ifndef instrucciones_H
#define instrucciones_H

/*** Includes **************************************************************/

#include "tipos.h"

/*** Defines ***************************************************************/

/* Enteras */

#define OP_NOP		0
#define OP_TRAP		1

#define OP_LD		64		
#define OP_SD		65		

#define PRI_ALU_INT     66

#define OP_DADD		66		
#define OP_DADDI	67		
#define OP_DSUB		68		
#define OP_DSUBI	69		

#define ULT_ALU_INT     95

#define OP_BEQZ		96
#define OP_BNEZ		97
#define OP_BEQ		98
#define OP_BNE		99

/* Coma flotante */

#define OP_L_D		128
#define OP_S_D		130

#define PRI_ALU_FP      132

#define OP_ADD_D	132
#define OP_SUB_D	134
#define OP_MUL_D	136
#define OP_DIV_D	138

#define PRI_FPSR        140
#define OP_C_GT_D       140
#define OP_C_LT_D       142
#define ULT_FPSR        142

#define ULT_ALU_FP      142

#define OP_BC1T         146
#define OP_BC1F         147

/*** Macros ****************************************************************/

#define inst_int(i) ((i) < 128)
#define inst_fp(i) ((i) >= 128)

#define inst_load_int(i) ((i) == OP_LD)
#define inst_load_fp(i) ((i) == OP_L_D)
#define inst_store_int(i) ((i) == OP_SD)
#define inst_store_fp(i) ((i) == OP_S_D)
#define inst_store(i) ((i) == OP_SD || (i) == OP_S_D)
#define inst_alu_int(i) ((i) >= PRI_ALU_INT && (i) <= ULT_ALU_INT)
#define inst_alu_fp(i) ((i) >= PRI_ALU_FP && (i) <= ULT_ALU_FP)

#define inst_fpsr(i) ((i) >= PRI_FPSR && (i) <= ULT_FPSR)

#define inst_comp_fp(i) ((i) == OP_C_GT_D || (i) == OP_C_LT_D)
#define inst_branch_int(i) ((i) == OP_BNEZ || (i) == OP_BEQZ)
#define inst_branch_fp(i)  ((i) == OP_BC1T || (i) == OP_BC1F)
#define inst_branch(i)  (inst_branch_int(i) || inst_branch_fp(i))

#endif /* Include instrucciones.h */


