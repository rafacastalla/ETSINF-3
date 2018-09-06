/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NL = 258,
     T_INT_LIT = 259,
     T_FP_LIT = 260,
     T_ALPHANUM = 261,
     REG_INT = 262,
     REG_FP = 263,
     DE_DATA = 264,
     DE_TEXT = 265,
     DE_DWORD = 266,
     DE_DOUBLE = 267,
     DE_SPACE = 268,
     DE_IREG = 269,
     FORM_INM_L = 270,
     FORM_INM_S = 271,
     FORM_INM = 272,
     FORM_INM_B = 273,
     FORM_INM_T = 274,
     INST_NOP = 275,
     FORM_REG = 276,
     LABEL = 277
   };
#endif
/* Tokens.  */
#define NL 258
#define T_INT_LIT 259
#define T_FP_LIT 260
#define T_ALPHANUM 261
#define REG_INT 262
#define REG_FP 263
#define DE_DATA 264
#define DE_TEXT 265
#define DE_DWORD 266
#define DE_DOUBLE 267
#define DE_SPACE 268
#define DE_IREG 269
#define FORM_INM_L 270
#define FORM_INM_S 271
#define FORM_INM 272
#define FORM_INM_B 273
#define FORM_INM_T 274
#define INST_NOP 275
#define FORM_REG 276
#define LABEL 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 66 "input.yacc.y"
{
  double fvalue;	
  long   ivalue;
  char   cvalue[128];
}
/* Line 1529 of yacc.c.  */
#line 99 "input.yacc.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

