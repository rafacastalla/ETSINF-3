%{
/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: input.yacc.c
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

/*** Declaraciones externas */

extern FILE *	yyin;   
extern int	yyerror (char *);
extern void     free(void*);
 
/*** Variables globales */
  
char	mensaje[256];
long	linenumber=1;

tipo_t tipo= t_word;
modo_t modo= m_ninguno;
  
dword	pos_datos= -1;
dword	pos_instruc= -1;
  
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
%token <ivalue> REG_INT REG_FP
%token <ivalue> DE_DATA DE_TEXT 
%token <ivalue> DE_BYTE DE_HALF DE_WORD DE_DWORD DE_FLOAT DE_DOUBLE DE_SPACE
%token <ivalue> INST_NOP FORM_INM_L FORM_INM_S FORM_INM_A FORM_INM_B FORM_INM_T
%token <ivalue> FORM_REG_F FORM_REG_I
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
	    te_inserta($1,linenumber,pos_datos,m_datos);
	    break;
	  case m_instruc:
	    te_inserta($1,linenumber,pos_instruc,m_instruc);
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
	
	| NL 
        {
        }
        r_inicio
	{
	}

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
	    MD.m_byte[dir_byte(pos_datos)]= (byte)$1;
            mem_etiqueta(pos_datos, tipo);
	    pos_datos+= sizeof(byte);    
	    break;	
	  case t_half:
	    if (!esta_alineada_dir_half(pos_datos))
	      pos_datos= (dir_half(pos_datos)+1)*sizeof(half);
            if ($1 > MAX_HALF)
              yyerror("Literal fuera del rango del tipo 'half'");
	    MD.m_half[dir_half(pos_datos)]= (half)$1;    
            mem_etiqueta(pos_datos, tipo);
	    pos_datos+= sizeof(half);    
	    break;	
	  case t_word:
	    if (!esta_alineada_dir_word(pos_datos))
	      pos_datos= (dir_word(pos_datos)+1)*sizeof(word);
            if ($1 > MAX_WORD)
              yyerror("Literal fuera del rango del tipo 'word'");
	    MD.m_word[dir_word(pos_datos)]= (word)$1;    
            mem_etiqueta(pos_datos, tipo);
	    pos_datos+= sizeof(word);    
	    break;	
	  case t_dword:
	    if (!esta_alineada_dir_dword(pos_datos))
	      pos_datos= (dir_dword(pos_datos)+1)*sizeof(dword);
	    MD.m_dword[dir_dword(pos_datos)]= (dword)$1;    
            mem_etiqueta(pos_datos, tipo);
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

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoR;
	  MI[pos_instruc].Rfuente1= 0;
	  MI[pos_instruc].Rfuente2= 0;
	  MI[pos_instruc].Rdestino= 0;
	  MI[pos_instruc].inmediato= 0;
	  pos_instruc++;
	}
	
	| FORM_INM_L REG_FP ',' r_inmediato '(' REG_INT ')'
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= $2;
	  MI[pos_instruc].Rfuente1= $6;
	  MI[pos_instruc].Rfuente2= 0;
	  MI[pos_instruc].inmediato= $4;
	  pos_instruc++;
	}

	| FORM_INM_S REG_FP ',' r_inmediato '(' REG_INT ')' 
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= 0;
	  MI[pos_instruc].Rfuente1= $6;
	  MI[pos_instruc].Rfuente2= $2;
	  MI[pos_instruc].inmediato= $4;
	  pos_instruc++;
	}

	| FORM_INM_L REG_INT ',' r_inmediato '(' REG_INT ')'
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= $2;
	  MI[pos_instruc].Rfuente1= $6;
	  MI[pos_instruc].Rfuente2= 0;
	  MI[pos_instruc].inmediato= $4;
	  pos_instruc++;
	}

	| FORM_INM_S REG_INT ',' r_inmediato '(' REG_INT ')'
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= 0;
	  MI[pos_instruc].Rfuente1= $6;
	  MI[pos_instruc].Rfuente2= $2;
	  MI[pos_instruc].inmediato= $4;
	  pos_instruc++;
	}

	| FORM_INM_B REG_INT ',' r_posicion
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= 0;
	  MI[pos_instruc].Rfuente1= $2;
	  MI[pos_instruc].Rfuente2= 0;
	  MI[pos_instruc].inmediato= $4 - pos_instruc -1;
	  pos_instruc++;
	}

	| FORM_INM_B REG_INT ',' REG_INT ',' r_inmediato
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= 0;
	  MI[pos_instruc].Rfuente1= $2;
	  MI[pos_instruc].Rfuente2= $4;
	  MI[pos_instruc].inmediato= $6 - pos_instruc -1;
	  pos_instruc++;
	}

	| FORM_INM_B r_posicion
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= 0;
	  MI[pos_instruc].Rfuente1= REG_FPSR; 
	  MI[pos_instruc].Rfuente2= 0;
	  MI[pos_instruc].inmediato= $2 - pos_instruc -1;
	  pos_instruc++;
	}

	| FORM_REG_F REG_FP ',' REG_FP ',' REG_FP
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoR;
	  MI[pos_instruc].Rdestino= $2;
	  MI[pos_instruc].Rfuente1= $4;
	  MI[pos_instruc].Rfuente2= $6;
	  MI[pos_instruc].inmediato= 0;
	  pos_instruc++;
	}

	| FORM_REG_F REG_FP ',' REG_FP
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoR;
	  MI[pos_instruc].Rdestino= REG_FPSR;
	  MI[pos_instruc].Rfuente1= $2;
	  MI[pos_instruc].Rfuente2= $4;
	  MI[pos_instruc].inmediato= 0;
	  pos_instruc++;
	}

	| FORM_REG_I REG_INT ',' REG_INT ',' REG_INT
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoR;
	  MI[pos_instruc].Rdestino= $2;
	  MI[pos_instruc].Rfuente1= $4;
	  MI[pos_instruc].Rfuente2= $6;
	  MI[pos_instruc].inmediato= 0;
	  pos_instruc++;
	}

	| FORM_REG_I REG_INT ',' REG_INT ',' r_inmediato
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1 + 1;
				/* El código de operación de las
                                   operaciones aritméticas enteras con
                                   valores inmediatos son iguales a
                                   las que usan registros MÁS UNO */
				/* Ver fichero instrucciones.h */
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= $2;
	  MI[pos_instruc].Rfuente1= $4;
	  MI[pos_instruc].Rfuente2= 0;
	  MI[pos_instruc].inmediato= $6;
	  pos_instruc++;
	}

	| FORM_INM_T T_INT_LIT
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= 0;
	  MI[pos_instruc].Rfuente1= 0;
	  MI[pos_instruc].Rfuente2= 0;
	  MI[pos_instruc].inmediato= $2;
	  pos_instruc++;
	}
	;

%%

/*** Definición de código ***********************************************/

int yyerror 
(
 char *s
 )
{
  fprintf(stderr,"\n%s:%ld. Error: %s\n", nombre_fich, linenumber, s);
  exit(1);
} /* end yyerror */

void ensamblador
(
 FILE * f_input
 )
{

   yyin = f_input;
   if (yyin == NULL) return;
   
   /*** Realiza el 'parsing' del fichero de entrada */
   yyparse();

   te_confirma();		/* Confirma que al final no quedan
				   etiquetas por resolver */

   SegDatos.inicio= 0;		/* Segmento de datos */
   SegDatos.final= pos_datos;
   SegInstruc.inicio= 0;	/* Segmento de instrucciones */
   SegInstruc.final= pos_instruc;

} /* end ensamblador */

