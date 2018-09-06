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
 * Date: Wed Mar 10 20:05:25 GMT 1999 
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

/*** Varaibles locales */

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
/* 	fprintf(stderr, "(%s) ", yytext); fflush(stderr); */
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
".ireg"	{ 
	return DE_IREG;
	}
 /* ".fpreg"	{ return DE_FREG;} */
 /* ".byte"		{ return DE_BYTE;} */
 /* ".half"		{ return DE_HALF;} */
 /* ".word"     { return DE_WORD;} */
".dword"	{
	return DE_DWORD;
	}
".double" {
	return DE_DOUBLE;
	}
".space" { 
	return DE_SPACE;
	}

 /*** Instrucciones implementadas *******************************************/

"nop"	{ yylval.ivalue= OP_NOP; 
	  return INST_NOP ; }

"ld"	{ yylval.ivalue= OP_LW;
	  return FORM_INM_L; }
"sd"	{ yylval.ivalue= OP_SW;
	  return FORM_INM_S; }
"dadd"	{ yylval.ivalue= OP_ADD;
	  return FORM_REG; }
"dsub"	{ yylval.ivalue= OP_SUB;
	  return FORM_REG; }
"and"	{ yylval.ivalue= OP_AND; 
	  return FORM_REG; }
"or"	{ yylval.ivalue= OP_OR; 
	  return FORM_REG; }
"xor"	{ yylval.ivalue= OP_XOR; 
	  return FORM_REG; }
"dsrav"	{ yylval.ivalue= OP_SRA;
	  return FORM_REG; }
"dsllv"	{ yylval.ivalue= OP_SLL;
	  return FORM_REG; }
"dsrlv"	{ yylval.ivalue= OP_SRL;
	  return FORM_REG; }
"seq"	{ yylval.ivalue= OP_SEQ; 
	  return FORM_REG; }
"sne"	{ yylval.ivalue= OP_SNE; 
	  return FORM_REG; }
"sgt"	{ yylval.ivalue= OP_SGT; 
	  return FORM_REG; }
"slt"	{ yylval.ivalue= OP_SLT; 
	  return FORM_REG; }
"sge"	{ yylval.ivalue= OP_SGE; 
	  return FORM_REG; }
"sle"	{ yylval.ivalue= OP_SLE; 
	  return FORM_REG; }
"daddi"	{ yylval.ivalue= OP_ADDI;
	  return FORM_INM; }
"dsubi"	{ yylval.ivalue= OP_SUBI;
	  return FORM_INM; }
"andi"	{ yylval.ivalue= OP_ANDI; 
	  return FORM_INM; }
"ori"	{ yylval.ivalue= OP_ORI; 
	  return FORM_INM; }
"xori"	{ yylval.ivalue= OP_XORI; 
	  return FORM_INM; }
"dsra"	{ yylval.ivalue= OP_SRAI;
	  return FORM_INM; }
"dsll"	{ yylval.ivalue= OP_SLLI;
	  return FORM_INM; }
"dsrl"	{ yylval.ivalue= OP_SRLI;
	  return FORM_INM; }
"seqi"	{ yylval.ivalue= OP_SEQI; 
	  return FORM_INM; }
"snei"	{ yylval.ivalue= OP_SNEI; 
	  return FORM_INM; }
"sgti"	{ yylval.ivalue= OP_SGTI; 
	  return FORM_INM; }
"slti"	{ yylval.ivalue= OP_SLTI; 
	  return FORM_INM; }
"sgei"	{ yylval.ivalue= OP_SGEI; 
	  return FORM_INM; }
"slei"	{ yylval.ivalue= OP_SLEI; 
	  return FORM_INM; }
"bnez"	{ yylval.ivalue= OP_BNEZ; 
	  return FORM_INM_B; }
"beqz"	{ yylval.ivalue= OP_BEQZ; 
	  return FORM_INM_B; }
"trap"	{ yylval.ivalue= OP_TRAP; 
	  return FORM_INM_T; }



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
