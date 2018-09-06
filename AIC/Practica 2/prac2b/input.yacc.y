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

#include "main.h"
#include "tipos.h"
#include "etiquetas.h"

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
long	pos_datos= -1;
long	pos_instruc= -1;
  
/*****************************************************************************/

%}

%union {
  double fvalue;	
  long   ivalue;
  char   cvalue[128];
}

%token <ivalue> NL 
%token <ivalue> T_INT_LIT 
%token <fvalue> T_FP_LIT
%token <cvalue> T_ALPHANUM
%token <ivalue> REG_INT REG_FP
%token <ivalue> DE_DATA DE_TEXT
%token <ivalue> DE_DWORD DE_DOUBLE DE_SPACE DE_IREG 
// DE_FREG
%token <ivalue> FORM_INM_L FORM_INM_S FORM_INM FORM_INM_B FORM_INM_T 
// %token <ivalue> FORM_INM_FP_L FORM_INM_FP_S FORM_FP_REG 
%token <ivalue> INST_NOP FORM_REG 
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
	
	| 
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

/*
	| DE_WORD
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");
         tipo= t_word;
	}
	r_lista_enteros
	{
	}
*/

	| DE_DWORD
	{
	 if (modo != m_datos)
	   yyerror("Datos en la memoria de instrucciones");
         tipo= t_dword;
	}
	r_lista_enteros
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

	| DE_IREG r_valores_enteros
	{
	}

/*
	| DE_FREG r_valores_fp
	{
	}
*/
	;

r_lista_enteros : T_INT_LIT 
	{
	switch (tipo)
	  {
	  case t_word:
	    if (!esta_alineada_dir_word(pos_datos))
	      pos_datos= (dir_word(pos_datos)+1)*sizeof(word);
            if ($1 > MAX_WORD)
              yyerror("Literal fuera del rango del tipo 'word'");
            MD.mword[dir_word(pos_datos)]= (word)$1;    
            /* mem_etiqueta(pos_datos, tipo); */
	    pos_datos+= sizeof(word);    
	    break;	
	  case t_dword:
	    if (!esta_alineada_dir_dword(pos_datos))
	      pos_datos= (dir_dword(pos_datos)+1)*sizeof(dword);
	    MD.mdword[dir_dword(pos_datos)]= (dword)$1;
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
	  case t_double:
	    if (!esta_alineada_dir_double(pos_datos))
	      pos_datos= (dir_double(pos_datos)+1)*sizeof(double);
	    MD.mdouble[dir_double(pos_datos)]= (double)$1;
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
	  case t_double:
	    if (!esta_alineada_dir_double(pos_datos))
	      pos_datos= (dir_double(pos_datos)+1)*sizeof(double);
	    MD.mdouble[dir_double(pos_datos)]= (double)$1;
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
	    yyerror("Excedido el número de registros");
	  Rint[idx_ireg].valor= $1;
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
/*
r_valores_fp : T_FP_LIT 
	{
  	  if (idx_fpreg >= TAM_REGISTROS)
	    yyerror("Excedido el número de registros");
	  Rfp[idx_fpreg].valor= $1;
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
*/
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

/*
	| FORM_INM_FP_L REG_FP ',' r_inmediato '(' REG_INT ')'
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
*/

//	dlx
//	| FORM_INM_S r_inmediato '(' REG_INT ')' ',' REG_INT 
	| FORM_INM_S REG_INT ',' r_inmediato '(' REG_INT ')'
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= 0;

//	dlx
//	  MI[pos_instruc].Rfuente1= $4;
//	  MI[pos_instruc].Rfuente2= $7;
//	  MI[pos_instruc].inmediato= $2;

	  MI[pos_instruc].Rfuente1= $6;
	  MI[pos_instruc].Rfuente2= $2;
	  MI[pos_instruc].inmediato= $4;
	  pos_instruc++;
	}

/*
	| FORM_INM_FP_S REG_FP ',' r_inmediato '(' REG_INT ')'
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
*/
	
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

	| FORM_REG REG_INT ',' REG_INT ',' REG_INT
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

/*
	| FORM_FP_REG REG_FP ',' REG_FP ',' REG_FP
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
*/

	| FORM_REG REG_INT ',' REG_INT ',' r_inmediato
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1 + 1;
	  /* El c�digo de operaci�n de las operaciones aritm�ticas
	     enteras con valores inmediatos son iguales a las que usan
	     registros M�S UNO. Ver fichero instrucciones.h */
	  MI[pos_instruc].tipo= FormatoI;
	  MI[pos_instruc].Rdestino= $2;
	  MI[pos_instruc].Rfuente1= $4;
	  MI[pos_instruc].Rfuente2= 0;
	  MI[pos_instruc].inmediato= $6;
	  pos_instruc++;
	}

	| FORM_INM REG_INT ',' REG_INT ',' r_inmediato
	{
	  if (modo != m_instruc)
	    yyerror("Se espera '.text' antes de las instrucciones");

	  MI[pos_instruc].codop= $1;
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
	
/*
	| FORM_FP_REG REG_FP ',' REG_FP
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
*/


	;

%%

/*** Definicion de codigo ***********************************************/

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

