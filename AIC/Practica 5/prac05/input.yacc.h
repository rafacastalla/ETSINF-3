/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_HOME_SSAEZ_SVN_GII_AIC_TRUNK_PRACTICAS_PRAC05_FICHEROS_PRAC05_INPUT_YACC_H_INCLUDED
# define YY_YY_HOME_SSAEZ_SVN_GII_AIC_TRUNK_PRACTICAS_PRAC05_FICHEROS_PRAC05_INPUT_YACC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NL = 258,
    T_INT_LIT = 259,
    T_FP_LIT = 260,
    T_ALPHANUM = 261,
    T_STRING = 262,
    REG_INT = 263,
    REG_FP = 264,
    DE_DATA = 265,
    DE_TEXT = 266,
    DE_SPACE = 267,
    DE_IREG = 268,
    DE_FREG = 269,
    DE_ASCIIZ = 270,
    DE_BTB = 271,
    DE_BYTE = 272,
    DE_HALF = 273,
    DE_WORD = 274,
    DE_DWORD = 275,
    DE_FLOAT = 276,
    DE_DOUBLE = 277,
    FORM_INM = 278,
    FORM_INM_L = 279,
    FORM_INM_S = 280,
    FORM_INM_DI = 281,
    FORM_INM_B = 282,
    FORM_INM_B_FI = 283,
    FORM_INM_B_FFI = 284,
    FORM_INM_T = 285,
    INST_NOP = 286,
    INST_RET = 287,
    INST_SYSCALL = 288,
    FORM_REG = 289,
    FORM_REG_FF = 290,
    FORM_INM_FP_L = 291,
    FORM_INM_FP_S = 292,
    FORM_FP_REG = 293,
    FORM_FP_REG_FF = 294,
    FORM_FP_REG_DF = 295,
    FORM_REG_R_FP = 296,
    FORM_REG_FP_R = 297,
    FORM_J = 298,
    FORM_J_F = 299,
    LABEL = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 74 "input.yacc.y" /* yacc.c:1909  */

  double        fvalue;	
  int64_t       ivalue;
  char          cvalue[128];

#line 106 "/home/ssaez/SVN/gii-aic/trunk/practicas/prac05/ficheros/prac05/input.yacc.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_SSAEZ_SVN_GII_AIC_TRUNK_PRACTICAS_PRAC05_FICHEROS_PRAC05_INPUT_YACC_H_INCLUDED  */
