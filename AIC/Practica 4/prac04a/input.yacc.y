%{
/**************************************************************************
 * 
 * Departamento de Inform·tica de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: input.yacc.c
 *  
 * Date: Wed Mar 10 20:05:25 GMT 1999
 *
 * Description: 
 *    Contiene la descripción sintáctica del lenguaje ensamblador
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *************************************************************************/

/***** Includes ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>

#include "main.h"
#include "tipos.h"
#include "etiquetas.h"
#include "instrucciones.h"
#include "memoria.h"

/*** Declaraciones externas */

extern FILE *	yyin;   
extern int	yyerror (char *);
extern void     free(void*);
extern int      yylex();
 
/*** Variables globales */
  
char	mensaje[256];
long	linenumber=1;

tipo_t tipo= t_dword;
modo_t modo= m_ninguno;
  
int	idx_ireg= 1;
int	idx_fpreg= 0;
int 	idx_BTB=0;
dword	pos_datos= 0;
dword	pos_instruc= 0;
int i=0;
instruccion_t instruccion;
valor_t valor;

/*****************************************************************************/

%}

%union {
  double        fvalue;	
  int64_t       ivalue;
  char          cvalue[128];
}

%token <ivalue> NL 
%token <ivalue> T_INT_LIT 
%token <fvalue> T_FP_LIT
%token <cvalue> T_ALPHANUM
%token <cvalue> T_STRING
%token <ivalue> REG_INT REG_FP
%token <ivalue> DE_DATA DE_TEXT DE_SPACE DE_IREG DE_FREG DE_ASCIIZ DE_BTB
%token <ivalue> DE_BYTE DE_HALF DE_WORD DE_DWORD 
%token <ivalue> DE_FLOAT DE_DOUBLE
%token <ivalue> FORM_INM FORM_INM_L FORM_INM_S FORM_INM_DI FORM_INM_B FORM_INM_B_FI FORM_INM_B_FFI FORM_INM_T
%token <ivalue> INST_NOP INST_RET INST_SYSCALL
%token <ivalue> FORM_REG FORM_REG_FF
%token <ivalue> FORM_INM_FP_L FORM_INM_FP_S
%token <ivalue> FORM_FP_REG FORM_FP_REG_FF FORM_FP_REG_DF 
%token <ivalue> FORM_REG_R_FP FORM_REG_FP_R
%token <ivalue> FORM_J FORM_J_F
%token <cvalue> LABEL

%type <ivalue> r_inmediato r_posicion

%start r_inicio

/*** Seccion de reglas *******************************************************/

%%

r_inicio : LABEL
	{
	  switch (modo)
	  {
	  case m_ninguno:
	    yyerror("Etiqueta indefinida");
	  case m_datos:
	    te_inserta($1,pos_datos,m_datos);
	    break;
	  case m_instruc:
	    te_inserta($1,pos_instruc,m_instruc);
	    break;
	  default:
	    yyerror("PÁNICO");
	  } /* endswitch */
	}
	r_linea_ensamblador	
	{
	}
	
	| r_linea_ensamblador
	{
	}
	
	| 
	{ 
	}
	;

r_linea_ensamblador : r_directiva NL 
	{
	}
	r_inicio
	{
	}
	
	| r_instruccion NL 
	{
	}
	r_inicio
	{
	}
	
	| NL r_inicio
	{
	}

	| r_directiva 
	{
	}
	
	| r_instruccion 
	{
	}
	;

r_directiva : DE_DATA
	{
	pos_datos= 0;
	modo= m_datos;
	}

	| DE_TEXT
	{
	pos_instruc= 0;
	modo= m_instruc;
	}

	| DE_BYTE
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");
         tipo= t_byte;
	}
	r_lista_enteros
	{
	}

	| DE_HALF
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");
         tipo= t_half;
	}
	r_lista_enteros
	{
	}

	| DE_WORD
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");
         tipo= t_word;
	}
	r_lista_enteros
	{
	}

	| DE_DWORD
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");
         tipo= t_dword;
	}
	r_lista_enteros
	{
	}

	| DE_FLOAT
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");
         tipo= t_float;
	}
	r_lista_reales
	{
	}

	| DE_DOUBLE
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");
         tipo= t_double;
	}
	r_lista_reales
	{
	}

	| DE_SPACE T_INT_LIT
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");

         pos_datos+= $2;

	 if (pos_datos > TAM_MEMO_DATOS)
	   yyerror("Excedido el tamaño de la memoria de datos");
	}

    | DE_ASCIIZ T_STRING
    {
		if (modo != m_datos)
		   yyerror("Datos en la memoria de instrucciones");

   		if (!esta_alineada_dir_byte(pos_datos)) 
			pos_datos= (dir_byte(pos_datos)+1)*sizeof(byte);

		for (i=0; i<=(strlen($2)+1); i++) // Sumo 1 por el null terminated
		{
		    valor.int_b = (byte)$2[i];
		    escribe_mem_datos(pos_datos+i, valor, t_byte);
			// MD.m_byte[dir_byte(pos_datos+i)]= (byte)$2[i];
 		}
		pos_datos+= sizeof(byte)*strlen($2)+1; // Sumo 1 por el null terminated
	
		if (pos_datos > TAM_MEMO_DATOS)
		yyerror("Excedido el tamaÒo de la memoria de datos");
	}
	

	| DE_IREG r_valores_enteros
	{
	}

	| DE_FREG r_valores_fp
	{
	}	

    | DE_BTB r_valores_btb
    {
    }
    ;

r_lista_enteros : T_INT_LIT 
	{
	switch (tipo)
	  {
	  case t_byte:
	    if (!esta_alineada_dir_byte(pos_datos))
	      pos_datos= (dir_byte(pos_datos)+1)*sizeof(byte);
            if ($1 > MAX_BYTE)
              yyerror("Literal fuera del rango del tipo 'byte'");
        valor.int_b = (byte)$1;
	    escribe_mem_datos(pos_datos, valor, t_byte);
	    pos_datos+= sizeof(byte);
	    break;	
	  case t_half:
	    if (!esta_alineada_dir_half(pos_datos))
	      pos_datos= (dir_half(pos_datos)+1)*sizeof(half);
            if ($1 > MAX_HALF)
              yyerror("Literal fuera del rango del tipo 'half'");
        valor.int_h = (half)$1;
	    escribe_mem_datos(pos_datos, valor, t_half);
	    pos_datos+= sizeof(half);    
	    break;	
	  case t_word:
	    if (!esta_alineada_dir_word(pos_datos))
	      pos_datos= (dir_word(pos_datos)+1)*sizeof(word);
            if ($1 > MAX_WORD)
              yyerror("Literal fuera del rango del tipo 'word'");
        valor.int_w = (word)$1;
	    escribe_mem_datos(pos_datos, valor, t_word);
	    pos_datos+= sizeof(word);    
	    break;	
	  case t_dword:
	    if (!esta_alineada_dir_dword(pos_datos))
	      pos_datos= (dir_dword(pos_datos)+1)*sizeof(dword);
	    valor.int_d = (dword)$1;
        escribe_mem_datos(pos_datos, valor, t_dword);
	    pos_datos+= sizeof(dword);    
	    break;	
	  default:
	    yyerror("PÁNICO");
	    break;
	  } /* endswitch */

        if (pos_datos > TAM_MEMO_DATOS)
	  yyerror("Excedido el tamaño de la memoria de datos");
	}
	r_lista_enteros_cont
	{
	}
	;

r_lista_enteros_cont : 	',' r_lista_enteros
	{
	}

	|
	{
	}
	;

r_lista_reales : T_FP_LIT 
	{
	switch (tipo)
	  {
	  case t_float:
	    if (!esta_alineada_dir_float(pos_datos))
	      pos_datos= (dir_float(pos_datos)+1)*sizeof(float);
	    valor.fp_s = (float)$1;
	    escribe_mem_datos(pos_datos, valor, t_float);
	    pos_datos+= sizeof(float);
	    break;	
	  case t_double:
	    if (!esta_alineada_dir_double(pos_datos))
	      pos_datos= (dir_double(pos_datos)+1)*sizeof(double);
	    valor.fp_d = (double)$1;
	    escribe_mem_datos(pos_datos, valor, t_double);
	    pos_datos+= sizeof(double);    
	    break;	
	  default:
	    yyerror("PÁNICO");
	    break;
	  } /* endswitch */

    	if (pos_datos > TAM_MEMO_DATOS)
	  yyerror("Excedido el tamaño de la memoria de datos");
	}
	r_lista_reales_cont
	{
	}
	
	| T_INT_LIT 
	{
	switch (tipo)
	  {
	  case t_float:
	    if (!esta_alineada_dir_float(pos_datos))
	      pos_datos= (dir_float(pos_datos)+1)*sizeof(float);
	    MD.m_float[dir_float(pos_datos)]= (float)$1;
            mem_etiqueta(pos_datos, tipo);
	    pos_datos+= sizeof(float);    
	    break;	
	  case t_double:
	    if (!esta_alineada_dir_double(pos_datos))
	      pos_datos= (dir_double(pos_datos)+1)*sizeof(double);
	    MD.m_double[dir_double(pos_datos)]= (double)$1;
            mem_etiqueta(pos_datos, tipo);
	    pos_datos+= sizeof(double);    
	    break;	
	  default:
	    yyerror("PÁNICO");
	    break;
	  } /* endswitch */

        if (pos_datos > TAM_MEMO_DATOS)
	  yyerror("Excedido el tamaño de la memoria de datos");
	}
	r_lista_reales_cont
	{
	}
	;

r_lista_reales_cont : ',' r_lista_reales
	{
	}

	|
	{
	}
	;

r_valores_enteros : T_INT_LIT
	{
  	  if (idx_ireg >= TAM_REGISTROS)
	    yyerror("Excedido el numero de registros");
	  Rint[idx_ireg].valor.int_d = $1;
	  idx_ireg++;
	}
	r_valores_enteros_cont
	{
	}
	;

r_valores_enteros_cont : ',' r_valores_enteros
	{
	}

	|
	{
	}
	;

r_valores_fp : T_FP_LIT 
	{
  	  if (idx_fpreg >= TAM_REGISTROS)
	    yyerror("Excedido el numero de registros");
	  Rfp[idx_fpreg].valor.fp_d = $1;
	  idx_fpreg++;
	}
	r_valores_fp_cont
	{
	}
	;

r_valores_fp_cont : ',' r_valores_fp
	{
	}

	|
	{
	}
	;

r_valores_btb : T_INT_LIT
    {
    if (idx_BTB==6)
    yyerror("BTB ya inicializado");
    if ((idx_BTB % 3)==0) {
        BTB[idx_BTB / 3].PC= $1;
        idx_BTB++;
    } else if ((idx_BTB % 3)==1) {
        BTB[idx_BTB / 3].estado= $1;
        idx_BTB++;
    } else {
        BTB[idx_BTB / 3].destino= $1;
        BTB[idx_BTB / 3].ciclo=0;
        idx_BTB++;
    }
    }
    r_valores_btb_cont
    {
    }
    ;
    
r_valores_btb_cont : ',' r_valores_btb
    {
    }
    
    |
    {
    }
    ;

r_inmediato : T_INT_LIT
	{
	  $$= $1;
	}

	| T_ALPHANUM
	{
	  $$= te_resuelve($1, linenumber, pos_instruc, m_datos);
	}
	;

r_posicion : T_INT_LIT
	{
	  $$= $1;
	}

	| T_ALPHANUM
	{
	  $$= te_resuelve($1, linenumber, pos_instruc, m_instruc);
	}
	;

r_instruccion : INST_NOP
	{ 
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoR;
	  instruccion.Rfuente1= 0;
	  instruccion.Rfuente2= 0;
	  instruccion.Rdestino= 0;
	  instruccion.inmediato= 0;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

	| INST_SYSCALL
	{ 
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoR;
	  instruccion.Rfuente1= 0;
	  instruccion.Rfuente2= 0;
	  instruccion.Rdestino= 0;
	  instruccion.inmediato= 0;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}
	
    // LOAD INT
	| FORM_INM_L REG_INT ',' r_inmediato '(' REG_INT ')'
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoI;
	  instruccion.Rdestino= $2;
	  instruccion.Rfuente1= $6;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= $4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // LOAD FP
	| FORM_INM_FP_L REG_FP ',' r_inmediato '(' REG_INT ')'
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoI;
	  instruccion.Rdestino= $2;
	  instruccion.Rfuente1= $6;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= $4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // STORE INT
	| FORM_INM_S REG_INT ',' r_inmediato '(' REG_INT ')'
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoI;
	  instruccion.Rdestino= 0;
	  instruccion.Rfuente1= $6;
	  instruccion.Rfuente2= $2;
	  instruccion.inmediato= $4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // STORE FP
	| FORM_INM_FP_S REG_FP ',' r_inmediato '(' REG_INT ')'
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoI;
	  instruccion.Rdestino= 0;
	  instruccion.Rfuente1= $6;
	  instruccion.Rfuente2= $2;
	  instruccion.inmediato= $4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // R R R
	| FORM_REG REG_INT ',' REG_INT ',' REG_INT
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoR;
	  instruccion.Rdestino= $2;
	  instruccion.Rfuente1= $4;
	  instruccion.Rfuente2= $6;
	  instruccion.inmediato= 0;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // FP FP FP
    | FORM_FP_REG REG_FP ',' REG_FP ',' REG_FP
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoR;
	  instruccion.Rdestino= $2;
	  instruccion.Rfuente1= $4;
	  instruccion.Rfuente2= $6;
	  instruccion.inmediato= 0;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // FP FP
    | FORM_FP_REG_DF REG_FP ',' REG_FP
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoR;
	  instruccion.Rdestino= $2;
	  instruccion.Rfuente1= $4;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= 0;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // R R I
	| FORM_REG REG_INT ',' REG_INT ',' r_inmediato
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1 + 1;
	  /* El código de operación de las operaciones aritméticas
	     enteras con valores inmediatos son iguales a las que usan
	     registros más UNO. Ver fichero instrucciones.h */
	  instruccion.tipo= FormatoI;
	  instruccion.Rdestino= $2;
	  instruccion.Rfuente1= $4;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= $6;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // R R I nativo
	| FORM_INM REG_INT ',' REG_INT ',' r_inmediato
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoI;
	  instruccion.Rdestino= $2;
	  instruccion.Rfuente1= $4;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= $6;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // TRAP
	| FORM_INM_T T_INT_LIT
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoI;
	  instruccion.Rdestino= 0;
	  instruccion.Rfuente1= 0;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= $2;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

	// LUI
	| FORM_INM_DI REG_INT ',' T_INT_LIT
	{
		if (modo != m_instruc)
		yyerror("Se espera '.text' antes de las instrucciones");
	
      bzero(&instruccion, sizeof(instruccion_t));
		instruccion.codop= $1;
		instruccion.tipo= FormatoI;
		instruccion.Rdestino= $2;
		instruccion.Rfuente1= 0;
		instruccion.Rfuente2= 0;
		instruccion.inmediato= $4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

    // C.xx.D C.xx.S
	| FORM_FP_REG_FF REG_FP ',' REG_FP
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoR;
	  instruccion.Rdestino= REG_FPSR;
	  instruccion.Rfuente1= $2;
	  instruccion.Rfuente2= $4;
	  instruccion.inmediato= 0;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}
	
	// BEQZ, BNEZ
	| FORM_INM_B_FI REG_INT ',' r_posicion
	{
		if (modo != m_instruc)
		yyerror("Se espera '.text' antes de las instrucciones");
	
      bzero(&instruccion, sizeof(instruccion_t));
		instruccion.codop= $1;
		instruccion.tipo= FormatoI;
		instruccion.Rdestino= 0;
		instruccion.Rfuente1= $2;
		instruccion.Rfuente2= 0;
		instruccion.inmediato= $4 - pos_instruc - 4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

	// BEQ, BNE
	| FORM_INM_B_FFI REG_INT ',' REG_INT ',' r_posicion
	{
		if (modo != m_instruc)
		yyerror("Se espera '.text' antes de las instrucciones");
	
      bzero(&instruccion, sizeof(instruccion_t));
		instruccion.codop= $1;
		instruccion.tipo= FormatoI;
		instruccion.Rdestino= 0;
		instruccion.Rfuente1= $2;
		instruccion.Rfuente2= $4;
		instruccion.inmediato= $6 - pos_instruc -4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}

	// BC1T BC1F
    | FORM_INM_B r_posicion
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoI;
	  instruccion.Rdestino= 0;
	  instruccion.Rfuente1= REG_FPSR;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= $2 - pos_instruc -4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}
	// J JAl
    | FORM_J r_posicion
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoJ;
	  instruccion.Rdestino= 0;
	  instruccion.Rfuente1= 0;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= $2 - pos_instruc -4;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}
	// J JR
    | FORM_J_F REG_INT
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= $1;
	  instruccion.tipo= FormatoJ;
	  instruccion.Rdestino= 0;
	  instruccion.Rfuente1= $2;
	  instruccion.Rfuente2= 0;
	  instruccion.inmediato= 0;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}
	// RET
	| INST_RET
	{ 
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

      bzero(&instruccion, sizeof(instruccion_t));
	  instruccion.codop= OP_JR;
	  instruccion.tipo= FormatoJ;
	  instruccion.Rfuente1= 31;
	  instruccion.Rfuente2= 0;
	  instruccion.Rdestino= 0;
	  instruccion.inmediato= 0;
	  escribe_mem_instruc(pos_instruc, instruccion);
	  pos_instruc += 4;
	}
	;

%%

/*** Definición de código ***********************************************/

int yyerror 
(
 char *s
 )
{
  fprintf(stderr,"%s:%ld. Error: %s\n", nombre_fich, linenumber, s);
  exit(1);
} /* end yyerror */

void ensamblador
(
 FILE * f_input
 )
{

   yyin = f_input;
   if (yyin == NULL) return;
   
   te_inserta(".text",0,m_instruc);
   te_inserta(".data",0,m_datos);

   /*** Realiza el 'parsing' del fichero de entrada */
   yyparse();

   te_confirma();		/* Confirma que al final no quedan
				   etiquetas por resolver */

   SegDatos.inicio= 0;		/* Segmento de datos */
   SegDatos.final= pos_datos;
   SegInstruc.inicio= 0;	/* Segmento de instrucciones */
   SegInstruc.final= pos_instruc;

   te_inserta(".etext",pos_instruc,m_instruc);
   te_inserta(".edata",pos_datos,m_datos);

} /* end ensamblador */

