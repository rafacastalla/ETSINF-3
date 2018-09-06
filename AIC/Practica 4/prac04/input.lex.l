%{
/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: input.lex.c
 *  
 * Description: 
 *    Contiene la descripción léxica del lenguaje ensamblador
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

/*** Includes */

#include <ctype.h>
#include <string.h>
#include "input.yacc.h"
#include "instrucciones.h"
#include "main.h"

/*** Declaraciones externas */

extern int linenumber;
extern int yyerror (char*);

/*** Variables locales */

static char mensaje[128];

%}

ALPHANUM [A-Za-z][A-Za-z0-9_]*
BLANK	 [ \t]+

DEC_LIT	 ([-+]?[1-9][0-9]*)|0
OCT_LIT	 0[0-9]+
HEX_LIT	 "0x"[0-9a-fA-F]+
FP_LIT	 [+-]?([0-9]*"."[0-9]+([eE][-+]?[0-9]+)?|[0-9]+[eE][-+]?[0-9]+)

REGI     "r"[0-9]?[0-9] 
REGF     "f"[0-9]?[0-9]

%option noyywrap

%%

 /*** Comentarios y conversiones **/

;.*$				/* Elimina los comentarios */
{BLANK}				/* Borra los espacios en blanco */
[A-Z] { unput(tolower(yytext[0])); }
				/* Convierte todos las letras a minusculas */

[\n] {	linenumber++; 
	return NL; }

 /*** Elementos del formato de instrucción */

{DEC_LIT} {
	sscanf(yytext, "%ld", &yylval.ivalue);
	return T_INT_LIT;
	}

{OCT_LIT} {
	sscanf(yytext, "%lo", &yylval.ivalue);
	return T_INT_LIT;
	}

{HEX_LIT} {
	sscanf(yytext, "%lx", &yylval.ivalue);
	return T_INT_LIT;
	}

"#"{DEC_LIT} {
	sscanf(yytext+1, "%ld", &yylval.ivalue);
	return T_INT_LIT;
	}

"#"{OCT_LIT} {
	sscanf(yytext+1, "%lo", &yylval.ivalue);
	return T_INT_LIT;
	}

"#"{HEX_LIT} {
	sscanf(yytext+1, "%lx", &yylval.ivalue);
	return T_INT_LIT;
	}

{FP_LIT} {
	sscanf(yytext, "%lg", &yylval.fvalue);
	return T_FP_LIT;
	}

{REGF} { 
	yylval.ivalue= atoi(yytext+1);
	if (yylval.ivalue >= TAM_REGISTROS)
	  {
	    sprintf(mensaje, 
		    "El rango de registros de coma flotante es F0-F%d",
		    TAM_REGISTROS-1); 
	    yyerror(mensaje);
	  }
	return REG_FP; 
	}

{REGI} { 
	yylval.ivalue= atoi(yytext+1);
	if (yylval.ivalue >= TAM_REGISTROS)
	  {
	    sprintf(mensaje, 
		    "El rango de registros enteros es R0-R%d",
		    TAM_REGISTROS-1); 
	    yyerror(mensaje);
	  }
	return REG_INT; 
	}

{ALPHANUM}":" { 
	strcpy(yylval.cvalue,yytext);
	yylval.cvalue[yyleng-1]= '\0';
	return LABEL; 
	}

 /*** Directivas del ensamblador */

".data" {
	return DE_DATA;
	}
".text"	{ 
	return DE_TEXT;
	}
".byte"	{ 
	return DE_BYTE;
	}
".half"	{ 
	return DE_HALF;
	}
".word"	{ 
	return DE_WORD;
	}
".dword" { 
	return DE_DWORD;
	}
".float" { 
	return DE_FLOAT;
	}
".double" { 
	return DE_DOUBLE;
	}
".space" { 
	return DE_SPACE;
	}

 /*** Instrucciones implementadas *******************************************/

"nop"	{ 
	yylval.ivalue= OP_NOP; 
	return INST_NOP ; }

 /*** Instrucciones enteras *************************************************/

"ld"	{ 
	yylval.ivalue= OP_LD; 
	  return FORM_INM_L; }
"sd"	{ 
	yylval.ivalue= OP_SD; 
	  return FORM_INM_S; }
"dadd"	{ 
	yylval.ivalue= OP_DADD; 
	  return FORM_REG_I; }
"dsub"	{ 
	yylval.ivalue= OP_DSUB; 
	  return FORM_REG_I; }
"beqz"	{ 
	yylval.ivalue= OP_BEQZ; 
	  return FORM_INM_B; }
"bnez"	{ 
	yylval.ivalue= OP_BNEZ; 
	  return FORM_INM_B; }

"beq"	{ 
	yylval.ivalue= OP_BEQ; 
	  return FORM_INM_B; }
"bne"	{ 
	yylval.ivalue= OP_BNE; 
	  return FORM_INM_B; }

"trap"	{ 
	yylval.ivalue= OP_TRAP; 
	  return FORM_INM_T; }

 /*** Instrucciones coma flotante *******************************************/

"l.d"	{ 
	yylval.ivalue= OP_L_D; 
	  return FORM_INM_L; }
"s.d"	{ 
	yylval.ivalue= OP_S_D; 
	  return FORM_INM_S; }
"add.d"	{ 
	yylval.ivalue= OP_ADD_D; 
	  return FORM_REG_F; }
"sub.d"	{ 
	yylval.ivalue= OP_SUB_D; 
	  return FORM_REG_F; }
"mul.d"	{ 
	yylval.ivalue= OP_MUL_D; 
	  return FORM_REG_F; }
"div.d"	{ 
	yylval.ivalue= OP_DIV_D; 
	  return FORM_REG_F; }
"c.gt.d" { 
	yylval.ivalue= OP_C_GT_D; 
	  return FORM_REG_F; }
"c.lt.d" { 
	yylval.ivalue= OP_C_LT_D; 
	  return FORM_REG_F; }
"bc1t"	{ 
	yylval.ivalue= OP_BC1T; 
	  return FORM_INM_B; }
"bc1f"	{ 
	yylval.ivalue= OP_BC1F; 
	  return FORM_INM_B; }

{ALPHANUM} {
	strcpy(yylval.cvalue, yytext);
	return T_ALPHANUM;
	}


 /*** Control de errores ****************************************************/

"."{ALPHANUM} { 
	yyerror("Directiva de ensamblador desconocida"); 
	}

. { 
	return yytext[0]; }
