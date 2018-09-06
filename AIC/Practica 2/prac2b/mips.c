/***************************************************************************
 *
 * Arquitectura de Computadores.
 * Departamento de Inform�tica de Sistemas y Computadores (DISCA)
 * Universidad Polit�cnica de Valencia.
 *
 * Autor: Sergio S�ez (ssaez@disca.upv.es)
 *	  Pedro L�pez (plopez@gap.upv.es)
 *
 * Fichero: mips.c
 *
 * Descripci�n:
 *   Contiene la descripcion de las fases del DLX basico
 *
 ****************************************************************************/

#define mips_C

/*** Includes **************************************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*** Definiciones Externas *************************************************/

#include "tipos.h"
#include "main.h"
#include "instrucciones.h"
#include "presentacion-html.h"

/*** Variables Globales ****************************************************/

/*** Variables Locales *****************************************************/

/*** Funciones Locales *****************************************************/

/***************************************************************
 *
 * Func: pasar_a_ID_NOP
 *
 * Desc: La fase IF entrega un NOP a la fase ID al pr�ximo ciclo
 *
 **************************************************************/
void pasar_a_ID_NOP (
    )
{
//    IF_IDn.NPC = ;
    IF_IDn.IR.codop = OP_NOP;
    IF_IDn.IR.tipo= FormatoR;
    IF_IDn.IR.Rfuente1 = 0;
    IF_IDn.IR.Rfuente2 = 0;
    IF_IDn.IR.Rdestino = 0;
    IF_IDn.IR.inmediato = 0;
    IF_IDn.iPC = -1;
    IF_IDn.orden = -1;
}  /* pasar_ID_NOP */


/***************************************************************
 *
 * Func: pasar_a_EX_NOP
 *
 * Desc: La fase ID entrega un NOP a la fase EX al pr�ximo ciclo
 *
 **************************************************************/
void pasar_a_EX_NOP (
    )
{
    ID_EXn.Ra = 0;
    ID_EXn.Rb = 0;
    ID_EXn.Imm = 0;
//    ID_EXn.NPC = ; no lo toco
    ID_EXn.IR.codop = OP_NOP;
    ID_EXn.IR.tipo= FormatoR;
    ID_EXn.IR.Rfuente1 = 0;
    ID_EXn.IR.Rfuente2 = 0;
    ID_EXn.IR.Rdestino = 0;
    ID_EXn.IR.inmediato = 0;
    ID_EXn.iPC = -1;
    ID_EXn.orden = -1;
} /* pasar_a_EX_NOP */


/***************************************************************
 *
 * Func: pasar_a_MEM_NOP
 *
 * Desc: La fase EX entrega un NOP a la fase MEM al pr�ximo ciclo
 *
 **************************************************************/
void pasar_a_MEM_NOP (
    )
{
    EX_MEMn.ALUout = 0;
    EX_MEMn.data = 0;
    EX_MEMn.cond = 0;
//    IF_IDn.NPC = ; no lo toco
    EX_MEMn.IR.codop = OP_NOP;
    EX_MEMn.IR.tipo= FormatoR;
    EX_MEMn.IR.Rfuente1 = 0;
    EX_MEMn.IR.Rfuente2 = 0;
    EX_MEMn.IR.Rdestino = 0;
    EX_MEMn.IR.inmediato = 0;
    EX_MEMn.iPC = -1;
    EX_MEMn.orden = -1;
} /* pasar_a_MEM_NOP */


/***************************************************************
 *
 * Func: hay_fuente1_ID
 *
 * Desc: Indica si en la fase ID hay una instrucci�n que
 *       tiene Rfte1
 *
 **************************************************************/
boolean hay_fuente1_ID (
    )
{
    return (
        ((IF_ID.IR.codop != OP_NOP) &&
         (IF_ID.IR.codop != OP_TRAP))
        );
} /* hay_fuente1_ID */


/***************************************************************
 *
 * Func: hay_fuente2_ID
 *
 * Desc: Indica si en la fase ID hay una instrucci�n que
 *       tiene Rfte2
 *
 **************************************************************/
boolean hay_fuente2_ID (
    )
{
    return (
        ((IF_ID.IR.codop != OP_NOP) &&
         (IF_ID.IR.codop != OP_TRAP) &&
         ((IF_ID.IR.tipo == FormatoR) ||
          (IF_ID.IR.codop == OP_SW)))
	);
} /* hay_fuente2_ID */


/***************************************************************
 *
 * Func: hay_fuente1_EX
 *
 * Desc: Indica si en la fase EX hay una instrucci�n que
 *       tiene Rfte1
 *
 **************************************************************/
boolean hay_fuente1_EX (
    )
{
    return (
        ((ID_EX.IR.codop != OP_NOP) &&
         (ID_EX.IR.codop != OP_TRAP))
	);
} /* hay_fuente1_EX */


/***************************************************************
 *
 * Func: hay_fuente2_EX
 *
 * Desc: Indica si en la fase EX hay una instrucci�n que
 *       tiene Rfte2
 *
 **************************************************************/
boolean hay_fuente2_EX (
    )
{
    return (
        ((ID_EX.IR.codop != OP_NOP) &&
         (ID_EX.IR.codop != OP_TRAP) &&
         (ID_EX.IR.codop != OP_LW) &&
         (ID_EX.IR.tipo == FormatoR))
	);
} /* hay_fuente2_EX */


/***************************************************************
 *
 * Func: hay_destino_EX
 *
 * Desc: Indica si en la fase EX hay una instrucci�n que
 *       tiene Rdst
 *
 **************************************************************/
boolean hay_destino_EX (
    )
{
    return (
        ((ID_EX.IR.codop != OP_NOP) &&
         (ID_EX.IR.codop != OP_TRAP) &&
         (ID_EX.IR.codop != OP_SW) &&
         (ID_EX.IR.codop != OP_BEQZ) &&
         (ID_EX.IR.codop != OP_BNEZ))
        );
} /* hay_destino_EX */


/***************************************************************
 *
 * Func: hay_destino_MEM
 *
 * Desc: Indica si en la fase MEM hay una instrucci�n que
 *       tiene Rdst
 *
 **************************************************************/
boolean hay_destino_MEM (
    )
{
    return (
        ((EX_MEM.IR.codop != OP_NOP) &&
         (EX_MEM.IR.codop != OP_TRAP) &&
         (EX_MEM.IR.codop != OP_SW) &&
         (EX_MEM.IR.codop != OP_BEQZ) &&
         (EX_MEM.IR.codop != OP_BNEZ))
        );
} /* hay_destino_MEM */


/***************************************************************
 *
 * Func: hay_destino_WB
 *
 * Desc: Indica si en la fase WB hay una instrucci�n que
 *       tiene Rdst
 *
 **************************************************************/
boolean hay_destino_WB (
    )
{
    return (
        ((MEM_WB.IR.codop != OP_NOP) &&
         (MEM_WB.IR.codop != OP_TRAP) &&
         (MEM_WB.IR.codop != OP_SW) &&
         (MEM_WB.IR.codop != OP_BEQZ) &&
         (MEM_WB.IR.codop != OP_BNEZ))
        );
}  /* hay_destino_WB */


/***************************************************************
 *
 * Func: operacion_ALU
 *
 * Desc: Realiza la operacion en el operador aritm�tico
 *
 **************************************************************/
dword operacion_ALU (byte codop, dword in1, dword in2)

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    dword		result;
    ciclo_t		tmp;


    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    switch (codop) {
    case OP_NOP:
    case OP_TRAP:
    case OP_ADD:
    case OP_ADDI:
        result = in1 + in2;
        break;
    case OP_SUB:
    case OP_SUBI:
        result = in1 - in2;
        break;
    case OP_AND:
    case OP_ANDI:
        result = in1 & in2;
        break;
    case OP_OR:
    case OP_ORI:
        result = in1 | in2;
        break;
    case OP_XOR:
    case OP_XORI:
        result = in1 ^ in2;
        break;
    case OP_SRA:
    case OP_SRAI:
        result = in1 >> (in2 & 0x1f);
        break;
    case OP_SLL:
    case OP_SLLI:
        result = in1 << (in2 & 0x1f);
        break;
    case OP_SRL:
    case OP_SRLI:
        tmp = in1;
        tmp >>= (in2 & 0x1f);
        result = tmp;
        break;
    case OP_SEQ:
    case OP_SEQI:
        result = (in1 == in2);
        break;
    case OP_SNE:
    case OP_SNEI:
        result = (in1 != in2);
        break;
    case OP_SGT:
    case OP_SGTI:
        result = (in1 > in2);
        break;
    case OP_SLT:
    case OP_SLTI:
        result = (in1 < in2);
        break;
    case OP_SGE:
    case OP_SGEI:
        result = (in1 >= in2);
        break;
    case OP_SLE:
    case OP_SLEI:
        result = (in1 <= in2);
        break;
    case OP_LW:
    case OP_SW:
    case OP_BEQZ: /* OJO, no con ds1 */
    case OP_BNEZ:
        result = in1 + in2;
        break;
    default:
        fprintf(stderr,
                "ERROR (%d %d): Operacion no implementada\n",
                __LINE__,ID_EX.IR.codop);
        exit(1);
    } /* endswitch */

    return (result);
} /* end operacion_ALU */


/***************************************************************
 *
 * Func: operacion_COMP
 *
 * Desc: Realiza la operacion en el comparador de la fase EX
 *
 **************************************************************/
dword operacion_COMP (byte codop, dword in1)
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    dword		result;


    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    /*** Operacion en el comparador */
    switch (codop) {
    case OP_BEQZ: /* OJO, no con ds1 */
        if (in1 == 0)
            result = 1;
        else
            result = 0;
        break;
    case OP_BNEZ:  /* OJO, no con ds1 */
        if (in1 != 0)
            result = 1;
        else
            result = 0;
        break;
    default:
        result = 0; /* No salta */
    } /* endswitch */
    return (result);
} /* end operacion_COMP */


/***************************************************************
 *
 * Func: mux_ALUsup
 *
 * Desc: Implementa el multiplexor superior de la ALU
 *
 **************************************************************/
dword mux_ALUsup (dword npc, dword ra, dword mem, dword wb)

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    dword		result;

    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    switch (ID_EX.IR.codop) {
    case OP_BNEZ: /* si es un salto */
    case OP_BEQZ:
        result = npc;
        break;
    default: /* el resto de instrucciones */
        result = ra; /* por defecto */
        switch (solucion_riesgos_datos) {
        case ninguno:
        case parada:
            break;

            case cortocircuito:
               /* Los cortocircuitos desde MEM tienen prioridad sobre WB, ya
                  que la instruccion que hay en MEM es mas moderna */

               /*** Insertar codigo ***/

               // WBtoEX

               if (hay_fuente1_EX() && hay_destino_WB() &&
                   ID_EX.IR.Rfuente1 == MEM_WB.IR.Rdestino)
               {
                   WBaEXalu_s = SI;
                   result = wb;
               }

               if (hay_fuente2_EX() && hay_destino_WB() &&
                   ID_EX.IR.Rfuente2 == MEM_WB.IR.Rdestino)
               {
                   WBaEXalu_s = SI;
                   result = wb;
               }

               // MEMtoEX

               if (hay_fuente1_EX() && hay_destino_MEM() &&
                   ID_EX.IR.Rfuente1 == EX_MEM.IR.Rdestino)
               {
                   MEMaEXalu_s = SI;
                   result = mem;
               }

               if (hay_fuente2_EX() && hay_destino_MEM() &&
                   ID_EX.IR.Rfuente2 == EX_MEM.IR.Rdestino)
               {
                   MEMaEXalu_s = SI;
                   result = mem;
               }

            break;
        }
    }
    return (result);
} /* end mux_ALUsup */


/***************************************************************
 *
 * Func: mux_ALUinf
 *
 * Desc: Implementa el multiplexor inferior de la ALU
 *
 **************************************************************/
dword mux_ALUinf (dword rb, dword imm, dword mem, dword wb)

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    dword		result;

    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    switch (ID_EX.IR.codop) {
    case OP_BNEZ: /* si es un salto */
    case OP_BEQZ:
        result = imm;
        break;
    default: /* el resto de instrucciones */
        switch (ID_EX.IR.tipo) {
        case FormatoR:
            result = rb;
            break;
        case FormatoI:
            result = imm;
            break;
        default:
            fprintf(stderr, "ERROR (%d): Formato no implementado\n",__LINE__);
            exit(1);
        } /* endswitch */

        switch (solucion_riesgos_datos) {
        case ninguno:
        case parada:
            break;
        case cortocircuito:
            /* Los cortocircuitos desde MEM tienen prioridad sobre WB, ya
               que la instruccion que hay en MEM es mas moderna */

            /*** Eliminado para la practica ***/
            // WBtoEX
            /*
            if (...)
            {
                WBaEXalu_i = SI;
                result = wb;
            }

            // MEMtoEX
            if (...)
            {
                MEMaEXalu_i = SI;
                result = mem;
            }
            */
            break;
        }
    }
    return (result);
} /* end mux_ALUinf */


/***************************************************************
 *
 * Func: mux_COMP
 *
 * Desc: Implementa el multiplexor superior del COMP de la fase EX
 *
 **************************************************************/
dword mux_COMP (dword ra, dword mem, dword wb)

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    dword		result;

    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/


    result = ra; /* por defecto */

    switch (solucion_riesgos_datos) {
    case ninguno:
    case parada:
        break;
    case cortocircuito:

        /*** Eliminado para la practica ***/
        // WBtoEX
        if (hay_destino_WB() && hay_fuente1_EX() &&
            MEM_WB.IR.Rdestino == ID_EX.IR.Rfuente1)
        {
            WBaEXcomp = SI;
            result = wb;
        }

        // MEMtoEX
        if (hay_destino_MEM() && hay_fuente1_EX() &&
            EX_MEM.IR.Rdestino == ID_EX.IR.Rfuente1)
        {
            MEMaEXcomp = SI;
            result = mem;
        }
        break;
    }

    return (result);
} /* end mux_COMP */



/***************************************************************
 *
 * Func: mux_EXmem
 *
 * Desc: Implementa el multiplexor hacia memoria de la fase EX
 *
 **************************************************************/
dword mux_EXmem (word rb, word wb)
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    word		result;


    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/


    result = rb; /* por defecto */

    switch (solucion_riesgos_datos) {
    case ninguno:
    case parada:
        break;
    case cortocircuito:

        /*** Eliminado para la practica ***/
		/*
        // WBtoEX
        if (...)
    	{
    	    WBaEXmem = SI;
    	    result = wb;
    	}  */

        /* MEMtoEX */
        /* No hace falta. WBtoMEM lo resuelve */
        break;
    }
    return (result);
} /* end mux_EXmem */


/***************************************************************
 *
 * Func: mux_MEMmem
 *
 * Desc: Implementa el multiplexor hacia memoria de la fase MEM
 *
 **************************************************************/
dword mux_MEMmem (dword rb, dword wb)

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    dword		result;


    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/


    result = rb; /* por defecto */

    switch (solucion_riesgos_datos) {
    case ninguno:
    case parada:
        break;
    case cortocircuito:

        /*** Eliminado para la practica ***/
        /*
		// WBtoMEM
        if (...)
        {
            WBaMEM = SI;
            result = wb;
        } */
        break;
    }
    return (result);
} /* end mux_MEMmem */



/***************************************************************
 *
 * Func: mux_COMPid
 *
 * Desc: Implementa el multiplexor del COMP de la fase ID
 *
 **************************************************************/
dword mux_COMPid (dword ra, dword mem, dword wb)

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    dword		result;


    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    result = ra; /* por defecto */

    switch (solucion_riesgos_datos) {

    case ninguno:
    case parada:
        break;
    case cortocircuito:

        /*** Eliminado para la practica ***/
		/*
        // MEMtoID
        if (...)
        {
            MEMaID = SI;
            result = mem;
		} */
		break;
    }
    return (result);
} /* end mux_COMPid */



/*** Funciones Exportables *************************************************/

/***************************************************************
 *
 * Func: fase_busqueda
 *
 * Desc: Implementa la fase IF
 *
 **************************************************************/
void fase_busqueda (
    )
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/


    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    init_instruc(PC, orden);      /*** VISUALIZACI�N ***/

    IF_IDn.IR = MI[PC];		/* Busca la siguiente instrucci�n */
    IF_IDn.NPC = PC+1;

    IF_IDn.iPC= PC;		/* Visualizaci�n */
    IF_IDn.orden= orden;

    SaltoEfectivo = NO;

    /* riesgos de control */
    switch (solucion_riesgos_control) {
    case ds3:
    case stall:
        if (EX_MEM.cond)
        {
	    	SaltoEfectivo = SI;
            PCn = EX_MEM.ALUout;
        } else {
            PCn = PC+1;
        }
        break;

    case ds2:

    	/*** Eliminado para la practica ***/

		break;

    case pnt:

		/*** Insertar c�digo ***/
        if (EX_MEM.cond)
        {
            SaltoEfectivo = SI;
            IFnop=SI;
            IDnop=SI;
            EXnop=SI;
            PCn = EX_MEM.ALUout;
        } else {
            PCn = PC+1;
        }

        break;

    case ds1:
    	/*** Eliminado para la practica ***/

        break;
    default:
        ;
    } /* end switch */

} /* end fase_busqueda */


/***************************************************************
 *
 * Func: fase_decodificacion
 *
 * Desc: Implementa la fase ID
 *
 **************************************************************/
int fase_decodificacion (
    )

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    MEMaID = NO;
    WBaID = NO;

    /* riesgos de control */

    switch (solucion_riesgos_control) {
    case stall:
        if (inst_branch_int(IF_ID.IR.codop))
        {
            IFstall=SI;
        }
        break;

    case ds1:
        IDdir = IF_ID.NPC + (word) IF_ID.IR.inmediato;

        IDcompin= mux_COMPid (Rint[IF_ID.IR.Rfuente1].valor, EX_MEM.ALUout, WBdata);

        break;

    default:
        ;
    } /* end switch */


    /* riesgos de datos: insertar ciclos de parada? */

    switch (solucion_riesgos_datos) {
    case parada:
        /*** Insertar c�digo ***/

        // Riesgo entre EX e ID */
        if(hay_destino_EX() && hay_fuente1_ID() &&
           ID_EX.IR.Rdestino == IF_ID.IR.Rfuente1)
        {
            IDstall=SI;
            IFstall=SI;
        }

        if(hay_destino_EX() && hay_fuente2_ID() &&
           ID_EX.IR.Rdestino == IF_ID.IR.Rfuente2)
        {
            IDstall=SI;
            IFstall=SI;
        }

        // Riesgo entre MEM e ID
        if(hay_fuente1_ID() && hay_destino_MEM() &&
           EX_MEM.IR.Rdestino == IF_ID.IR.Rfuente1)
        {
            IDstall=SI;
            IFstall=SI;
        }

        if(hay_fuente2_ID() && hay_destino_MEM()  &&
           EX_MEM.IR.Rdestino == IF_ID.IR.Rfuente2)
        {
            IDstall=SI;
            IFstall=SI;
        }

        break;

    case cortocircuito:
        /*** Insertar c�digo ***/
        // Riesgo entre LD en fase EX con otra en ID
        if (hay_fuente1_ID() && hay_destino_EX() &&
           ID_EX.IR.codop == OP_LW &&
           ID_EX.IR.Rdestino == IF_ID.IR.Rfuente1)
       {
           IFstall=SI;
           IDstall=SI;
       }

       if (hay_fuente2_ID() && hay_destino_EX() &&
           ID_EX.IR.codop == OP_LW &&
           ID_EX.IR.Rdestino == IF_ID.IR.Rfuente2)
       {
           IFstall=SI;
           IDstall=SI;
       }

        if (solucion_riesgos_control == ds1) {
            /* Riesgo entre EX e ID en los saltos */

    		/*** Eliminado para la practica ***/
        }
        break;
    default:
        ;

    } /* endswitch */

    /* leer operandos */

    ID_EXn.Ra = Rint[IF_ID.IR.Rfuente1].valor;
    ID_EXn.Rb = Rint[IF_ID.IR.Rfuente2].valor;
    ID_EXn.Imm = (word) IF_ID.IR.inmediato;

    /* propagar datos */

    ID_EXn.NPC = IF_ID.NPC;
    ID_EXn.IR = IF_ID.IR;

    ID_EXn.iPC = IF_ID.iPC;
    ID_EXn.orden = IF_ID.orden;


    return (0);

} /* end fase_decodificacion */


/***************************************************************
 *
 * Func: fase_ejecucion
 *
 * Desc: Implementa la fase EX
 *
 **************************************************************/
void fase_ejecucion (
    )

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    word		aluin1,aluin2;
    word		compin;
    word          datain;
    ciclo_t		tmp;


    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/


    MEMaEXalu_s = NO;
    MEMaEXalu_i = NO;
    MEMaEXcomp = NO;
    WBaEXalu_s = NO;
    WBaEXalu_i = NO;
    WBaEXcomp = NO;
    WBaEXmem = NO;

    /* riesgos de control */

    switch (solucion_riesgos_control) {
    case stall:
        if (inst_branch_int(ID_EX.IR.codop))
        {
            IFstall=SI;
        }
        break;

    default:
        ;
    } /* end switch */


    /* multiplexores */

    aluin1 = mux_ALUsup (ID_EX.NPC, ID_EX.Ra, EX_MEM.ALUout, WBdata);
    aluin2 = mux_ALUinf (ID_EX.Rb, ID_EX.Imm, EX_MEM.ALUout, WBdata);

    if (solucion_riesgos_control != ds1) {
    	compin = mux_COMP (ID_EX.Ra, EX_MEM.ALUout, WBdata);
    }

    /* hacemos la operacion */

    ALUout = operacion_ALU (ID_EX.IR.codop, aluin1, aluin2);
    EX_MEMn.ALUout = ALUout;

    CONDout = operacion_COMP (ID_EX.IR.codop, compin);
    EX_MEMn.cond = CONDout;

    /* propagar datos */

    EX_MEMn.data = mux_EXmem (ID_EX.Rb, WBdata); /* Para SW */

    EX_MEMn.IR = ID_EX.IR;

    EX_MEMn.iPC = ID_EX.iPC;
    EX_MEMn.orden = ID_EX.orden;

} /* end fase_ejecucion */


/***************************************************************
 *
 * Func: fase_memoria
 *
 * Desc: Implementa la fase MEM
 *
 **************************************************************/
void fase_memoria (
    )

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    word		data;

    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    WBaMEM = NO;

    /* Riesgos de control */
    switch (solucion_riesgos_control) {
    case stall:
        if (inst_branch_int(EX_MEM.IR.codop))
        {
            if (EX_MEM.cond)
            { /* salto que s� salta  -> cancelamos inst en IF */
                IFnop=SI;
            } else { /* salto que no salta -> que siga la inst en IF */
                IFstall=SI;
            }
        }
        break;

    default:
        ;
    } /* end switch */


    /* multiplexores */
    data = mux_MEMmem (EX_MEM.data, WBdata); /* Para SW */


    /* acceso a memoria */

    switch (EX_MEM.IR.codop) {
    case OP_LW:
        if (!esta_alineada_dir_dword(EX_MEM.ALUout)) {
                fprintf(stderr,
                        "ERROR (%d %d): Acceso desalineado a memoria\n",
                        __LINE__,EX_MEM.IR.codop);
                exit(1);
        }
        MEM_WBn.MEMout = MD.mdword[dir_dword(EX_MEM.ALUout)];
        break;
    case OP_SW:
        if (!esta_alineada_dir_dword(EX_MEM.ALUout)) {
            fprintf(stderr,
                    "ERROR (%d %d): Acceso desalineado a memoria\n",
                    __LINE__,EX_MEM.IR.codop);
            exit(1);
        }
        MD.mdword[dir_dword(EX_MEM.ALUout)] = data;
        break;
    default:
        ;
    } /* endswitch */


    /* propagar datos */

    MEM_WBn.ALUout = EX_MEM.ALUout;
    MEM_WBn.IR = EX_MEM.IR;

    MEM_WBn.iPC = EX_MEM.iPC;
    MEM_WBn.orden = EX_MEM.orden;

} /* end fase_memoria */


/***************************************************************
 *
 * Func: fase_escritura
 *
 * Desc: Implementa la fase 'WB'
 *
 **************************************************************/
boolean fase_escritura (
    )

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    boolean		final;

    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    /* Notese que no se simula el multiplexor que selecciona los bits
       adecuados del IR para seleccionar el registro destino. Simplemente
       se supone que la variable Rdestino ya contiene el valor correcto */

    final = NO;
    if (MEM_WB.iPC !=-1) {
        Instrucciones++;
        estat.instrucciones++;
		estat.enteras++;
    }

    switch (MEM_WB.IR.codop) {
    case OP_LW:
        if (MEM_WB.IR.Rdestino !=0)
        {
            Rint[MEM_WB.IR.Rdestino].valor = MEM_WB.MEMout;
            WBdata = MEM_WB.MEMout;
        }
        break;
    case OP_SW:
    case OP_BEQZ:
    case OP_BNEZ:
        break;
    case OP_TRAP:
        final = SI;
        break;
    default:
        if (MEM_WB.IR.Rdestino !=0)
        {
            Rint[MEM_WB.IR.Rdestino].valor = MEM_WB.ALUout;
            WBdata = MEM_WB.ALUout;
        }
    } /* endswitch */

    return (final);

} /* end fase_escritura */


/***************************************************************
 *
 * Func: impulso_reloj
 *
 * Desc: Actualiza los registros inter-etapa
 *
 **************************************************************/
void impulso_reloj ( )
{
    /*************************************/
    /*  Variables locales                */
    /*************************************/


    /*************************************/
    /*  Cuerpo funci�n                   */
    /*************************************/

    /* IFnop se activa para abortar una instruccion. Si esta activado tb IFstall, la ignoramos */
    if (IFnop) {
        pasar_a_ID_NOP();
        IFnop = NO;
        IFstall = NO; // Por si estaba activada
    }

    if (!IFstall) {
        orden= orden+1;         /* VISUALIZACI�N */
        PC = PCn;
    } else {
        pasar_a_ID_NOP();
        IFstall = NO;
    }

/*    if (SaltoEfectivo) {
        orden= orden+1;
        PC = PCn;
        IFstall = NO; // Por si estaba activada
    } else if (!IFstall) {
        orden= orden+1;
        PC = PCn;
    } else {
        pasar_a_ID_NOP();
        IFstall = NO;
    } */


/*    if (IFnop) {
        pasar_a_ID_NOP();
        IFnop = NO;
    } */

    if (IDnop) {
        pasar_a_EX_NOP();
        IDnop = NO;
        IDstall = NO; // Por si estaba activada
    }

    if (!IDstall) {
        IF_ID = IF_IDn;
    } else {
        pasar_a_EX_NOP();
        IDstall = NO;
    }

/*    if (IDnop) {
        pasar_a_EX_NOP();
        IDnop = NO;
    } */

    if (EXnop) {
        pasar_a_MEM_NOP();
        EXnop = NO;
        EXstall = NO; // Por si estaba activada
    }

    if (!EXstall) {
        ID_EX = ID_EXn;
    } else {
        pasar_a_MEM_NOP();
        EXstall = NO;
    }

/*    if (EXnop) {
        pasar_a_MEM_NOP();
        EXnop = NO;
    } */

    EX_MEM = EX_MEMn;

    MEM_WB = MEM_WBn;


} /* end impulso_reloj */
