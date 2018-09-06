/**************************************************************************
 * 
 * Departamento de Informatica de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio S‡ez (ssaez@disca.upv.es)
 *	   Pedro L—pez (plopez@gap.upv.es)
 * 
 * File: presentacion-html.c
 *  
 * Description: Contiene las funciones necesarias para presentar la
 *    informacion sobre la ejecuci—n del algoritmo
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#define presentatxt_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** Definiciones Externas **********************************/

#include "tipos.h"
#include "main.h"
#include "instrucciones.h"
#include "presentacion-html.h"

/***** Variables Globales *************************************/

/***** Variables Locales **************************************/

/***** Funciones Locales **************************************/


/***** Funciones Exportables **********************************/


/***************************************************************
 *
 * Func: imprime_etapas_txt
 *
 * Desc:
 *   Imprime el estado de la maquina
 *
 **************************************************************/

void imprime_etapas_txt (
   )

{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  char		inst[80];

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/


  fprintf(stdout, "\n");

  fprintf(stdout, "\n*** Ciclo: %ld ***\n\n", Ciclo);

  fprintf(stdout, "PC: %d \n\n", PC);

/*
    imprime_instruccion(PC, inst); 
    fprintf (stdout, "--/IF: %s \n",inst);

    imprime_instruccion(IF_ID.iPC, inst);
    fprintf (stdout, "IF/ID: %s \n",inst);
  
    imprime_instruccion(ID_EX.iPC, inst);
    fprintf (stdout, "ID/EX: %s \n",inst);
  
    imprime_instruccion(EX_MEM.iPC, inst);
    fprintf (stdout, "EX/MEM: %s \n",inst);

    imprime_instruccion(MEM_WB.iPC, inst);
    fprintf (stdout, "MEM/WB: %s \n",inst);

    fprintf (stdout, "\n");
*/
//    fprintf (stdout, "IF              ID              EX              MEM             WB\n");
 
    fprintf (stdout, "%-18s","IF");
    fprintf (stdout, "%-18s","ID");
    fprintf (stdout, "%-18s","EX");
    fprintf (stdout, "%-18s","MEM");
    fprintf (stdout, "%-18s\n","WB");
 
    imprime_instruccion(inst, PC);
    fprintf (stdout, "%-18s",inst);

    imprime_instruccion(inst, IF_ID.iPC);
    fprintf (stdout, "%-18s",inst);
  
    imprime_instruccion(inst, ID_EX.iPC);
    fprintf (stdout, "%-18s",inst);
  
    imprime_instruccion(inst, EX_MEM.iPC);
    fprintf (stdout, "%-18s",inst);

    imprime_instruccion(inst, MEM_WB.iPC);
    fprintf (stdout, "%-18s \n",inst);
    fprintf (stdout, "\n");

    fprintf (stdout, "Senyales: ");
    if (IFstall == SI)  {fprintf (stdout, "IFstall ");};
    if (IDstall == SI)  {fprintf (stdout, "IDstall ");};
    if (IFnop == SI)  {fprintf (stdout, "IFnop ");};
    if (IDnop == SI)  {fprintf (stdout, "IDnop ");};
    if (EXnop == SI)  {fprintf (stdout, "EXnop ");};
    if (MEMaEXalu_s == SI)  {fprintf (stdout, "MEMaEXalu_i ");};
    if (MEMaEXalu_i == SI)  {fprintf (stdout, "MEMaEXalu_s ");};
    if (MEMaEXcomp == SI)  {fprintf (stdout, "MEMaEXcomp ");};
    if (WBaEXalu_s == SI)  {fprintf (stdout, "WBaEXalu_i ");};
    if (WBaEXalu_i == SI)  {fprintf (stdout, "WBaEXalu_s ");};
    if (WBaEXcomp == SI)  {fprintf (stdout, "WBaEXcomp ");};
    if (WBaMEM == SI)  {fprintf (stdout, "WBaMEM ");};
    if (MEMaID == SI)  {fprintf (stdout, "MEMaID ");};
    if (WBaID == SI)  {fprintf (stdout, "WBaID ");};
    fprintf (stdout, "\n");
    

} /* end imprime_etapas_txt */

/***************************************************************
 *
 * Func: imprime_reg_txt
 *
 * Desc: 
 *   Imprime el estado de la maquina (i: Registros)
 *
 **************************************************************/

void imprime_reg_txt (
   )

{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int		i,j;

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/

  fprintf(stdout, "\n");

  j = 1;
  for (i=0; i<TAM_REGISTROS; i++)
    {
      /*** Registros enteros */
      fprintf (stdout, "Regs[%2d]: %4lld ",i, Rint[i].valor); 
      if ((j % 4) == 0) fprintf (stdout, "\n");
      j++;
    } /* endfor */
 
} /* end imprime_reg */


/***************************************************************
 *
 * Func: imprime_memdatos_txt
 *
 * Desc: 
 *   Imprime el estado de la maquina (ii: memoria de datos)
 *
 **************************************************************/

void imprime_memdatos_txt (
   )

{
  /*************************************/
  /*  Variables locales                */
  /*************************************/

  int		i,j;

  /*************************************/
  /*  Cuerpo función                   */
  /*************************************/


  fprintf(stdout, "\n");

  j = 1;
  for (i= SegDatos.inicio; i< SegDatos.final; i+= sizeof(dword))
    {
      fprintf(stdout, "Mem[%4d]: ", i); 
      fprintf(stdout, "%4lld ", MD.mdword[dir_dword(i)]);
      if ((j % 4) == 0) fprintf (stdout, "\n");
      j++;
    } /* endfor */
  fprintf(stdout, "\n"); 

 
} /* end imprime_mem */

/***************************************************************
 *
 * Func: imprime_final_txt
 *
 * Desc: Imprime la configuracion y resultados finales
 *
 **************************************************************/

void imprime_final_txt ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
	
		
    /*************************************/
    /*  Function body                    */
    /*************************************/
	
	
	/*** Resultados de la ejecucion ***/
    fprintf(stdout, "Resultados de la ejecucion\n\n");
	
    
    fprintf(stdout, "Ciclos= %ld\n", estat.ciclos);
    fprintf(stdout, "Instrucciones= %ld\n", estat.instrucciones);
    fprintf(stdout, "CPI= %1.2f\n", (float) estat.ciclos/estat.instrucciones);
    fprintf(stdout, "\n\n");
	
    
	
} /* end imprime_final */


