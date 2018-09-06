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

#ifdef MAX
#undef MAX
#endif
#define MAX(x,y) (((x)>(y)) ? (x) : (y))

typedef enum {
    MF_OCIOSO=0,
    MF_ESCRITURA=1,
    MF_LECTURA=2
} modo_firmas_t;

#define LONG_FIRMA 20480
#define FIRMA_DEL_FICHERO "<Fichero de firmas> ssaez@disca.upv.es"

/***** Variables Globales *************************************/

/***** Variables Locales **************************************/

static FILE *	f_salida;

static FILE *	f_firmas;
static modo_firmas_t modo_firmas= MF_OCIOSO;
static char     linea_firma[LONG_FIRMA];
static boolean  error_firma= NO;

static ciclo_t	primera_instruccion= 1;
static ciclo_t	primer_ciclo= 1;
static short    maxima_columna_visible= MAX_CICLOS_INIC;

static  char          campo[64];
static  char          valor[64];
static  char *        vstr;

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
    char *	fichero
    )
{
    /*************************************/
    /*  Function body                    */
    /*************************************/

    f_firmas= fopen(fichero, "w");
    if (f_firmas == NULL)
    {
        fprintf(stderr, "Error creando %s\n", fichero);
        exit(1);
    } /* endif */

    modo_firmas= MF_ESCRITURA;
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
    char *	fichero
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char * lin;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    f_firmas= fopen(fichero, "r");
    if (f_firmas == NULL)
    {
        fprintf(stderr, "Error abriendo %s\n", fichero);
        exit(1);
    } /* endif */

    modo_firmas= MF_LECTURA;

    /*** Comprueba que es un fichero de firmas ***/

    lin= fgets(linea_firma, LONG_FIRMA, f_firmas);
    if (lin == NULL)
    {
        fprintf(stderr, "Error leyendo el fichero de firmas\n");
        exit(1);
    } /* endif */
  
    /* Comprueba que la firma es correcta */
    if (strcmp(linea_firma, FIRMA_DEL_FICHERO "\n"))
    {
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
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char * tok;
    char s_ciclo[8];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(s_ciclo, "%ld", Ciclo);

    switch (modo_firmas) {
    case MF_LECTURA:
    {
        char * lin;
        lin= fgets(linea_firma, LONG_FIRMA, f_firmas);
        if (lin == NULL)
        {
            fprintf(stderr, "Error leyendo el fichero de firmas\n");
            exit(1);
        } /* endif */
      
        /* Comprueba que el ciclo es el correcto */
        tok= strtok(linea_firma, "@");
        if (strcmp(tok, s_ciclo))
        {
            fprintf(stderr, "ERROR. "
                    "El ciclo actual no coincide con el ciclo del fichero de firmas.\n"
                    "Seguramente no deberías haber alcanzado este ciclo\n");
            exit(1);
        } /* endif */
    } break; /* endcase */
    case MF_ESCRITURA:
    {
        fprintf(f_firmas, "\n%s@", s_ciclo);
    } break; /* endcase */
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

char * procesa_firma
(
    char *	campo,
    char *	valor
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char * tok;
    static char msg[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    switch (modo_firmas) {
    case MF_LECTURA:
    {
        tok= strtok(NULL, "$");
        if (tok == NULL)
        {
            fprintf(stderr, "%s: %s\n", campo, valor);
            fprintf(stderr, "Error leyendo el fichero de firmas: %d\n", __LINE__);
            exit(1);
        } /* endif */
        if (strcmp(tok, campo))
        {
            fprintf(stderr, "ERROR. "
                    "Los nombres de los campos no coinciden con los del fichero de firmas.\n"
                    "Probablemente exista un error en la configuración del simulador\n");
            exit(1);
        } /* endif */
      
        tok= strtok(NULL, "@");
        if (tok == NULL)
        {
            fprintf(stderr, "%s: %s\n", campo, valor);
            fprintf(stderr, "Error leyendo el fichero de firmas: %d\n", __LINE__);
            exit(1);
        } /* endif */
        if (strcmp(tok, valor))
        {
            if (!strcmp(valor, "&nbsp;"))
                strcpy(msg, "<i><font color=\"red\"><b> ??? </b></font></i>");
            else
                sprintf(msg, "<i><font color=\"red\"><b>%s</b></font></i>", valor);
          
            error_firma= SI;
            return msg;
        } /* endif */
    } break; /* endcase */
    case MF_ESCRITURA:
    {
        fprintf(f_firmas, "%s$%s@", campo, valor);
    } break; /* endcase */
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
    )
{
    /*************************************/
    /*  Function body                    */
    /*************************************/

    fprintf(f_firmas, "\n");
    fclose(f_firmas);

} /* end cierra_firma */

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

static void imprime_instruccion 
(  
    char *	instruc,
    word	PC
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char		aux[128];

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    if (PC == -1)
    {
        strcpy(instruc, "???");
        return ;
    } /* endif */

    switch (MI[PC].codop)
    {
    case OP_NOP:
        sprintf(instruc, "nop");
        break;
    case OP_TRAP:
        sprintf(instruc, "trap %d", 
                MI[PC].inmediato);
        break;
    case OP_LD:
        sprintf(instruc, "ld r%d, %d(r%d)", 
                MI[PC].Rdestino,
                MI[PC].inmediato,
                MI[PC].Rfuente1
            );
        break;
    case OP_SD:
        sprintf(instruc, "sd r%d, %d(r%d)", 
                MI[PC].Rfuente2,
                MI[PC].inmediato,
                MI[PC].Rfuente1
            );
        break;
    case OP_DADD:
        sprintf(instruc, "dadd r%d, r%d, r%d", 
                MI[PC].Rdestino,
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_DSUB:
        sprintf(instruc, "dsub r%d, r%d, r%d", 
                MI[PC].Rdestino,
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_DADDI:
        sprintf(instruc, "daddi r%d, r%d, %d", 
                MI[PC].Rdestino,
                MI[PC].Rfuente1,
                MI[PC].inmediato
            );
        break;
    case OP_DSUBI:
        sprintf(instruc, "dsubi r%d, r%d, %d", 
                MI[PC].Rdestino,
                MI[PC].Rfuente1,
                MI[PC].inmediato
            );
        break;
    case OP_BEQZ:
        te_etiqueta(aux, PC + 1 + MI[PC].inmediato, m_instruc);  
        sprintf(instruc, "beqz r%d, %s", 
                MI[PC].Rfuente1,
                aux
            );
        break;
    case OP_BNEZ:
        te_etiqueta(aux, PC + 1 + MI[PC].inmediato, m_instruc);  
        sprintf(instruc, "bnez r%d, %s", 
                MI[PC].Rfuente1,
                aux
            );
        break;
    case OP_BEQ:
        te_etiqueta(aux, PC + 1 + MI[PC].inmediato, m_instruc);  
        sprintf(instruc, "beq r%d, r%d, %s", 
                MI[PC].Rfuente1,
                MI[PC].Rfuente2,
                aux
            );
        break;
    case OP_BNE:
        te_etiqueta(aux, PC + 1 + MI[PC].inmediato, m_instruc);  
        sprintf(instruc, "bne r%d, r%d, %s", 
                MI[PC].Rfuente1,
                MI[PC].Rfuente2,
                aux
            );
        break;
    case OP_L_D:
        sprintf(instruc, "l.d f%d, %d(r%d)", 
                MI[PC].Rdestino,
                MI[PC].inmediato,
                MI[PC].Rfuente1
            );
        break;
    case OP_S_D:
        sprintf(instruc, "s.d %d(r%d), f%d", 
                MI[PC].inmediato,
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_ADD_D:
        sprintf(instruc, "add.d f%d, f%d, f%d", 
                MI[PC].Rdestino,
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_SUB_D:
        sprintf(instruc, "sub.d f%d, f%d, f%d", 
                MI[PC].Rdestino,
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_MUL_D:
        sprintf(instruc, "mul.d f%d, f%d, f%d", 
                MI[PC].Rdestino,
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_DIV_D:
        sprintf(instruc, "div.d f%d, f%d, f%d", 
                MI[PC].Rdestino,
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_C_GT_D:
        sprintf(instruc, "c.gt.d f%d, f%d", 
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_C_LT_D:
        sprintf(instruc, "c.lt.d f%d, f%d", 
                MI[PC].Rfuente1,
                MI[PC].Rfuente2
            );
        break;
    case OP_BC1T:
        te_etiqueta(aux, PC + 1 + MI[PC].inmediato, m_instruc);  
        sprintf(instruc, "bc1t %s", 
                aux
            );
        break;
    case OP_BC1F:
        te_etiqueta(aux, PC + 1 + MI[PC].inmediato, m_instruc);  
        sprintf(instruc, "bc1f %s", 
                aux
            );
        break;
    default:
        sprintf(instruc, "Instrucción ilegal");
        break;
    } /* endswitch */

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
    marca_t	s,
    char *		nom
    )
{
    /*************************************/
    /*  Function body                    */
    /*************************************/

    if (/* s >= INICIO_RS_ENTEROS && */ /* Es siempre cierto en está
                                           implementación */
        s <= FIN_RS_ENTEROS)
    {
        sprintf(nom, "e%d", s - INICIO_RS_ENTEROS +1);
    }
    else if (s >= INICIO_RS_SUMA_RESTA &&
             s <= FIN_RS_SUMA_RESTA)
    {
        sprintf(nom, "a%d", s - INICIO_RS_SUMA_RESTA +1);
    }
    else if (s >= INICIO_RS_MULT_DIV &&
             s <= FIN_RS_MULT_DIV)
    {
        sprintf(nom, "m%d", s - INICIO_RS_MULT_DIV +1);
    }
    else if (s >= INICIO_TAMPON_LECT &&
             s <= FIN_TAMPON_LECT)
    {
        sprintf(nom, "l%d", s - INICIO_TAMPON_LECT +1);
    }
    else if (s >= INICIO_TAMPON_ESCR &&
             s <= FIN_TAMPON_ESCR)
    {
        sprintf(nom, "s%d", s - INICIO_TAMPON_ESCR +1);
    }
    else 
    {
        nom[0]= '\0';		/* Invalido o marca nula */
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
    codop_t       	c,
    char *		nom
    )
{
    /*************************************/
    /*  Function body                    */
    /*************************************/

    switch (c)
    {
    case OP_C_GT_D:
        sprintf(nom, ">");
        break;
    case OP_C_LT_D:
        sprintf(nom, "<");
        break;
    case OP_MUL_D:
        sprintf(nom, "*");
        break;
    case OP_DIV_D:
        sprintf(nom, "/");
        break;
    case OP_ADD_D:
    case OP_DADD:
    case OP_DADDI:
        sprintf(nom, "+");
        break;
    case OP_SUB_D:
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
    char *		nom,
    estado_predic_t     e
    )
{
    /*************************************/
    /*  Function body                    */
    /*************************************/

    switch (e)
    {
    case NO_SALTA:
        sprintf(nom, "<font color=\"red\">NO Salta</font>");
        break;
    case NO_SALTA_UN_FALLO:
        sprintf(nom, "<font color=\"red\">NO Salta (1 falo)</font>");
        break;
    case SALTA_UN_FALLO:
        sprintf(nom, "<font color=\"green\">Salta (1 falo)</font>");
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
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i, j;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    for (i= 0; i<MAX_INSTRUC; i++)
    {
        for (j= 0; j<MAX_CICLOS-1; j++)
            strcpy(crono[i].fase[j], crono[i].fase[j+1]);
      
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
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i, j, desp;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    /* Averigua si la linea se va a quedar vacia al principio */
    for (desp= 0; 
         desp < MAX_CICLOS && 
             !strlen(crono[1].fase[desp]); desp++);
    if (desp == MAX_CICLOS)
        desp= 1;                  /* La línea está completamente vacia. Avanzamos sólo un
                                   * ciclo */
	
    for (i= 0; i<MAX_INSTRUC-1; i++)
    {
        strcpy(crono[i].inst, crono[i+1].inst);
      
        for (j= 0; j<MAX_CICLOS-desp; j++)
            strcpy(crono[i].fase[j], crono[i+1].fase[j+desp]);
      
        /* Borra las últimas columnas */
        for (j= MAX_CICLOS-desp; j<MAX_CICLOS; j++) 
            strcpy(crono[i].fase[j], "");
    } /* endfor */
  
    /* Borra la última fila */
    strcpy(crono[MAX_INSTRUC-1].inst, "");
    for (j= 0; j<MAX_CICLOS; j++)
        strcpy(crono[MAX_INSTRUC-1].fase[j], "");

    /*** Actualiza los desplazamientos iniciales ***/
  
    primer_ciclo+= desp;
    primera_instruccion++;
    maxima_columna_visible-= desp;

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
    word	PC,
    ciclo_t	orden
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    int	o;
    char		aux[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    if (orden == primera_instruccion + MAX_INSTRUC)
        desplazamiento_vertical();

    o= orden - primera_instruccion;

    imprime_instruccion(aux, PC);
    sprintf(crono[o].inst, "%2d: %s", PC, aux);

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
    char *	fase,
    ciclo_t	orden
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    int	o, c;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    if (Ciclo >= primer_ciclo + MAX_CICLOS)
        desplazamiento_horizontal();
  
    o= orden - primera_instruccion;
    c= Ciclo - primer_ciclo;

    if (o >= 0 && c >= 0)
    {
        strcpy(crono[o].fase[c], fase);
        if (c + 1 > maxima_columna_visible)
            maxima_columna_visible= c + 1;
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
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short		i;

    char		aux[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "index.html");
    f_salida= fopen(aux, "w");
    if (f_salida == NULL)
    {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */

    /*** HTML INTRO ***/

    fprintf(f_salida, 
            "<html><head><title>mips-especulacion: %s. Ciclo %ld</title></head>\n", 
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
    fprintf(f_salida, "  <td align=\"center\">Número</td>\n");
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
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Multiplicación/División</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_MULT_DIV);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Enteros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_ENTEROS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Tampón&nbsp;de&nbsp;lectura</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_TAMPON_LECT);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Tampón&nbsp;de&nbsp;escritura</td>\n");
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
    fprintf(f_salida, "  <td align=\"center\">Tiempo</td>\n");
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Suma/Resta</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_SUMREST);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Multiplicación/División</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_MULTDIV);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Enteros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_ENTEROS);
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Memoria de datos</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_MEMORIA);
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
    fprintf(f_salida, "  <td width=\"75\">Dirección</td>\n");
    fprintf(f_salida, "  <td width=\"75\">Datos</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (i= SegDatos.inicio; i< SegDatos.final; i+= sizeof(double))
    {
        fprintf(f_salida, " <tr>\n");
        if (te_etiqueta(aux, i, m_datos))  
            fprintf(f_salida, "  <td align=\"right\" bgcolor=\"#ddeeff\">"
                    "%s: %d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", aux, i);
        else
            fprintf(f_salida, "  <td align=\"right\" bgcolor=\"#ddeeff\">"
                    "%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", i);
        fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"right\">%.2f</td>\n", 
                MD.m_double[dir_double(i)]);
        fprintf(f_salida, " </tr>\n");

    } /* endif */
  
    fprintf(f_salida, "</table>\n"); 

    fprintf(f_salida, "  </td><td>\n");

    /*** Contenido de la memoria de instrucciones ***/

    fprintf(f_salida, "<table>\n"); 

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"75\">Dirección</td>\n");
    fprintf(f_salida, "  <td width=\"200\">Instrucciones</td>\n");
    fprintf(f_salida, " </tr>\n");

    for (i= SegInstruc.inicio; i< SegInstruc.final; i++)
    {
        fprintf(f_salida, " <tr>\n");
        if (te_etiqueta(aux, i, m_instruc))  
            fprintf(f_salida, "  <td align=\"right\" bgcolor=\"#ddeeff\">"
                    "%s: %d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", aux, i);
        else
            fprintf(f_salida, "  <td align=\"right\" bgcolor=\"#ddeeff\">"
                    "%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", i);
        imprime_instruccion(aux, i);
        fprintf(f_salida, "  <td bgcolor=\"#eeeeee\">%s</td>\n", aux);
        fprintf(f_salida, " </tr>\n");
    } 
  
    fprintf(f_salida, "</table>\n"); 

    fprintf(f_salida, "  </td></tr>\n");
    fprintf(f_salida, "</table><br>\n"); 

    fprintf(f_salida, "<address>Arquitectura e Ingeniería de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n"); 

    fclose(f_salida);

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
)
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    short		i;
    
    char		aux[128];
    
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    sprintf(aux, "final.html");
    f_salida= fopen(aux, "w");
    if (f_salida == NULL)
    {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */
    
    /*** HTML INTRO ***/
    
    fprintf(f_salida,
            "<html><head><title>mips-especulacion: %s. Ciclo %ld</title></head>\n",
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
    fprintf(f_salida, "  <td>%1.2f</td>\n", (float) estat.ciclos/estat.instrucciones);
    fprintf(f_salida, "  <td>%ld</td>\n", estat.flops);
    fprintf(f_salida, "  <td>%1.2f</td>\n", (float) estat.flops/estat.ciclos);
    fprintf(f_salida, "  <td>%ld </td>\n", estat.saltos_accedidos);
    fprintf(f_salida, "  <td>%ld (%2.1f%%)</td>\n", estat.saltos_encontrados,(float) (estat.saltos_encontrados*100)/estat.saltos_accedidos);
    fprintf(f_salida, "  <td>%ld (%2.1f%%)</td>\n", estat.saltos_ejecutados,(float) (estat.saltos_ejecutados*100)/estat.instrucciones);
    fprintf(f_salida, "  <td>%ld (%2.1f%%)</td>\n", estat.saltos_acertados,(float) (estat.saltos_acertados*100)/estat.saltos_ejecutados);
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table><br>\n");
    
    /*** Datos de la implementación ***/
    
    fprintf(f_salida, "<table>\n");
    
    fprintf(f_salida, " <tr valign=\"top\"><td>\n");
    
    /*** Estructuras ***/
    
    fprintf(f_salida, "<table>\n");
    
    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td>Estructura</td>\n");
    fprintf(f_salida, "  <td align=\"center\">Número</td>\n");
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
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Multiplicación/División</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_MULT_DIV);
    fprintf(f_salida, " </tr>\n");
    
    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">E.R.&nbsp;Enteros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_RS_ENTEROS);
    fprintf(f_salida, " </tr>\n");
    
    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Tampón&nbsp;de&nbsp;lectura</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TAM_TAMPON_LECT);
    fprintf(f_salida, " </tr>\n");
    
    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Tampón&nbsp;de&nbsp;escritura</td>\n");
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
    fprintf(f_salida, "  <td align=\"center\">Tiempo</td>\n");
    fprintf(f_salida, " </tr>\n");
    
    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Suma/Resta</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_SUMREST);
    fprintf(f_salida, " </tr>\n");
    
    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Multiplicación/División</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_MULTDIV);
    fprintf(f_salida, " </tr>\n");
    
    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Enteros</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_ENTEROS);
    fprintf(f_salida, " </tr>\n");
    
    fprintf(f_salida, " <tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\">Memoria de datos</td>\n");
    fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"center\">%d</td>\n", TEVAL_MEMORIA);
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
    fprintf(f_salida, "  <td width=\"75\">Dirección</td>\n");
    fprintf(f_salida, "  <td width=\"75\">Datos</td>\n");
    fprintf(f_salida, " </tr>\n");
    
    for (i= SegDatos.inicio; i< SegDatos.final; i+= sizeof(double))
    {
        fprintf(f_salida, " <tr>\n");
        if (te_etiqueta(aux, i, m_datos))
            fprintf(f_salida, "  <td align=\"right\" bgcolor=\"#ddeeff\">"
                    "%s: %d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", aux, i);
        else
            fprintf(f_salida, "  <td align=\"right\" bgcolor=\"#ddeeff\">"
                    "%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", i);
        fprintf(f_salida, "  <td bgcolor=\"#eeeeee\" align=\"right\">%.2f</td>\n",
                MD.m_double[dir_double(i)]);
        fprintf(f_salida, " </tr>\n");
        
    } /* endif */
    
    fprintf(f_salida, "</table>\n");
    
    fprintf(f_salida, "  </td><td>\n");
    
    /*** Contenido de la memoria de instrucciones ***/
    
    fprintf(f_salida, "<table>\n");
    
    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"75\">Dirección</td>\n");
    fprintf(f_salida, "  <td width=\"200\">Instrucciones</td>\n");
    fprintf(f_salida, " </tr>\n");
    
    for (i= SegInstruc.inicio; i< SegInstruc.final; i++)
    {
        fprintf(f_salida, " <tr>\n");
        if (te_etiqueta(aux, i, m_instruc))
            fprintf(f_salida, "  <td align=\"right\" bgcolor=\"#ddeeff\">"
                    "%s: %d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", aux, i);
        else
            fprintf(f_salida, "  <td align=\"right\" bgcolor=\"#ddeeff\">"
                    "%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", i);
        imprime_instruccion(aux, i);
        fprintf(f_salida, "  <td bgcolor=\"#eeeeee\">%s</td>\n", aux);
        fprintf(f_salida, " </tr>\n");
    }
    
    fprintf(f_salida, "</table>\n");
    
    fprintf(f_salida, "  </td></tr>\n");
    fprintf(f_salida, "</table><br>\n");
    
    fprintf(f_salida, "<address>Arquitectura e Ingeniería de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n"); 
    
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
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    marca_t             s;
    int                 i, next;

    char		aux[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "estado%03ld.html", Ciclo);
    f_salida= fopen(aux, "w");
    if (f_salida == NULL)
    {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */

    nueva_firma();                /*** FIRMAS ***/

    /*** HTML INTRO ***/

    fprintf(f_salida, 
            "<html><head><title>Estado: %s. Ciclo %ld</title></head>\n", 
            nombre_fich, Ciclo);
    fprintf(f_salida, 
            "<body bgcolor=\"white\">\n"); 

    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    if (Ciclo > 5)
        fprintf(f_salida, "<a href=\"estado%03ld.html\">[-5]</a>&nbsp;\n", 
                Ciclo -5); 
    else
        fprintf(f_salida, "[-5]&nbsp;\n");
    if (Ciclo > 1)
        fprintf(f_salida, "<a href=\"estado%03ld.html\">[-1]</a>&nbsp;\n", 
                Ciclo -1);
    else
        fprintf(f_salida, "[-1]\n");
      
    fprintf(f_salida, "<a href=\"estado%03ld.html\">[+1]</a>\n", Ciclo +1); 
    fprintf(f_salida, "<a href=\"estado%03ld.html\">[+5]</a>\n", Ciclo +5); 

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<!a href=\"estado%03ld.html\">Estado<!/a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"crono%03ld.html\">Crono</a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"predictor%03ld.html\">BTB</a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<tt><b>Programa: %s</b></tt>\n", nombre_fich); 
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<b>Ciclo: %ld</b>\n", Ciclo); 
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
    for (i= 0; i<TAM_REGISTROS; i++) {
        fprintf(f_salida, "  <td width=\"75\" align=\"center\">F%d</td>\n", i);
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    fprintf(f_salida, "  <td width=\"50\" bgcolor=\"#ddeeff\">rob</td>\n");
    for (i= 0; i<TAM_REGISTROS; i++) {
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
    for (i= 0; i<TAM_REGISTROS; i++) {
        FIRMA_2_2("F%d.valor", i, "%.2f", Rfp[i].valor);
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
    for (i= 0; i<TAM_REGISTROS; i++) {
        fprintf(f_salida, "  <td width=\"75\" align=\"center\">R%d</td>\n", i);
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    fprintf(f_salida, "  <td width=\"50\" bgcolor=\"#ddeeff\">rob</td>\n");
    for (i= 0; i<TAM_REGISTROS; i++) {
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
    for (i= 0; i<TAM_REGISTROS; i++) {
        FIRMA_2_2("R%d.valor", i, "%ld", Rint[i].valor);
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
    fprintf(f_salida, "  <td align=\"center\" width=\"125\">Instrucción</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Est.</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"100\">Destino</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"75\">Valor</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Exc.</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">PC</td>\n"); 
    fprintf(f_salida, " </tr>\n");

    for (i= 0; i < TAM_REORDER; i++) {
        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");

        if (i == RB_inicio)
            fprintf(f_salida, 
                    "  <td bgcolor=\"#ffddaa\" align=\"center\">%d</td>\n", i);
        else
            fprintf(f_salida, 
                    "  <td bgcolor=\"#ddeeff\" align=\"center\">%d</td>\n", i);

        if (RB[i].ocupado) {
            FIRMA_2_1("ROB%d.ocupado", i, "SI");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 

            imprime_instruccion(aux, RB[i].PC);
            FIRMA_2_1("ROB%d.inst", i, aux);
            fprintf(f_salida, "  <td align=\"center\" nowrap=\"nowrap\">%s</td>\n", vstr); 

            FIRMA_2_1("ROB%d.estado", i, (RB[i].estado == EX) ? "EX" : "WB");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 

            if (inst_store(RB[i].OP)) {
                imprime_codigo(RB[i].dest, aux);
                FIRMA_2_1("ROB%d.dest", i, aux);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 

                FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } else if (inst_branch_int(RB[i].OP)) {
                FIRMA_2_2("ROB%d.dest", i, "%ld", RB[i].dest);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                if (RB[i].estado == WB) {
                    strcpy(aux, (RB[i].valor.i == (dword)RB[i].prediccion) ? "green" : "red");
                    FIRMA_2_1("ROB%d.valor", i, (RB[i].valor.i) ? "Salta" : "No salta");
                    fprintf(f_salida, "  <td align=\"center\"><font color=\"%s\">%s</font></td>\n", 
                            aux, vstr); 
                } else {
                    FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } /* endif */
	    } else if (inst_branch_fp(RB[i].OP)) {
                FIRMA_2_2("ROB%d.dest", i, "%ld", RB[i].dest);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                if (RB_inicio == i) {
                    if (RB[i].OP == OP_BC1T) {
                        FIRMA_2_1("ROB%d.valor", i, (Rint[REG_FPSR].valor) ? "Salta" : "No salta");
                        strcpy(aux, ((Rint[REG_FPSR].valor && RB[i].prediccion) || 
                                     (!Rint[REG_FPSR].valor && !RB[i].prediccion))
                               ? "green" : "red");
                    } else {
                        FIRMA_2_1("ROB%d.valor", i, (!Rint[REG_FPSR].valor) ? "Salta" : "No salta");
                        strcpy(aux, ((!Rint[REG_FPSR].valor && RB[i].prediccion) || 
                                     (Rint[REG_FPSR].valor && !RB[i].prediccion))
                               ? "green" : "red");
                    } /* endif */
                    fprintf(f_salida, "  <td align=\"center\"><font color=\"%s\">%s</font></td>\n", 
                            aux, vstr); 
                } else {
                    FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } /* endif */
	    } else if (inst_comp_fp(RB[i].OP)) {
                FIRMA_2_1("ROB%d.dest", i, "fpsr");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                if (RB[i].estado == WB) {
                    FIRMA_2_1("ROB%d.valor", i, (RB[i].valor.i) ? "Cierto" : "Falso");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } else {
                    FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } /* endif */
	    } else if (RB[i].OP != OP_NOP && RB[i].OP != OP_TRAP) {
                FIRMA_2_2("ROB%d.dest", i, "%ld", RB[i].dest);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	      
                if (RB[i].estado == WB)
                    if (inst_int(RB[i].OP))
                        FIRMA_2_2("ROB%d.valor", i, "%ld", RB[i].valor.i);
                    else
                        FIRMA_2_2("ROB%d.valor", i, "%.2f", RB[i].valor.f);
                else
                    FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
	      
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } else {
                FIRMA_2_1("ROB%d.dest", i, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
                FIRMA_2_1("ROB%d.valor", i, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
	    } /* endif */

            if (RB[i].excepcion != EXC_NONE)
                FIRMA_2_2("ROB%d.exc", i, "%d", RB[i].excepcion);
            else
                FIRMA_2_1("ROB%d.exc", i, "&nbsp;");

            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	  
            FIRMA_2_2("ROB%d.pc", i, "%ld", RB[i].PC);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
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
    fprintf(f_salida, "  <td align=\"center\">Estado</td>\n"); 
    fprintf(f_salida, " </tr>\n");

    /*** Estaciones de reserva de enteros ***/

    for (s= INICIO_RS_ENTEROS; 
         s <= FIN_RS_ENTEROS; s++) {
        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
        imprime_codigo(s, aux);
        FIRMA_2_1("RS%d.cod", s, aux);
        fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);
      
        if (RS[s].ocupado) {
            FIRMA_2_1("RS%d.ocupado", s, "SI");
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
                FIRMA_2_2("RS%d.Vj", s, "%ld", RS[s].Vj.i);          
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
                FIRMA_2_2("RS%d.Vk", s, "%ld", RS[s].Vk.i);          
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } /* endif */

            FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", RS[s].rob);
            fprintf(f_salida, "  <td>%s</td>\n", vstr); 

            if (Enteros.ocupado && Enteros.estacion == s) {
                FIRMA_2_3("RS%d.est", s, "%d/%d", Enteros.ciclo, Enteros.Teval);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } else if (RegEnteros.ocupado && RegEnteros.estacion == s) {
                FIRMA_2_3("RS%d.est", s, "%d/%d", Enteros.Teval, Enteros.Teval);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } else {
                FIRMA_2_1("RS%d.est", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
	    } /* endif */
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
            FIRMA_2_1("RS%d.est", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	} /* endif */
      
        fprintf(f_salida, " </tr>\n");

    } /* endfor */

    /*** Estaciones de reserva de suma/resta ***/

    for (s= INICIO_RS_SUMA_RESTA; 
         s <= FIN_RS_SUMA_RESTA; s++) {
        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
        imprime_codigo(s, aux);
        FIRMA_2_1("RS%d.cod", s, aux);
        fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);
      
        if (RS[s].ocupado) {
            FIRMA_2_1("RS%d.ocupado", s, "SI");
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
                FIRMA_2_2("RS%d.Vj", s, "%.2f", RS[s].Vj.f);          
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
                FIRMA_2_2("RS%d.Vk", s, "%.2f", RS[s].Vk.f);          
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } /* endif */

            FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", RS[s].rob);
            fprintf(f_salida, "  <td>%s</td>\n", vstr); 

            if (SumRest.ocupado && SumRest.estacion == s) {
                FIRMA_2_3("RS%d.est", s, "%d/%d", SumRest.ciclo, SumRest.Teval);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } else if (RegSumRest.ocupado && RegSumRest.estacion == s) {
                FIRMA_2_3("RS%d.est", s, "%d/%d", SumRest.Teval, SumRest.Teval);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } else {
                FIRMA_2_1("RS%d.est", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
	    } /* endif */
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
            FIRMA_2_1("RS%d.est", s, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	} /* endif */
      
        fprintf(f_salida, " </tr>\n");

    } /* endfor */

    /*** Estaciones de reserva de multiplicación/división ***/

    for (s= INICIO_RS_MULT_DIV; 
         s <= FIN_RS_MULT_DIV; s++) {
        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
        imprime_codigo(s, aux);
        FIRMA_2_1("RS%d.cod", s, aux);
        fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);

        if (RS[s].ocupado) {
            FIRMA_2_1("RS%d.ocupado", s, "SI");
            fprintf(f_salida, "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr); 

            imprime_operacion(RS[s].OP, aux);
            FIRMA_2_1("RS%d.op", s, aux);          
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 

            if (RS[s].Qj != MARCA_NULA)	{
                FIRMA_2_2("RS%d.Qj", s, "#&nbsp;%d", RS[s].Qj);          
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                FIRMA_2_1("RS%d.Vj", s, "&nbsp;");          
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
	    } else {
                FIRMA_2_1("RS%d.Qj", s, "&nbsp;");          
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
                FIRMA_2_2("RS%d.Vj", s, "%.2f", RS[s].Vj.f);          
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
                FIRMA_2_2("RS%d.Vk", s, "%.2f", RS[s].Vk.f);          
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } /* endif */

            FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", RS[s].rob);
            fprintf(f_salida, "  <td>%s</td>\n", vstr); 

            if (MultDiv.ocupado && MultDiv.estacion == s) {
                FIRMA_2_3("RS%d.est", s, "%d/%d", MultDiv.ciclo, MultDiv.Teval);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } else if (RegMultDiv.ocupado && RegMultDiv.estacion == s) {
                FIRMA_2_3("RS%d.est", s, "%d/%d", MultDiv.Teval, MultDiv.Teval);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } else {
                FIRMA_2_1("RS%d.est", s, "&nbsp;");
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
	    } /* endif */
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

    /*** Tampones de lectura/escritura ***/
  
    fprintf(f_salida, "<table>\n"); 

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Cod</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"40\">Busy</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Dir.</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">rob</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\">Estado</td>\n"); 

    fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");

    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Cod</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"40\">Busy</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Dir.</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">Qk</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"50\">Vk</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\">Confirm.</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\">Estado</td>\n"); 
    fprintf(f_salida, " </tr>\n");

    for (i= 0; 
         i <MAX(TAM_TAMPON_LECT, TAM_TAMPON_ESCR); i++) {
        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");

        /*** Tampones de lectura ***/
  
        if (i < TAM_TAMPON_LECT) {
            s= INICIO_TAMPON_LECT + i;

            imprime_codigo(s, aux);
            FIRMA_2_1("RS%d.cod", s, aux);
            fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);

            if (TL[s].ocupado) {
                FIRMA_2_1("RS%d.ocupado", s, "SI");
                fprintf(f_salida, "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr); 

                FIRMA_2_2("RS%d.dir", s, "%ld", TL[s].direccion);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	      
                FIRMA_2_2("RS%d.rob", s, "#&nbsp;%d", TL[s].rob);
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
              
                if (MemDatos.ocupado && MemDatos.estacion == s) {
                    FIRMA_2_3("RS%d.est", s, "%d/%d", MemDatos.ciclo, MemDatos.Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } else if (RegMemDatos.ocupado && RegMemDatos.estacion == s) {
                    FIRMA_2_3("RS%d.est", s, "%d/%d", MemDatos.Teval, MemDatos.Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } else {
                    FIRMA_2_1("RS%d.est", s, "&nbsp;");
                    fprintf(f_salida, "  <td>%s</td>\n", vstr); 
                } /* endif */
	    } else {
                FIRMA_2_1("RS%d.ocupado", s, "NO");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                FIRMA_2_1("RS%d.dir", s, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                FIRMA_2_1("RS%d.rob", s, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                FIRMA_2_1("RS%d.est", s, "&nbsp;");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	    } /* endif */
	} else {
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
	} /* endif */

        fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");

        /*** Tampones de escritura ***/


        if (i < TAM_TAMPON_ESCR) {
            s= INICIO_TAMPON_ESCR + i; 
	  
            imprime_codigo(s, aux);
            FIRMA_2_1("RS%d.cod", s, aux);
            fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);

            if (TE[s].ocupado) {
                FIRMA_2_1("RS%d.ocupado", s, "SI");
                fprintf(f_salida, "  <td bgcolor=\"#ffddaa\" align=\"center\">%s</td>\n", vstr); 

                FIRMA_2_2("RS%d.dir", s, "%ld", TE[s].direccion);
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
	      
                if (TE[s].Qk != MARCA_NULA) {
                    FIRMA_2_2("RS%d.Qk", s, "#&nbsp;%d", TE[s].Qk);          
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                    FIRMA_2_1("RS%d.Vk", s, "&nbsp;");          
                    fprintf(f_salida, "  <td>%s</td>\n", vstr); 
                } else {
                    FIRMA_2_1("RS%d.Qk", s, "&nbsp;");          
                    fprintf(f_salida, "  <td>%s</td>\n", vstr); 
                    FIRMA_2_2("RS%d.Vk", s, "%.2f", TE[s].Vk.f);          
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } /* endif */


                FIRMA_2_2("RS%d.conf", s, "%s", (TE[s].confirm) ? "SI" : "NO"); 
                fprintf(f_salida, "  <td>%s</td>\n", vstr); 
	      
                if (MemDatos.ocupado && MemDatos.estacion == s) {
                    FIRMA_2_3("RS%d.est", s, "%d/%d", MemDatos.ciclo, MemDatos.Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } else if (RegMemDatos.ocupado && RegMemDatos.estacion == s) {
                    FIRMA_2_3("RS%d.est", s, "%d/%d", MemDatos.Teval, MemDatos.Teval);
                    fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                } else {
                    FIRMA_2_1("RS%d.est", s, "&nbsp;");
                    fprintf(f_salida, "  <td>%s</td>\n", vstr); 
                } /* endif */
	    } else {
                FIRMA_2_1("RS%d.ocupado", s, "NO");
                fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
                FIRMA_2_1("RS%d.dir", s, "&nbsp;");
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
	} else {
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
            fprintf(f_salida, "  <td bgcolor=white>&nbsp;</td>\n");
	} /* endif */

        fprintf(f_salida, " </tr>\n");

    } /* endfor */

    fprintf(f_salida, "</table>\n"); 

    fprintf(f_salida, "  </td><td>\n"); 

    /*** Registros de salida ***/
  
    fprintf(f_salida, "<table>\n"); 

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"75\">Registros</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"40\">Busy</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"75\">Dato</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"25\">rob</td>\n"); 
    fprintf(f_salida, " </tr>\n");

    /*** RegSumRest */
    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    FIRMA_1_1("Reg.name", "SumRest");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);
    if (RegSumRest.ocupado) {
        FIRMA_2_1("%s.ocupado", "SumRest", "SI");
        fprintf(f_salida, "  <td align=\"center\" bgcolor=\"#ffddaa\">%s</td>\n", vstr); 
        FIRMA_2_2("%s.valor", "SumRest", "%.2f", RegSumRest.valor.f);
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_2("%s.rob", "SumRest", "#&nbsp;%d", RegSumRest.codigo);
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
    } else {
        FIRMA_2_1("%s.ocupado", "SumRest", "NO");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_1("%s.valor", "SumRest", "&nbsp;");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_1("%s.rob", "SumRest", "&nbsp;");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    /*** RegMultDiv */
    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    FIRMA_1_1("Reg.name", "MultDiv");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);
    if (RegMultDiv.ocupado) {
        FIRMA_2_1("%s.ocupado", "MultDiv", "SI");
        fprintf(f_salida, "  <td align=\"center\" bgcolor=\"#ffddaa\">%s</td>\n", vstr); 
        FIRMA_2_2("%s.valor", "MultDiv", "%.2f", RegMultDiv.valor.f);
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_2("%s.rob", "MultDiv", "#&nbsp;%d", RegMultDiv.codigo);
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
    } else {
        FIRMA_2_1("%s.ocupado", "MultDiv", "NO");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_1("%s.valor", "MultDiv", "&nbsp;");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_1("%s.rob", "MultDiv", "&nbsp;");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    /*** RegMemDatos */
    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    FIRMA_1_1("Reg.name", "MemDatos");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);
    if (RegMemDatos.ocupado) {
        FIRMA_2_1("%s.ocupado", "MemDatos", "SI");
        fprintf(f_salida, "  <td align=\"center\" bgcolor=\"#ffddaa\">%s</td>\n", vstr); 
        if (inst_int(RB[RegMemDatos.codigo].OP))
            FIRMA_2_2("%s.valor", "MemDatos", "%ld", RegMemDatos.valor.i);
        else
            FIRMA_2_2("%s.valor", "MemDatos", "%.2f", RegMemDatos.valor.f);
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_2("%s.rob", "MemDatos", "#&nbsp;%d", RegMemDatos.codigo);
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
    } else {
        FIRMA_2_1("%s.ocupado", "MemDatos", "NO");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_1("%s.valor", "MemDatos", "&nbsp;");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_1("%s.rob", "MemDatos", "&nbsp;");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
    } /* endif */
    fprintf(f_salida, " </tr>\n");

    /*** RegEnteros */
    fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
    FIRMA_1_1("Reg.name", "Enteros");
    fprintf(f_salida, "  <td bgcolor=\"#ddeeff\" align=\"center\">%s</td>\n", vstr);
    if (RegEnteros.ocupado) {
        FIRMA_2_1("%s.ocupado", "Enteros", "SI");
        fprintf(f_salida, "  <td align=\"center\" bgcolor=\"#ffddaa\">%s</td>\n", vstr); 
        if (inst_branch(RB[RegEnteros.codigo].OP))
            FIRMA_2_2("%s.valor", "Enteros", "%s", (RegEnteros.valor.i) ? "Salta" : "No Salta");
        else 
            FIRMA_2_2("%s.valor", "Enteros", "%ld", RegEnteros.valor.i);
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_2("%s.rob", "Enteros", "#&nbsp;%d", RegEnteros.codigo);
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
    } else {
        FIRMA_2_1("%s.ocupado", "Enteros", "NO");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_1("%s.valor", "Enteros", "&nbsp;");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
        FIRMA_2_1("%s.rob", "Enteros", "&nbsp;");
        fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
    } /* endif */
    fprintf(f_salida, " </tr>\n");

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
    for (i= 0; i< 4; i++) {
        fprintf(f_salida, "  <td width=\"20\" align=\"center\">+%d</td>\n", i);
    } /* endif */
    fprintf(f_salida, " </tr>\n");
  
    next= SegDatos.inicio;
    for (i= SegDatos.inicio; i< SegDatos.final; i++) {

        if (i % sizeof(word) == 0) {
            fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");
            fprintf(f_salida, "   <td bgcolor=\"#ddeeff\" align=\"right\">%d</td>\n", i);
        } /* endif */

        if (i == next) {
            switch (md_tipo[i]) {
            case t_byte:
                FIRMA_2_2("MD%d", i, "%hhX", MD.m_byte[dir_byte(i)]);
                fprintf(f_salida, 
                        "  <td align=\"center\">%s</td>\n", vstr);
                next= i + sizeof(byte);
                break;
            case t_half:
                FIRMA_2_2("MD%d", i, "%hd", MD.m_half[dir_half(i)]);
                fprintf(f_salida, 
                        "  <td align=\"center\" colspan=\"2\">%s</td>\n", vstr);
                next= i + sizeof(half);
                break;
            case t_word:
                FIRMA_2_2("MD%d", i, "%d", MD.m_word[dir_word(i)]);
                fprintf(f_salida, 
                        "  <td align=\"center\" colspan=\"4\">%s</td>\n", vstr);
                next= i + sizeof(word);
                break;
            case t_dword:
                FIRMA_2_2("MD%d", i, "%ld", MD.m_dword[dir_dword(i)]);
                fprintf(f_salida, 
                        "  <td align=\"center\" rowspan=\"2\" colspan=\"4\">%s</td>\n", vstr);
                next= i + sizeof(dword);
                break;
            case t_float:
                FIRMA_2_2("MD%d", i, "%.2f", MD.m_float[dir_float(i)]);
                fprintf(f_salida, 
                        "  <td align=\"center\" colspan=\"4\">%s</td>\n", vstr);
                next= i + sizeof(float);
                break;
            case t_double:
                FIRMA_2_2("MD%d", i, "%.2f", MD.m_double[dir_double(i)]);
                fprintf(f_salida, 
                        "  <td align=\"center\" rowspan=\"2\" colspan=\"4\">%s</td>\n", vstr);
                next= i + sizeof(double);
                break;
            default:
                fprintf(f_salida, "  <td>&nbsp;</td>\n");
                next= i + 1;
            } /* endswitch */
        } /* endif */
        if ((i+1) % sizeof(word) == 0) {
            fprintf(f_salida, " </tr>\n");
        } /* endif */
    } /* endif */
  
    fprintf(f_salida, "</table><br>\n"); 

    fprintf(f_salida, "</td>\n"); 
    fprintf(f_salida, "</tr>\n"); 
    fprintf(f_salida, "</table>\n"); 

    fprintf(f_salida, "<address>Arquitectura e Ingeniería de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n"); 

    fclose(f_salida);

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
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char		aux[128];

    short		x, y;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "crono%03ld.html", Ciclo);
    f_salida= fopen(aux, "w");
    if (f_salida == NULL)
    {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */

    /*** HTML INTRO ***/

    fprintf(f_salida, 
            "<html><head><title>Cronograma: %s. Ciclo %ld</title></head>\n", 
            nombre_fich, Ciclo);
    fprintf(f_salida, 
            "<body bgcolor=\"white\">\n"); 

    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    if (Ciclo > 5)
        fprintf(f_salida, "<a href=\"crono%03ld.html\">[-5]</a>&nbsp;\n", 
                Ciclo -5); 
    else
        fprintf(f_salida, "[-5]&nbsp;\n");
    if (Ciclo > 1)
        fprintf(f_salida, "<a href=\"crono%03ld.html\">[-1]</a>&nbsp;\n", 
                Ciclo -1);
    else
        fprintf(f_salida, "[-1]\n");
      
    fprintf(f_salida, "<a href=\"crono%03ld.html\">[+1]</a>\n", Ciclo +1); 
    fprintf(f_salida, "<a href=\"crono%03ld.html\">[+5]</a>\n", Ciclo +5); 

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"estado%03ld.html\">Estado</a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<!a href=\"crono%03ld.html\">Crono<!/a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"predictor%03ld.html\">BTB</a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<tt><b>Programa: %s</b></tt>\n", nombre_fich); 
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<b>Ciclo: %ld</b>\n", Ciclo); 
    fprintf(f_salida, "<br>\n"); 

    fprintf(f_salida, "<p>Estado al final del ciclo\n"); 

    /*** Cronograma de ejecución ***/

    fprintf(f_salida, "<table>\n"); 
  
    fprintf(f_salida, " <tr bgcolor=\"#ccddff\" align=\"center\">\n"); 
    fprintf(f_salida, "  <td width=\"150\">Instruc.</td>\n");
    for (x= 0; x< MAX(MAX_CICLOS_INIC, maxima_columna_visible); x++)
        fprintf(f_salida, "  <td width=\"25\"><a href=\"crono%03ld.html\">%ld</a></td>\n", 
                x+primer_ciclo, x+primer_ciclo); 
    fprintf(f_salida, " </tr>\n"); 

    for (y= 0; y< MAX_INSTRUC; y++) {
        if (y % 2 == 0)
            fprintf(f_salida, " <tr bgcolor=\"#eeeeee\" align=\"center\">\n"); 
        else
            fprintf(f_salida, " <tr bgcolor=\"#dddddd\" align=\"center\">\n"); 
	

        if (!strlen(crono[y].inst))
            if (y % 2 == 0)
                fprintf(f_salida, 
                        "  <td bgcolor=\"#ddeeff\">&nbsp;</td>\n");
            else
                fprintf(f_salida, 
                        "  <td bgcolor=\"#ccddff\">&nbsp;</td>\n");
        else
            if (y % 2 == 0)
                fprintf(f_salida, 
                        "  <td nowrap=\"nowrap\" align=\"left\" bgcolor=\"#ddeeff\">%s</td>\n",
                        crono[y].inst); 
            else
                fprintf(f_salida, 
                        "  <td nowrap=\"nowrap\" align=\"left\" bgcolor=\"#ccddff\">%s</td>\n", 
                        crono[y].inst); 

        for (x= 0; x< MAX(MAX_CICLOS_INIC, maxima_columna_visible); x++) {
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

    fprintf(f_salida, "<address>Arquitectura e Ingeniería de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n"); 

    fclose(f_salida);

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
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short		i;

    char		aux[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "predictor%03ld.html", Ciclo);
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */

    nueva_firma();                /*** FIRMAS ***/

    /*** HTML INTRO ***/

    fprintf(f_salida, 
            "<html><head><title>Predictor: %s. Ciclo %ld</title></head>\n", 
            nombre_fich, Ciclo);
    fprintf(f_salida, 
            "<body bgcolor=\"white\">\n"); 

    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    if (Ciclo > 5)
        fprintf(f_salida, "<a href=\"predictor%03ld.html\">[-5]</a>&nbsp;\n", 
                Ciclo -5); 
    else
        fprintf(f_salida, "[-5]&nbsp;\n");
    if (Ciclo > 1)
        fprintf(f_salida, "<a href=\"predictor%03ld.html\">[-1]</a>&nbsp;\n", 
                Ciclo -1);
    else
        fprintf(f_salida, "[-1]\n");
      
    fprintf(f_salida, "<a href=\"predictor%03ld.html\">[+1]</a>\n", Ciclo +1); 
    fprintf(f_salida, "<a href=\"predictor%03ld.html\">[+5]</a>\n", Ciclo +5); 

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"estado%03ld.html\">Estado</a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"crono%03ld.html\">Crono</a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<!a href=\"predictor%03ld.html\">BTB<!/a>\n", Ciclo);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<tt><b>Programa: %s</b></tt>\n", nombre_fich); 
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"); 
    fprintf(f_salida, "<b>Ciclo: %ld</b>\n", Ciclo); 
    fprintf(f_salida, "<br>\n"); 

    fprintf(f_salida, "<p>Estado al final del ciclo\n"); 

    /*** Bancos de registros ***/

    /* Branch Target Buffer */

    fprintf(f_salida, "<table>\n"); 

    fprintf(f_salida, " <tr bgcolor=\"#ccddff\">\n");
    fprintf(f_salida, "  <td width=\"150\">PC (instr.)</td>\n");
    fprintf(f_salida, "  <td align=\"center\" width=\"150\">Estado</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"150\">Dir. Destino</td>\n"); 
    fprintf(f_salida, "  <td align=\"center\" width=\"150\">(Último acceso)</td>\n"); 
    fprintf(f_salida, " </tr>\n");

    for (i= 0; i < TAM_BUFFER_PREDIC; i++) {
        fprintf(f_salida, " <tr bgcolor=\"#eeeeee\">\n");

        if (BTB[i].orden > 0) {    /* Entrada ocupada */
            FIRMA_2_2("BTB%d.pc", i, "%ld", BTB[i].PC);
            imprime_instruccion(aux, BTB[i].PC);
            fprintf(f_salida, "  <td>%s (%s)</td>\n", vstr, aux); 

            imprime_estado_predictor(aux, BTB[i].estado); 
            FIRMA_2_1("BTB%d.estado", i, aux);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 

            FIRMA_2_2("BTB%d.destino", i, "%ld", BTB[i].destino);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 

            FIRMA_2_2("BTB%d.orden", i, "%ld", BTB[i].orden);
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	} else {
            FIRMA_2_1("BTB%d.pc", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
            FIRMA_2_1("BTB%d.estado", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
            FIRMA_2_1("BTB%d.destino", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
            FIRMA_2_1("BTB%d.orden", i, "&nbsp;");
            fprintf(f_salida, "  <td align=\"center\">%s</td>\n", vstr); 
	} /* endif */

        fprintf(f_salida, " </tr>\n");
    } /* endfor */

    fprintf(f_salida, "</table>\n"); 

    fprintf(f_salida, "<address>Arquitectura e Ingeniería de Computadores</address>\n");
    fprintf(f_salida, "</body></html>\n"); 

    fclose(f_salida);

    if (error_firma) {
        fprintf(stderr, "ERROR. "
                "Existen diferencias entre la ejecución actual y el fichero de firmas.\n"
                "Analice el fichero de estado 'estado%03ld.html'\n", Ciclo);
        exit(1);
    } /* endif */

} /* end imprime_predictor */

/***************************************************************
 *
 * Func: imprime_estadisticas
 *
 * Desc: Imprime las estadisticas del programa
 *
 **************************************************************/

void imprime_estadisticas
(
    )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/


    /*************************************/
    /*  Function body                    */
    /*************************************/

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
