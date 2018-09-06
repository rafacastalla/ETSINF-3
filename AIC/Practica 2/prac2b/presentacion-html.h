/*********************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio S‡ez (ssaez@disca.upv.es)
 *	   Pedro López (plopez@disca.upv.es)
 * 
 * File: presentacion-html.h
 *  
 * Description: 
 *    Definiciones para el módulo de presentación
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *********************************************************************/

#ifndef presentacion_html_H
#define presentacion_html_H

/***** Includes ***********************************************/


/***** Constants **********************************************/

#define MAX_INSTRUC	15	/* Número máximo de instrucciones visibles */
#define MAX_CICLOS_INIC	20	/* Número máximo de ciclos visibles
                                   inicialmente */
#define MAX_CICLOS	30	/* Número máximo de ciclos visibles */

/* Colores */
#define BG_HEADER "#ccddff"// Header 

#define BG_DIT1 "#ddeeff"  // D i-t
#define BG_DIT2 "#ccddff"  // D i-t
#define BG_VAL1 "#eeeeee"  // D i-t
#define BG_VAL2 "#dddddd"  // D i-t

#define BG_OPER BG_DIT2  // Oper Name 
#define BG_STAGE BG_DIT1 // Stage

#define BG_REGS BG_DIT1  // Registros

#define BG_SIG BG_DIT2   // Signals

#define BG_VAL BG_VAL1   // Value

#define BG_HEADER_COL1 BG_DIT2// Header col
#define BG_HEADER_COL2 BG_DIT1// Header col

#define BG_COL1 BG_VAL1// Value col 
#define BG_COL2 BG_VAL2// Value col

#define BG_DIR1 BG_DIT2
#define BG_DIR2 BG_DIT1
#define BG_DIR_VAL BG_VAL2


#define BG_RW "yellow"     // BG [Rx] RW
#define BG_W "tomato"      // BG [Rx] W
#define BG_R "turquoise"   // BG [Rx] R

/* Tama–o fuente */
#define FONT_SIZE 10
#define FONT_NAME "Tahoma"
#define LINE_HEIGHT "100%"


/* Para dibujar el datapath */

#define trazo_grueso 1.5
#define trazo_fino 1.5
#define trazo_resaltado 3.0

#define PC_ancho 30
#define PC_alto 100
#define reg_ancho 30
#define reg_alto 450
#define mem_ancho 100
#define mem_alto 100
#define sep1x 10
#define sep1y 10
#define aluPC_ancho 50
#define aluPC_alto 100
#define alu_ancho 50
#define alu_alto 140
#define mux2_ancho 20
#define mux2_alto 40
#define mux4_ancho 20
#define mux4_alto 80
#define regs_ancho 100
#define regs_alto 180
#define elipse_ancho 70
#define elipse_alto 80
#define zero_ancho 40
#define zero_alto 40

#define eje_x_IF 50
#define eje_x_ID eje_x_IF+PC_ancho+mem_ancho+5*sep1x
#define eje_x_EX eje_x_ID+260 // experimental
#define eje_x_M eje_x_EX+mux4_ancho+alu_ancho+10*sep1x+reg_ancho
#define eje_x_WB eje_x_M+mux2_ancho+mem_ancho+7*sep1x+reg_ancho

#define eje_y_texto 15

#define eje_y1_IF 80 // Registro IF/ID
#define eje_y2_IF eje_y1_IF-20 // ALU PC
#define eje_y3_IF eje_y2_IF+aluPC_alto+30 // PC, meminstr
#define eje_y4_IF eje_y2_IF+aluPC_alto // npc

#define eje_y1_ID eje_y1_IF // Registro ID/EX
#define eje_y2_ID eje_y1_ID-20 // control
#define eje_y3_ID eje_y3_IF // regs
#define eje_y4_ID eje_y3_ID+regs_alto+30 // ext
#define eje_y5_ID eje_y4_ID+elipse_alto+30 // mux
#define eje_y6_ID eje_y4_ID+30 // IR
#define eje_y7_ID eje_y1_ID+30 // zero


#define eje_y1_EX eje_y1_ID // Registro EX/M
#define eje_y2_EX eje_y7_ID // zero
#define eje_y3_EX eje_y3_ID+(regs_alto-alu_alto)/2 // ALU
#define eje_y4_EX eje_y3_EX+30 // mux

#define eje_y1_M eje_y1_ID // Registro M/WB
#define eje_y2_M eje_y3_ID+(regs_alto-mem_alto)/2 // memdatos
#define eje_y3_M eje_y4_EX // mux

#define PC_x eje_x_IF
#define PC_y eje_y3_IF
#define mem_instr_x PC_x+PC_ancho+2*sep1x
#define mem_instr_y eje_y3_IF
#define alu1_x mem_instr_x
#define alu1_y eje_y2_IF
#define muxpc_x alu1_x+aluPC_ancho+3*sep1x
#define muxpc_y alu1_y+aluPC_alto/2

#define IFID_x eje_x_ID
#define IFID_y eje_y1_IF
#define regs_x IFID_x+reg_ancho+6*sep1x
#define regs_y eje_y3_ID
#define regs_y eje_y3_ID
//#define control_x IFID_x+reg_ancho+2*sep1x
//#define control_y eje_y2_ID
#define ext_x regs_x
#define ext_y eje_y4_ID
#define muxid_x ext_x
#define muxid_y eje_y5_ID
#define aluid_x IFID_x+reg_ancho+4*sep1x
#define aluid_y alu1_y
#define muxzeroid_x aluid_x+aluPC_ancho+4*sep1x
#define zeroid_x muxzeroid_x+mux2_ancho+2*sep1x
#define zeroid_y eje_y7_ID



#define IDEX_x eje_x_EX
#define IDEX_y IFID_y
#define alu_x IDEX_x+12*sep1x
#define alu_y eje_y3_EX
#define mux2s_x alu1_x+alu_ancho+3*sep1x
#define mux2i_x alu1_x+alu_ancho+3*sep1x
#define zero_x alu_x
#define zero_y eje_y2_EX

#define EXM_x eje_x_M
#define EXM_y IDEX_y
#define mem_datos_y eje_y2_M
#define muxmem_x EXM_x+6*sep1x
#define mem_datos_x muxmem_x+mux2_ancho+2*sep1x

#define MWB_x eje_x_WB
#define MWB_y EXM_y
#define muxwb_x MWB_x+reg_ancho+3*sep1x



/***** Types **************************************************/

typedef char n_fase_t[64];	  /* Nombre de la fase */
typedef char n_instruccion_t[64]; /* Instrucción */

typedef struct {
  n_instruccion_t	inst;	/* Instrucción */
  n_fase_t		fase[MAX_CICLOS]; 
				/* Fases de la instrucción */
} linea_crono_t;		/* Una linea del cronograma */

typedef struct {
    word			ctrl;
    char			color[20];
} muxctrl_t;


typedef struct {
  word			x;
  word			y;
} coord_t;

typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		out1;
  char 			dibujo[1024];
} elem_1i1o_t;

typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		out1;
  coord_t		in2;
  coord_t		out2;
  char 			dibujo[1024];
} elem_2i2o_t;

typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		out1;
  coord_t		in2;
  coord_t		out2;
  coord_t		in3;
  coord_t		out3;
  char 			dibujo[1024];
} elem_3i3o_t;

typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		out1;
  coord_t		in2;
  coord_t		out2;
  coord_t		in3;
  coord_t		out3;
  coord_t		in4;
  coord_t		out4;
  char 			dibujo[1024];
} elem_4i4o_t;

typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		out1;
  coord_t		in2;
  coord_t		out2;
  coord_t		in3;
  coord_t		out3;
  coord_t		in4;
  coord_t		out4;
  coord_t		in5;
  coord_t		out5;
  char 			dibujo[1024];
} elem_5i5o_t;

typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		out1;
  coord_t		in2;
  coord_t		out2;
  coord_t		in3;
  coord_t		out3;
  coord_t		in4;
  coord_t		out4;
  coord_t		in5;
  coord_t		out5;
  coord_t		in6;
  coord_t		out6;
  char 			dibujo[1024];
} elem_6i6o_t;

typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		in2;
  coord_t		out1;
  char 			dibujo[1024];
} elem_2i1o_t;

typedef struct {
    coord_t	        pos1;
    coord_t	        pos2;
    int			ancho;
    int			alto;
    coord_t		in1;
    coord_t		in2;
    coord_t		in3;
    coord_t		out1;
    char 			dibujo[1024];
} elem_3i1o_t;


typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		in2;
  coord_t		in3;
  coord_t		in4;
  coord_t		out1;
  coord_t		out2;
  char 			dibujo[1024];
} elem_4i2o_t;

typedef struct {
  coord_t	        pos1;
  coord_t	        pos2;
  int			ancho;
  int			alto;
  coord_t		in1;
  coord_t		in2;
  coord_t		in3;
  coord_t		in4;
  coord_t		out1;
  char 			dibujo[1024];
} elem_4i1o_t;

typedef struct {
    coord_t	        pos1;
    coord_t	        pos2;
    int			ancho;
    int			alto;
    coord_t		in1;
    coord_t		in2;
    coord_t		in3;
    coord_t		in4;
    coord_t		in5;
    coord_t		out1;
    char 			dibujo[1024];
} elem_5i1o_t;

/***** Macros *************************************************/


/***** Prototypes *********************************************/

#include "presentacion-html.hi"

#ifdef presentacion_html_C		/*** Privado ***/

char		p_str[256];	/* Cadena auxiliar */

linea_crono_t		crono[MAX_INSTRUC];
				/* Instrucciones visibles en el
                                   cronograma */
#else				/*** Público ***/

extern char		p_str[256]; /* Cadena auxiliar */

extern linea_crono_t	crono[MAX_INSTRUC];
				/* Instrucciones visibles en el
                                   cronograma */
#endif

#endif /* end presentacion-html.h */

