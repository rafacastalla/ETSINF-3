/*********************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: tipos.h
 *  
 * Description: 
 *    Contiene las definiciones de tipos comunes
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *********************************************************************/

#ifndef tipos_H
#define tipos_H

/***** Includes ***********************************************/

#include <sys/types.h>
#include <stdint.h>
#include <inttypes.h>

/***** Constants **********************************************/

#define KB   (1024)

#define TAM_MEMO_DATOS          (16*KB) /* MAX: 32KB para poder utilizar las direcciones en los desplazamientos */
#define TAM_MEMO_INSTRUC        (4*KB)  /* 4KB = 1K instrucciones */

/***** Types **************************************************/

typedef char byte; /* Un byte: 8 bits */
#define MAX_BYTE (0xFF)
typedef short half; /* Media palabra: 16 bits */
#define MAX_HALF (0xFFFF)
//typedef long		word;	/* Una palabra: 32 bits */
#define MAX_WORD (0xFFFFFFFF)
//typedef long long	dword;	/* Una doble palabra: 64 bits */
#define MAX_DWORD (0xFFFFFFFFFFFFFFFF)

#define F_BYTE "%" PRId8
#define F_HALF "%" PRId16
#define F_WORD "%" PRId32
#define F_DWORD "%" PRId64

typedef int32_t word; /* Una palabra: 32 bits */
typedef int64_t dword; /* Una doble palabra: 64 bits */

typedef unsigned long ciclo_t;

typedef enum {
    NO = 0,
    SI = 1
} boolean; /* Valor lógico */

typedef enum {
    t_ninguno,
    t_byte,
    t_half,
    t_word,
    t_float,
    t_dword,
    t_double
} tipo_t; /* Tipo de dato utilizado */

typedef union {
    byte int_b;
    half int_h;
    word int_w;
    dword int_d;
    float fp_s;
    double fp_d;
} valor_t; /* Dato utilizado */

typedef enum {
    m_ninguno,
    m_datos,
    m_instruc
} modo_t; /* Segmento de memoria accedido */

typedef enum {
    l_bypassing,
    l_forwarding
} dep_mem_t;

/*** Estructuras espécificas ****/

typedef int codop_t; /* Código de operación */

typedef enum {
    FormatoR,
    FormatoI,
    FormatoJ
} formato_t; /* El formato J no esta implementado */

typedef enum {
    NONE,
    EX,
    WB
} estado_t; /* Estado de una operación en el ROB */

typedef enum {
    PENDIENTE,
    PREPARADA, /* Este estado sólo lo utiliza la memoria de datos */
    EN_CURSO,
    FINALIZADA
} estado_oper_t; /* Estado de una operación en una ER */

typedef int marca_t; /* Tipo marca/código */

typedef enum {
    NO_SALTA,
    NO_SALTA_UN_FALLO,
    SALTA_UN_FALLO,
    SALTA
} estado_predic_t; /* Estado del predictor de 2 bits */

typedef enum {
    OPER_ENTEROS,
    OPER_SUMREST,
    OPER_MULTDIV,
    OPER_MEMDATOS,
    OPER_DIRECCIONES,
    NUM_TIPOS_OPERADORES
} tipo_operador_t;

/*** Branch Target Buffer ******/

typedef struct {
    dword PC; /* Dirección de la instrucción de salto */
    estado_predic_t estado; /* Estado del predictor */
    dword destino; /* Dirección de destino */

    ciclo_t orden; /* Antiguedad de la última consulta */
    ciclo_t ciclo; /* Antiguedad de la última consulta */
} entrada_btb_t;

/*** Formato de instruccion ****/

typedef struct {
    codop_t codop;
    formato_t tipo;

    int Rfuente1, /* Índice del registro fuente 1 */
            Rfuente2, /* Índice del registro fuente 2 */
            Rdestino; /* Índice del registro destino */
    half inmediato; /* Valor Inmediato */

    dword PC; /* Posición de memoria de la instrucción */
} instruccion_t;

/*** Banco de registros ********/

//typedef struct {
//    double valor; /* Valor del registro: simple o doble precisión */
//    marca_t rob;  /* Marca del registro */
//} reg_fp_t;

//typedef struct {
//    dword valor; /* Valor del registro: sólo tiene dword */
//    marca_t rob; /* Marca del registro */
//} reg_int_t;

typedef struct {
    valor_t valor; /* Valor del registro */
    marca_t rob;   /* Marca del registro */
} reg_t;

/*** Registros inter-etapas ************************************************/

typedef struct { /* IF/ID */
    instruccion_t IR; /* Instrucción */

    dword PC; /* Posición de memoria de la instrucción */
    ciclo_t orden; /* Orden de la instrucción */

    int prediccion; /* Indica se se ha predicho salto o no */

    int excepcion; /* Indica si se ha producido alguna
                                           excepción y cual */
    boolean cancelar; /* Índica que esta instrucción se debe descartar en ISSUE */
    boolean ignorar; /* Índica que esta instrucción ya se ha lanzado anteriormente */
} reg_if_iss_t;

typedef struct {
    dword NPC; /* Siguiente PC */
    boolean Parar; /* Instrucción bloqueada en ISS */
    boolean Cancelar; /* Ejecución cancelada */
    boolean Excepcion; /* Hay una excepción en la unidad segmentada. Dejar de buscar */
    ciclo_t orden; /* Mantiene el orden de las instrucciones */
} reg_control_t;

/*** Estructuras internas de la ruta de datos de coma flotante *************/

/*** Estaciones de reserva ******/

typedef struct {
    boolean ocupado; /* Bit de ocupado */
    codop_t OP; /* Código de operación a realizar */

    marca_t Qj; /* Marca del primer operando. ALU */
    valor_t Vj; /* Valor del primer operando. ALU */

    marca_t Qk; /* Marca del segundo operando. ALU y TE */
    valor_t Vk; /* Valor del segundo operando. ALU y TE */

    dword direccion; /* Dirección de acceso a memoria. TL y TE */
    dword desplazamiento; /* Desplazamiento en el acceso a memoria. TL y TE */

    boolean confirm; /* Indica si la operación de memoria
				   ha sido confirmada. TE */

    estado_oper_t estado; /* Indica si la operación está pendiente, preparada, en curso o si 
                           *  ya ha terminado y el resultado está en la RS */
    unsigned int operador; /* Indica qué operador la está atendiendo mientras está en el estado EN_CURSO */
    valor_t resultado; /* Resultado de la operación */
    marca_t rob; /* Indica para quien es la operación.  */

    int excepcion; /* Indica si se ha producido alguna excepción
                                   al ejecutar está operación */
    dword PC; /* Posición de memoria de la instrucción */
    ciclo_t orden; /* Orden de la instrucción */
} estacion_t;

/*** Reorder buffer *************/

typedef struct {
    boolean ocupado; /* Bit de ocupado */
    codop_t OP; /* Código de operación a realizar */

    estado_t estado; /* Estado de la oepración */

    dword dest; /* Registro destino, TE o dirección dest. */
    valor_t valor; /* Resultado de la operación */

    int prediccion; /* Indica se se ha predicho salto o no */

    int excepcion; /* Indica si se ha producido alguna excepción
                                   al ejecutar está instrucción */
    dword PC; /* Posición de memoria de la instrucción */
    ciclo_t orden; /* Orden de la instrucción */
} reorder_t;

/*** Operador *******************/

typedef struct {
    boolean ocupado; /* Bit de ocupado */
    tipo_operador_t tipo; /* Tipo de operador */
    int estacion; /* Estación de reserva en uso */
    marca_t codigo; /* Código del reorder buffer */
    int ciclo; /* Ciclo actual de la operación */
    int Teval; /* Tiempo de evaluación */

    ciclo_t orden; /* Orden de la instrucción */
} operador_t;

/*** Bus común ******************/

typedef struct {
    boolean ocupado; /* Linea de ocupado */
    marca_t codigo; /* Lineas para los códigos */
    valor_t valor; /* Lineas de datos */
    int excepcion; /* Indica si se ha producido alguna excepción */
} bus_comun_t;

/*** Segmento de memoria ********/

typedef struct {
    dword inicio;
    dword final;
} segmento_t;

/*** Memoria de datos ***********/

typedef union {
    byte m_byte[TAM_MEMO_DATOS / sizeof(byte)];
    half m_half[TAM_MEMO_DATOS / sizeof(half)];
    word m_word[TAM_MEMO_DATOS / sizeof(word)];
    dword m_dword[TAM_MEMO_DATOS / sizeof(dword)];
    float m_float[TAM_MEMO_DATOS / sizeof(float)];
    double m_double[TAM_MEMO_DATOS / sizeof(double)];
} memoria_datos_t;

/*** Memoria de instrucciones ***/

typedef instruccion_t memoria_intrucciones_t[TAM_MEMO_INSTRUC];

/*** Estadisticas ***/

typedef struct {
    long ciclos;
    long instrucciones;
    long flops;
    long saltos_accedidos;
    long saltos_encontrados;
    long saltos_ejecutados;
    long saltos_acertados;
} estadisticas_t;

/***** Macros *************************************************/

#define dir_byte(d) (dword)((d) / sizeof(byte))
#define dir_half(d) (dword)((d) / sizeof(half))
#define dir_word(d) (dword)((d) / sizeof(word))
#define dir_dword(d) (dword)((d) / sizeof(dword))
#define dir_float(d) (dword)((d) / sizeof(float))
#define dir_double(d) (dword)((d) / sizeof(double))

#define esta_alineada_dir_byte(d) (((d) % sizeof(byte)) == 0 )
#define esta_alineada_dir_half(d) (((d) % sizeof(half)) == 0 )
#define esta_alineada_dir_word(d) (((d) % sizeof(word)) == 0 )
#define esta_alineada_dir_dword(d) (((d) % sizeof(dword)) == 0 )
#define esta_alineada_dir_float(d) (((d) % sizeof(float)) == 0 )
#define esta_alineada_dir_double(d) (((d) % sizeof(double)) == 0 )

#endif /* end tipos.h */
