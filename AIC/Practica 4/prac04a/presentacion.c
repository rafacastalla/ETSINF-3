/**************************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: presentacion.c
 *  
 * Description: Contiene las funciones necesarias para presentar la
 *    información sobre la ejecución del algoritmo
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#define presentacion_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** Definiciones Externas **********************************/

#include "tipos.h"
#include "main.h"
#include "instrucciones.h"
#include "etiquetas.h"
#include "presentacion.h"
#include "memoria.h"

#ifdef MAX
#undef MAX
#endif
#define MAX(x, y) (((x)>(y)) ? (x) : (y))

typedef enum {
    MF_OCIOSO = 0,
    MF_ESCRITURA = 1,
    MF_LECTURA = 2
} modo_firmas_t;

#define LONG_FIRMA 20480
#define FIRMA_DEL_FICHERO "<Fichero de firmas> ssaez@disca.upv.es"

/***** Variables Globales *************************************/

boolean html_merge = NO;

/***** Variables Locales **************************************/

static FILE *f_salida;

static FILE *f_firmas;
static modo_firmas_t modo_firmas = MF_OCIOSO;
static char linea_firma[LONG_FIRMA];
static boolean error_firma = NO;

static ciclo_t primera_instruccion = 1;
static ciclo_t primer_ciclo = 1;
static short maxima_columna_visible = MAX_CICLOS_INIC;

static char campo[64];
static char valor[64];
static char *vstr;

/***** Macros *************************************************/

#define FIRMA_1_1(s1, s2)                       \
    do {                                        \
        strcpy(valor, (s1));                    \
        strcpy(valor, (s2));                    \
        vstr= procesa_firma(campo, valor);      \
    } while (0)

#define FIRMA_1_2(s1, f2, p2)                   \
    do {                                        \
        strcpy(campo, (s1));                    \
        sprintf(valor, (f2), (p2));             \
        vstr= procesa_firma(campo, valor);      \
    } while (0)

#define FIRMA_2_1(f1, p1, s2)                   \
    do {                                        \
        sprintf(campo, (f1),(p1));              \
        strcpy(valor, (s2));                    \
        vstr= procesa_firma(campo, valor);      \
    } while (0)

#define FIRMA_2_2(f1, p1, f2, p2)               \
    do {                                        \
        sprintf(campo, (f1), (p1));             \
        sprintf(valor, (f2), (p2));             \
        vstr= procesa_firma(campo, valor);      \
    } while (0)

#define FIRMA_2_3(f1, p1, f2, p2a, p2b)         \
    do {                                        \
        sprintf(campo, (f1), (p1));             \
        sprintf(valor, (f2), (p2a), (p2b));     \
        vstr= procesa_firma(campo, valor);      \
    } while (0)

/***** Funciones Locales **************************************/

/***************************************************************
 *
 * Func: crea_firma
 *
 * Description: 
 *   Crea un fichero de firmas
 *
 **************************************************************/

void crea_firma
        (
                char *fichero
        ) {
    /*************************************/
    /*  Function body                    */
    /*************************************/

    f_firmas = fopen(fichero, "w");
    if (f_firmas == NULL) {
        fprintf(stderr, "Error creando %s\n", fichero);
        exit(1);
    } /* endif */

    modo_firmas = MF_ESCRITURA;
    fprintf(f_firmas, FIRMA_DEL_FICHERO);

} /* end crea_firma */

/***************************************************************
 *
 * Func: abre_firma
 *
 * Description: 
 *   Abre un fichero de firmas ya existente
 *
 **************************************************************/

void abre_firma
        (
                char *fichero
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char *lin;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    f_firmas = fopen(fichero, "r");
    if (f_firmas == NULL) {
        fprintf(stderr, "Error abriendo %s\n", fichero);
        exit(1);
    } /* endif */

    modo_firmas = MF_LECTURA;

    /*** Comprueba que es un fichero de firmas ***/

    lin = fgets(linea_firma, LONG_FIRMA, f_firmas);
    if (lin == NULL) {
        fprintf(stderr, "Error leyendo el fichero de firmas\n");
        exit(1);
    } /* endif */

    /* Comprueba que la firma es correcta */
    if (strcmp(linea_firma, FIRMA_DEL_FICHERO "\n")) {
        fprintf(stderr, "ERROR. El fichero NO es un fichero de firmas.\n");
        exit(1);
    } /* endif */

} /* end abre_firma */

/***************************************************************
 *
 * Func: nueva_firma
 *
 * Description: 
 *   Comienza la firma de un nuevo ciclo
 *
 **************************************************************/

void nueva_firma
        (
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char *tok;
    char s_ciclo[8];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(s_ciclo, "%lu", Ciclo);

    switch (modo_firmas) {
        case MF_LECTURA: {
            char *lin;
            lin = fgets(linea_firma, LONG_FIRMA, f_firmas);
            if (lin == NULL) {
                fprintf(stderr, "Error leyendo el fichero de firmas\n");
                exit(1);
            } /* endif */

            /* Comprueba que el ciclo es el correcto */
            tok = strtok(linea_firma, "@");
            if (strcmp(tok, s_ciclo)) {
                fprintf(stderr, "ERROR. "
                        "El ciclo actual no coincide con el ciclo del fichero de firmas.\n"
                        "Seguramente no deberías haber alcanzado este ciclo\n");
                exit(1);
            } /* endif */
        }
            break; /* endcase */
        case MF_ESCRITURA: {
            fprintf(f_firmas, "\n%s@", s_ciclo);
        }
            break; /* endcase */
        default:
            break;
    } /* endswitch */

} /* end nueva_firma */

/***************************************************************
 *
 * Func: procesa_firma
 *
 * Description: 
 *   MF_ESCRITURA: Añade un trozo de la firma correspondiente al ciclo actual.
 *   MF_LECTURA: Comprueba si uno de los campos de la firma es correcto.
 *
 *   En cualquier caso devuelve la cadena que se debe insertar 
 *   como valor.
 *
 **************************************************************/

char *procesa_firma
        (
                char *campo,
                char *valor
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char *tok;
    static char msg[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    switch (modo_firmas) {
        case MF_LECTURA: {
            tok = strtok(NULL, "$");
            if (tok == NULL) {
                fprintf(stderr, "%s: %s\n", campo, valor);
                fprintf(stderr, "Error leyendo el fichero de firmas: %d\n", __LINE__);
                exit(1);
            } /* endif */
            if (strcmp(tok, campo)) {
                fprintf(stderr, "ERROR. "
                        "Los nombres de los campos no coinciden con los del fichero de firmas.\n"
                        "Probablemente exista un error en la configuración del simulador\n");
                exit(1);
            } /* endif */

            tok = strtok(NULL, "@");
            if (tok == NULL) {
                fprintf(stderr, "%s: %s\n", campo, valor);
                fprintf(stderr, "Error leyendo el fichero de firmas: %d\n", __LINE__);
                exit(1);
            } /* endif */
            if (strcmp(tok, valor)) {
                if (!strcmp(valor, "&nbsp;"))
                    strcpy(msg, "<i><font color=\"red\"><b> ??? </b></font></i>");
                else
                    sprintf(msg, "<i><font color=\"red\"><b>%s</b></font></i>", valor);

                error_firma = SI;
                return msg;
            } /* endif */
        }
            break; /* endcase */
        case MF_ESCRITURA: {
            fprintf(f_firmas, "%s$%s@", campo, valor);
        }
            break; /* endcase */
        default:
            break;
    } /* endswitch */

    return valor;

} /* end procesa_firma */

/***************************************************************
 *
 * Func: cierra_firma
 *
 * Description: 
 *   Cierra el fichero de firmas
 *
 **************************************************************/

void cierra_firma
        (
        ) {
    /*************************************/
    /*  Function body                    */
    /*************************************/

    fprintf(f_firmas, "\n");
    fclose(f_firmas);

} /* end cierra_firma */

void color_etiqueta_memdatos(
        char *color,
        dword direccion
) {
    int index = te_busca(direccion, m_datos);

    static char *paleta[15] = {
            "red", "darkcyan", "orange", "limegreen", "deeppink", "royalblue", "brown", "seagreen",
            "lightcoral", "magenta", "salmon", "steelblue", "mediumseagreen", "darkorange", "orchid"
    };

    strcpy(color, paleta[index % 15]);

}

/***************************************************************
 *
 * Func: imprime_instruccion
 *
 * Parametros:
 *	instruc  (char *) ; 
 *
 * Descripción: 
 *   Imprime la intrucción localizada en el PC sobre la
 *   cadena de caracteres 'instruc'
 *
 **************************************************************/

void __imprime_instruccion
        (
                char *instruc,
                dword PC,
                char * file,
                int line
        ) {

    if (PC % 4 != 0) {
        fprintf(stderr, "%s:%d ERROR: Dirección incorrecta al imprimir una instrucción (" F_DWORD ")\n", file, line, PC);
    }

    if (!EN_MEMORIA(PC, SegInstruc)) {
        sprintf(instruc, "&lt;unknown&gt;");
        return;
    } /* endif */

    imprime_instruccion_color(instruc, PC, SI);

} /* end imprime_instruccion */

/***************************************************************
 *
 * Func: imprime_codigo
 *
 * Description: 
 *   Obtiene el nombre de una estación de reserva
 *
 **************************************************************/

static void imprime_codigo
        (
                marca_t s,
                char *nom
        ) {
    /*************************************/
    /*  Function body                    */
    /*************************************/

    if (/* s >= INICIO_RS_ENTEROS && */ /* Es siempre cierto en está
                                           implementación */
            s <= FIN_RS_ENTEROS) {
        sprintf(nom, "e%d", s - INICIO_RS_ENTEROS + 1);
    } else if (s >= INICIO_RS_SUMA_RESTA &&
               s <= FIN_RS_SUMA_RESTA) {
        sprintf(nom, "a%d", s - INICIO_RS_SUMA_RESTA + 1);
    } else if (s >= INICIO_RS_MULT_DIV &&
               s <= FIN_RS_MULT_DIV) {
        sprintf(nom, "m%d", s - INICIO_RS_MULT_DIV + 1);
    } else if (s >= INICIO_TAMPON_LECT &&
               s <= FIN_TAMPON_LECT) {
        sprintf(nom, "l%d", s - INICIO_TAMPON_LECT + 1);
    } else if (s >= INICIO_TAMPON_ESCR &&
               s <= FIN_TAMPON_ESCR) {
        sprintf(nom, "s%d", s - INICIO_TAMPON_ESCR + 1);
    } else {
        nom[0] = '\0'; /* Invalido o marca nula */
    } /* endif */

} /* end imprime_codigo */

/***************************************************************
 *
 * Func: imprime_operacion
 *
 * Description: 
 *   Obtiene el nombre de una estación de reserva
 *
 **************************************************************/

static void imprime_operacion
        (
                codop_t c,
                char *nom
        ) {
    /*************************************/
    /*  Function body                    */
    /*************************************/

    switch (c) {
        case OP_FP_GT_D:
            sprintf(nom, ">");
            break;
        case OP_FP_LT_D:
            sprintf(nom, "<");
            break;
        case OP_FP_MUL_D:
            sprintf(nom, "*");
            break;
        case OP_FP_DIV_D:
            sprintf(nom, "/");
            break;
        case OP_FP_ADD_D:
        case OP_DADD:
        case OP_DADDI:
            sprintf(nom, "+");
            break;
        case OP_FP_SUB_D:
        case OP_DSUB:
        case OP_DSUBI:
            sprintf(nom, "-");
            break;
        case OP_BC1T:
        case OP_BC1F:
        case OP_BNEZ:
        case OP_BEQZ:
        case OP_BNE:
        case OP_BEQ:
            sprintf(nom, "B");
            break;
        default:
            sprintf(nom, "?");
            break;
    } /* endswitch */

} /* end imprime_operacion */

/***************************************************************
 *
 * Func: imprime_estado_predictor
 *
 * Description: 
 *   Obtiene el nombre de una estación de reserva
 *
 **************************************************************/

static void imprime_estado_predictor
        (
                char *nom,
                estado_predic_t e
        ) {
    /*************************************/
    /*  Function body                    */
    /*************************************/

    switch (e) {
        case NO_SALTA:
            sprintf(nom, "<font color=\"orange\">NO Salta</font>");
            break;
        case NO_SALTA_UN_FALLO:
            sprintf(nom, "<font color=\"orange\">NO Salta (1 fallo)</font>");
            break;
        case SALTA_UN_FALLO:
            sprintf(nom, "<font color=\"green\">Salta (1 fallo)</font>");
            break;
        case SALTA:
            sprintf(nom, "<font color=\"green\">Salta</font>");
            break;
        default:
            sprintf(nom, "?");
            break;
    } /* endswitch */

} /* end imprime_estado_predictor */

/***************************************************************
 *
 * Func: desplazamiento_horizontal
 *
 * Description: 
 *   Desplaza la zona visible un ciclo hacia la izquierda
 *
 **************************************************************/

static void desplazamiento_horizontal
        (
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i, j;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    for (i = 0; i < MAX_INSTRUC; i++) {
        for (j = 0; j < MAX_CICLOS - 1; j++)
            strcpy(crono[i].fase[j], crono[i].fase[j + 1]);

        /* Borra la Última columna */
        strcpy(crono[i].fase[j], "");
    } /* endfor */

    /*** Actualiza los desplazamientos iniciales ***/

    primer_ciclo++;

} /* end desplazamiento_horizontal */

/***************************************************************
 *
 * Func: desplazamiento_vertical
 *
 * Description: 
 *   Desplaza la zona visible un ciclo hacia la izquierda
 *
 **************************************************************/

static void desplazamiento_vertical
        (
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i, j, desp;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    /* Averigua si la linea se va a quedar vacia al principio */
    for (desp = 0;
         desp < MAX_CICLOS &&
         !strlen(crono[1].fase[desp]); desp++);
    if (desp == MAX_CICLOS)
        desp = 1; /* La línea está completamente vacia. Avanzamos sólo un
                                   * ciclo */

    for (i = 0; i < MAX_INSTRUC - 1; i++) {
        crono[i].PC = crono[i + 1].PC;
        strcpy(crono[i].inst, crono[i + 1].inst);

        for (j = 0; j < MAX_CICLOS - desp; j++)
            strcpy(crono[i].fase[j], crono[i + 1].fase[j + desp]);

        /* Borra las últimas columnas */
        for (j = MAX_CICLOS - desp; j < MAX_CICLOS; j++)
            strcpy(crono[i].fase[j], "");
    } /* endfor */

    /* Borra la última fila */
    strcpy(crono[MAX_INSTRUC - 1].inst, "");
    for (j = 0; j < MAX_CICLOS; j++)
        strcpy(crono[MAX_INSTRUC - 1].fase[j], "");

    /*** Actualiza los desplazamientos iniciales ***/

    primer_ciclo += desp;
    primera_instruccion++;
    maxima_columna_visible -= desp;

} /* end desplazamiento_vertical */

/***** Funciones Exportables **********************************/

/***************************************************************
 *
 * Func: init_instruc
 *
 * Description: 
 *   Inicializa una instrucción en el cronograma
 *
 **************************************************************/

void init_instruc
        (
                dword PC,
                ciclo_t orden
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    int o;
    char aux[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    if (orden == primera_instruccion + MAX_INSTRUC)
        desplazamiento_vertical();

    o = orden - primera_instruccion;

    imprime_instruccion(aux, PC);
    crono[o].PC = PC;
    sprintf(crono[o].inst, "%s", aux);

} /* end init_instruc */

/***************************************************************
 *
 * Func: muestra_fase
 *
 * Description: 
 *   Muestra la fase de cada instrucción en el cronograma
 *
 **************************************************************/

void muestra_fase
        (
                char *fase,
                ciclo_t orden
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    int o, c;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    if (Ciclo >= primer_ciclo + MAX_CICLOS)
        desplazamiento_horizontal();

    o = orden - primera_instruccion;
    c = Ciclo - primer_ciclo;

    if (o >= 0 && c >= 0) {
        strcpy(crono[o].fase[c], fase);
        if (c + 1 > maxima_columna_visible)
            maxima_columna_visible = c + 1;
    } /* endif */

} /* end muestra_fase */

/***************************************************************
 *
 * Func: imprime_inicio
 *
 * Desc: Imprime el cronograma de ejecución
 *
 **************************************************************/

void imprime_inicio
        (
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i;

    char aux[128];
    char color[64];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    if (html_merge == SI) {
        sprintf(aux, "%s.htm", nombre_fich);
    } else {
        sprintf(aux, "index.html");
    } /* endif */

    f_salida = fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */

    if (html_merge == SI) {
        fputs("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
                      "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                      "<head>\n"
                      "<title>HTML merge</title>\n"
                      "<!--\n"
                      "     Iframe occupies the whole body\n"
                      "-->\n"
                      "<style type=\"text/css\">\n"
                      "  body, html\n"
                      "  {\n"
                      "     margin: 0; padding: 0; height: 100%; overflow: hidden;\n"
                      "  }\n"
                      "\n"
                      "  #content\n"
                      "  {\n"
                      "     position:absolute; left: 0; right: 0; bottom: 0; top: 0px;\n"
                      "  }\n"
                      "</style>\n"
                      "\n"
                      "<script>\n"
                      "\n"
                      "var files={\n"
                      "'index.html':`",
              f_salida);
    } /* endif */

    /*** HTML INTRO ***/

    fprintf(f_salida,
            "<html><head><title>mips-especulacion: %s. Ciclo %lu</title></head>\n",
            nombre_fich, Ciclo);
    fprintf(f_salida,
            "<body bgcolor=\"white\">\n");

    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n");
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    fprintf(f_salida, "<a href=\"estado%03d.html\">Estado</a>\n", 1);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"crono%03d.html\">Cronograma</a>\n", 1);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"predictor%03d.html\">BTB</a>\n", 1);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<tt><b>Programa: %s</b></tt>\n", nombre_fich);
    fprintf(f_salida, "<br>\n");
    fprintf(f_salida, "<br>\n");

    /*** Datos de la implementación ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr valign=\"top\"><td>\n");

    /*** Estructuras ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td>Estructura</td>\n");
    fprintf(f_salida, "  <td align=\"center\">N&uacute;mero</td>\n");
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Registros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_REGISTROS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Reorder&nbsp;Buffer</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_REORDER);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Suma/Resta</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_SUMA_RESTA);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Multiplicaci&oacute;n/Divisi&oacute;n</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_MULT_DIV);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Enteros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_ENTEROS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Tamp&oacute;n&nbsp;de&nbsp;lectura</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_TAMPON_LECT);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Tamp&oacute;n&nbsp;de&nbsp;escritura</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_TAMPON_ESCR);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Buffer&nbsp;predictor</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_BUFFER_PREDIC);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, "</table><br>\n");


    fprintf(f_salida, "  </td><td>\n");

    /*** Tiempos de evaluación ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td>Operador</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Cantidad</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Latencia</td>\n");
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Suma/Resta</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", NUM_OPER_SUMREST);
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_SUMREST);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Multiplicaci&oacute;n/Divisi&oacute;n</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", NUM_OPER_MULTDIV);
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_MULTDIV);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Enteros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", NUM_OPER_ENTEROS);
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_ENTEROS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Memoria de datos</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", NUM_OPER_MEMDATOS);
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_MEMDATOS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, "</table><br>\n");

    fprintf(f_salida, "  </td></tr>\n");
    fprintf(f_salida, "</table><br>\n");

    /*** Memorias ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr  valign=\"top\" bgcolor=\"#ddeeff\">\n");
    fprintf(f_salida, "  <td>Memoria&nbsp;de&nbsp;datos</td>\n");
    fprintf(f_salida, "  <td>Memoria&nbsp;de&nbsp;instrucciones</td>\n");
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr valign=\"top\"><td>\n");

    /*** Contenido de la memoria de datos ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"75\">Direcci&oacute;n</td>\n");
    fprintf(f_salida, "  <td width=\"75\">Datos</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (i = SegDatos.inicio; i < SegDatos.final; i += sizeof(double)) {
        fprintf(f_salida, " <tr>\n");
        te_etiqueta(aux, i, m_datos);
        color_etiqueta_memdatos(color, i);
        fprintf(f_salida, "  <td align=\"left\" nowrap='nowrap' bgcolor=\"#ddeeff\">"
                "<span style='color: %s; margin: 0 0.5em'>%s</span></td>\n", color, aux);
        fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" nowrap='nowrap' align=\"right\">%.2f</td>\n",
                MD.m_double[dir_double(i)]);
        fprintf(f_salida, " </tr>\n");

    } /* endif */

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "  </td><td>\n");

    /*** Contenido de la memoria de instrucciones ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"75\">Direcci&oacute;n</td>\n");
    fprintf(f_salida, "  <td width=\"200\">Instrucciones</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (i = SegInstruc.inicio; i < SegInstruc.final; i+= 4) {
        fprintf(f_salida, " <tr>\n");
        te_etiqueta(aux, i, m_instruc);
        fprintf(f_salida, "  <td align=\"right\" nowrap='nowrap' bgcolor=\"#ddeeff\">"
                "%s&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", aux);
        imprime_instruccion(aux, i);
        fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" nowrap='nowrap'>%s</td>\n", aux);
        fprintf(f_salida, " </tr>\n");
    }

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "  </td></tr>\n");
    fprintf(f_salida, "</table><br>\n");

    fprintf(f_salida, "<address>Arquitectura e Ingenier&iacute;a de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n");

    if (html_merge == SI) {
        fputs("`,", f_salida);
    } else {
        fclose(f_salida);
    } /* endif */

} /* end imprime_inicio */

/***************************************************************
 *
 * Func: imprime_final
 *
 * Desc: Imprime el cronograma de ejecución
 *
 **************************************************************/

void imprime_final
        (
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i;

    char aux[128];
    char color[64];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "final.html");
    if (html_merge == SI) {
        fprintf(f_salida, "'%s':`", aux);
    } else {
        f_salida = fopen(aux, "w");
        if (f_salida == NULL) {
            fprintf(stderr, "Error creando %s\n", aux);
            exit(1);
        } /* endif */
    } /* endif */

    /*** HTML INTRO ***/

    fprintf(f_salida,
            "<html><head><title>mips-especulacion: %s. Ciclo %lu</title></head>\n",
            nombre_fich, Ciclo);
    fprintf(f_salida,
            "<body bgcolor=\"white\">\n");

    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n");
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    fprintf(f_salida, "<a href=\"estado%03d.html\">Estado</a>\n", 1);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"crono%03d.html\">Cronograma</a>\n", 1);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"predictor%03d.html\">BTB</a>\n", 1);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<tt><b>Programa: %s</b></tt>\n", nombre_fich);
    fprintf(f_salida, "<br>\n");
    fprintf(f_salida, "<br>\n");

    /*** Resultados de la ejecucion ***/

    fprintf(f_salida, "<table>\n");
    fprintf(f_salida, "<tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td>Ciclos</td>\n");
    fprintf(f_salida, "  <td>Instrucciones</td>\n");
    fprintf(f_salida, "  <td>CPI</td>\n");
    fprintf(f_salida, "  <td>Op. CF</td>\n");
    fprintf(f_salida, "  <td>Op. CF/ciclo</td>\n");
    fprintf(f_salida, "  <td>Saltos buscados</td>\n");
    fprintf(f_salida, "  <td>Saltos en BTB</td>\n");
    fprintf(f_salida, "  <td>Saltos ejecutados (C)</td>\n");
    fprintf(f_salida, "  <td>Saltos acertados</td>\n");
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "<tr bgcolor=\"#eeeeee\">\n");
    fprintf(f_salida, "  <td>%ld</td>\n", estat.ciclos);
    fprintf(f_salida, "  <td>%ld</td>\n", estat.instrucciones);
    fprintf(f_salida, "  <td>%1.2f</td>\n", (float) estat.ciclos / estat.instrucciones);
    fprintf(f_salida, "  <td>%ld</td>\n", estat.flops);
    fprintf(f_salida, "  <td>%1.2f</td>\n", (float) estat.flops / estat.ciclos);
    fprintf(f_salida, "  <td>%ld </td>\n", estat.saltos_accedidos);
    fprintf(f_salida, "  <td>%ld (%2.1f%%)</td>\n", estat.saltos_encontrados,
            (float) (estat.saltos_encontrados * 100) / estat.saltos_accedidos);
    fprintf(f_salida, "  <td>%ld (%2.1f%%)</td>\n", estat.saltos_ejecutados,
            (float) (estat.saltos_ejecutados * 100) / estat.instrucciones);
    fprintf(f_salida, "  <td>%ld (%2.1f%%)</td>\n", estat.saltos_acertados,
            (float) (estat.saltos_acertados * 100) / estat.saltos_ejecutados);
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table><br>\n");

    /*** Datos de la implementación ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr valign=\"top\"><td>\n");

    /*** Estructuras ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td>Estructura</td>\n");
    fprintf(f_salida, "  <td align=\"center\">N&uacute;mero</td>\n");
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Registros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_REGISTROS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Reorder&nbsp;Buffer</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_REORDER);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Suma/Resta</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_SUMA_RESTA);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Multiplicaci&oacute;n/Divisi&oacute;n</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_MULT_DIV);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Enteros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_ENTEROS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Tamp&oacute;n&nbsp;de&nbsp;lectura</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_TAMPON_LECT);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Tamp&oacute;n&nbsp;de&nbsp;escritura</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_TAMPON_ESCR);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Buffer&nbsp;predictor</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_BUFFER_PREDIC);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, "</table><br>\n");


    fprintf(f_salida, "  </td><td>\n");

    /*** Tiempos de evaluación ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td>Operador</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Cantidad</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Latencia</td>\n");
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Suma/Resta</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", NUM_OPER_SUMREST);
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_SUMREST);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Multiplicaci&oacute;n/Divisi&oacute;n</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", NUM_OPER_MULTDIV);
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_MULTDIV);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Enteros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", NUM_OPER_ENTEROS);
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_ENTEROS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Memoria de datos</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", NUM_OPER_MEMDATOS);
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_MEMDATOS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, "</table><br>\n");

    fprintf(f_salida, "  </td></tr>\n");
    fprintf(f_salida, "</table><br>\n");

    /*** Memorias ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr  valign=\"top\" bgcolor=\"#ddeeff\">\n");
    fprintf(f_salida, "  <td>Memoria&nbsp;de&nbsp;datos</td>\n");
    fprintf(f_salida, "  <td>Memoria&nbsp;de&nbsp;instrucciones</td>\n");
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr valign=\"top\"><td>\n");

    /*** Contenido de la memoria de datos ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"75\">Direcci&oacute;n</td>\n");
    fprintf(f_salida, "  <td width=\"75\">Datos</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (i = SegDatos.inicio; i < SegDatos.final; i += sizeof(double)) {
        fprintf(f_salida, " <tr>\n");
        te_etiqueta(aux, i, m_datos);
        color_etiqueta_memdatos(color, i);
        fprintf(f_salida, "  <td align=\"left\" nowrap='nowrap' bgcolor=\"#ddeeff\">"
                "<span style='color: %s; margin: 0 0.5em'>%s</span></td>\n", color, aux);
        fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" nowrap='nowrap' align=\"right\">%.2f</td>\n",
                MD.m_double[dir_double(i)]);
        fprintf(f_salida, " </tr>\n");

    } /* endif */

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "  </td><td>\n");

    /*** Contenido de la memoria de instrucciones ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"75\">Direcci&oacute;n</td>\n");
    fprintf(f_salida, "  <td width=\"200\">Instrucciones</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (i = SegInstruc.inicio; i < SegInstruc.final; i+= 4) {
        fprintf(f_salida, " <tr>\n");
        te_etiqueta(aux, i, m_instruc);
        fprintf(f_salida, "  <td align=\"right\" nowrap='nowrap' bgcolor=\"#ddeeff\">"
                "%s&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", aux);
        imprime_instruccion(aux, i);
        fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" nowrap='nowrap'>%s</td>\n", aux);
        fprintf(f_salida, " </tr>\n");
    }

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "  </td></tr>\n");
    fprintf(f_salida, "</table><br>\n");

    fprintf(f_salida, "<address>Arquitectura e Ingenier&iacute;a de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n");

    if (html_merge == SI) {
        fputs("`};\n"
                      "\n"
                      "function get_iframedoc()\n"
                      "{\n"
                      "   var iframe = document.getElementById('iframe');\n"
                      "   var iframedoc = iframe.document;\n"
                      "      if (iframe.contentDocument)\n"
                      "      {\n"
                      "         iframedoc = iframe.contentDocument;\n"
                      "      }\n"
                      "      else if (iframe.contentWindow)\n"
                      "      {\n"
                      "         iframedoc = iframe.contentWindow.document;\n"
                      "      }\n"
                      "   return iframedoc;\n"
                      "}\n"
                      "\n"
                      "//\n"
                      "// loads file on iframe\n"
                      "//\n"
                      "function load_file(file)\n"
                      "{\n"
                      "   var iframedoc = get_iframedoc();\n"
                      "\n"
                      "   if (iframedoc)\n"
                      "   {\n"
                      "      iframedoc.open();\n"
                      "      iframedoc.writeln(files[file]);\n"
                      "      iframedoc.close();\n"
                      "   }\n"
                      "   else\n"
                      "   {\n"
                      "      alert('Cannot inject dynamic contents into iframe.');\n"
                      "   }\n"
                      "}\n"
                      "\n"
                      "function check_anchor_click(event)\n"
                      "{\n"
                      "\n"
                      "   if (event.target.tagName !== 'A')\n"
                      "   {\n"
                      "      return;\n"
                      "   }\n"
                      "\n"
                      "   event.preventDefault();\n"
                      "   load_file(event.target.href.split('/').pop());\n"
                      "}\n"
                      "\n"
                      "function init_page()\n"
                      "{\n"
                      "   var iframedoc = get_iframedoc();\n"
                      "\n"
                      "   document.title = iframedoc.title;\n"
                      "   iframedoc.addEventListener('click', check_anchor_click, false);\n"
                      "}\n"
                      "\n"
                      "</script>\n"
                      "</head>\n"
                      "<!--\n"
                      "     loads 'index.html' on first load\n"
                      "-->\n"
                      "<body onLoad='load_file(\"index.html\")'>\n"
                      "\n"
                      "<div id=\"content\">\n"
                      "   <iframe id=\"iframe\" width=\"100%\" height=\"100%\" frameborder=\"0\" src=\"about:blank\" onLoad=\"init_page()\" />\n"
                      "</div>\n"
                      "\n"
                      "</body>\n"
                      "</html>\n",
              f_salida);
    } /* endif */

    fclose(f_salida);

} /* end imprime_final */

/***************************************************************
 *
 * Func: imprime_estado
 *
 * Desc: Imprime el estado de las estructuras de coma flotante
 *
 **************************************************************/

void imprime_estado
        (
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    marca_t s;
    int i, next;

    char aux[128];
    char color[64];
    char *clase;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "estado%03ld.html", Ciclo);
    if (html_merge == SI) {
        fprintf(f_salida, "'%s':`", aux);
    } else {
        f_salida = fopen(aux, "w");
        if (f_salida == NULL) {
            fprintf(stderr, "Error creando %s\n", aux);
            exit(1);
        } /* endif */
    } /* endif */

    nueva_firma(); /*** FIRMAS ***/

    /*** HTML INTRO ***/

    fprintf(f_salida,
            "<html><head><title>Estado: %s. Ciclo %lu</title>\n",
            nombre_fich, Ciclo);
    fprintf(f_salida, "<style type='text/css'>");
    fprintf(f_salida, ".old td {color:#aaa; font-style: italic;}");
    fprintf(f_salida, "</style>");
    fprintf(f_salida, "</head>");
    fprintf(f_salida,
            "<body bgcolor=\"white\">\n");

    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n");
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    if (Ciclo > 5)
        fprintf(f_salida, "<a href=\"estado%03ld.html\">[-5]</a>&nbsp;\n",
                Ciclo - 5);
    else
        fprintf(f_salida, "[-5]&nbsp;\n");
    if (Ciclo > 1)
        fprintf(f_salida, "<a href=\"estado%03ld.html\">[-1]</a>&nbsp;\n",
                Ciclo - 1);
    else
        fprintf(f_salida, "[-1]\n");

    fprintf(f_salida, "<a href=\"estado%03ld.html\">[+1]</a>\n", Ciclo + 1);
    fprintf(f_salida, "<a href=\"estado%03ld.html\">[+5]</a>\n", Ciclo + 5);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<!a href=\"estado%03ld.html\">Estado<!/a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"crono%03ld.html\">Crono</a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"predictor%03ld.html\">BTB</a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<tt><b>Programa: %s</b></tt>\n", nombre_fich);
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<b>Ciclo: %lu</b>\n", Ciclo);
    fprintf(f_salida, "<br>\n");

    fprintf(f_salida, "<p>Estado al final del ciclo\n");


    /*** ORGANIZACIÖN EN DOS COLUMNAS  */
    fprintf(f_salida, "<table>\n");
    fprintf(f_salida, "<tr valign=\"top\">\n");
    fprintf(f_salida, "<td>\n");

    /*** Bancos de registros ***/

    fprintf(f_salida, "<table>\n");

    /* Banco de registros de coma flotante */

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"50\" bgcolor=\"white\">&nbsp;</td>\n");
    for (i = 0; i < TAM_REGISTROS; i++) {
        fprintf(f_salida, "  <td width=\"75\" align=\"center\">F%d</td>\n", i);
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    fprintf(f_salida, "  <td width=\"50\" bgcolor=\"#ddeeff\">rob</td>\n");
    for (i = 0; i < TAM_REGISTROS; i++) {
        if (Rfp[i].rob != MARCA_NULA) {
            FIRMA_2_2("F%d.rob", i, "#&nbsp;%d", Rfp[i].rob);
            fprintf(f_salida,
                    "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);
        } else {
            FIRMA_2_1("F%d.rob", i, "&nbsp;");
            fprintf(f_salida, "  <td>%s</td>\n", vstr);
        } /* endif */
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    fprintf(f_salida, "  <td width=\"50\" bgcolor=\"#ddeeff\">valor</td>\n");
    for (i = 0; i < TAM_REGISTROS; i++) {
        FIRMA_2_2("F%d.valor", i, "%.2f", Rfp[i].valor.fp_d);
        if (Rfp[i].rob != MARCA_NULA) {
            fprintf(f_salida,
                    "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);
        } else {
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    /* Banco de registros de enteros */

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"50\" bgcolor=\"white\">&nbsp;</td>\n");
    for (i = 0; i < TAM_REGISTROS; i++) {
        fprintf(f_salida, "  <td width=\"75\" align=\"center\">R%d</td>\n", i);
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    fprintf(f_salida, "  <td width=\"50\" bgcolor=\"#ddeeff\">rob</td>\n");
    for (i = 0; i < TAM_REGISTROS; i++) {
        if (Rint[i].rob != MARCA_NULA) {
            FIRMA_2_2("R%d.rob", i, "#&nbsp;%d", Rint[i].rob);
            fprintf(f_salida,
                    "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);
        } else {
            FIRMA_2_1("R%d.rob", i, "&nbsp;");
            fprintf(f_salida, "  <td>%s</td>\n", vstr);
        } /* endif */
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    fprintf(f_salida, "  <td width=\"50\" bgcolor=\"#ddeeff\">valor</td>\n");
    for (i = 0; i < TAM_REGISTROS; i++) {
        FIRMA_2_2("R%d.valor", i, F_DWORD, Rint[i].valor.int_d);
        if (Rint[i].rob != MARCA_NULA) {
            fprintf(f_salida,
                    "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);
        } else {
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, "</table><br>\n");

    fprintf(f_salida, "<table bgcolor=\"white\">\n");
    fprintf(f_salida, " <tr valign=\"top\"><td>\n");

    /*** Reorder buffer ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"25\">Cod</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"40\">Busy</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"125\">Instrucci&oacute;n</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Est.</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"100\">Destino</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"75\">Valor</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"75\">Predic.</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Exc.</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">PC</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (i = 0; i < TAM_REORDER; i++) {
        if (!RB[i].ocupado && RB[i].orden > 0) {
            clase = "old";
        } else {
            clase = "normal";
        }

        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\" class=\"%s\">\n", clase);

        if (i == RB_inicio)
            fprintf(f_salida,
                    "  <td bgcolor=\"#ffddaa\" align=\"center\">%d</td>\n", i);
        else
            fprintf(f_salida,
                    "  <td bgcolor=\"#ddeeff\" align=\"center\">%d</td>\n", i);

        if (RB[i].ocupado || (!RB[i].ocupado && RB[i].orden > 0)) {
            FIRMA_2_1("ROB%d.ocupado", i, (RB[i].ocupado) ? "SI" : "NO");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            imprime_instruccion(aux, RB[i].PC);
            FIRMA_2_1("ROB%d.inst", i, aux);
            fprintf(f_salida, "  <td align=\"center\" nowrap=\"nowrap\">%s</td>\n", vstr);

            FIRMA_2_1("ROB%d.estado", i, (RB[i].estado == EX) ? "EX" : ((RB[i].estado == WB) ? "WB" : "ERR"));
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            if (inst_store(RB[i].OP)) {
                imprime_codigo(RB[i].dest, aux);
                FIRMA_2_1("ROB%d.dest", i, aux);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

                FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("ROB%d.pred", i, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } else if (inst_branch_int(RB[i].OP)) {
                te_etiqueta(aux, RB[i].dest, m_instruc);

                FIRMA_2_1("ROB%d.dest", i, aux);
                fprintf(f_salida, "  <td align=\"center\" nowrap='nowrap'>%s</td>\n", vstr);
                if (RB[i].estado == WB) {
                    FIRMA_2_1("ROB%d.valor", i, (RB[i].valor.int_d) ? "Salta" : "No salta");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n",
                            vstr);
                } else {
                    FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                } /* endif */

                FIRMA_2_1("ROB%d.pred", i, (RB[i].prediccion) ? "Salta" : "No salta");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } else if (inst_branch_fp(RB[i].OP)) {
                te_etiqueta(aux, RB[i].dest, m_instruc);

                FIRMA_2_1("ROB%d.dest", i, aux);
                fprintf(f_salida, "  <td align=\"center\" nowrap='nowrap'>%s</td>\n", vstr);
                if (RB_inicio == i) {
                    if (RB[i].OP == OP_BC1T) {
                        FIRMA_2_1("ROB%d.valor", i, (Rint[REG_FPSR].valor.int_d) ? "Salta" : "No salta");
                    } else {
                        FIRMA_2_1("ROB%d.valor", i, (!Rint[REG_FPSR].valor.int_d) ? "Salta" : "No salta");
                    } /* endif */
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n",
                            vstr);
                } else {
                    FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                } /* endif */

                FIRMA_2_1("ROB%d.pred", i, (RB[i].prediccion) ? "Salta" : "No salta");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } else if (inst_fpsr(RB[i].OP)) {
                FIRMA_2_1("ROB%d.dest", i, "fpsr");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                if (RB[i].estado == WB) {
                    FIRMA_2_1("ROB%d.valor", i, (RB[i].valor.int_d) ? "Cierto" : "Falso");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                } else {
                    FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                } /* endif */
                FIRMA_2_1("ROB%d.pred", i, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } else if (RB[i].OP != OP_NOP && RB[i].OP != OP_TRAP) {
                FIRMA_2_2("ROB%d.dest", i, F_DWORD, RB[i].dest);
                fprintf(f_salida, "  <td align=\"center\">%s%s</td>\n", (inst_int(RB[i].OP)) ? "R" : "F", vstr);

                if (RB[i].estado == WB)
                    if (inst_int(RB[i].OP))
                        FIRMA_2_2("ROB%d.valor", i, F_DWORD, RB[i].valor.int_d);
                    else
                        FIRMA_2_2("ROB%d.valor", i, "%.2f", RB[i].valor.fp_d);
                else
                    FIRMA_2_1("ROB%d.valor", i, "&nbsp;");

                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("ROB%d.pred", i, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } else {
                FIRMA_2_1("ROB%d.dest", i, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("ROB%d.pred", i, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            if (RB[i].excepcion != EXC_NONE)
                FIRMA_2_2("ROB%d.exc", i, "%d", RB[i].excepcion);
            else
                FIRMA_2_1("ROB%d.exc", i, "&nbsp;");

            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            te_etiqueta(aux, RB[i].PC, m_instruc);
            FIRMA_2_1("ROB%d.pc", i, aux);
            fprintf(f_salida, "  <td align=\"center\" nowrap='nowrap'>%s</td>\n", vstr);
        } else {
            FIRMA_2_1("ROB%d.ocupado", i, "NO");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("ROB%d.inst", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("ROB%d.estado", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("ROB%d.dest", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("ROB%d.pred", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("ROB%d.exc", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("ROB%d.pc", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */

        fprintf(f_salida, " </tr>\n");
    } /* endfor */

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "  </td><td>\n");

    /*** Estaciones de reserva ***/

    /* Contenido de las estaciones de reserva */

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"25\">Cod</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"40\">Busy</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Op</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Qj</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"75\">Vj</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Qk</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"75\">Vk</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">rob</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Resultado</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Estado</td>\n");
    fprintf(f_salida, " </tr>\n");

    /*** Estaciones de reserva de enteros ***/

    for (s = INICIO_RS_ENTEROS;
         s <= FIN_RS_ENTEROS; s++) {

        if (!RS[s].ocupado && RS[s].orden > 0) {
            clase = "old";
        } else {
            clase = "normal";
        }

        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\" class=\"%s\">\n", clase);

        imprime_codigo(s, aux);
        FIRMA_2_1("RS%d.cod", s, aux);
        fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);

        if (RS[s].ocupado || (!RS[s].ocupado && RS[s].orden > 0)) {
            FIRMA_2_1("RS%d.ocupado", s, (RS[s].ocupado) ? "SI" : "NO");
            fprintf(f_salida, "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);

            imprime_operacion(RS[s].OP, aux);
            FIRMA_2_1("RS%d.op", s, aux);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            if (RS[s].Qj != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qj", s, "#&nbsp;%d", RS[s].Qj);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                FIRMA_2_2("RS%d.Vj", s, F_DWORD, RS[s].Vj.int_d);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            if (RS[s].Qk != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qk", s, "#&nbsp;%d", RS[s].Qk);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vk", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qk", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                FIRMA_2_2("RS%d.Vk", s, F_DWORD, RS[s].Vk.int_d);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", RS[s].rob);
            fprintf(f_salida, "  <td>%s</td>\n", vstr);

            switch (RS[s].estado) {
                case EN_CURSO:
                    FIRMA_2_1("RS%d.result", s, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_3("RS%d.est", s, "%d/%d", Op[RS[s].operador].ciclo, Op[RS[s].operador].Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                case FINALIZADA:
                    FIRMA_2_2("RS%d.result", s, F_DWORD, RS[s].resultado.int_d);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_1("RS%d.est", s, "end");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                default:
                    FIRMA_2_1("RS%d.result", s, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_1("RS%d.est", s, "&nbsp;");
                    fprintf(f_salida, "  <td>%s</td>\n", vstr);
            }
        } else {
            FIRMA_2_1("RS%d.ocupado", s, "NO");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.op", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qk", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vk", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.rob", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.result", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.est", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */

        fprintf(f_salida, " </tr>\n");

    } /* endfor */

    /*** Estaciones de reserva de suma/resta ***/

    for (s = INICIO_RS_SUMA_RESTA;
         s <= FIN_RS_SUMA_RESTA; s++) {
        if (!RS[s].ocupado && RS[s].orden > 0) {
            clase = "old";
        } else {
            clase = "normal";
        }

        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\" class=\"%s\">\n", clase);

        imprime_codigo(s, aux);
        FIRMA_2_1("RS%d.cod", s, aux);
        fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);

        if (RS[s].ocupado || (!RS[s].ocupado && RS[s].orden > 0)) {
            FIRMA_2_1("RS%d.ocupado", s, (RS[s].ocupado) ? "SI" : "NO");
            fprintf(f_salida, "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);

            imprime_operacion(RS[s].OP, aux);
            FIRMA_2_1("RS%d.op", s, aux);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            if (RS[s].Qj != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qj", s, "#&nbsp;%d", RS[s].Qj);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                FIRMA_2_2("RS%d.Vj", s, "%.2f", RS[s].Vj.fp_d);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            if (RS[s].Qk != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qk", s, "#&nbsp;%d", RS[s].Qk);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vk", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qk", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                FIRMA_2_2("RS%d.Vk", s, "%.2f", RS[s].Vk.fp_d);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", RS[s].rob);
            fprintf(f_salida, "  <td>%s</td>\n", vstr);

            switch (RS[s].estado) {
                case EN_CURSO:
                    FIRMA_2_1("RS%d.result", s, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_3("RS%d.est", s, "%d/%d", Op[RS[s].operador].ciclo, Op[RS[s].operador].Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                case FINALIZADA:
                    FIRMA_2_2("RS%d.result", s, "%.2f", RS[s].resultado.fp_d);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_1("RS%d.est", s, "end");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                default:
                    FIRMA_2_1("RS%d.result", s, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_1("RS%d.est", s, "&nbsp;");
                    fprintf(f_salida, "  <td>%s</td>\n", vstr);
            }
        } else {
            FIRMA_2_1("RS%d.ocupado", s, "NO");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.op", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qk", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vk", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.rob", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.result", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.est", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */

        fprintf(f_salida, " </tr>\n");

    } /* endfor */

    /*** Estaciones de reserva de multiplicación/división ***/

    for (s = INICIO_RS_MULT_DIV;
         s <= FIN_RS_MULT_DIV; s++) {

        if (!RS[s].ocupado && RS[s].orden > 0) {
            clase = "old";
        } else {
            clase = "normal";
        }

        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\" class=\"%s\">\n", clase);

        imprime_codigo(s, aux);
        FIRMA_2_1("RS%d.cod", s, aux);
        fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);

        if (RS[s].ocupado || (!RS[s].ocupado && RS[s].orden > 0)) {
            FIRMA_2_1("RS%d.ocupado", s, (RS[s].ocupado) ? "SI" : "NO");
            fprintf(f_salida, "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);

            imprime_operacion(RS[s].OP, aux);
            FIRMA_2_1("RS%d.op", s, aux);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            if (RS[s].Qj != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qj", s, "#&nbsp;%d", RS[s].Qj);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                FIRMA_2_2("RS%d.Vj", s, "%.2f", RS[s].Vj.fp_d);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            if (RS[s].Qk != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qk", s, "#&nbsp;%d", RS[s].Qk);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vk", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qk", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                FIRMA_2_2("RS%d.Vk", s, "%.2f", RS[s].Vk.fp_d);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", RS[s].rob);
            fprintf(f_salida, "  <td>%s</td>\n", vstr);

            switch (RS[s].estado) {
                case EN_CURSO:
                    FIRMA_2_1("RS%d.result", s, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_3("RS%d.est", s, "%d/%d", Op[RS[s].operador].ciclo, Op[RS[s].operador].Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                case FINALIZADA:
                    FIRMA_2_2("RS%d.result", s, "%.2f", RS[s].resultado.fp_d);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_1("RS%d.est", s, "end");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                default:
                    FIRMA_2_1("RS%d.result", s, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_1("RS%d.est", s, "&nbsp;");
                    fprintf(f_salida, "  <td>%s</td>\n", vstr);
            }
        } else {
            FIRMA_2_1("RS%d.ocupado", s, "NO");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.op", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qk", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vk", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.rob", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.result", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.est", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */

        fprintf(f_salida, " </tr>\n");

    } /* endfor */

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "  </td></tr>\n");
    fprintf(f_salida, "</table><br>\n");

    fprintf(f_salida, "<table bgcolor=\"white\">\n");
    fprintf(f_salida, " <tr valign=\"top\"><td>\n");

    /*** Tampones de lectura ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Cod</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"40\">Busy</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Qj</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Vj</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Desplaz.</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Direc.</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">rob</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Resultado</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Estado</td>\n");
    fprintf(f_salida, " </tr>\n");


    for (s = INICIO_TAMPON_LECT;
         s <= FIN_TAMPON_LECT; s++) {

        if (!RS[s].ocupado && RS[s].orden > 0) {
            clase = "old";
        } else {
            clase = "normal";
        }

        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\" class=\"%s\">\n", clase);

        imprime_codigo(s, aux);
        FIRMA_2_1("RS%d.cod", s, aux);
        fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);

        if (TL[s].ocupado || (!TL[s].ocupado && TL[s].orden > 0)) {
            FIRMA_2_1("RS%d.ocupado", s, TL[s].ocupado ? "SI" : "NO");
            fprintf(f_salida, "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);

            if (TL[s].Qj != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qj", s, "#&nbsp;%d", TL[s].Qj);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                FIRMA_2_2("RS%d.Vj", s, F_DWORD, TL[s].Vj.int_d);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            FIRMA_2_2("RS%d.desp", s, F_DWORD, TL[s].desplazamiento);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

//                if (TL[s].estado == PREPARADA) {
            if (TL[s].estado != PENDIENTE) {
                te_etiqueta(aux, TL[s].direccion, m_datos);

                FIRMA_2_1("RS%d.dir", s, aux);
            } else {
                FIRMA_2_1("RS%d.dir", s, "&nbsp;");
            }
            fprintf(f_salida, "  <td align=\"center\" nowrap='nowrap'>%s</td>\n", vstr);

            FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", TL[s].rob);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            switch (RS[s].estado) {
                case EN_CURSO:
                    FIRMA_2_1("RS%d.result", s, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_3("RS%d.est", s, "%d/%d", Op[RS[s].operador].ciclo, Op[RS[s].operador].Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                case FINALIZADA:
                    if (RS[s].OP == OP_LD) {
                        FIRMA_2_2("RS%d.result", s, F_DWORD, RS[s].resultado.int_d);
                    } else {
                        FIRMA_2_2("RS%d.result", s, "%.2f", RS[s].resultado.fp_d);
                    }
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_1("RS%d.est", s, "end");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                default:
                    FIRMA_2_1("RS%d.result", s, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    FIRMA_2_1("RS%d.est", s, "&nbsp;");
                    fprintf(f_salida, "  <td>%s</td>\n", vstr);
            }

        } else {
            FIRMA_2_1("RS%d.ocupado", s, "NO");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.desp", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.dir", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.rob", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.result", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.est", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */

        fprintf(f_salida, " </tr>\n");

    } /* endfor */

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "  </td>\n");
    fprintf(f_salida, "  <td>\n");

    fprintf(f_salida, "<table>\n");
    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Cod</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"40\">Busy</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Qj</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Vj</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Desplaz.</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Direc.</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">rob</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Qk</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Vk</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Confirm.</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Estado</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (s = INICIO_TAMPON_ESCR;
         s <= FIN_TAMPON_ESCR; s++) {

        if (!RS[s].ocupado && RS[s].orden > 0) {
            clase = "old";
        } else {
            clase = "normal";
        }

        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\" class=\"%s\">\n", clase);

        imprime_codigo(s, aux);
        FIRMA_2_1("RS%d.cod", s, aux);
        fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);

        if (TE[s].ocupado || (!TE[s].ocupado && TE[s].orden > 0)) {
            FIRMA_2_1("RS%d.ocupado", s, TE[s].ocupado ? "SI" : "NO");
            fprintf(f_salida, "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr);

            if (TE[s].Qj != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qj", s, "#&nbsp;%d", TE[s].Qj);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                FIRMA_2_2("RS%d.Vj", s, F_DWORD, TE[s].Vj.int_d);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */

            FIRMA_2_2("RS%d.desp", s, F_DWORD, TE[s].desplazamiento);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

//                if (TE[s].estado == PREPARADA) {
            if (TL[s].estado != PENDIENTE) {
                te_etiqueta(aux, TE[s].direccion, m_datos);

                FIRMA_2_1("RS%d.dir", s, aux);
            } else {
                FIRMA_2_1("RS%d.dir", s, "&nbsp;");
            }
            fprintf(f_salida, "  <td align=\"center\" nowrap='nowrap'>%s</td>\n", vstr);

            FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", TL[s].rob);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            if (TE[s].Qk != MARCA_NULA) {
                FIRMA_2_2("RS%d.Qk", s, "#&nbsp;%d", TE[s].Qk);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                FIRMA_2_1("RS%d.Vk", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
            } else {
                FIRMA_2_1("RS%d.Qk", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr);
                if (TE[s].OP == OP_SD) {
                    FIRMA_2_2("RS%d.Vk", s, F_DWORD, TE[s].Vk.int_d);
                } else {
                    FIRMA_2_2("RS%d.Vk", s, "%.2f", TE[s].Vk.fp_d);
                }
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            } /* endif */


            FIRMA_2_2("RS%d.conf", s, "%s", (TE[s].confirm) ? "SI" : "NO");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            switch (RS[s].estado) {
                case EN_CURSO:
                    FIRMA_2_3("RS%d.est", s, "%d/%d", Op[RS[s].operador].ciclo, Op[RS[s].operador].Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                case FINALIZADA:
                    FIRMA_2_1("RS%d.est", s, "end");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
                    break;
                default:
                    FIRMA_2_1("RS%d.est", s, "&nbsp;");
                    fprintf(f_salida, "  <td>%s</td>\n", vstr);
            }

        } else {
            FIRMA_2_1("RS%d.ocupado", s, "NO");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qj", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.desp", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.dir", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.rob", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Qk", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.Vk", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.conf", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("RS%d.est", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */

        fprintf(f_salida, " </tr>\n");

    } /* endfor */

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "  </td></tr>\n");
    fprintf(f_salida, "</table>\n");


    /*** SEGUNDA COLUMNA **********************************************/

    fprintf(f_salida, "</td>\n");
    fprintf(f_salida, "<td>\n");

    /*** Contenido de la memoria de datos ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"50\" align=\"center\">Dir</td>\n");
    for (i = 0; i < 4; i++) {
        fprintf(f_salida, "  <td width=\"20\" align=\"center\">+%d</td>\n", i);
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    next = SegDatos.inicio;
    for (i = SegDatos.inicio; i < SegDatos.final; i++) {

        if (i % sizeof(word) == 0) {
            fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
            te_etiqueta(aux, i, m_datos);
            color_etiqueta_memdatos(color, i);
            fprintf(f_salida, "  <td align=\"left\" nowrap='nowrap' bgcolor=\"#ddeeff\">"
                    "<span style='color: %s; margin: 0 0.5em'>%s</span></td>\n", color, aux);
        } /* endif */

        if (i == next) {
            switch (md_tipo[i]) {
                case t_byte:
                    FIRMA_2_2("MD%d", i, "%hhX", MD.m_byte[dir_byte(i)]);
                    fprintf(f_salida,
                            "  <td align=\"center\">%s</td>\n", vstr);
                    next = i + sizeof(byte);
                    break;
                case t_half:
                    FIRMA_2_2("MD%d", i, "%hd", MD.m_half[dir_half(i)]);
                    fprintf(f_salida,
                            "  <td align=\"center\" colspan=\"2\">%s</td>\n", vstr);
                    next = i + sizeof(half);
                    break;
                case t_word:
                    FIRMA_2_2("MD%d", i, "%d", MD.m_word[dir_word(i)]);
                    fprintf(f_salida,
                            "  <td align=\"center\" colspan=\"4\">%s</td>\n", vstr);
                    next = i + sizeof(word);
                    break;
                case t_dword:
                    FIRMA_2_2("MD%d", i, F_DWORD, MD.m_dword[dir_dword(i)]);
                    fprintf(f_salida,
                            "  <td align=\"center\" rowspan=\"2\" colspan=\"4\">%s</td>\n", vstr);
                    next = i + sizeof(dword);
                    break;
                case t_float:
                    FIRMA_2_2("MD%d", i, "%.2f", MD.m_float[dir_float(i)]);
                    fprintf(f_salida,
                            "  <td align=\"center\" colspan=\"4\">%s</td>\n", vstr);
                    next = i + sizeof(float);
                    break;
                case t_double:
                    FIRMA_2_2("MD%d", i, "%.2f", MD.m_double[dir_double(i)]);
                    fprintf(f_salida,
                            "  <td align=\"center\" rowspan=\"2\" colspan=\"4\">%s</td>\n", vstr);
                    next = i + sizeof(double);
                    break;
                default:
                    fprintf(f_salida, "  <td>&nbsp;</td>\n");
                    next = i + 1;
            } /* endswitch */
        } /* endif */
        if ((i + 1) % sizeof(word) == 0) {
            fprintf(f_salida, " </tr>\n");
        } /* endif */
    } /* endif */

    fprintf(f_salida, "</table><br>\n");

    fprintf(f_salida, "</td>\n");
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "<address>Arquitectura e Ingenier&iacute;a de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n");

    if (html_merge == SI) {
        fputs("`,", f_salida);
    } else {
        fclose(f_salida);
    } /* endif */

    if (error_firma) {
        fprintf(stderr, "ERROR. "
                "Existen diferencias entre la ejecución actual y el fichero de firmas.\n"
                "Analice el fichero de estado 'estado%03ld.html'\n", Ciclo);
        exit(1);
    } /* endif */

} /* end imprime_estado */

/***************************************************************
 *
 * Func: imprime_crono
 *
 * Desc: Imprime el cronograma de ejecución
 *
 **************************************************************/

void imprime_crono
        (
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char aux[128];

    short x, y;
    char *color;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "crono%03ld.html", Ciclo);
    if (html_merge == SI) {
        fprintf(f_salida, "'%s':`", aux);
    } else {
        f_salida = fopen(aux, "w");
        if (f_salida == NULL) {
            fprintf(stderr, "Error creando %s\n", aux);
            exit(1);
        } /* endif */
    } /* endif */

    /*** HTML INTRO ***/

    fprintf(f_salida,
            "<html><head><title>Cronograma: %s. Ciclo %lu</title></head>\n",
            nombre_fich, Ciclo);
    fprintf(f_salida,
            "<body bgcolor=\"white\">\n");

    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n");
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    if (Ciclo > 5)
        fprintf(f_salida, "<a href=\"crono%03ld.html\">[-5]</a>&nbsp;\n",
                Ciclo - 5);
    else
        fprintf(f_salida, "[-5]&nbsp;\n");
    if (Ciclo > 1)
        fprintf(f_salida, "<a href=\"crono%03ld.html\">[-1]</a>&nbsp;\n",
                Ciclo - 1);
    else
        fprintf(f_salida, "[-1]\n");

    fprintf(f_salida, "<a href=\"crono%03ld.html\">[+1]</a>\n", Ciclo + 1);
    fprintf(f_salida, "<a href=\"crono%03ld.html\">[+5]</a>\n", Ciclo + 5);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"estado%03ld.html\">Estado</a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<!a href=\"crono%03ld.html\">Crono<!/a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"predictor%03ld.html\">BTB</a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<tt><b>Programa: %s</b></tt>\n", nombre_fich);
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<b>Ciclo: %lu</b>\n", Ciclo);
    fprintf(f_salida, "<br>\n");

    fprintf(f_salida, "<p>Estado al final del ciclo\n");

    /*** Cronograma de ejecución ***/

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\" align=\"center\">\n");
    fprintf(f_salida, "  <td width=\"20\">PC</td>\n");
    fprintf(f_salida, "  <td width=\"150\">Instruc.</td>\n");
    for (x = 0; x < MAX(MAX_CICLOS_INIC, maxima_columna_visible); x++)
        fprintf(f_salida, "  <td width=\"25\"><a href=\"crono%03ld.html\">%lu</a></td>\n",
                x + primer_ciclo, x + primer_ciclo);
    fprintf(f_salida, " </tr>\n");

    for (y = 0; y < MAX_INSTRUC; y++) {
        if (y % 2 == 0)
            fprintf(f_salida, " <tr bgcolor=\"#eeeeee\" align=\"center\">\n");
        else
            fprintf(f_salida, " <tr bgcolor=\"#dddddd\" align=\"center\">\n");


        color = (y % 2 == 0) ? "#ddeeff" : "#ccddff";
        if (!strlen(crono[y].inst)) {
            fprintf(f_salida,
                    "  <td bgcolor=\"%s\">&nbsp;</td>\n", color);
            fprintf(f_salida,
                    "  <td bgcolor=\"%s\">&nbsp;</td>\n", color);
        } else {
            te_etiqueta(aux, crono[y].PC, m_instruc);

            fprintf(f_salida,
                    "  <td nowrap=\"nowrap\" align=\"left\" bgcolor=\"%s\">%s</td>\n",
                    color, aux);
            fprintf(f_salida,
                    "  <td nowrap=\"nowrap\" align=\"left\" bgcolor=\"%s\">%s</td>\n",
                    color, crono[y].inst);
        }

        for (x = 0; x < MAX(MAX_CICLOS_INIC, maxima_columna_visible); x++) {
            fprintf(f_salida, "  <td>");

            if (strlen(crono[y].fase[x]))
                fprintf(f_salida, "%s", crono[y].fase[x]);
            else
                fprintf(f_salida, "&nbsp;");

            fprintf(f_salida, "  </td>\n");
        } /* endfor */
        fprintf(f_salida, " </tr>\n");
    } /* endfor */

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "<address>Arquitectura e Ingenier&iacute;a de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n");

    if (html_merge == SI) {
        fputs("`,", f_salida);
    } else {
        fclose(f_salida);
    } /* endif */

} /* end imprime_crono */

/***************************************************************
 *
 * Func: imprime_predictor
 *
 * Desc: Imprime el estado del predictor
 *
 **************************************************************/

void imprime_predictor
        (
        ) {
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i;

    char aux[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "predictor%03ld.html", Ciclo);
    if (html_merge == SI) {
        fprintf(f_salida, "'%s':`", aux);
    } else {
        f_salida = fopen(aux, "w");
        if (f_salida == NULL) {
            fprintf(stderr, "Error creando %s\n", aux);
            exit(1);
        } /* endif */
    } /* endif */

    nueva_firma(); /*** FIRMAS ***/

    /*** HTML INTRO ***/

    fprintf(f_salida,
            "<html><head><title>Predictor: %s. Ciclo %lu</title></head>\n",
            nombre_fich, Ciclo);
    fprintf(f_salida,
            "<body bgcolor=\"white\">\n");

    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n");
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    if (Ciclo > 5)
        fprintf(f_salida, "<a href=\"predictor%03ld.html\">[-5]</a>&nbsp;\n",
                Ciclo - 5);
    else
        fprintf(f_salida, "[-5]&nbsp;\n");
    if (Ciclo > 1)
        fprintf(f_salida, "<a href=\"predictor%03ld.html\">[-1]</a>&nbsp;\n",
                Ciclo - 1);
    else
        fprintf(f_salida, "[-1]\n");

    fprintf(f_salida, "<a href=\"predictor%03ld.html\">[+1]</a>\n", Ciclo + 1);
    fprintf(f_salida, "<a href=\"predictor%03ld.html\">[+5]</a>\n", Ciclo + 5);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"estado%03ld.html\">Estado</a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"crono%03ld.html\">Crono</a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<!a href=\"predictor%03ld.html\">BTB<!/a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<tt><b>Programa: %s</b></tt>\n", nombre_fich);
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<b>Ciclo: %lu</b>\n", Ciclo);
    fprintf(f_salida, "<br>\n");

    fprintf(f_salida, "<p>Estado al final del ciclo\n");

    /*** Bancos de registros ***/

    /* Branch Target Buffer */

    fprintf(f_salida, "<table>\n");

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"150\">PC (instr.)</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"150\">Estado</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"150\">Dir. Destino</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"150\">(Ultimo acceso)</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (i = 0; i < TAM_BUFFER_PREDIC; i++) {
        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");

        if (BTB[i].orden > 0) { /* Entrada ocupada */
            te_etiqueta(aux, BTB[i].PC, m_instruc);

            FIRMA_2_1("BTB%d.pc", i, aux);
            imprime_instruccion(aux, BTB[i].PC);
            fprintf(f_salida, "  <td nowrap='nowrap'>%s (%s)</td>\n", vstr, aux);

            imprime_estado_predictor(aux, BTB[i].estado);
            FIRMA_2_1("BTB%d.estado", i, aux);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);

            te_etiqueta(aux, BTB[i].destino, m_instruc);

            FIRMA_2_1("BTB%d.destino", i, aux);
            fprintf(f_salida, "  <td align=\"center\" nowrap='nowrap'>%s</td>\n", vstr);

            FIRMA_2_2("BTB%d.ciclo", i, "%lu", BTB[i].ciclo);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } else {
            FIRMA_2_1("BTB%d.pc", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("BTB%d.estado", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("BTB%d.destino", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
            FIRMA_2_1("BTB%d.ciclo", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr);
        } /* endif */

        fprintf(f_salida, " </tr>\n");
    } /* endfor */

    fprintf(f_salida, "</table>\n");

    fprintf(f_salida, "<address>Arquitectura e Ingenier&iacute;a de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n");

    if (html_merge == SI) {
        fputs("`,", f_salida);
    } else {
        fclose(f_salida);
    } /* endif */

    if (error_firma) {
        fprintf(stderr, "ERROR. "
                "Existen diferencias entre la ejecución actual y el fichero de firmas.\n"
                "Analice el fichero de estado 'estado%03ld.html'\n", Ciclo);
        exit(1);
    } /* endif */

} /* end imprime_predictor */

/***************************************************************
 *
 * Func: imprime_config
 *
 * Desc: Imprime la configuración del simulador
 *
 **************************************************************/

void imprime_config() {

    fprintf(stdout, "\n*** CONFIGURACIÓN ***\n\n");

    fprintf(stdout, "  Grado superescalar: \n");
    fprintf(stdout, "        ISSUE:        %d\n", NUM_VIAS_ISSUE);
    fprintf(stdout, "        BUSES:        %d\n", NUM_VIAS_BUS);
    fprintf(stdout, "        COMMIT:       %d\n", NUM_VIAS_COMMIT);
    fprintf(stdout, "  Reorder Buffer:     %d\n", TAM_REORDER);
    fprintf(stdout, "  E.R. Suma/Resta:    %d\n", TAM_RS_SUMA_RESTA);
    fprintf(stdout, "  E.R. Mult/Div:      %d\n", TAM_RS_MULT_DIV);
    fprintf(stdout, "  E.R. Enteros:       %d\n", TAM_RS_ENTEROS);
    fprintf(stdout, "  Buffer lectura:     %d\n", TAM_TAMPON_LECT);
    fprintf(stdout, "  Buffer escritura:   %d\n", TAM_TAMPON_ESCR);
    fprintf(stdout, "  Buffer predictor:   %d\n", TAM_BUFFER_PREDIC);
    fprintf(stdout, "  Registros:          %d\n", TAM_REGISTROS);

    /*** Tiempos de evaluación ***/

    fprintf(stdout, "\n");

#define INFO_OPER(op) NUM_INICIO_##op, TEVAL_##op, ((NUM_INICIO_##op != NUM_OPER_##op) ? "SEGM" : "CONV")

    fprintf(stdout, "                    Cantidad   Latencia  Tipo\n");
    fprintf(stdout, "                    --------   --------  ----\n");
    fprintf(stdout, "  Oper. Suma/Resta:  %3d         %3d     %s\n", INFO_OPER(SUMREST));
    fprintf(stdout, "  Oper. Mult/Div:    %3d         %3d     %s\n", INFO_OPER(MULTDIV));
    fprintf(stdout, "  Oper. Enteros:     %3d         %3d     %s\n", INFO_OPER(ENTEROS));
    fprintf(stdout, "  Oper. Memoria:     %3d         %3d     %s\n", INFO_OPER(MEMDATOS));

    fprintf(stdout, "\n");

} /* end imprime_config */

/***************************************************************
 *
 * Func: imprime_estadisticas
 *
 * Desc: Imprime las estadisticas del programa
 *
 **************************************************************/

void imprime_estadisticas() {

    fprintf(stdout, "\n*** ESTADISTICAS ***\n\n");

    fprintf(stdout, "Ciclos:              %4ld\n", estat.ciclos);
    fprintf(stdout, "Instrucciones:       %4ld\n", estat.instrucciones);
    fprintf(stdout, "  Operaciones C.F.:  %4ld\n", estat.flops);
    fprintf(stdout, "  Saltos accedidos:  %4ld\n", estat.saltos_accedidos);
    fprintf(stdout, "    Encontrados:     %4ld\n", estat.saltos_encontrados);
    fprintf(stdout, "  Saltos ejecutados: %4ld\n", estat.saltos_ejecutados);
    fprintf(stdout, "    Acertados:       %4ld\n", estat.saltos_acertados);

    fprintf(stdout, "\n\n");

} /* end imprime_estadisticas */
