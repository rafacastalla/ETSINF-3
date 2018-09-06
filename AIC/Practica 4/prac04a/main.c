/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politécnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: main.c
 *  
 * Description: 
 *    Módulo principal del simulador
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

#define main_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/*** Definiciones Externas *************************************************/

#include "tipos.h"
#include "prediccion.h"
#include "presentacion.h"
#include "instrucciones.h"
#include "algoritmo.h"

extern void ensamblador(FILE*);

/*** Variables Globales ****************************************************/

extern int pos_datos;

/*** Variables Locales *****************************************************/

static boolean f_depuracion;

/*** Funciones Locales *****************************************************/

/***************************************************************
 *
 * Func: inicializa_estructuras
 *
 * Desc: Inicializa las estructuras de la unidad de gestión de
 * instrucciones
 *
 **************************************************************/

static void inicializa_estructuras() {

    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int i, oper;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /* Estadisticas */

    estat.ciclos = 0;
    estat.instrucciones = 0;
    estat.flops = 0;
    estat.saltos_accedidos = 0;
    estat.saltos_encontrados = 0;
    estat.saltos_ejecutados = 0;
    estat.saltos_acertados = 0;

    /* Registros inter-etapas */

    IF_ISS_1.IR.codop = OP_NOP;
    IF_ISS_1.PC = -1;
    IF_ISS_1.orden = 0;
    IF_ISS_1.excepcion = EXC_NONE;

    IF_ISS_2 = IF_ISS_1;

    Control_1.Parar = NO;
    Control_1.Cancelar = NO;
    Control_1.NPC = 0;
    Control_1.orden = 1;

    Control_2 = Control_1;

    for (i = 0; i < NUM_VIAS_ISSUE; i++) {
        M_IF_ISS_1[i] = IF_ISS_1;
        M_IF_ISS_2[i] = IF_ISS_2;
    }

    /* Registros */

    for (i = 0; i < TAM_REGISTROS; i++) {
        Rfp[i].valor.fp_d = 0.0;
        Rfp[i].rob = MARCA_NULA;
        Rint[i].valor.int_d = 0;
        Rint[i].rob = MARCA_NULA;
    }

    Rint[REG_FPSR].rob = MARCA_NULA; /* FPSR */
    Rint[REG_FPSR].valor.int_d = 0; /* FPSR */

    /* Memoria de datos */

    for (i = 0; i < TAM_MEMO_DATOS; i += sizeof (dword)) {
        MD.m_dword[dir_dword(i)] = 0;
    } /* endfor */

    for (i = 0; i < TAM_MEMO_DATOS; i++) {
        md_tipo[i] = t_ninguno;
    } /* endfor */

    /* Memoria de instrucciones */

    for (i = 0; i < TAM_MEMO_INSTRUC; i++) {
        MI[i].codop = OP_NOP;
        MI[i].tipo = FormatoI;
        MI[i].Rdestino = 0;
        MI[i].Rfuente1 = 0;
        MI[i].Rfuente2 = 0;
        MI[i].inmediato = 0;
    } /* endfor */

    /* Predictor */

    inicializa_prediccion();

    /* Estaciones de reserva */

    TAM_ESTACIONES = TAM_RS_ENTEROS + TAM_RS_SUMA_RESTA + TAM_RS_MULT_DIV +
            TAM_TAMPON_LECT + TAM_TAMPON_ESCR;

    for (i = 0; i < TAM_ESTACIONES; i++) {
        RS[i].OP = OP_NOP;
        RS[i].ocupado = NO;
        RS[i].Qj = MARCA_NULA;
        RS[i].Vj.int_d = 0;
        RS[i].Qk = MARCA_NULA;
        RS[i].Vk.int_d = 0;
        RS[i].direccion = 0;
        RS[i].resultado.int_d = 0;
        RS[i].estado = PENDIENTE;
        RS[i].confirm = NO;
        RS[i].rob = MARCA_NULA;
        RS[i].orden = 0;
    } /* endfor */

    /* Reorder Buffer */

    RB_inicio = 0;
    RB_fin = 0;
    RB_long = 0;

    for (i = 0; i < TAM_REORDER; i++) {
        RB[i].OP = OP_NOP;
        RB[i].ocupado = NO;
        RB[i].estado = NONE;
        RB[i].dest = MARCA_NULA;
        RB[i].valor.int_d = 0;
        RB[i].orden = 0;
    } /* endfor */

    /* Operadores */

    if (NUM_OPER_ENTEROS + NUM_OPER_SUMREST + NUM_OPER_MULTDIV +
            NUM_OPER_DIRECCIONES + NUM_OPER_MEMDATOS > MAX_OPERADORES) {
        fprintf(stderr, "ERROR: Número de operadores excesivo actualice la constante MAX_OPERADORES (mínimo %d)",
                NUM_OPER_ENTEROS + NUM_OPER_SUMREST + NUM_OPER_MULTDIV +
                NUM_OPER_DIRECCIONES + NUM_OPER_MEMDATOS);
        exit(1);
    }

    oper = 0;
    for (i = 0; i < NUM_OPER_ENTEROS; i++, oper++) {
        Op[oper].tipo = OPER_ENTEROS;
        Op[oper].ocupado = NO;
        Op[oper].codigo = 0;
        Op[oper].ciclo = 0;
        Op[oper].Teval = TEVAL_ENTEROS;
    }

    for (i = 0; i < NUM_OPER_SUMREST; i++, oper++) {
        Op[oper].tipo = OPER_SUMREST;
        Op[oper].ocupado = NO;
        Op[oper].codigo = 0;
        Op[oper].ciclo = 0;
        Op[oper].Teval = TEVAL_SUMREST;
    }

    for (i = 0; i < NUM_OPER_MULTDIV; i++, oper++) {
        Op[oper].tipo = OPER_MULTDIV;
        Op[oper].ocupado = NO;
        Op[oper].codigo = 0;
        Op[oper].ciclo = 0;
        Op[oper].Teval = TEVAL_MULTDIV;
    }

    for (i = 0; i < NUM_OPER_DIRECCIONES; i++, oper++) {
        Op[oper].tipo = OPER_DIRECCIONES;
        Op[oper].ocupado = NO;
        Op[oper].codigo = 0;
        Op[oper].ciclo = 0;
        Op[oper].Teval = TEVAL_DIRECCIONES;
    }

    for (i = 0; i < NUM_OPER_MEMDATOS; i++, oper++) {
        Op[oper].tipo = OPER_MEMDATOS;
        Op[oper].ocupado = NO;
        Op[oper].codigo = 0;
        Op[oper].ciclo = 0;
        Op[oper].Teval = TEVAL_MEMDATOS;
    }

    NUM_OPERADORES = oper;

    /* Bus común */

    BUS.ocupado = NO;
    BUS.codigo = MARCA_NULA;
    BUS.valor.int_d = 0;

} /* end inicializa_estructuras */

/***************************************************************
 *
 * Func: mira_si_todo_vacio
 *
 * Retorna:  (boolean) 
 *
 * Desc: Mira si queda alguna operación por acabar
 *
 **************************************************************/

static boolean mira_si_todo_vacio(
        ) {
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int i;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    for (i = INICIO_TAMPON_ESCR; i <= FIN_TAMPON_ESCR; i++) {
        if (TE[i].ocupado)
            return (NO);
    } /* endfor */

    return (SI);

} /* end mira_si_todo_vacio */

/***************************************************************
 *
 * Func: ejecutar_codigo
 *
 *
 * Retorna:  RC  (int) 
 *
 * Descripción: 
 *   Ejecuta el bucle principal del computador
 *
 **************************************************************/

static void ejecutar_codigo
(
        ) {
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    boolean final;

    unsigned int m;
    dword validNPC;
    boolean Ignorar, IFstall;
    boolean Lanzada[MAX_VIAS_SUPERESCALAR];

    reg_control_t Bloque;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /*** Inicializacion del computador */

    Ciclo = 0;
    terminando = NO;
    final = NO;

    imprime_inicio();

    /*** Bucle principal */

    for (m = 0; m < NUM_VIAS_ISSUE; m++) {
        Lanzada[m] = NO;
    }

    while (!final) {
        Control_1.Parar = NO;
        Control_1.Cancelar = NO;
        Ignorar = NO;

        Ciclo++; /* Incrementa el número de ciclos
				   ejecutados */

        /*** Fase: EX (1) **********/

        fase_EX_1();

        /*** Fase: COMMIT ***********/

        for (m = 0; m < NUM_VIAS_COMMIT; m++) {
            fase_COM();
        }

        /*** Fase: WB **************/

        for (m = 0; m < NUM_VIAS_BUS; m++) {
            fase_WB();
        }

        /*** Fase: ISSUE ***********/

        IFstall = NO;
        for (m = 0; m < NUM_VIAS_ISSUE; m++) {
            IF_ISS_2 = M_IF_ISS_2[m];
            IF_ISS_2.ignorar = Lanzada[m];
            fase_ISS();
            Lanzada[m] = (!Control_1.Parar || IF_ISS_2.cancelar);
            if (!Lanzada[m]) {
                IFstall = SI;
            }
        }

        /*** Fase: EX (2) **********/

        fase_EX_2();

        /*** Fase: IF **************/

        Bloque = Control_2;
        validNPC = Bloque.NPC; // Sólo para inicializarlo

        for (m = 0; m < NUM_VIAS_ISSUE; m++) {
            // Engañando a la fase de búsqueda
            Control_2.NPC = Bloque.NPC - (Bloque.NPC % (NUM_VIAS_ISSUE*4)) + (m*4);

            fase_IF();

            Control_2.orden = Control_1.orden;

            if (!IFstall) {
                M_IF_ISS_1[m] = IF_ISS_1;

                if (Control_2.NPC < Bloque.NPC || Ignorar) {
                    // Esta instrucción no la queremos ejecutar
                    M_IF_ISS_1[m].cancelar = SI;
                } else if (IF_ISS_1.prediccion) {
                    // Ignorar el resto de instrucciones
                    Ignorar = SI;
                    validNPC = Control_1.NPC;
                } else {
                    // Instrucción normal
                    validNPC = Control_1.NPC;
                }
            }
        }

        if (IFstall) {
            Control_1.orden = Bloque.orden;
        }

        Control_1.NPC = validNPC;

        /*** Estadisticas ***/

        estat.ciclos++;

        /*** Control del simulador ****************/

        if (terminando) {
            if (mira_si_todo_vacio()) {
                final = SI; /* Termina */
            } else {
                Control_2 = Bloque; /* Repetimos bloque */
                Control_2.Parar = SI;
            }
        } else if (!IFstall && !Control_1.Cancelar) { /* Ejecución normal */
            Control_2 = Control_1;
            for (m = 0; m < NUM_VIAS_ISSUE; m++) {
                M_IF_ISS_2[m] = M_IF_ISS_1[m];
                Lanzada[m] = NO;
            }
        } else if (IFstall) { /* Búsqueda parada */
            Control_2 = Bloque; /* Repetimos bloque */
            Control_2.Parar = NO;
        } else { /* Búsqueda cancelada */
            Control_2 = Control_1;
            IF_ISS_2.orden = IF_ISS_1.orden;
            IF_ISS_2.PC = IF_ISS_1.PC;
            for (m = 0; m < NUM_VIAS_ISSUE; m++) {
                M_IF_ISS_2[m].orden = M_IF_ISS_1[m].orden;
                M_IF_ISS_2[m].PC = M_IF_ISS_1[m].PC;
            }
        } /* endif */

        /*** Imprime el estado del los operadores, etc.  */

        if (f_depuracion) {
            imprime_crono();
            imprime_estado();
            imprime_predictor();
        } /* endif */

    } /* endwhile */

    imprime_final();

} /* end ejecutar_codigo */

/***************************************************************
 *
 * Func: error_fatal
 *
 * Descripción: 
 *   Muestra el mensaje y sale
 *
 **************************************************************/

static void error_fatal
(
        char * msg_format,
        char * msg_value
        ) {
    fprintf(stderr, msg_format, msg_value);
    exit(1);
} /* end error_fatal */

/*** Funciones Exportables *************************************************/

/***************************************************************
 *
 * Func: main
 *
 * Parametros:
 *	argc  (int) ; Número de parametros en linea
 *	argv[]  (char*) ; Texto de los parametros en linea
 *
 * Retorna:  RC  (int) 
 *
 * Descripción: 
 *   Función principal
 *
 **************************************************************/

int main
(
        int argc,
        char* argv[]
        ) {
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int RC = 0; /* Valor de retorno */
    int np;

    int argn;
    char * uso =
            "\n%s [OPCIONES] -f <fichero.s>\n"
            "\n\t----- Ejecución -----\n\n"
            "\t-t <fichero.sign>\n"
            "\t          Comprueba que la ejecución corresponde con la que hay en el fichero de firmas.\n"
            "\t-g <fichero.sign>\n"
            "\t          Genera un fichero de firmas correspondiente a la ejecución actual.\n"
            "\t-h\n"
            "\t          Genera un sólo archivo .htm con todos los ficheros de estado y cronogramas.\n"
            "\t-w\n"
            "\t          La salida utiliza direcciones simbólicas"
            "\t-s\n"
            "\t          Ejecuta sin imprimir los ficheros de estado y los cronogramas.\n"
            "\t          Se deshabilita la comprobación de firmas.\n"
            "\t-n\n"
            "\t          No borra archivos html antes de la ejecución.\n"
            "\n\t----- Configuración -----\n\n"
            "\t NOTA: Un valor 0 en cualquier parámetro indica que se mantiene el valor por omisión.\n\n"
            "\t-e <num>:<lat>:<segm>:<er>\n"
            "\t          Número y latencia de los operadores de enteros/saltos, tipo ([s]egmentado/[c]onvencional), y estaciones de reserva\n"
            "\t-l <num>:<lat>:<segm>:<tl>:<te>\n"
            "\t          Número y latencia de los operadores de memoria, tipo ([s]egmentado/[c]onvencional), y tampones de lectura y escritura\n"
            "\t-a <num>:<lat>:<segm>:<er>\n"
            "\t          Número y latencia de los operadores de suma/resta/comparación, tipo ([s]egmentado/[c]onvencional), y estaciones de reserva\n"
            "\t-m <num>:<lat>:<segm>:<er>\n"
            "\t          Número y latencia de los operadores de multiplicación/división, tipo ([s]egmentado/[c]onvencional), y estaciones de reserva\n"
            "\t-r <num>\n"
            "\t          Número de entradas del Reorder Buffer\n"
            "\t-v <issue>:<buses>:<commits>\n"
            "\t          Número de vías del procesador superescalar en ISSUE, BUSES y COMMIT\n"
            "\t-b <num>\n"
            "\t          Número de entradas del BTB\n"
            "\t-c\n"
            "\t          Muestra la configuración y termina.\n"
            "\t-d {b|f}\n"
            "\t          Determina el mecanismo de resolución de dependencias en memoria.\n"
            "\t            [b]: Load Bypassing (opción por omisión)\n"
            "\t            [f]: Load Forwarding\n"
            "\n\t----- Entrada -----\n\n"
            "\t-f <fichero.s>\n"
            "\t          Nombre del fichero en ensamblador\n"
            "";

    FILE* f_entrada = NULL;
    boolean f_firmas = NO;
    boolean borrar_html = SI;

    char tipo_oper;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /*** Lectura de parametros */

    f_depuracion = SI;

    argn = 1;
    if (argc < 2) {
        fprintf(stderr, uso, argv[0]);
        exit(1);
    } /* endif */

    while (argn < argc) {
        if (!strncmp(argv[argn], "-f", 2)) {
            argn++;
            strcpy(nombre_fich, argv[argn]);
            f_entrada = fopen(nombre_fich, "r");
            if (f_entrada == NULL) {
                fprintf(stderr, "%s: Error abriendo fichero '%s'.\n", argv[0], nombre_fich);
                error_fatal(uso, argv[0]);
            } /* endif */
        } else if (!strncmp(argv[argn], "-t", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);
            abre_firma(argv[argn]);
            f_firmas = SI;
        } else if (!strncmp(argv[argn], "-g", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);
            crea_firma(argv[argn]);
            f_firmas = SI;
        } else if (!strncmp(argv[argn], "-w", 2)) {
            f_etiquetas = SI;
        } else if (!strncmp(argv[argn], "-s", 2)) {
            f_depuracion = NO;
        } else if (!strncmp(argv[argn], "-e", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);

            np = sscanf(argv[argn], "%d:%d:%c:%d", &NUM_INICIO_ENTEROS, &TEVAL_ENTEROS, &tipo_oper, &TAM_RS_ENTEROS);
            if (np != 4) {
                fprintf(stderr, "%s: Formato erroneo en el parámetro 'e'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            if (tipo_oper != 's' && tipo_oper != 'c') {
                fprintf(stderr, "%s: Formato erroneo en el tipo del operador del parámetro 'e'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            CHECK_DEFAULT_VALUE(NUM_INICIO_ENTEROS);
            CHECK_DEFAULT_VALUE(TEVAL_ENTEROS);
            CHECK_DEFAULT_VALUE(TAM_RS_ENTEROS);

            NUM_OPER_ENTEROS = (tipo_oper == 'c') ? NUM_INICIO_ENTEROS : NUM_INICIO_ENTEROS * TEVAL_ENTEROS;

        } else if (!strncmp(argv[argn], "-l", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);

            np = sscanf(argv[argn], "%d:%d:%c:%d:%d", &NUM_INICIO_MEMDATOS, &TEVAL_MEMDATOS, &tipo_oper, &TAM_TAMPON_LECT, &TAM_TAMPON_ESCR);
            if (np != 5) {
                fprintf(stderr, "%s: Formato erroneo en el parámetro 'l'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            if (tipo_oper != 's' && tipo_oper != 'c') {
                fprintf(stderr, "%s: Formato erroneo en el tipo del operador del parámetro 'l'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            NUM_OPER_DIRECCIONES = NUM_INICIO_MEMDATOS;
            NUM_INICIO_DIRECCIONES = NUM_INICIO_MEMDATOS;

            CHECK_DEFAULT_VALUE(NUM_INICIO_MEMDATOS);
            CHECK_DEFAULT_VALUE(TEVAL_MEMDATOS);
            CHECK_DEFAULT_VALUE(TAM_TAMPON_LECT);
            CHECK_DEFAULT_VALUE(TAM_TAMPON_ESCR);

            NUM_OPER_MEMDATOS = (tipo_oper == 'c') ? NUM_INICIO_MEMDATOS : NUM_INICIO_MEMDATOS * TEVAL_MEMDATOS;

        } else if (!strncmp(argv[argn], "-a", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);

            np = sscanf(argv[argn], "%d:%d:%c:%d", &NUM_INICIO_SUMREST, &TEVAL_SUMREST, &tipo_oper, &TAM_RS_SUMA_RESTA);
            if (np != 4) {
                fprintf(stderr, "%s: Formato erroneo en el parámetro 'a'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            if (tipo_oper != 's' && tipo_oper != 'c') {
                fprintf(stderr, "%s: Formato erroneo en el tipo del operador del parámetro 'a'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            CHECK_DEFAULT_VALUE(NUM_INICIO_SUMREST);
            CHECK_DEFAULT_VALUE(TEVAL_SUMREST);
            CHECK_DEFAULT_VALUE(TAM_RS_SUMA_RESTA);

            NUM_OPER_SUMREST = (tipo_oper == 'c') ? NUM_INICIO_SUMREST : NUM_INICIO_SUMREST * TEVAL_SUMREST;

        } else if (!strncmp(argv[argn], "-m", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);

            np = sscanf(argv[argn], "%d:%d:%c:%d", &NUM_INICIO_MULTDIV, &TEVAL_MULTDIV, &tipo_oper, &TAM_RS_MULT_DIV);
            if (np != 4) {
                fprintf(stderr, "%s: Formato erroneo en el parámetro 'm'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            if (tipo_oper != 's' && tipo_oper != 'c') {
                fprintf(stderr, "%s: Formato erroneo en el tipo del operador del parámetro 'm'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            CHECK_DEFAULT_VALUE(NUM_INICIO_MULTDIV);
            CHECK_DEFAULT_VALUE(TEVAL_MULTDIV);
            CHECK_DEFAULT_VALUE(TAM_RS_MULT_DIV);

            NUM_OPER_MULTDIV = (tipo_oper == 'c') ? NUM_INICIO_MULTDIV : NUM_INICIO_MULTDIV * TEVAL_MULTDIV;

        } else if (!strncmp(argv[argn], "-r", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);

            TAM_REORDER = atoi(argv[argn]);
            if (TAM_REORDER <= 0 || TAM_REORDER > MAX_REORDER) {
                fprintf(stderr, "%s: Tamaño del reorder buffer inválido\n", argv[0]);
                error_fatal(uso, argv[0]);
            }
        } else if (!strncmp(argv[argn], "-v", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);

            np = sscanf(argv[argn], "%d:%d:%d", &NUM_VIAS_ISSUE, &NUM_VIAS_BUS, &NUM_VIAS_COMMIT);
            if (np != 3) {
                fprintf(stderr, "%s: Formato erroneo en el parámetro 'v'\n", argv[0]);
                error_fatal(uso, argv[0]);
            }

            CHECK_DEFAULT_VALUE(NUM_VIAS_ISSUE);
            CHECK_DEFAULT_VALUE(NUM_VIAS_BUS);
            CHECK_DEFAULT_VALUE(NUM_VIAS_COMMIT);

            if (NUM_VIAS_ISSUE <= 0 || NUM_VIAS_ISSUE > MAX_VIAS_SUPERESCALAR) {
                fprintf(stderr, "%s: Número de vías en ISSUE inválido\n", argv[0]);
                error_fatal(uso, argv[0]);
            }
            if (NUM_VIAS_BUS <= 0 || NUM_VIAS_BUS > MAX_VIAS_SUPERESCALAR) {
                fprintf(stderr, "%s: Número de vías en el BUS inválido\n", argv[0]);
                error_fatal(uso, argv[0]);
            }
            if (NUM_VIAS_COMMIT <= 0 || NUM_VIAS_COMMIT > MAX_VIAS_SUPERESCALAR) {
                fprintf(stderr, "%s: Número de vías en COMMIT inválido\n", argv[0]);
                error_fatal(uso, argv[0]);
            }
        } else if (!strncmp(argv[argn], "-b", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);

            TAM_BUFFER_PREDIC = atoi(argv[argn]);
            if (TAM_BUFFER_PREDIC < 0 || TAM_BUFFER_PREDIC > MAX_BUFFER_PREDIC) {
                fprintf(stderr, "\n%s: Tamaño del BTB inválido\n", argv[0]);
                error_fatal(uso, argv[0]);
            }
        } else if (!strncmp(argv[argn], "-d", 2)) {
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);
            if (!strncmp(argv[argn], "b", 1)) {
                dep_mem = l_bypassing;
            } else if (!strncmp(argv[argn], "f", 1)) {
                dep_mem = l_forwarding;
            } else {
                error_fatal(uso, argv[0]);
            }
        } else if (!strncmp(argv[argn], "-c", 2)) {
            imprime_config();
            exit(0);
        } else if (!strncmp(argv[argn], "-n", 2)) {
            borrar_html = NO;
        } else if (!strncmp(argv[argn], "-h", 2)) {
            html_merge = SI;
        } else if (!strncmp(argv[argn], "-x", 2)) {  // No documentado: Ejecutar hasta un ciclo
            argn++;
            if (argn == argc)
                error_fatal(uso, argv[0]);

            TAM_REORDER = atoi(argv[argn]);
            if (TAM_REORDER <= 0 || TAM_REORDER > MAX_REORDER) {
                fprintf(stderr, "%s: Tamaño del reorder buffer inválido\n", argv[0]);
                error_fatal(uso, argv[0]);
            }
        } else {
            error_fatal(uso, argv[0]);
        } /* endif */

        argn++;
    } /* endwhile */

    if (f_entrada == NULL) {
        fprintf(stderr, "%s: Falta el fichero de entrada.", argv[0]);
        error_fatal(uso, argv[0]);
    } /* endif */

	/*** Borrar html */

    if (borrar_html) {
	int rc __attribute__((unused));
    	rc = system("rm -f *.html 2>/dev/null");
    }

    /*** Inicializacion de estructuras */

    inicializa_estructuras();

    /*** Imprime configuración */

    imprime_config();

    /*** Carga el codigo en lenguaje ensamblador */

    ensamblador(f_entrada);

    /*** Llama al bucle principal */

    ejecutar_codigo();

    if (f_firmas)
        cierra_firma();

    /*** Imprime estadisticas */

    imprime_estadisticas();

    return RC;

} /* end main */

