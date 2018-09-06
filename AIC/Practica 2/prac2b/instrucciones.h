/*********************************************************************
 *
 * Arquitectura de Computadores.
 * Departamento de Informática de Sistemas y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 *
 * Autor: Sergio Sáez (ssaez@disca.upv.es)
 *	  Pedro López (plopez@gap.upv.es)
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

/* El c—digo de operaci—n de las operaciones aritmŽticas
 enteras con valores inmediatos son iguales a las que usan
 registros MçS UNO. Ver fichero input.lex.l */


#define OP_NOP       0
#define OP_TRAP 	 1

/*
No implementadas
#define OP_LB 		 10 
#define OP_LBU 		 11 
#define OP_LH 		 12 
#define OP_LHI 		 13 
#define OP_LHU 		 14 
*/
#define OP_LW 		 15 
/*
No implementadas
#define OP_SB 		 16 
#define OP_SH 		 17
*/
#define OP_SW 		 18 
 
/* Las versiones xxxU y xxxUI no est‡n implementadas */
#define OP_ADD 		 20
#define OP_ADDI 	 21
#define OP_ADDU 	 22 
#define OP_ADDUI 	 23
#define OP_SUB 		 24 
#define OP_SUBI 	 25 
#define OP_SUBU 	 26 
#define OP_SUBUI 	 27 
#define OP_AND 		 28
#define OP_ANDI 	 29 
#define OP_OR 		 30 
#define OP_ORI 		 31 
#define OP_XOR 		 32 
#define OP_XORI 	 33
#define OP_SLL 		 34 
#define OP_SLLI 	 35 
#define OP_SRA 		 36 
#define OP_SRAI 	 37 
#define OP_SRL 		 38 
#define OP_SRLI 	 39 
#define OP_SEQ 		 40 
#define OP_SEQI 	 41 
#define OP_SEQU 	 42 
#define OP_SEQUI 	 43 
#define OP_SGE 		 44 
#define OP_SGEI 	 45 
#define OP_SGEU 	 46 
#define OP_SGEUI 	 47 
#define OP_SGT 		 48 
#define OP_SGTI 	 49 
#define OP_SGTU 	 50 
#define OP_SGTUI 	 51 
#define OP_SLE 		 52 
#define OP_SLEI 	 53 
#define OP_SLEU 	 54 
#define OP_SLEUI 	 55 
#define OP_SLT 		 56 
#define OP_SLTI 	 57 
#define OP_SLTU 	 58 
#define OP_SLTUI 	 59 
#define OP_SNE 		 60 
#define OP_SNEI 	 61 
#define OP_SNEU 	 62 
#define OP_SNEUI 	 63 

/* Las J no est‡n implementadas */
#define OP_BEQZ 	 70 
#define OP_BNEZ 	 71
#define OP_J 		 72
#define OP_JAL 		 73
#define OP_JALR 	 74 
#define OP_JR 		 75 



/*** Macros ****************************************************************/

#define instruccion_entera(i) ((i) < 128)
#define instruccion_comaflotante(i) ((i) >= 128)

#define instruccion_carga_entera(i) ((i) == OP_LW)
// #define instruccion_aritmetica_entera(i) ((i) != OP_LW) && (i) != OP_SW))
#define inst_branch_int(i) ((i) == OP_BNEZ || (i) == OP_BEQZ)


#endif /* Include instrucciones.h */


