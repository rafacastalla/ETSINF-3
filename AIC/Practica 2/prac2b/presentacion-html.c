/**************************************************************************
 * 
 * Departamento de Informatica de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 *	   Pedro López (plopez@gap.upv.es)
 * 
 * File: presentacion-html.c
 *  
 * Description: Contiene las funciones necesarias para presentar la
 *    informacion sobre la ejecución del algoritmo
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *************************************************************************/

#define presentacion_html_C

/***** Includes ***********************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


/***** Definiciones Externas **********************************/

#include "tipos.h"
#include "main.h"
#include "instrucciones.h"
#include "mips.hi"
#include "etiquetas.h"
#include "presentacion-html.h"

#ifdef MAX
#undef MAX
#endif
#define MAX(x,y) (((x)>(y)) ? (x) : (y))

#define F_DWORD "%" PRId64
#define S_READ "&#8592"
#define S_WRITE "&#8594"
#define S_READWRITE "&#8646"


/***** Variables Globales *************************************/

/***** Variables Locales **************************************/

static FILE *	f_salida;

static ciclo_t	primera_instruccion= 1;
static ciclo_t	primer_ciclo= 1;
static short    maxima_columna_visible= MAX_CICLOS_INIC;


/***** Funciones Locales **************************************/

/***************************************************************
 *
 * Func: imprime_intro
 *
 * Desc: Imprime la intro HTML
 *
 **************************************************************/

static void imprime_intro (char* titulo)
{
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /*** HTML INTRO ***/

    fprintf(f_salida,"<!DOCTYPE html>\n");
    fprintf(f_salida, 
            "<html lang=\"es-ES\">\n<head>\n<title>%s:%s. Ciclo %ld</title>\n",
            titulo, nombre_fich, Ciclo);
    fprintf(f_salida,
            "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
    fprintf(f_salida,
            "<body bgcolor=\"white\">\n</head>\n"); 

}


/***************************************************************
 *
 * Func: imprime_w3css
 *
 * Desc: Imprime la intro HTML incluyendo el archivo css
 *
 **************************************************************/

static void imprime_w3css (char* titulo)
{
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /*** HTML INTRO ***/

    fprintf(f_salida,"<!DOCTYPE html>\n");
    fprintf(f_salida, 
            "<html lang=\"es-ES\">\n<head>\n<title>%s:%s. Ciclo %ld</title>\n",
            titulo, nombre_fich, Ciclo);
    fprintf(f_salida,
            "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
    fprintf(f_salida, 
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n");
    fprintf(f_salida, 
			"<link rel=\"stylesheet\" href=\"http://www.w3schools.com/lib/w3.css\">\n");
	fprintf(f_salida,"<style>\n");
	fprintf(f_salida,"html, body {\n");
	fprintf(f_salida,"    font-family:\"%s\", Times, serif;\n", FONT_NAME);
	fprintf(f_salida,"    font-size:%dpt;\n", FONT_SIZE);
	fprintf(f_salida,"    line-height:%s;\n", LINE_HEIGHT);
	fprintf(f_salida,"}\n");
	fprintf(f_salida,"</style>\n");
    fprintf(f_salida,"</head>\n<body>\n\n"); 

}

/***************************************************************
 *
 * Func: imprime_footer
 *
 * Desc: Imprime el final HTML
 *
 **************************************************************/
static void imprime_footer ()
{
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /*** HTML FINAL ***/
    fprintf(f_salida, "<!-- Final -->\n");
//    fprintf(f_salida, "<div class=\"w3-row w3-container\">\n"); 
   	fprintf(f_salida, "<address>\n");
   	fprintf(f_salida, "Arquitectura e Ingeniería de Computadores<br>\n");
	fprintf(f_salida, "Departamento de Informática de Sistemas y Computadores (DISCA)<br>\n");
 	fprintf(f_salida, "Universitat Politècnica de València<br>\n");
 	fprintf(f_salida, "</address>\n");
//	fprintf(f_salida, "</div>\n\n");

    fprintf(f_salida, "</body>\n</html>\n"); 
}

/***************************************************************
 *
 * Func: imprime_footer_css
 *
 * Desc: Imprime el final HTML con css
 *
 **************************************************************/
static void imprime_footer_css ()
{
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /*** HTML FINAL ***/
    fprintf(f_salida, "<!-- Final -->\n");
    fprintf(f_salida, "<div class=\"w3-row w3-container w3-light-grey\">\n"); 
   	fprintf(f_salida, "<address>\n");
   	fprintf(f_salida, "Arquitectura e Ingeniería de Computadores<br>\n");
	fprintf(f_salida, "Departamento de Informática de Sistemas y Computadores (DISCA)<br>\n");
 	fprintf(f_salida, "Universitat Politècnica de València<br>\n");
 	fprintf(f_salida, "</address>\n");
	fprintf(f_salida, "</div>\n\n");

    fprintf(f_salida, "</body>\n</html>\n"); 
}


/***************************************************************
 *
 * Func: imprime_nav1
 *
 * Desc: Imprime la barra de navegación
 *
 **************************************************************/

static void imprime_nav1 ()
{
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /* Barra de navegación */
    fprintf(f_salida, "<!-- Barra de navegacion -->\n");
    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n"); 
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n"); 
	
    fprintf(f_salida, "<a href=\"estado%03d.html\">Estado</a>\n", 1);    

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"crono%03d.html\">Cronograma</a>\n", 1);    

    /*
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"datapath%03d.html\">Datapath</a>\n", 1);
     */
     
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "Programa: %s\n\n", nombre_fich);
}


/***************************************************************
 *
 * Func: imprime_nav2
 *
 * Desc: Imprime la barra de navegación con estado ciclo a ciclo
 *
 **************************************************************/

static void imprime_nav2 (char* archivo)
{
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /* Barra de navegación */
    fprintf(f_salida, "<!-- Barra de navegacion -->\n");
    fprintf(f_salida, "<a href=\"index.html\">INICIO</a>&nbsp;\n");
    fprintf(f_salida, "<a href=\"final.html\">FINAL</a>&nbsp;\n");
    if (Ciclo > 5)
        fprintf(f_salida, "<a href=\"%s%03ld.html\">[-5]</a>&nbsp;\n", archivo,
                Ciclo -5);
    else
        fprintf(f_salida, "[-5]&nbsp;\n");
    if (Ciclo > 1)
        fprintf(f_salida, "<a href=\"%s%03ld.html\">[-1]</a>&nbsp;\n", archivo, 
                Ciclo -1);
    else
        fprintf(f_salida, "[-1]\n");

    fprintf(f_salida, "<a href=\"%s%03ld.html\">[+1]</a>\n", archivo, Ciclo +1);
    fprintf(f_salida, "<a href=\"%s%03ld.html\">[+5]</a>\n", archivo, Ciclo +5);
    
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"estado%03ld.html\">Estado</a>\n", Ciclo);
    
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<a href=\"crono%03ld.html\">Crono</a>\n", Ciclo);

//    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
//    fprintf(f_salida, "<a href=\"datapath%03ld.html\">Datapath</a>\n", Ciclo);

    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "Programa: %s\n", nombre_fich);
    fprintf(f_salida, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    fprintf(f_salida, "<b>Ciclo: %ld</b>\n\n", Ciclo);
}


/***************************************************************
 *
 * Func: imprime_nav1_css
 *
 * Desc: Imprime la barra de navegación, utilizando CSS
 *
 **************************************************************/

static void imprime_nav1_css ()
{
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /* Barra de navegación */
    fprintf(f_salida, "<!-- Barra de navegacion CSS -->\n");
    fprintf(f_salida,"<div>\n");
    fprintf(f_salida,"<ul class=\"w3-navbar w3-top w3-light-grey\">\n");
	fprintf(f_salida,"<li><a class=\"w3-hover-grey\" href=\"index.html\">INICIO</a>\n");
  	fprintf(f_salida,"<li><a class=\"w3-hover-grey\" href=\"final.html\">FINAL</a>\n");
  	fprintf(f_salida,"<li><a class=\"w3-hover-grey\" href=\"result001.html\">Estado</a>\n");
	fprintf(f_salida,"</ul>\n");
	fprintf(f_salida,"</div>\n<br>\n");
}

/***************************************************************
 *
 * Func: imprime_nav2_css
 *
 * Desc: Imprime la barra de navegación con estado ciclo a ciclo, utilizando CSS
 *
 **************************************************************/

static void imprime_nav2_css (char* archivo)
{
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /* Barra de navegación */
    fprintf(f_salida, "<!-- Barra de navegacion CSS -->\n");
    fprintf(f_salida,"<div>\n");
    fprintf(f_salida,"<ul class=\"w3-navbar w3-top w3-light-grey\">\n");
	fprintf(f_salida,"<li><a class=\"w3-hover-grey\" href=\"index.html\">INICIO</a>\n");
  	fprintf(f_salida,"<li><a class=\"w3-hover-grey\" href=\"final.html\">FINAL</a>\n");

  	if (Ciclo > 10)
        fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[-10]</a>\n", archivo,
                Ciclo -15);
    else
        fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[-10]</a>\n", archivo,
                Ciclo);
                
  	if (Ciclo > 5)
        fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[-5]</a>\n", archivo,
                Ciclo -5);
    else
        fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[-5]</a>\n", archivo,
                Ciclo);

    if (Ciclo > 1)
        fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[-1]</a>\n", archivo, 
                Ciclo -1);
    else
         fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[-1]</a>\n", archivo, 
                Ciclo);

        fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[+1]</a>\n", archivo, 
                Ciclo+1);
        fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[+5]</a>\n", archivo, 
                Ciclo+5);
        fprintf(f_salida, "<li><a class=\"w3-hover-grey\" href=\"%s%03ld.html\">[+10]</a>\n", archivo, 
                Ciclo+10);

	fprintf(f_salida,"</ul>\n");
	fprintf(f_salida,"</div>\n<br>\n");
}


/***************************************************************
 *
 * Func: imprime_conf
 *
 * Desc: Imprime la configuración
 *
 **************************************************************/

static void imprime_conf ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

     char		aux[128];    
    
    /*************************************/
    /*  Function body                    */
    /*************************************/
    

    /*** Configuración ***/

    fprintf(f_salida, "<!-- Configuración -->\n");
    
    fprintf(f_salida, "<table>\n"); 
    
    fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td colspan=\"2\" bgcolor=\"%s\" align=\"center\">Configuración</td>\n", BG_HEADER);
    fprintf(f_salida, "</tr>\n");

    fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"%s\" align=\"center\">Parámetro</td>\n", BG_HEADER_COL1);
    fprintf(f_salida, "  <td bgcolor=\"%s\" align=\"center\">Valor</td>\n", BG_HEADER_COL2);
    fprintf(f_salida, "</tr>\n");
 
	/*** Nombre programa ***/
	fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"%s\">Programa</td>\n", BG_VAL1);
    fprintf(f_salida, "  <td bgcolor=\"%s\" align=\"center\">%s</td>\n", BG_VAL2, nombre_fich);
    fprintf(f_salida, "</tr>\n");
   
	/*** Riesgos datos ***/
    switch (solucion_riesgos_datos) {
      case ninguno:
      		sprintf(aux, "%s", "Ninguno");
             break;
      case parada:
      		sprintf(aux, "%s", "Stalls");
             break;
      case cortocircuito:   
      		sprintf(aux, "%s", "Forwarding");
    };
        
	/*** Riesgos datos ***/
    fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"%s\">Riesgos de datos</td>\n", BG_VAL1);
    fprintf(f_salida, "  <td bgcolor=\"%s\" align=\"center\">%s</td>\n", BG_VAL2, aux);
    fprintf(f_salida, "</tr>\n");

    switch (solucion_riesgos_control) {
      case ds3:
      		sprintf(aux, "%s", "S. Retardado (DS=3)");
             break;
      case ds2:
      		sprintf(aux, "%s", "S. Retardado (DS=2)");
             break;
      case ds1:
      		sprintf(aux, "%s", "S. Retardado (DS=1)");
             break;
      case pnt:
      		sprintf(aux, "%s", "Predict-not-taken");
             break;
      case parada:   
      		sprintf(aux, "%s", "Stalls");
    };

    fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"%s\">Riesgos de control&nbsp;&nbsp;</td>\n", BG_VAL1);
    fprintf(f_salida, "  <td bgcolor=\"%s\" align=\"center\">%s</td>\n", BG_VAL2, aux);
    fprintf(f_salida, "</tr>\n\n");

    /*** Registros ***/
    fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td bgcolor=\"%s\">Registros</td>\n", BG_VAL1);
    fprintf(f_salida, "  <td bgcolor=\"%s\" align=\"center\">%d</td>\n", BG_VAL2, TAM_REGISTROS);
    fprintf(f_salida, "</tr>\n\n");

    
    fprintf(f_salida, "</table>\n\n"); 
}


/***************************************************************
 *
 * Func: desplazamiento_horizontal
 *
 * Description: 
 *   Desplaza la zona visible un ciclo hacia la izquierda
 *
 **************************************************************/

static void desplazamiento_horizontal ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i, j;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    for (i= 0; i<MAX_INSTRUC; i++) {
        for (j= 0; j<MAX_CICLOS-1; j++)
            strcpy(crono[i].fase[j], crono[i].fase[j+1]);
      
        /* Borra la última columna */
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

static void desplazamiento_vertical ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    short i, j, desp;

    /*************************************/
    /*  Function body                    */
    /*************************************/

    /* Averigua si la línea se va a quedar vacía al principio */
    for (desp= 0; 
         desp < MAX_CICLOS && 
             !strlen(crono[1].fase[desp]); desp++);
    if (desp == MAX_CICLOS)
        desp= 1;                /* La línea está completamente vacia. Avanzamos sólo un
                                 * ciclo */
    
	
    for (i= 0; i<MAX_INSTRUC-1; i++) {
        strcpy(crono[i].inst, crono[i+1].inst);
      
        for (j= 0; j<MAX_CICLOS-desp; j++)
            strcpy(crono[i].fase[j], crono[i+1].fase[j+desp]);
      
        /* Borra las �ltimas columnas */
        for (j= MAX_CICLOS-desp; j<MAX_CICLOS; j++) 
            strcpy(crono[i].fase[j], "");
    } /* endfor */
  
    /* Borra la �ltima fila */
    crono[MAX_INSTRUC-1].inst[0]= '\0';
    for (j= 0; j<MAX_CICLOS; j++)
        crono[MAX_INSTRUC-1].fase[j][0]= '\0';

    /*** Actualiza los desplazamientos iniciales ***/
  
    primer_ciclo+= desp;
    primera_instruccion++;
    maxima_columna_visible-= desp;

} /* end desplazamiento_vertical */

/***************************************************************
 *
 * Func: color_instruccion
 *
 * Desc: Devuelve un color
 *
 **************************************************************/

static void color_instruccion (
                               char *	color,
                               word	PC
                               )
{
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    if (PC == -1) {
        sprintf(color, "lightgray");
        return ;
    } /* endif */
    
    switch (PC % 10) {
        case 0:
            sprintf(color, "red");
            break;
        case 1:
            sprintf(color, "darkcyan");
            break;
        case 2:
            sprintf(color, "limegreen");
            break;
        case 3:
            sprintf(color, "orange");
            break;
        case 4:
            sprintf(color, "deeppink");
            break;
        case 5:
            sprintf(color, "brown");
            break;
        case 6:
            sprintf(color, "royalblue");
            break;
        case 7:
            sprintf(color, "olive");
            break;
        case 8:
            sprintf(color, "lightcoral");
            break;
        case 9:
            sprintf(color, "magenta");
            break;
    } /* endswitch */
    
} /* end color_instruccion */


/***************************************************************
 *
 * Func: muestra_senyal
 *
 * Description:
 *   Imprime el nombre de la señal, si está activada
 *
 **************************************************************/

static void muestra_senyal (boolean senyal, char nombre[128])
{
    char		aux[128];
    
    if (senyal == SI)
        sprintf(aux, "%s", nombre);
    else
        sprintf(aux, "&nbsp;");
    fprintf(f_salida, "<td width=112>%s</td>\n", aux);
}


/***************************************************************
 *
 * Func: muestra_fase
 *
 * Description:
 *   Muestra la fase de cada instruccion en el cronograma
 *
 **************************************************************/

static void muestra_fase (
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
    
    if (o >= 0 && c >= 0) {
        strcpy(crono[o].fase[c], fase);
        if (c + 1 > maxima_columna_visible)
            maxima_columna_visible= c + 1;
    } /* endif */
    
} /* end muestra_fase */

/***************************************************************
 *
 * Func: imprime_int_regs
 *
 * Desc: Imprime el estado de los registros enteros
 *
 **************************************************************/

static void imprime_int_regs ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    short		i, j;
    
    char col_ID[20], col_WB[20];

    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /* Banco de registros enteros */
    
    // Colores
    color_instruccion(col_ID, IF_ID.iPC);
    color_instruccion(col_WB, MEM_WB.iPC);
  
    fprintf(f_salida, "<!-- Registros enteros -->\n");
    fprintf(f_salida, "<table>\n");
        
    j=0;
    while (j<TAM_REGISTROS) {
        fprintf(f_salida, "<tr>\n");
        fprintf(f_salida, "<td width=50 bgcolor=\"%s\">Rint</td>\n", BG_OPER);
        
        for (i= 0; i<(NUM_REG_VISIBLES<TAM_REGISTROS-j ? NUM_REG_VISIBLES: TAM_REGISTROS-j); i++) {
            fprintf(f_salida, "<td width=75 bgcolor=\"%s\" align=center>R%d</td>\n", BG_REGS, i+j);
        } /* endfor */
        fprintf(f_salida, "</tr>\n");
        
        fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
        fprintf(f_salida, "<td width=50 bgcolor=\"%s\">&nbsp</td>\n", "white");
        for (i= 0; i<(NUM_REG_VISIBLES<TAM_REGISTROS-j ? NUM_REG_VISIBLES: TAM_REGISTROS-j); i++) {
            // El registro se escribe
            if (hay_destino_WB() && (MEM_WB.IR.Rdestino==(i+j))) {
                // Y tambien se lee
                if ((hay_fuente1_ID() && (IF_ID.IR.Rfuente1==(i+j))) ||
                    (hay_fuente2_ID() && (IF_ID.IR.Rfuente2==(i+j)))) {
                    fprintf(f_salida, "<td align=\"right\" bgcolor=\"%s\">" F_DWORD "</td>\n",BG_RW,
                            Rint[i+j].valor);
                    // Solo se escribe
                } else {
                    fprintf(f_salida, "<td align=\"right\" bgcolor=\"%s\">" F_DWORD "</td>\n",col_WB,
                            Rint[i+j].valor);
                }
                // El registro se lee
            } else if ((hay_fuente1_ID() && (IF_ID.IR.Rfuente1==(i+j))) ||
                       (hay_fuente2_ID() && (IF_ID.IR.Rfuente2==(i+j)))) {
                fprintf(f_salida, "<td align=\"right\" bgcolor=\"%s\">"  F_DWORD "</td>\n",col_ID,
                        Rint[i+j].valor);
                // Ni se lee ni se escribe
            } else {
                fprintf(f_salida, "<td align=\"right\">" F_DWORD "</td>\n",
                        Rint[i+j].valor);
            }
            //			fprintf(f_salida, "<td align=center>" F_DWORD "</td>\n",
            //					Rint[i+j].valor);
        } /* endfor */
        j=j+NUM_REG_VISIBLES;
    }
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table>\n\n");
    
  
} /* end imprime_int_regs */

/***************************************************************
 *
 * Func: imprime_int_regs_col
 *
 * Desc: Imprime el estado de los registros enteros en una columna
 *
 **************************************************************/

static void imprime_int_regs_col ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    short		i, j;
    
    char col_ID[20], col_WB[20];

    
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    /* Banco de registros enteros */
    
     // Colores
    color_instruccion(col_ID, IF_ID.iPC);
    color_instruccion(col_WB, MEM_WB.iPC);

   fprintf(f_salida, "<!-- Registros enteros en columna -->\n");
    fprintf(f_salida, "<table>\n");
 
 
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n", BG_HEADER);
    fprintf(f_salida, "  <td align=\"center\" colspan=2>Registros enteros</td>\n");
    fprintf(f_salida, "</tr>\n");
        fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td width=75 bgcolor=\"%s\" align=\"center\">Registro</td>\n", BG_DIR1);
    fprintf(f_salida, "  <td width=75 bgcolor=\"%s\" align=\"center\">Valor</td>\n", BG_DIR2);
    fprintf(f_salida, "</tr>\n");
	
	i=0; // NO hace falta, pero así reutilizo el código
    j=0;
    while (j<TAM_REGISTROS) {
        fprintf(f_salida, "<tr>\n");
/*		fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
					"R%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", BG_VAL1, i+j); */

        // El registro se escribe
        if (hay_destino_WB() && (MEM_WB.IR.Rdestino==(i+j))) {
            // Y tambien se lee
                if ((hay_fuente1_ID() && (IF_ID.IR.Rfuente1==(i+j))) ||
                    (hay_fuente2_ID() && (IF_ID.IR.Rfuente2==(i+j)))) {
                    // Rx
					fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
						S_READWRITE " R%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", BG_RW, i+j);
					// Valor
                    fprintf(f_salida, "<td align=\"right\" bgcolor=\"%s\"><i><b>" F_DWORD "</b></i></td>\n",BG_VAL2,
                            Rint[i+j].valor);
                    // Solo se escribe
                } else {
                    // Rx
					fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
						S_WRITE " R%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", col_WB, i+j);
					// Valor
                    fprintf(f_salida, "<td align=\"right\" bgcolor=\"%s\"><b>" F_DWORD "</b></td>\n",BG_VAL2,
                            Rint[i+j].valor);
                }
                // El registro se lee
        } else if ((hay_fuente1_ID() && (IF_ID.IR.Rfuente1==(i+j))) ||
                       (hay_fuente2_ID() && (IF_ID.IR.Rfuente2==(i+j)))) {
                // Rx
                fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
						S_READ " R%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", col_ID, i+j);
				// Valor
                fprintf(f_salida, "<td align=\"right\" bgcolor=\"%s\"><i>" F_DWORD "</i></td>\n",BG_VAL2,
                        Rint[i+j].valor);
                // Ni se lee ni se escribe
        } else {
                // Rx
        		fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
						"R%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", BG_VAL1, i+j);
				// Valor
                fprintf(f_salida, "<td align=\"right\" bgcolor=\"%s\">" F_DWORD "</td>\n",BG_VAL2,
                        Rint[i+j].valor);
        }

        fprintf(f_salida, "</tr>\n");
		j = j+1;
    } /* while */
	
    fprintf(f_salida, "</table>\n\n"); 
    
} /* end imprime_int_regs_col */

/***************************************************************
 *
 * Func: imprime_mem
 *
 * Desc: Imprime el estado de la memoria de datos 
 *
 **************************************************************/

static void imprime_Dmem ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    short		i= 0;
    
    char		aux[128];
    
    char col_M[20];

    
    
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    // Colores
    color_instruccion(col_M, EX_MEM.iPC);
   
    /*** Contenido de la memoria de datos ***/
    
    fprintf(f_salida, "<!-- Mem Datos -->\n");
    fprintf(f_salida, "<table>\n");
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_OPER);
    fprintf(f_salida, "<td align=\"center\" colspan=\"9\">Memoria de Datos</td>\n");
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_DIR1);
    fprintf(f_salida, "<td width=75>Dirección</td>\n");

    for (i= 0; i< 8; i++) {
    	    fprintf(f_salida, "<td width=75 bgcolor=\"%s\" align=\"center\">+%lu</td>\n", BG_DIR2, i*sizeof(word));
	} /* endfor */
    fprintf(f_salida, "</tr>\n");
    
    for (i= SegDatos.inicio; i< SegDatos.final; i+= sizeof(dword)) {
            if (dir_dword(i) % 8 == 0) {
				fprintf(f_salida, "<tr bgcolor=%s>\n",BG_VAL1);
                fprintf(f_salida, "<td bgcolor=\"%s\" align=right>%d</td>\n", BG_VAL2, i);
        		} /* endif */
        
        sprintf(aux, "" F_DWORD "", MD.mdword[dir_dword(i)]);
        
        if ((EX_MEM.IR.codop==OP_LW) && (EX_MEM.ALUout==i)) {
            fprintf(f_salida, "<td bgcolor=\"%s\" align=\"right\">%s</td>\n", col_M, aux);
        } else if ((EX_MEM.IR.codop==OP_SW) && (EX_MEM.ALUout==i)) {
            fprintf(f_salida, "<td bgcolor=\"%s\" align=\"right\">%s</td>\n", col_M, aux);
        } else {
            fprintf(f_salida, "<td align=\"right\">%s</td>\n", aux);
        }
        
        if ((dir_dword(i+sizeof(dword))) % 8 == 0) {
            fprintf(f_salida, "</tr>\n");
        } /* endif */
    } /* endfor */
    
    fprintf(f_salida, "</table>\n\n");
    
} /* end imprime_Dmem */


/***************************************************************
 *
 * Func: imprime_mem_col
 *
 * Desc: Imprime el estado de la memoria de datos en una columna
 *
 **************************************************************/

static void imprime_Dmem_col ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    short		i= 0;
    char		aux[128];
    char		dir[128];
    char		dato[128];
    char 		col_M[20];

     
    
    /*************************************/
    /*  Function body                    */
    /*************************************/    

    // Colores
    color_instruccion(col_M, EX_MEM.iPC);
   

    
    /*** Contenido de la memoria de datos ***/
	
    fprintf(f_salida, "<!-- Mem Datos en columna -->\n");
    fprintf(f_salida, "<table>\n"); 
	
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n", BG_HEADER);
    fprintf(f_salida, "  <td align=\"center\" colspan=2>Memoria de Datos</td>\n");
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td width=75 bgcolor=\"%s\" align=\"center\">Dirección</td>\n", BG_DIR1);
    fprintf(f_salida, "  <td width=75 bgcolor=\"%s\" align=\"center\">Valor</td>\n", BG_DIR2);
    fprintf(f_salida, "</tr>\n");
	
    for (i= SegDatos.inicio; i< SegDatos.final; i+= sizeof(dword)) {
        fprintf(f_salida, "<tr>\n");
		if (te_etiqueta(aux, i, m_datos)==0) { // No es una etiqueta
			sprintf(dir, "%d", i);
			/* fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
					"%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", BG_VAL1, i); */
		} else {
			sprintf(dir, "%s", aux);
			/* fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
					"%s:%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", BG_VAL1, aux,i); */
		}
		
		sprintf(dato, "" F_DWORD "", MD.mdword[dir_dword(i)]);
	
		if ((EX_MEM.IR.codop==OP_LW) && (EX_MEM.ALUout==i)) {
			// LOAD
			fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
					S_READ " %s&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", col_M, dir);
            fprintf(f_salida, "<td bgcolor=\"%s\" align=\"right\"><i>%s</i></td>\n", BG_VAL2, dato);
        } else if ((EX_MEM.IR.codop==OP_SW) && (EX_MEM.ALUout==i)) {
        	// STORE
			fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
					S_WRITE " %s&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", col_M, dir);
            fprintf(f_salida, "<td bgcolor=\"%s\" align=\"right\"><b>%s</b></td>\n", BG_VAL2, dato);
        } else {
			fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
					"%s&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", BG_VAL1, dir);
            fprintf(f_salida, "<td bgcolor=\"%s\" align=\"right\">%s</td>\n", BG_VAL2, dato);
        }
        fprintf(f_salida, "</tr>\n");
		
    } /* endfor */
	
    fprintf(f_salida, "</table>\n\n"); 
}	


/***************************************************************
 *
 * Func: imprime_Imem_col
 *
 * Desc: Imprime el estado de la memoria de instrucciones en una columna
 *
 **************************************************************/

static void imprime_Imem_col ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    short		i= 0;
    char		aux[128];

    
    
    /*************************************/
    /*  Function body                    */
    /*************************************/    
    
 	
    /*** Contenido de la memoria de instrucciones ***/
	
    fprintf(f_salida, "<!-- Mem Instr en columna -->\n");
    fprintf(f_salida, "<table>\n"); 
	
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n", BG_HEADER);
    fprintf(f_salida, "  <td align=\"center\" colspan=2>Memoria de Instrucciones</td>\n");
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "<tr>\n");
    fprintf(f_salida, "  <td width=75 bgcolor=\"%s\" align=\"center\">Dirección</td>\n", BG_DIR1);
    fprintf(f_salida, "  <td width=200 bgcolor=\"%s\" align=\"center\">Instrucciones</td>\n", BG_DIR2);
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</tr>\n");
	
    for (i= SegInstruc.inicio; i< SegInstruc.final; i++) {
        fprintf(f_salida, "<tr>\n");
		if (te_etiqueta(aux, i, m_instruc)==0) { // No es una etiqueta
			fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
					"%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", BG_VAL1, i);
		} else {
			fprintf(f_salida, "  <td align=\"right\" bgcolor=\"%s\">"
					"%s:%d&nbsp;&nbsp;&nbsp;&nbsp;</td>\n", BG_VAL1, aux,i);
		}
        imprime_instruccion(aux, i);
        fprintf(f_salida, "  <td bgcolor=\"%s\">%s</td>\n", BG_VAL2, aux);
        fprintf(f_salida, "</tr>\n");
    } /* endfor */
    fprintf(f_salida, "</table>\n\n"); 
}


/***************************************************************
 *
 * Func: imprime_etapas
 *
 * Desc: Imprime las etapas del procesador
 *
 **************************************************************/

static void imprime_etapas ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    char		aux[128];
    
    
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
   /*** Muestra etapas ***/
    
    fprintf(f_salida, "<!-- Etapas -->\n");
    fprintf(f_salida, "<table>\n");
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_STAGE);
    fprintf(f_salida, "<td width=75 bgcolor=\"white\">&nbsp;</td>\n");
    fprintf(f_salida, "<td width=112 align=center>--/IF</td>\n");
    fprintf(f_salida, "<td width=112 align=center>IF/ID</td>\n");
    fprintf(f_salida, "<td width=112 align=center>ID/EX</td>\n");
    fprintf(f_salida, "<td width=112 align=center>EX/MEM</td>\n");
    fprintf(f_salida, "<td width=112 align=center>MEM/WB</td>\n");
    fprintf(f_salida, "</tr>\n");
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
    fprintf(f_salida, "<td width=75 bgcolor=\"%s\">Instruc.</td>\n",BG_OPER);
    
    imprime_instruccion(aux, PC);
    fprintf(f_salida, "<td>%s</td>\n", aux);
    imprime_instruccion(aux, IF_ID.iPC);
    fprintf(f_salida, "<td>%s</td>\n", aux);
    imprime_instruccion(aux, ID_EX.iPC);
    fprintf(f_salida, "<td>%s</td>\n", aux);
    imprime_instruccion(aux, EX_MEM.iPC);
    fprintf(f_salida, "<td>%s</td>\n", aux);
    imprime_instruccion(aux, MEM_WB.iPC);
    fprintf(f_salida, "<td>%s</td>\n", aux);
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table>\n\n");
    
    

} /* end imprime_etapas */


/***************************************************************
 *
 * Func: imprime_senyales
 *
 * Desc: Imprime las señales activas del procesador
 *
 **************************************************************/

static void imprime_senyales ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
        
    /*************************************/
    /*  Function body                    */
    /*************************************/
    

    /*** Señales ***/
    
//    fprintf(f_salida, "<tr bgcolor=\"white\"><td colspan=\"6\">&nbsp;</td></tr>\n");
    
    fprintf(f_salida, "<!-- Señales activas -->\n");
    fprintf(f_salida, "<table>\n");
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
    fprintf(f_salida, "<td width=75 bgcolor=\"%s\">Señales</td>\n",BG_SIG);
    
    muestra_senyal (IFstall, "IFstall");
    muestra_senyal (IDstall, "IDstall");
    muestra_senyal (MEMaEXalu_s, "MEMaEXalu_s");
    muestra_senyal (0, " ");
    muestra_senyal (0, " ");
    
    fprintf(f_salida, "</tr>\n");
    
    
    /*** Mas Señales ***/
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
    fprintf(f_salida, "<td width=75 bgcolor=\"white\">&nbsp</td>\n");
    
    muestra_senyal (0, " ");
    muestra_senyal (MEMaID, "MEMaID");
    muestra_senyal (MEMaEXalu_i, "MEMaEXalu_i");
    muestra_senyal (0, " ");
    muestra_senyal (0, " ");
    
    fprintf(f_salida, "</tr>\n");
    
    
    /*** Mas Señales ***/
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
    fprintf(f_salida, "<td width=75 bgcolor=\"white\">&nbsp</td>\n");
    
    muestra_senyal (0, " ");
    muestra_senyal (0, " ");
    muestra_senyal (MEMaEXcomp, "MEMaEXcomp");
    muestra_senyal (0, " ");
    muestra_senyal (0, " ");
    
    fprintf(f_salida, "</tr>\n");
    
    
    /*** Mas Señales ***/
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
    fprintf(f_salida, "<td width=75 bgcolor=\"white\">&nbsp</td>\n");
    
    muestra_senyal (0, " ");
    muestra_senyal (WBaID, "WBaID");
    muestra_senyal (WBaEXalu_s, "WBaEXalu_s");
    muestra_senyal (WBaMEM, "WBaMEM ");
    muestra_senyal (0, " ");
    
    fprintf(f_salida, "</tr>\n");
    
    
    /*** Mas Se�ales ***/
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
    fprintf(f_salida, "<td width=75 bgcolor=\"white\">&nbsp</td>\n");
    
    muestra_senyal (0, " ");
    muestra_senyal (0, " ");
    muestra_senyal (WBaEXalu_i, "WBaEXalu_i");
    muestra_senyal (0, " ");
    muestra_senyal (0, " ");
    
    fprintf(f_salida, "</tr>\n");
    
    
    /*** Mas Señales ***/
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
    fprintf(f_salida, "<td width=75 bgcolor=\"white\">&nbsp</td>\n");
    
    muestra_senyal (0, " ");
    muestra_senyal (0, " ");
    muestra_senyal (WBaEXcomp, "WBaEXcomp");
    muestra_senyal (0, " ");
    muestra_senyal (0, " ");
    
    fprintf(f_salida, "</tr>\n");
    
    
    
    /*** Mas Señales ***/
    
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL);
    fprintf(f_salida, "<td width=75 bgcolor=\"white\">&nbsp</td>\n");
    
    muestra_senyal (IFnop, "IFnop");
    muestra_senyal (IDnop, "IDnop ");
    muestra_senyal (EXnop, "EXnop");
    muestra_senyal (MEMnop, "MEMnop");
    muestra_senyal (0, " ");
    
    fprintf(f_salida, "</tr>\n");
    
    fprintf(f_salida, "</table>\n\n");
    
} /* end imprime_senyales */


/***************************************************************
 *
 * Func: imprime_dit
 *
 * Desc: Imprime el diagrama instrucciones - tiempo 
 *
 **************************************************************/

static void imprime_dit (int num_instrucciones, char* archivo)
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    short		x, y;
    
    /*************************************/
    /*  Function body                    */
    /*************************************/
  
    /*** Cronograma de ejecución ***/
    
    fprintf(f_salida, "<!-- Diagrama instrucciones - tiempo  -->\n");
    fprintf(f_salida, "<table>\n");
    
    fprintf(f_salida, "<tr bgcolor=\"%s\" align=\"center\">\n", BG_HEADER);
    fprintf(f_salida, "  <td width=\"150\">Instruc.</td>\n");
    for (x= 0; x< MAX(MAX_CICLOS_INIC, maxima_columna_visible); x++)
//        fprintf(f_salida, "  <td width=\"25\"><a href=\"estado%03ld.html\">%ld</a></td>\n",
//                primer_ciclo + x, primer_ciclo + x);
        fprintf(f_salida, "  <td width=\"25\"><a href=\"%s%03ld.html\">%ld</a></td>\n",
                archivo, primer_ciclo + x, primer_ciclo + x);

        // fprintf(f_salida, "  <td width=\"25\">%ld</td>\n", x+primer_ciclo);
    fprintf(f_salida, "</tr>\n");
    
    for (y= 0; y< num_instrucciones; y++) {
        if (y % 2 == 0)
    		fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_VAL1);
        else
            fprintf(f_salida, "<tr bgcolor=\"%s\" align=\"center\">\n", BG_VAL2);
        
        if (!strlen(crono[y].inst))
            if (y % 2 == 0)
                fprintf(f_salida,
                        "  <td bgcolor=\"%s\" >&nbsp;</td>\n", BG_DIT1);
            else
                fprintf(f_salida,
                        "  <td bgcolor=\"%s\">&nbsp;</td>\n", BG_DIT2);
            else
                if (y % 2 == 0)
                    fprintf(f_salida,
                            "  <td align=\"left\" bgcolor=\"%s\">%s</td>\n", BG_DIT1, 
                            crono[y].inst);
                else
                    fprintf(f_salida,
                            "  <td align=\"left\" bgcolor=\"%s\">%s</td>\n", BG_DIT2,
                            crono[y].inst);
        
        for (x= 0; x< MAX(MAX_CICLOS_INIC, maxima_columna_visible); x++) {
            fprintf(f_salida, "  <td align=\"center\">");
            
            if (strlen(crono[y].fase[x]))
                fprintf(f_salida, "%s", crono[y].fase[x]);
            else
                fprintf(f_salida, "&nbsp;");
            
            fprintf(f_salida, "</td>\n");
        } /* endfor */
        fprintf(f_salida, "</tr>\n");
    } /* endfor */
    
    fprintf(f_salida, "</table><br>\n\n");
}

/***************************************************************
 *
 * Func: asigna
 *
 * Desc: Asigna un valor a un punto
 *
 **************************************************************/

/*
static void asigna (coord_t* punto, int x, int y)
{
    (*punto).x = x;
    (*punto).y = y;
}
*/

/***************************************************************
 *
 * Func: escribe
 *
 * Desc: Escribe un texto en el dibujo
 *
 **************************************************************/

static void escribe (int x, int y, char* texto, char* tcolor, int tsize)
{
   	fprintf(f_salida, "<text x=\"%d\" y=\"%d\"\n     style=\"fill:%s;stroke:%s;font-family:Arial;font-size:%dpx;\"\n     >%s</text>\n",x,y,tcolor,"null",tsize,texto);
}

/***************************************************************
 *
 * Func: genera_alu
 *
 * Desc: Dibuja el símbolo de la ALU
 *
 **************************************************************/

static void genera_alu (elem_2i1o_t* alu, int x1, int y1, int ancho, int alto, char* nombre, char* color, char* relleno)
{
    int x2;
    int y2;
    
    x2 = x1+ancho;
    y2 = y1+alto;
    
    (*alu).pos1.x = x1;
    (*alu).pos1.y = y1;
    (*alu).pos2.x = x2;
    (*alu).pos2.y = y2;
    (*alu).ancho = ancho;
    (*alu).alto = alto;
    (*alu).in1.x = x1;
    (*alu).in1.y = y1+alto/6;
    (*alu).in2.x = x1;
    (*alu).in2.y = y2-alto/6;
    (*alu).out1.x = x2;
    (*alu).out1.y = y1+alto/2;
    sprintf ((*alu).dibujo, "<g>\n  <polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d\" \n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", x1,y1,x1,y1+(int)(3*alto/8),x1+(int)(ancho/4),y1+(int) alto/2,x1,y1+(int) (5*alto/8),x1,y1+alto,x2,y2-(int) alto/4,x2,y1+(int) alto/4,x1,y1,relleno, color, trazo_grueso);
   	sprintf((*alu).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n</g>\n",(*alu).dibujo, x1+ancho/2+5, y1+alto/2, color, "none", nombre);
    fprintf (f_salida,"%s",(*alu).dibujo);
}

/***************************************************************
 *
 * Func: genera_mem
 *
 * Desc: Dibuja el símbolo de la memoria
 *
 **************************************************************/

static void genera_mem (elem_2i1o_t* mem, int x1, int y1, int ancho, int alto, char* nombre, char* in1, char* in2, char* out1, char* color, char* relleno)
{
    int x2;
    int y2;
    
    x2 = x1+ancho;
    y2 = y1+alto;
    
    (*mem).pos1.x = x1;
    (*mem).pos1.y = y1;
    (*mem).pos2.x = x2;
    (*mem).pos2.y = y2;
    (*mem).ancho = ancho;
    (*mem).alto = alto;
    (*mem).in1.x = x1;
    (*mem).in1.y = y1+alto/4;
    (*mem).in2.x = x1;
    (*mem).in2.y = y2-alto/4;
    (*mem).out1.x = x2;
    (*mem).out1.y = y1+alto/2;
    sprintf ((*mem).dibujo, "<g>\n  <polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", x1,y1,x1,y1+alto,x1+ancho,y1+alto,x1+ancho,y1,x1,y1,relleno,color,trazo_grueso);
    sprintf((*mem).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*mem).dibujo, x1+ancho/2, (int) y1+3*alto/8, color, "none", nombre);
    sprintf((*mem).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:start\"\n    >%s</text>\n",(*mem).dibujo, (*mem).in1.x+5, (*mem).in1.y, color, "none", in1);
    sprintf((*mem).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:start\"\n    >%s</text>\n",(*mem).dibujo, (*mem).in2.x+5, (*mem).in2.y, color, "none", in2);
    sprintf((*mem).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:end\"\n    >%s</text>\n</g>\n",(*mem).dibujo, (*mem).out1.x-5, (*mem).out1.y, color, "none", out1);
    fprintf (f_salida,"%s",(*mem).dibujo);
}

/***************************************************************
 *
 * Func: genera_elipse
 *
 * Desc: Dibuja una elipse
 *
 **************************************************************/

static void genera_elipse (elem_1i1o_t* mem, int x1, int y1, int ancho, int alto, char* nombre, char* in1, char* out1, char* tcolor, char* color, char* relleno)
{
    int x2;
    int y2;
    int cx, cy, rx, ry;
    
    x2 = x1+ancho;
    y2 = y1+alto;
    rx = ancho/2;
    ry = alto/2;
    cx = x1+rx;
    cy = y1+ry;
    
    (*mem).pos1.x = x1;
    (*mem).pos1.y = y1;
    (*mem).pos2.x = x1+ancho;
    (*mem).pos2.y = y1+alto;
    (*mem).ancho = ancho;
    (*mem).alto = alto;
    (*mem).in1.x = x1;
    (*mem).in1.y = y1+alto/2;
    (*mem).out1.x = x2;
    (*mem).out1.y = y1+alto/2;;
    sprintf ((*mem).dibujo, "<g>\n  <ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", cx,cy,rx,ry,relleno,color,trazo_grueso);
    sprintf((*mem).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*mem).dibujo, x1+ancho/2, (int) y1+alto/2, tcolor, "none", nombre);
    sprintf((*mem).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:start\"\n    >%s</text>\n",(*mem).dibujo, (*mem).in1.x, (*mem).in1.y, tcolor, "none", in1);
    sprintf((*mem).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:end\"\n    >%s</text>\n</g>\n",(*mem).dibujo, (*mem).out1.x, (*mem).out1.y, tcolor, "none", out1);
    fprintf (f_salida,"%s",(*mem).dibujo);
}


/***************************************************************
 *
 * Func: genera_latch
 *
 * Desc: Dibuja un registro de 1 entrada
 *
 **************************************************************/

static void genera_latch (elem_1i1o_t* reg, int x1, int y1, int ancho, int alto, char* nombre, char* in1, char* tcolor, char* color, char * relleno)
{
    int x2;
    int y2;
    
    x2 = x1+ancho;
    y2 = y1+alto;
    
    (*reg).pos1.x = x1;
    (*reg).pos1.y = y1;
    (*reg).pos2.x = x2;
    (*reg).pos2.y = y2;
    (*reg).ancho = ancho;
    (*reg).alto = alto;
    (*reg).in1.x = x1;
    (*reg).in1.y = y1+alto/2;
    (*reg).out1.x = x2;
    (*reg).out1.y = y1+alto/2;
    sprintf ((*reg).dibujo, "<g>\n  <polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", x1,y1,x1,y1+alto,x1+ancho,y1+alto,x1+ancho,y1,x1,y1,relleno, color, trazo_grueso);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, x1+ancho/2, y1-10, color, tcolor, nombre);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n</g>\n",(*reg).dibujo, (*reg).in1.x+ancho/2, (*reg).in1.y-2, tcolor, "none", in1);
    fprintf (f_salida,"%s",(*reg).dibujo);
}

/*
 void genera_latch2 (elem_2i2o_t* reg, int x1, int y1, int ancho, int alto, int i1_y, int i2_y)
 {
	int x2;
	int y2;
 
	x2 = x1+ancho;
	y2 = y1+alto;
 
	(*reg).pos1.x = x1;
	(*reg).pos1.y = y1;
	(*reg).pos2.x = x2;
	(*reg).pos2.y = y2;
	(*reg).ancho = ancho;
	(*reg).alto = alto;
	(*reg).in1.x = x1;
	(*reg).in1.y = i1_y;
	(*reg).out1.x = x2;
	(*reg).out1.y = i1_y;
	(*reg).in2.x = x1;
	(*reg).in2.y = i2_y;
	(*reg).out2.x = x2;
	(*reg).out2.y = i2_y;
 sprintf ((*reg).dibujo, "<polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:purple;stroke-width:3\"/>\n", x1,y1,x1,y1+alto,x1+ancho,y1+alto,x1+ancho,y1,x1,y1,"none");
	fprintf (f_salida,(*reg).dibujo);
 }
 
 
 void genera_latch3 (elem_3i3o_t* reg, int x1, int y1, int ancho, int alto, int i1_y, int i2_y, int i3_y)
 {
	int x2;
	int y2;
 
	x2 = x1+ancho;
	y2 = y1+alto;
 
	(*reg).pos1.x = x1;
	(*reg).pos1.y = y1;
	(*reg).pos2.x = x2;
	(*reg).pos2.y = y2;
	(*reg).ancho = ancho;
	(*reg).alto = alto;
	(*reg).in1.x = x1;
	(*reg).in1.y = i1_y;
	(*reg).out1.x = x2;
	(*reg).out1.y = i1_y;
	(*reg).in2.x = x1;
	(*reg).in2.y = i2_y;
	(*reg).out2.x = x2;
	(*reg).out2.y = i2_y;
	(*reg).in3.x = x1;
	(*reg).in3.y = i3_y;
	(*reg).out3.x = x2;
	(*reg).out3.y = i3_y;
 sprintf ((*reg).dibujo, "<polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:purple;stroke-width:3\"/>\n", x1,y1,x1,y1+alto,x1+ancho,y1+alto,x1+ancho,y1,x1,y1,"none");
	fprintf (f_salida,(*reg).dibujo);
 }
 
 void genera_latch4 (elem_4i4o_t* reg, int x1, int y1, int ancho, int alto, int i1_y, int i2_y, int i3_y, int i4_y, char* nombre, char* in1, char* in2, char* in3, char* in4, char* tcolor, char* color, char * relleno)
 {
	int x2;
	int y2;
 
	x2 = x1+ancho;
	y2 = y1+alto;
 
	(*reg).pos1.x = x1;
	(*reg).pos1.y = y1;
	(*reg).pos2.x = x2;
	(*reg).pos2.y = y2;
	(*reg).ancho = ancho;
	(*reg).alto = alto;
	(*reg).in1.x = x1;
	(*reg).in1.y = i1_y;
	(*reg).out1.x = x2;
	(*reg).out1.y = i1_y;
	(*reg).in2.x = x1;
	(*reg).in2.y = i2_y;
	(*reg).out2.x = x2;
	(*reg).out2.y = i2_y;
	(*reg).in3.x = x1;
	(*reg).in3.y = i3_y;
	(*reg).out3.x = x2;
	(*reg).out3.y = i3_y;
	(*reg).in4.x = x1;
	(*reg).in4.y = i4_y;
	(*reg).out4.x = x2;
	(*reg).out4.y = i4_y;
 sprintf ((*reg).dibujo, "<g>  <polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:3\"/>\n", x1,y1,x1,y1+alto,x1+ancho,y1+alto,x1+ancho,y1,x1,y1,relleno,color);
	sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, x1+ancho/2, y1-10, color, "none", nombre);
	sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, (*reg).in1.x+ancho/2, (*reg).in1.y-2, tcolor, "none", in1);
	sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, (*reg).in2.x+ancho/2, (*reg).in2.y-2, tcolor, "none", in2);
	sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, (*reg).in3.x+ancho/2, (*reg).in3.y-2, tcolor, "none", in3);
	sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n</g>\n",(*reg).dibujo, (*reg).in4.x+ancho/2, (*reg).in4.y-2, tcolor, "none", "B");
	fprintf (f_salida,(*reg).dibujo);
 }
 
 void genera_latch5 (elem_5i5o_t* reg, int x1, int y1, int ancho, int alto, int i1_y, int i2_y, int i3_y, int i4_y, int i5_y)
 {
	int x2;
	int y2;
 
	x2 = x1+ancho;
	y2 = y1+alto;
 
	(*reg).pos1.x = x1;
	(*reg).pos1.y = y1;
	(*reg).pos2.x = x2;
	(*reg).pos2.y = y2;
	(*reg).ancho = ancho;
	(*reg).alto = alto;
	(*reg).in1.x = x1;
	(*reg).in1.y = i1_y;
	(*reg).out1.x = x2;
	(*reg).out1.y = i1_y;
	(*reg).in2.x = x1;
	(*reg).in2.y = i2_y;
	(*reg).out2.x = x2;
	(*reg).out2.y = i2_y;
	(*reg).in3.x = x1;
	(*reg).in3.y = i3_y;
	(*reg).out3.x = x2;
	(*reg).out3.y = i3_y;
	(*reg).in4.x = x1;
	(*reg).in4.y = i4_y;
	(*reg).out4.x = x2;
	(*reg).out4.y = i4_y;
 (*reg).in5.x = x1;
	(*reg).in5.y = i5_y;
	(*reg).out5.x = x2;
	(*reg).out5.y = i5_y;
 sprintf ((*reg).dibujo, "<polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d\"\n     style=\"fill:%s;stroke:purple;stroke-width:3\"/>\n", x1,y1,x1,y1+alto,x1+ancho,y1+alto,x1+ancho,y1,x1,y1,"none");
	fprintf (f_salida,(*reg).dibujo);
 }
 */

/***************************************************************
 *
 * Func: genera_latch6
 *
 * Desc: Dibuja un registro de 6 entradas y 6 salidas
 *
 **************************************************************/

static void genera_latch6 (elem_6i6o_t* reg, int x1, int y1, int ancho, int alto, int i1_y, int i2_y, int i3_y, int i4_y, int i5_y, int i6_y, char* nombre, char* in1, char* in2, char* in3, char* in4, char* in5, char* in6, char* tcolor, char* color, char * relleno)
{
    int x2;
    int y2;
    
    x2 = x1+ancho;
    y2 = y1+alto;
    
    (*reg).pos1.x = x1;
    (*reg).pos1.y = y1;
    (*reg).pos2.x = x2;
    (*reg).pos2.y = y2;
    (*reg).ancho = ancho;
    (*reg).alto = alto;
    (*reg).in1.x = x1;
    (*reg).in1.y = i1_y;
    (*reg).out1.x = x2;
    (*reg).out1.y = i1_y;
    (*reg).in2.x = x1;
    (*reg).in2.y = i2_y;
    (*reg).out2.x = x2;
    (*reg).out2.y = i2_y;
    (*reg).in3.x = x1;
    (*reg).in3.y = i3_y;
    (*reg).out3.x = x2;
    (*reg).out3.y = i3_y;
    (*reg).in4.x = x1;
    (*reg).in4.y = i4_y;
    (*reg).out4.x = x2;
    (*reg).out4.y = i4_y;
    (*reg).in5.x = x1;
    (*reg).in5.y = i5_y;
    (*reg).out5.x = x2;
    (*reg).out5.y = i5_y;
    (*reg).in6.x = x1;
    (*reg).in6.y = i6_y;
    (*reg).out6.x = x2;
    (*reg).out6.y = i6_y;
    sprintf ((*reg).dibujo, "<g>  <polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", x1,y1,x1,y1+alto,x1+ancho,y1+alto,x1+ancho,y1,x1,y1,relleno,color,trazo_grueso);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, x1+ancho/2, y1-10, color, "none", nombre);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, (*reg).in1.x+ancho/2, (*reg).in1.y-2, tcolor, "none", in1);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, (*reg).in2.x+ancho/2, (*reg).in2.y-2, tcolor, "none", in2);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, (*reg).in3.x+ancho/2, (*reg).in3.y-2, tcolor, "none", in3);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, (*reg).in4.x+ancho/2, (*reg).in4.y-2, tcolor, "none", in4);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*reg).dibujo, (*reg).in5.x+ancho/2, (*reg).in5.y-2, tcolor, "none", in5);
    sprintf((*reg).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n</g>\n",(*reg).dibujo, (*reg).in6.x+ancho/2, (*reg).in6.y-2, tcolor, "none", in6);
    fprintf (f_salida,"%s",(*reg).dibujo);
}

/***************************************************************
 *
 * Func: genera_regs
 *
 * Desc: Dibuja un banco de registros
 *
 **************************************************************/


static void genera_regs (elem_4i2o_t* regs, int x1, int y1, int ancho, int alto, int in1, char* in1_col, int in2, char* in2_col, int in3, char* in3_col, char* color, char* relleno)
{
    int x2;
    int y2;
    
    x2 = x1+ancho;
    y2 = y1+alto;
    
    (*regs).pos1.x = x1;
    (*regs).pos1.y = y1;
    (*regs).pos2.x = x2;
    (*regs).pos2.y = y2;
    (*regs).ancho = ancho;
    (*regs).alto = alto;
    (*regs).in1.x = x1;
    (*regs).in1.y = y1+alto/6;
    (*regs).in2.x = x1;
    (*regs).in2.y = y1+2*alto/6;
    (*regs).in3.x = x1;
    (*regs).in3.y = y1+4*alto/6;
    (*regs).in4.x = x1;
    (*regs).in4.y = y1+5*alto/6;
    (*regs).out1.x = x2;
    (*regs).out1.y = y1+alto/4;
    (*regs).out2.x = x2;
    (*regs).out2.y = y1+3*alto/4;
    sprintf ((*regs).dibujo, "<g>\n  <polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", x1,y1,x1,y1+alto,x1+ancho,y1+alto,x1+ancho,y1,x1,y1,relleno,color,trazo_grueso);
    sprintf((*regs).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:middle\"\n    >%s</text>\n",(*regs).dibujo, x1+ancho/2, (int) y1+alto/2, color, "none", "Regs");
    sprintf((*regs).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:start\"\n    >R%d</text>\n",(*regs).dibujo, (*regs).in1.x+5, (*regs).in1.y, in1_col, "none", in1);
    sprintf((*regs).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:start\"\n    >R%d</text>\n",(*regs).dibujo, (*regs).in2.x+5, (*regs).in2.y, in2_col, "none", in2);
    sprintf((*regs).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:start\"\n    >R%d</text>\n",(*regs).dibujo, (*regs).in3.x+5, (*regs).in3.y, in3_col, "none", in3);
    sprintf((*regs).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:start\"\n    >%s</text>\n",(*regs).dibujo, (*regs).in4.x+5, (*regs).in4.y, color, "none", "W");
    sprintf((*regs).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:end\"\n    >%s</text>\n",(*regs).dibujo, (*regs).out1.x-5, (*regs).out1.y, color, "none", "A");
    sprintf((*regs).dibujo, "%s  <text x=\"%d\" y=\"%d\" \n    style=\"fill:%s;stroke:%s;font-family:Arial;font-size:14;text-anchor:end\"\n    >%s</text>\n</g>\n",(*regs).dibujo, (*regs).out1.x-5, (*regs).out2.y, color, "none", "B");
    fprintf (f_salida,"%s",(*regs).dibujo);
}


/***************************************************************
 *
 * Func: genera_mux2
 *
 * Desc: Dibuja un multiplexor de 2 entradas. 
 * Fijamos la posición de la salida
 * El in3 es el de contro
 *
 **************************************************************/

static void genera_mux2 (elem_3i1o_t* mux, int xi, int yo, int ancho, int alto, int selected, char* scolor, char* color, char* relleno)
{
    int x1, x2, y1, y2;
    int radio;
    int lado;
    int xsel, ysel;
    
    x1=xi;
    y1=yo-alto/2;
    //    x1 = xo;
    //    x1 = x2-ancho;
    
    //    y1 = yo-alto/2;
    //    y2 = y1+alto;
    x2= x1+ancho;
    y2= y1+alto;
    
    radio = ancho/2;
    lado = alto-ancho;
    
    (*mux).pos1.x = x1;
    (*mux).pos1.y = y1;
    (*mux).pos2.x = x2;
    (*mux).pos2.y = y2;
    (*mux).ancho = ancho;
    (*mux).alto = alto;
    (*mux).in1.x = x1;
    (*mux).in1.y = y1+radio;
    (*mux).in2.x = x1;
    (*mux).in2.y = y1+radio+lado;
    (*mux).in3.x = x1+radio;
    (*mux).in3.y = y1;
    (*mux).out1.x = x2;
    (*mux).out1.y = y1+radio+lado/2;
    
    if (selected==0) {
        xsel = (*mux).in1.x;
        ysel = (*mux).in1.y;
    } else {
        xsel = (*mux).in2.x;
        ysel = (*mux).in2.y;
    }
    sprintf ((*mux).dibujo, "<g>  <path d=\"M%d,%d\n     A%d,%d 0 0,1 %d,%d\n     L%d,%d\n     A%d,%d 0 0,1 %d,%d\n     L%d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", x1, y1+radio, radio, radio, x1+ancho, y1+radio, x1+ancho, y1+radio+lado, radio, radio, x1, y1+radio+lado, x1, y1+radio,relleno, color, trazo_grueso);
    sprintf((*mux).dibujo, "%s  <polyline points=\"%d,%d %d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n</g>\n", (*mux).dibujo, xsel,ysel,(*mux).out1.x, (*mux).out1.y, "none", scolor, trazo_resaltado);
    fprintf (f_salida,"%s",(*mux).dibujo);
}

/***************************************************************
 *
 * Func: genera_mux4
 *
 * Desc: Dibuja un multiplexor de 4 entradas // in5 es la de control
 *
 **************************************************************/

static void genera_mux4 (elem_5i1o_t* mux, int xi, int yo, int ancho, int alto, int selected, char* scolor, char* color, char* relleno)
{
    /*
     int x2;
     int y2;
     int radio;
     int lado;
     
     x2 = x1+ancho;
     y2 = y1+alto;
     radio = ancho/2;
     lado = (alto-ancho)/2;
     */
    int x1, x2, y1, y2;
    int radio;
    int lado;
    int xsel, ysel;
    
    x1=xi;
    y1=yo-alto/2;
    //    x1 = xo;
    //    x1 = x2-ancho;
    
    //    y1 = yo-alto/2;
    //    y2 = y1+alto;
    x2= x1+ancho;
    y2= y1+alto;
    
    radio = ancho/2;
    lado = alto-ancho;
    
    (*mux).pos1.x = x1;
    (*mux).pos1.y = y1;
    (*mux).pos2.x = x2;
    (*mux).pos2.y = y2;
    (*mux).ancho = ancho;
    (*mux).alto = alto;
    (*mux).in1.x = x1;
    (*mux).in1.y = y1+radio+lado/5;
    (*mux).in2.x = x1;
    (*mux).in2.y = y1+radio+2*lado/5;
    (*mux).in3.x = x1;
    (*mux).in3.y = y1+radio+3*lado/5;
    (*mux).in4.x = x1;
    (*mux).in4.y = y1+radio+4*lado/5;
    (*mux).in5.x = x1+radio;
    (*mux).in5.y = y1;
    (*mux).out1.x = x2;
    (*mux).out1.y = y1+radio+lado/2;
    
    if (selected==0) {
        xsel = (*mux).in1.x;
        ysel = (*mux).in1.y;
    } else if (selected==1) {
        xsel = (*mux).in2.x;
        ysel = (*mux).in2.y;
    } else if (selected==2) {
        xsel = (*mux).in3.x;
        ysel = (*mux).in3.y;
    } else {
        xsel = (*mux).in4.x;
        ysel = (*mux).in4.y;
    }
    sprintf ((*mux).dibujo, "<g>  <path d=\"M%d,%d\n     A%d,%d 0 0,1 %d,%d\n     L%d,%d\n     A%d,%d 0 0,1 %d,%d\n     L%d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", x1, y1+radio, radio, radio, x1+ancho, y1+radio, x1+ancho, y1+radio+lado, radio, radio, x1, y1+radio+lado, x1, y1+radio,relleno, color,trazo_grueso);
    sprintf((*mux).dibujo, "%s  <polyline points=\"%d,%d %d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n</g>\n", (*mux).dibujo, xsel,ysel,(*mux).out1.x, (*mux).out1.y, "none", scolor, trazo_resaltado);
    fprintf (f_salida,"%s",(*mux).dibujo);
    
    /*
     sprintf ((*mux).dibujo, "<path d=\"M%d,%d\n     A%d,%d 0 0,1 %d,%d\n     L%d,%d\n     A%d,%d 0 0,1 %d,%d\n     L%d,%d\"\n     style=\"fill:%s;stroke:purple;stroke-width:1\"/>\n", x1, y1+radio, radio, radio, x1+ancho, y1+radio, x1+ancho, y1+alto, radio, radio, x1, y1+alto, x1, y1+radio,"none");
     fprintf (f_salida,(*mux).dibujo); */
}

/***************************************************************
 *
 * Func: conecta
 *
 * Desc: Dibuja la conexión entre dos puntos
 *
 **************************************************************/

static void conecta (coord_t punto1, coord_t punto2, char* color)
{
    int x_medio;
    x_medio = punto1.x+(punto2.x-punto1.x)/2;
    
    fprintf (f_salida, "<polyline points=\"%d,%d %d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", punto1.x,punto1.y,x_medio,punto1.y,x_medio,punto2.y, punto2.x, punto2.y, "none", color, trazo_fino) ;
}

/***************************************************************
 *
 * Func: conecta_p
 *
 * Desc: Dibuja la conexi�n entre dos puntos
 *
 **************************************************************/

/*
static void conecta_p (coord_t punto1, coord_t punto2, int percent,  char* color)
{
    int ancho;
    int alto;
    
    ancho = punto2.x-punto1.x;
    alto = punto2.y-punto1.x;
    
    fprintf (f_salida, "<polyline points=\"%d,%d %d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", punto1.x,punto1.y,punto1.x+(int) ancho*percent/100,punto1.y,punto1.x+(int) ancho*percent/100,punto2.y, punto2.x, punto2.y,"none", color, trazo_fino) ;
}
*/

/***************************************************************
 *
 * Func: conecta_int
 *
 * Desc: Dibuja la conexi�n entre dos puntos
 *
 **************************************************************/

/*
static void conecta_int (coord_t punto1, coord_t punto2, int desp_xmedio, char* color)
{
    int x_medio;
    
    x_medio = punto1.x+desp_xmedio;
    
    fprintf (f_salida, "<polyline points=\"%d,%d %d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", punto1.x,punto1.y,x_medio,punto1.y,x_medio,punto2.y, punto2.x, punto2.y,"none", color, trazo_fino) ;
}
*/

/***************************************************************
 *
 * Func: conecta_p1_dx1_dy_dx2_p2
 *
 * Desc: Dibuja la conexi�n entre dos puntos p1 y p2: p1 -> rel_x, rel_y, rel_x -> p2
 *
 **************************************************************/

/*
static void conecta_p1_dx1_dy_dx2_p2 (coord_t punto1, coord_t punto2, int desp_xmedio1, int desp_ymedio, int desp_xmedio2, char* color)
{
    int x_medio1;
    int x_medio2;
    int y_medio1;
    
    x_medio1 = punto1.x+desp_xmedio1;
    x_medio2 = punto2.x+desp_xmedio2;
    y_medio1 = punto1.y+desp_ymedio;
    
    fprintf (f_salida, "<polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", punto1.x,punto1.y,x_medio1,punto1.y,x_medio1,y_medio1,x_medio2,y_medio1,x_medio2, punto2.y ,punto2.x, punto2.y,"none", color, trazo_fino) ;
}
*/

/***************************************************************
 *
 * Func: conecta_p1_dx1_y_dx2_p2
 *
 * Desc: Dibuja la conexi�n entre dos puntos p1 y p2: p1 -> rel_x, abs_y, rel_x -> p2
 *
 **************************************************************/

static void conecta_p1_dx1_y_dx2_p2 (coord_t punto1, coord_t punto2, int desp_xmedio1, int y_medio1, int desp_xmedio2, char* color)
{
    int x_medio1;
    int x_medio2;
    //    int y_medio1;
    
    x_medio1 = punto1.x+desp_xmedio1;
    x_medio2 = punto2.x+desp_xmedio2;
    //    y_medio1 = punto1.y+desp_ymedio;
    
    fprintf (f_salida, "<polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d\"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", punto1.x,punto1.y,x_medio1,punto1.y,x_medio1,y_medio1,x_medio2,y_medio1,x_medio2, punto2.y ,punto2.x, punto2.y,"none", color, trazo_fino) ;
}

/***************************************************************
 *
 * Func: conecta_x
 *
 * Desc: Dibuja la conexi�n entre dos puntos p1 y p2 moviendo en x
 *
 **************************************************************/

/*
static void conecta_x (coord_t punto1, coord_t punto2, char* color)
{
    fprintf (f_salida, "<polyline points=\"%d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", punto1.x,punto1.y,punto2.x,punto1.y,punto2.x, punto2.y,"none", color, trazo_fino) ;
}
*/

/***************************************************************
 *
 * Func: conecta_y
 *
 * Desc: Dibuja la conexi�n entre dos puntos p1 y p2, moviendo en y
 *
 **************************************************************/

/*
static void conecta_y (coord_t punto1, coord_t punto2, char* color)
{
    fprintf (f_salida, "<polyline points=\"%d,%d %d,%d %d,%d \"\n     style=\"fill:%s;stroke:%s;stroke-width:%f\"/>\n", punto1.x,punto1.y,punto1.x,punto2.y, punto2.x, punto2.y,"none", color, trazo_fino) ;
}
*/



/***************************************************************
 *
 * Func: dibuja_datapath
 *
 * Desc: Dibuja el datapath. Necesita que este abierto f_salida
 *
 **************************************************************/

static void dibuja_datapath ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    char		aux[128];
    elem_1i1o_t		RegPC, zero_id, zero, ext;
    
    elem_6i6o_t     RegIF_ID, RegID_EX, RegEX_M, RegM_WB;
    elem_2i1o_t		alu1, alu2, alu3, mem_instr, mem_datos;
    elem_4i2o_t		regs;
    elem_5i1o_t		mux4_alu_s, mux4_alu_i, mux3_zero, mux3_zero_id;
    elem_3i1o_t     mux_rdst, mux2_alu_s, mux2_alu_i, mux_wb, mux2_W_ex, mux2_W_mem, mux_pc;
    
    muxctrl_t       muxctrl; // para los MUX
    
    char col_IF[20], col_ID[20], col_EX[20], col_M[20], col_WB[20];
    
    /*
     char *	registro=
     "<symbol id=\"registro\">\n"
     "    <polygon points=\"0,0 20,0 20,60 0,60\" />\n"
     "</symbol>\n";
     
     char *	registro_intermedio=
     "<symbol id=\"registro_intermedio\">\n"
     "    <polygon points=\"0,0 20,0 20,200 0,200\" />\n"
     "</symbol>\n";
     
     char *	bancoreg=
     "<symbol id=\"bancoreg\">\n"
     "    <polygon points=\"0,0 40,0 40,80 0,80\" />\n"
     "</symbol>\n";
     
     char *	memoria=
     "<symbol id=\"memoria\">\n"
     "    <polygon points=\"0,0 40,0 40,80 0,80\" />\n"
     "</symbol>\n";
     
     char *	alu=
     "<symbol id=\"alu\">\n"
     "    <polyline points=\"0,0 0,40 10,50 0,60 0,100 40,80 40,30 0,0\" />\n"
     "</symbol>\n";
     
     
     char *	triangulo=
     "<symbol id=\"triangulo\">\n"
     "    <polyline points=\"10,2  60,2  35,52  10,2\""
     "    style=\"stroke:#006600; fill: #33cc33;\"/>\n"
     "</symbol>\n";
     */
    
    
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    
    /*** Datapath ***/
    
    // Colores
    color_instruccion(col_IF, PC);
    color_instruccion(col_ID, IF_ID.iPC);
    color_instruccion(col_EX, ID_EX.iPC);
    color_instruccion(col_M, EX_MEM.iPC);
    color_instruccion(col_WB, MEM_WB.iPC);
    
    
    /*
     sprintf(col_IF, "red");
     sprintf(col_ID, "blue");
     sprintf(col_EX,"green");
     sprintf(col_M, "magenta");
     sprintf(col_WB,"brown");
     */
    
    fprintf(f_salida, "<!-- Datapath en SVG -->\n");
    fprintf(f_salida, "<svg style='width: 100%%' viewbox=\"0 0 1100 650\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" shape-rendering=\"geometricPrecision\" >\n");
    //    fprintf(f_salida, "<svg width=\"800\" viewbox=\"0 0 1100 650\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" shape-rendering=\"geometricPrecision\" >\n");
    //    fprintf(f_salida, "<svg width=\"1100\" height=\"650\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" shape-rendering=\"geometricPrecision\" >\n");
    fprintf(f_salida, "<symbol id=\"datapath\"> width=\"1100\" height=\"650\" \n");
    
    imprime_instruccion(aux, PC);
    escribe(PC_x+4*sep1x,eje_y_texto, aux, col_IF, 18);
    imprime_instruccion(aux, IF_ID.iPC);
    escribe(IFID_x+10*sep1x,eje_y_texto,aux,col_ID,18);
    imprime_instruccion(aux, ID_EX.iPC);
    escribe(IDEX_x+8*sep1x,eje_y_texto,aux,col_EX,18);
    imprime_instruccion(aux, EX_MEM.iPC);
    escribe(EXM_x+8*sep1x,eje_y_texto,aux,col_M,18);
    imprime_instruccion(aux, MEM_WB.iPC);
    escribe(MWB_x+2*sep1x,eje_y_texto,aux,col_WB,18);
    
    
    /* Etapa IF **/
    genera_latch (&RegPC, PC_x, PC_y, reg_ancho, PC_alto, "", "PC", "black", "black", "lightgray" );
    genera_mem (&mem_instr, mem_instr_x, mem_instr_y, mem_ancho, mem_alto, "Mem Instr", "Dir", "", "Inst", "black", "lightgray");
    conecta (RegPC.out1, mem_instr.in1, col_IF);
    genera_alu (&alu1, alu1_x, alu1_y, aluPC_ancho, aluPC_alto, "+", "black", "lightgray");
    escribe (alu1.in1.x-20, alu1.in1.y, "4", "black", 14);
    conecta (RegPC.out1, alu1.in2, col_IF);
    
    // mux PC
    muxctrl.ctrl = (SaltoEfectivo ? 0 : 1);
    if (solucion_riesgos_control==ds1) {
        if (SaltoEfectivo) {
            sprintf(muxctrl.color, "%s", col_ID);
        } else {
            sprintf(muxctrl.color, "%s", col_IF);
        }
    } else if (solucion_riesgos_control==ds2) {
        if (SaltoEfectivo) {
            sprintf(muxctrl.color, "%s", col_EX);
        } else {
            sprintf(muxctrl.color, "%s", col_IF);
        }
    } else {
        if (SaltoEfectivo) {
            sprintf(muxctrl.color, "%s", col_M);
        } else {
            sprintf(muxctrl.color, "%s", col_IF);
        }
    }
    genera_mux2 (&mux_pc, muxpc_x, muxpc_y, mux2_ancho, mux2_alto, muxctrl.ctrl, muxctrl.color, "black", "lightgray");
    
    conecta_p1_dx1_y_dx2_p2 (alu1.out1, mux_pc.in2,sep1x,mux_pc.in2.y,-sep1x, col_IF);
    
    genera_latch6 (&RegIF_ID, IFID_x, IFID_y, reg_ancho, reg_alto, alu1.pos2.y-2*sep1y, mem_instr.out1.y, 0, 0, 0, 0, "IF_ID", "npc", "IR", "", "", "", "", "red", "gray", "lightgray");
    
    conecta_p1_dx1_y_dx2_p2 (alu1.out1, RegIF_ID.in1, sep1x, RegIF_ID.in1.y, 0, col_IF);
    conecta (mem_instr.out1, RegIF_ID.in2, col_IF);
    conecta_p1_dx1_y_dx2_p2 (mux_pc.out1, RegPC.in1,sep1x,alu1.pos2.y+(RegPC.pos1.y-alu1.pos2.y)/2,-sep1x, col_IF);
    
    /* Etapa ID **/
    genera_regs (&regs, regs_x, regs_y, regs_ancho, regs_alto, IF_ID.IR.Rfuente1, col_ID, IF_ID.IR.Rfuente2, col_ID ,MEM_WB.IR.Rdestino, col_WB, "black", "lightgray");
    genera_elipse (&ext, ext_x, ext_y,  elipse_ancho,elipse_alto, "Ext Signo", "", "", "black", "black", "lightgray");
	// Control
    //genera_elipse (&ctrl, control_x, control_y, elipse_ancho,elipse_alto, "Control", "", "", "black", "black", "lightgray");
    
    conecta_p1_dx1_y_dx2_p2 (RegIF_ID.out2, regs.in1, sep1x, regs.in1.y, 0, col_ID);
    conecta_p1_dx1_y_dx2_p2 (RegIF_ID.out2, regs.in2, sep1x, regs.in2.y, 0, col_ID);
    conecta_p1_dx1_y_dx2_p2 (RegIF_ID.out2, ext.in1, sep1x, ext.in1.y, 0, col_ID);
	// Control
    // conecta_p1_dx1_y_dx2_p2 (RegIF_ID.out2, ctrl.in1, sep1x, ctrl.in1.y, 0, col_ID);
    
    if (solucion_riesgos_control != ds1) {
        genera_latch6 (&RegID_EX, IDEX_x, IDEX_y, reg_ancho, reg_alto, 0, RegIF_ID.out1.y, regs.out1.y, regs.out2.y, ext.out1.y, ext.pos2.y+3*sep1y,  "ID_EX", "", "npc", "A", "B", "Imm", "IR",  "red", "gray", "lightgray");
    } else {
        genera_latch6 (&RegID_EX, IDEX_x, IDEX_y, reg_ancho, reg_alto, 0, RegIF_ID.out1.y, regs.out1.y, regs.out2.y, ext.out1.y, ext.pos2.y+3*sep1y,  "ID_EX", "", "", "A", "B", "Imm", "IR",  "red", "gray", "lightgray");
    }
    
    // mux Rdst
    muxctrl.ctrl = (IF_ID.IR.tipo==FormatoR ? 0 : 1);
    genera_mux2 (&mux_rdst, muxid_x, muxid_y, mux2_ancho, mux2_alto, muxctrl.ctrl, col_ID, "black", "lightgray");
    conecta_p1_dx1_y_dx2_p2 (RegIF_ID.out2, mux_rdst.in2, sep1x, mux_rdst.in2.y, 0, col_ID);
    conecta_p1_dx1_y_dx2_p2 (RegIF_ID.out2, mux_rdst.in1, sep1x, mux_rdst.in1.y, 0, col_ID);
    
    conecta (regs.out1, RegID_EX.in3, col_ID);
    conecta (regs.out2, RegID_EX.in4, col_ID);
    conecta (ext.out1, RegID_EX.in5, col_ID);
	// Control
    // conecta (ctrl.out1, RegID_EX.in1, col_ID);
    conecta (mux_rdst.out1, RegID_EX.in6, col_ID);
    
    // Si ds1
    if (solucion_riesgos_control == ds1) {
        genera_latch (&zero_id, zeroid_x, zeroid_y, zero_ancho, zero_alto, "", "zero","red", "black", "lightgray" );
        genera_alu (&alu3, aluid_x, aluid_y, aluPC_ancho, aluPC_alto, "+", "black", "lightgray");
        conecta_p1_dx1_y_dx2_p2 (ext.out1, alu3.in2, sep1x, ext.pos1.y-sep1y, -sep1x, col_ID);
        conecta_p1_dx1_y_dx2_p2 (RegIF_ID.out1, alu3.in1, 2*sep1x, alu3.in1.y, 0, col_ID);
        conecta_p1_dx1_y_dx2_p2 (zero_id.out1, mux_pc.in3, sep1x, RegIF_ID.pos1.y-3*sep1y, 0, col_ID);
        conecta_p1_dx1_y_dx2_p2 (alu3.out1, mux_pc.in1, sep1x, RegIF_ID.pos1.y-4*sep1y, -sep1x, col_ID);
        
        // Si no hay cortocircuitos
        if (solucion_riesgos_datos != cortocircuito) {
            conecta_p1_dx1_y_dx2_p2 (regs.out1, zero_id.in1, sep1x, zero_id.pos2.y+(regs.pos1.y-zero_id.pos2.y)/2, -sep1x, col_ID);
        }
        if (solucion_riesgos_datos == cortocircuito) {
            // mux ZERO en ID
            if (WBaID) {
                muxctrl.ctrl = 1;
                sprintf(muxctrl.color, "%s", col_WB);
            } else if (MEMaID) {
                muxctrl.ctrl = 0;
                sprintf(muxctrl.color, "%s", col_M);
            } else {
                muxctrl.ctrl = 2;
                sprintf(muxctrl.color, "%s", col_ID);
            }
            genera_mux4 (&mux3_zero_id, muxzeroid_x, zero_id.out1.y, mux4_ancho, mux4_alto, muxctrl.ctrl, muxctrl.color, "black", "lightgray");
            conecta (mux3_zero_id.out1, zero_id.in1, col_ID);
            conecta_p1_dx1_y_dx2_p2 (regs.out1, mux3_zero_id.in3, sep1x, mux3_zero_id.pos2.y+(regs.pos1.y-mux3_zero_id.pos2.y)/2, -sep1x, col_ID);
        }
    }
    
    if (solucion_riesgos_control != ds1) {
        conecta (RegIF_ID.out1, RegID_EX.in2, col_ID);
    }
    
    
    /* Etapa EX **/
    genera_alu (&alu2, alu_x, alu_y, alu_ancho, alu_alto, "ALU", "black", "lightgray");
    
    // Si ds1
    if (solucion_riesgos_control == ds1) {
        genera_latch6 (&RegEX_M, EXM_x, EXM_y, reg_ancho, reg_alto, RegID_EX.out1.y, zero.out1.y, alu2.out1.y, alu2.pos2.y+5*sep1y, RegID_EX.out6.y, 0, "EX_M", "", "", "ALUout", "B", "IR", "", "red", "gray", "lightgray");
        
    }
    
    
    // Si ds2
    if (solucion_riesgos_control == ds2) {
        genera_latch6 (&RegEX_M, EXM_x, EXM_y, reg_ancho, reg_alto, RegID_EX.out1.y, zero.out1.y, alu2.out1.y, alu2.pos2.y+5*sep1y, RegID_EX.out6.y, 0, "EX_M", "", "", "ALUout", "B", "IR", "", "red", "gray", "lightgray");
        genera_latch (&zero, zero_x, zero_y, zero_ancho, zero_alto, "", "zero","red", "black", "lightgray" );
        conecta_p1_dx1_y_dx2_p2 (zero.out1, mux_pc.in3, sep1x, RegID_EX.pos1.y-3*sep1y, 0, col_EX);
        conecta_p1_dx1_y_dx2_p2 (alu2.out1, mux_pc.in1, sep1x, RegID_EX.pos1.y-4*sep1y, -sep1x, col_EX);
        
    }
    
    // Si pnt o ds3
    if ((solucion_riesgos_control == parada) || (solucion_riesgos_control == pnt) || (solucion_riesgos_control == ds3))  {
        genera_latch (&zero, zero_x, zero_y, zero_ancho, zero_alto, "", "zero","red", "black", "lightgray" );
        genera_latch6 (&RegEX_M, EXM_x, EXM_y, reg_ancho, reg_alto, RegID_EX.out1.y, zero.out1.y, alu2.out1.y, alu2.pos2.y+5*sep1y, RegID_EX.out6.y, 0, "EX_M", "", "cond", "ALUout", "B", "IR", "", "red", "gray", "lightgray");
        conecta (zero.out1, RegEX_M.in2, col_EX);
        
    }
    
    
    // Si no hay cortocircuitos
    if (solucion_riesgos_datos != cortocircuito) {
        if (solucion_riesgos_control != ds1) {
            // mux ALUs
            if ((ID_EX.IR.codop==OP_BNEZ) || (ID_EX.IR.codop==OP_BEQZ)) {
                muxctrl.ctrl = 0;
            } else {
                muxctrl.ctrl = 1;
            }
            genera_mux2 (&mux2_alu_s, IDEX_x+6*sep1x+mux2_ancho, alu2.in1.y, mux2_ancho, mux2_alto, muxctrl.ctrl, col_EX, "black", "lightgray");
            conecta (mux2_alu_s.out1, alu2.in1, col_EX);
            conecta_p1_dx1_y_dx2_p2 (RegID_EX.out3, mux2_alu_s.in2, sep1x, mux2_alu_s.in2.y, 0, col_EX);
            // conexion del npc
            conecta_p1_dx1_y_dx2_p2 (RegID_EX.out2, mux2_alu_s.in1, 2*sep1x, mux2_alu_s.in1.y, 0, col_EX);
            conecta_p1_dx1_y_dx2_p2 (RegID_EX.out3, zero.in1, sep1x, zero.in1.y, 0, col_EX);
        } else { // Si ds1, no hay mux superior
            // conexion de A
            conecta_p1_dx1_y_dx2_p2 (RegID_EX.out3, alu2.in1, sep1x, alu2.in1.y, 0, col_EX);
        }
        
        // mux ALUi
        muxctrl.ctrl = (ID_EX.IR.tipo==FormatoR ? 0 : 1);
        genera_mux2 (&mux2_alu_i, IDEX_x+6*sep1x+mux2_ancho, alu2.in2.y, mux2_ancho, mux2_alto, muxctrl.ctrl, col_EX, "black", "lightgray");
        conecta (mux2_alu_i.out1, alu2.in2, col_EX);
        conecta_p1_dx1_y_dx2_p2 (RegID_EX.out4, mux2_alu_i.in1, sep1x, mux2_alu_i.in1.y, 0, col_EX);
        conecta_p1_dx1_y_dx2_p2 (RegID_EX.out5, mux2_alu_i.in2, 2*sep1x, mux2_alu_i.in2.y, 0, col_EX);
        // conexion de B hacia EX/M
        conecta_p1_dx1_y_dx2_p2 (RegID_EX.out4, RegEX_M.in4, sep1x, RegEX_M.in4.y, 0, col_EX);
    }
    
    // Si hay cortocircuitos
    if (solucion_riesgos_datos == cortocircuito) {
        // mux ALUs
        if (WBaEXalu_s) {
            muxctrl.ctrl = 2;
            sprintf(muxctrl.color, "%s", col_WB);
        } else if (MEMaEXalu_s) {
            muxctrl.ctrl = 1;
            sprintf(muxctrl.color, "%s", col_M);
        } else if ((ID_EX.IR.codop == OP_BNEZ) || (ID_EX.IR.codop == OP_BEQZ)) {
            if (solucion_riesgos_control != ds1) {
                muxctrl.ctrl = 0;
                sprintf(muxctrl.color, "%s", col_EX);
            } else {
                muxctrl.ctrl = 3;
                sprintf(muxctrl.color, "%s", col_EX);
            }
        } else {
            muxctrl.ctrl = 3;
            sprintf(muxctrl.color, "%s", col_EX);
        }
        genera_mux4 (&mux4_alu_s, IDEX_x+6*sep1x+mux4_ancho, alu2.in1.y, mux4_ancho, mux4_alto, muxctrl.ctrl, muxctrl.color, "black", "lightgray");
        
        // mux ALUi
        if (WBaEXalu_i) {
            muxctrl.ctrl = 2;
            sprintf(muxctrl.color, "%s", col_WB);
        } else if (MEMaEXalu_i) {
            muxctrl.ctrl = 1;
            sprintf(muxctrl.color, "%s", col_M);
        } else if (ID_EX.IR.tipo==FormatoR) {
            muxctrl.ctrl = 0;
            sprintf(muxctrl.color, "%s", col_EX);
        } else {
            if (solucion_riesgos_control != ds1) {
                muxctrl.ctrl = 3;
                sprintf(muxctrl.color, "%s", col_EX);
            } else {
                muxctrl.ctrl = 0;
                sprintf(muxctrl.color, "%s", col_EX);
            }
        }
        genera_mux4 (&mux4_alu_i, IDEX_x+6*sep1x+mux4_ancho, alu2.in2.y, mux4_ancho, mux4_alto, muxctrl.ctrl, muxctrl.color, "black", "lightgray");
        
        // mux MEM en EX
        muxctrl.ctrl = (WBaEXmem ? 1 : 0);
        if (WBaEXmem) {
            sprintf(muxctrl.color, "%s", col_WB);
        } else {
            sprintf(muxctrl.color, "%s", col_EX);
        }
        genera_mux2 (&mux2_W_ex, IDEX_x+6*sep1x+mux4_ancho, RegEX_M.in4.y, mux2_ancho, mux2_alto, muxctrl.ctrl, muxctrl.color, "black", "lightgray");
        
        conecta (mux4_alu_s.out1, alu2.in1, col_EX);
        conecta (mux4_alu_i.out1, alu2.in2, col_EX);
        conecta_p1_dx1_y_dx2_p2 (RegID_EX.out3, mux4_alu_s.in4, sep1x, mux4_alu_s.in4.y, 0, col_EX);
        conecta_p1_dx1_y_dx2_p2 (RegID_EX.out4, mux4_alu_i.in1, sep1x, mux4_alu_i.in1.y, 0, col_EX);
        
        if (solucion_riesgos_control != ds1) {
            conecta_p1_dx1_y_dx2_p2 (RegID_EX.out2, mux4_alu_s.in1, 2*sep1x, mux4_alu_s.in1.y, 0, col_EX);
        }
        
        conecta_p1_dx1_y_dx2_p2 (RegID_EX.out5, mux4_alu_i.in4, 2*sep1x, mux4_alu_i.in4.y, 0, col_EX);
        conecta_p1_dx1_y_dx2_p2 (RegID_EX.out4, mux2_W_ex.in1, sep1x, mux2_W_ex.in1.y, 0, col_EX);
        conecta (mux2_W_ex.out1, RegEX_M.in4, col_EX);
        
        // mux ZERO en EX
        if (solucion_riesgos_control != ds1) {
            if (WBaEXcomp) {
                muxctrl.ctrl = 2;
                sprintf(muxctrl.color, "%s", col_WB);
            } else if (MEMaEXcomp) {
                muxctrl.ctrl = 1;
                sprintf(muxctrl.color, "%s", col_M);
            } else {
                muxctrl.ctrl = 0;
                sprintf(muxctrl.color, "%s", col_EX);
            }
            genera_mux4 (&mux3_zero, IDEX_x+6*sep1x+mux4_ancho, zero.in1.y, mux4_ancho, mux4_alto, muxctrl.ctrl, muxctrl.color, "black", "lightgray");
            conecta_p1_dx1_y_dx2_p2 (RegID_EX.out3, mux3_zero.in1, sep1x, mux3_zero.in1.y, 0, col_EX);
            conecta (mux3_zero.out1, zero.in1, col_EX);
        }
    }
    
    
    conecta (alu2.out1, RegEX_M.in3, col_EX);
    
	// Control
	// conecta (RegID_EX.out1, RegEX_M.in1, col_EX);
    conecta (RegID_EX.out6, RegEX_M.in5, col_EX);
    
    /* Etapa MEM **/
    genera_mem (&mem_datos, mem_datos_x, mem_datos_y, mem_ancho, mem_alto, "Mem\nDatos", "Dir", "W", "Dato", "black", "lightgray");
    conecta_p1_dx1_y_dx2_p2 (RegEX_M.out3, mem_datos.in1, 3*sep1x, mem_datos.in1.y, 0, col_M);
    genera_latch6 (&RegM_WB, MWB_x, MWB_y, reg_ancho, reg_alto, RegEX_M.out1.y, mem_datos.pos1.y-3*sep1y, mem_datos.out1.y, RegEX_M.out5.y, 0, 0, "MEM_WB", "", "ALUout", "LMD", "IR", "", "", "red", "gray", "lightgray");
    conecta (mem_datos.out1, RegM_WB.in3, col_M);
    conecta_p1_dx1_y_dx2_p2 (RegEX_M.out3, RegM_WB.in2, 3*sep1x, RegM_WB.in2.y, 0, col_M);
    // Control conecta_p1_dx1_y_dx2_p2 (RegEX_M.out1, RegM_WB.in1, 3*sep1x, RegM_WB.in1.y, 0, col_M);
	// Control    conecta (RegEX_M.out1, RegM_WB.in1, col_M);
    conecta (RegEX_M.out5, RegM_WB.in4, col_M);
    
    // Si no hay cortocircuitos
    if (solucion_riesgos_datos != cortocircuito) {
        conecta (RegEX_M.out4, mem_datos.in2, col_M);
    }
    if (solucion_riesgos_datos == cortocircuito) {
        
        // mux MEM en MEM
        muxctrl.ctrl = (WBaMEM ? 1 : 0);
        if (WBaMEM) {
            sprintf(muxctrl.color, "%s", col_WB);
        } else {
            sprintf(muxctrl.color, "%s", col_M);
        }
        genera_mux2 (&mux2_W_mem, muxmem_x, RegEX_M.in4.y, mux2_ancho, mux2_alto, muxctrl.ctrl, muxctrl.color, "black", "lightgray");
        
        conecta (mux2_W_mem.out1,mem_datos.in2, col_M);
        conecta (RegEX_M.out4, mux2_W_mem.in1, col_M);
        conecta_p1_dx1_y_dx2_p2 (RegEX_M.out3, mux4_alu_s.in2, 3*sep1x, RegEX_M.pos1.y-4*sep1y, -2*sep1x, col_M);
        conecta_p1_dx1_y_dx2_p2 (RegEX_M.out3, mux4_alu_i.in2, 3*sep1x, RegEX_M.pos1.y-4*sep1y, -2*sep1x, col_M);
        if (solucion_riesgos_control == ds1) {
            conecta_p1_dx1_y_dx2_p2 (RegEX_M.out3, mux3_zero_id.in1, 3*sep1x, RegEX_M.pos1.y-5*sep1y, -sep1x, col_M);
        }
        if (solucion_riesgos_control != ds1) {
            conecta_p1_dx1_y_dx2_p2 (RegEX_M.out3, mux3_zero.in2, 3*sep1x, RegEX_M.pos1.y-4*sep1y, -2*sep1x, col_M);
        }
    }
    
    // Si parada, pnt o ds3
    if ((solucion_riesgos_control == parada) || (solucion_riesgos_control == pnt) || (solucion_riesgos_control == ds3))  {
        conecta_p1_dx1_y_dx2_p2 (RegEX_M.out2, mux_pc.in3, sep1x, RegEX_M.pos1.y-3*sep1y, 0, col_M);
        conecta_p1_dx1_y_dx2_p2 (RegEX_M.out3, mux_pc.in1, 3*sep1x, RegEX_M.pos1.y-4*sep1y, -sep1x, col_M);
    }
    
    
    /* Etapa WB **/
    
    // mux WB
    muxctrl.ctrl = (MEM_WB.IR.codop!=OP_LW ? 0 : 1);
    genera_mux2 (&mux_wb, muxwb_x, mem_datos.out1.y-mux2_alto/2, mux2_ancho, mux2_alto, muxctrl.ctrl, col_WB, "black", "lightgray");
    
    conecta (RegM_WB.out2, mux_wb.in1, col_WB);
    conecta (RegM_WB.out3, mux_wb.in2, col_WB);
    conecta_p1_dx1_y_dx2_p2 (RegM_WB.out4, regs.in3, sep1x, mux_rdst.pos2.y+sep1y, -sep1x, col_WB);
    conecta_p1_dx1_y_dx2_p2 (mux_wb.out1, regs.in4, sep1x, mux_rdst.pos2.y+2*sep1y, -2*sep1x, col_WB);
    
    if (solucion_riesgos_datos == cortocircuito) {
        conecta_p1_dx1_y_dx2_p2 (mux_wb.out1, mux4_alu_i.in3, sep1x, mux_rdst.pos2.y+2*sep1y, -sep1x, col_WB);
        conecta_p1_dx1_y_dx2_p2 (mux_wb.out1, mux4_alu_s.in3, sep1x, mux_rdst.pos2.y+2*sep1y, -sep1x, col_WB);
        conecta_p1_dx1_y_dx2_p2 (mux_wb.out1, mux2_W_mem.in2, sep1x, mux_rdst.pos2.y+2*sep1y, -sep1x, col_WB);
        conecta_p1_dx1_y_dx2_p2 (mux_wb.out1, mux2_W_ex.in2, sep1x, mux_rdst.pos2.y+2*sep1y, -sep1x, col_WB);
        /* Corto WB a ID. No es necesario si lectura y escritura simult�neas */
        /*
         if (solucion_riesgos_control == ds1) {
         conecta_p1_dx1_y_dx2_p2 (mux_wb.out1, mux3_zero_id.in2, sep1x, RegEX_M.pos1.y-6*sep1y, -2*sep1x, col_WB);
         }
         */
        if (solucion_riesgos_control != ds1) {
            conecta_p1_dx1_y_dx2_p2 (mux_wb.out1, mux3_zero.in3, sep1x, mux_rdst.pos2.y+2*sep1y, -sep1x, col_WB);
        }
    }
    
    fprintf(f_salida, "</symbol> \n");
    
    
    fprintf(f_salida, "<use xlink:href=\"#datapath\"\n");
    //	fprintf(f_salida, "transform=\"translate(0) scale(0.77)\"/>\n");
    
    fprintf(f_salida, "</svg>\n\n");
    
    
} /* end dibuja_datapath */



/***** Funciones Exportables **********************************/

/***************************************************************
 *
 * Func: imprime_instruccion
 *
 * Parametros:
 *	instruc  (char *) ;
 *
 * Descripcipn:
 *   Imprime la intrucción localizada en el PC sobre la
 *   cadena de caracteres 'instruc'
 *
 **************************************************************/

void imprime_instruccion (
                          char *	instruc,
                          word	PC
                          )
{
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    if (PC == -1) {
        strcpy(instruc, "-nop-");
        return ;
    } /* endif */
    
    switch (MI[PC].codop) {
        case OP_NOP:
            sprintf(instruc, "nop");
            break;
        case OP_TRAP:
            sprintf(instruc, "trap %d",
                    MI[PC].inmediato);
            break;
        case OP_LW:
            sprintf(instruc, "ld r%d,%d(r%d)",
                    MI[PC].Rdestino,
                    MI[PC].inmediato,
                    MI[PC].Rfuente1
                    );
            break;
        case OP_SW:
            sprintf(instruc, "sd r%d,%d(r%d)",
                    MI[PC].Rfuente2,
                    MI[PC].inmediato,
                    MI[PC].Rfuente1
                    );
            break;
        case OP_ADD:
            sprintf(instruc, "dadd r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SUB:
            sprintf(instruc, "dsub r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_AND:
            sprintf(instruc, "and r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_OR:
            sprintf(instruc, "or r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_XOR:
            sprintf(instruc, "xor r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SRA:
            sprintf(instruc, "srav r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SRL:
            sprintf(instruc, "srlv r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SLL:
            sprintf(instruc, "sllv r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SEQ:
            sprintf(instruc, "seq r%d,r%d,r%d",
    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SNE:
            sprintf(instruc, "sne r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SGT:
            sprintf(instruc, "sgt r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SGE:
            sprintf(instruc, "sge r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SLT:
            sprintf(instruc, "slt r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_SLE:
            sprintf(instruc, "sle r%d,r%d,r%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2
                    );
            break;
        case OP_ADDI:
            sprintf(instruc, "dadd r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SUBI:
            sprintf(instruc, "dsub r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_ANDI:
            sprintf(instruc, "and r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_ORI:
            sprintf(instruc, "or r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_XORI:
            sprintf(instruc, "xor r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SRAI:
            sprintf(instruc, "sra r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SRLI:
            sprintf(instruc, "srl r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SLLI:
            sprintf(instruc, "sll r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SEQI:
            sprintf(instruc, "seq r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SNEI:
            sprintf(instruc, "sne r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SGTI:
            sprintf(instruc, "sgt r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SGEI:
            sprintf(instruc, "sge r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SLTI:
            sprintf(instruc, "slt r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_SLEI:
            sprintf(instruc, "sle r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].inmediato
                    );
            break;
        case OP_BNEZ:
            sprintf(instruc, "bnez r%d,%d",
                    MI[PC].Rfuente1,
                    MI[PC].inmediato);
            break;
        case OP_BEQZ:
            sprintf(instruc, "beqz r%d,%d",
                    MI[PC].Rfuente1,
                    MI[PC].inmediato);
            break;
        default:
            sprintf(instruc, "Inst desconocida r%d,r%d,r%d,#%d",
                    MI[PC].Rdestino,
                    MI[PC].Rfuente1,
                    MI[PC].Rfuente2,
                    MI[PC].inmediato
                    );
            break;
    } /* endswitch */
    
} /* end imprime_instruccion */

/***************************************************************
 *
 * Func: init_instruc
 *
 * Description: 
 *   Inicializa una instrucci�n en el cronograma
 *
 **************************************************************/

void init_instruc (
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
 * Func: actualiza_crono
 *
 * Description: 
 *   Actualiza el cronograma con el estado de las fases
 *
 **************************************************************/

void actualiza_crono ( )
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    char		aux[128];
    char        fase[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    sprintf(fase,"%s","IF");
    if (IFstall) {
        sprintf(fase,"<i>%s</i>","if");
    }
    if (IFnop) {
        sprintf(aux,"%s",fase);
        //sprintf(fase,"<b>%s</b>",aux);
        sprintf(fase,"<font color=\"red\">%s</font>", aux);
    }
    muestra_fase(fase, orden);

    if (IF_ID.orden != -1) {
        sprintf(fase,"%s","ID");
        if (IDstall) {
            sprintf(fase,"<i>%s</i>","id");
        }
        if (IDnop) {
            sprintf(aux,"%s",fase);
            //sprintf(fase,"<b>%s</b>",aux);
            sprintf(fase,"<font color=\"red\">%s</font>", aux);
        }
        muestra_fase(fase, IF_ID.orden);
    }

    if (ID_EX.orden != -1) {
        sprintf(fase,"%s","EX");
        if (EXstall) {
            sprintf(fase,"<i>%s</i>","ex");
        }
        if (EXnop) {
            sprintf(aux,"%s",fase);
            //sprintf(fase,"<b>%s</b>",aux);
            sprintf(fase,"<font color=\"red\">%s</font>", aux);
        }
        muestra_fase(fase, ID_EX.orden);
    }

    if (EX_MEM.orden != -1)
        muestra_fase("ME", EX_MEM.orden);

    if (MEM_WB.orden != -1)
        muestra_fase("WB", MEM_WB.orden);

} /* end actualiza_crono */




/***************************************************************
 *
 * Func: imprime_estado
 *
 * Desc: Imprime el estado del procesador
 *
 **************************************************************/

void imprime_estado ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char		aux[128];


    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "estado%03ld.html", Ciclo);
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */

    /*** HTML INTRO ***/

	imprime_intro ("Estado");

	
    /* Barra de navegación */
	imprime_nav2 ("estado");
	fprintf(f_salida, "<br><br>\n");

    /*** Etapas ***/
    imprime_etapas();
    fprintf(f_salida, "<br>\n");

    /*** Señales ***/

    imprime_senyales();
    fprintf(f_salida, "<br>\n");
    

    /**** Banco de registros enteros */
    imprime_int_regs();
    fprintf(f_salida, "<br>\n");


    /*** Memoria de datos ***/
    imprime_Dmem();
    fprintf(f_salida, "<br>\n");


  
    fprintf(f_salida, "<address>Arquitectura e Ingeniería de Computadores\n");
    fprintf(f_salida, "</address>\n");
    fprintf(f_salida, "</body></html>\n"); 

    fclose(f_salida);

} /* end imprime_estado */




/***************************************************************
 *
 * Func: imprime_estado_datapath 
 *
 * Desc: Imprime el estado de las estructuras de coma flotante
 *
 **************************************************************/

void imprime_estado_datapath ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    char		aux[128];
    
     
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    sprintf(aux, "estado%03ld.html", Ciclo);
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */
    
    /*** HTML INTRO ***/
    
	imprime_intro ("Estado");
	
	/*** Navegación ***/
	
	imprime_nav2 ("estado");
    fprintf(f_salida, "<br><br>\n");
    
    /*** Muestra ruta de datos ***/
    
    dibuja_datapath();
    fprintf(f_salida, "<br>\n");
    
    
    fprintf(f_salida, "<a name='regs'></a>\n");

    /*** Etapas ***/
    
    imprime_etapas ();
    fprintf(f_salida, "<br>\n");
    
    
    /* Banco de registros enteros */

    imprime_int_regs ();
    fprintf(f_salida, "<br>\n");
        
        
    /*** Contenido de la memoria de datos ***/
    
    imprime_Dmem ();
    fprintf(f_salida, "<br>\n");
    
	/*** Final ***/
	imprime_footer ();

    fclose(f_salida);
    
} /* end imprime_estado_datapath */


/***************************************************************
 *
 * Func: imprime_crono
 *
 * Desc: Imprime el cronograma de ejecuci�n
 *
 **************************************************************/

void imprime_crono ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    char		aux[128];
    
    
    /*************************************/
    /*  Function body                    */
    /*************************************/
    
    sprintf(aux, "crono%03ld.html", Ciclo);
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */
    
    /*** HTML INTRO ***/
    
    imprime_intro ("Cronograma");
    
    /* Barra de navegación */
	imprime_nav2 ("crono");
	fprintf(f_salida, "<br><br>\n");

    
    /*** Cronograma de ejecución ***/
    
    imprime_dit (MAX_INSTRUC, "crono");
	fprintf(f_salida, "<br>\n");
        
    fprintf(f_salida, "<a name='ruta'></a>\n");
    dibuja_datapath();
	fprintf(f_salida, "<br>\n");

    
	/*** Final ***/
	imprime_footer ();
	
    
    fclose(f_salida);
    
} /* end imprime_crono */


/***************************************************************
 *
 * Func: imprime_css
 *
 * Desc: Imprime todo 
 *
 **************************************************************/

void imprime_css ()
{

    /*************************************/
    /*  Local variables                  */
    /*************************************/
    
    char		aux[128];
    
    
    /*************************************/
    /*  Function body                    */
    /*************************************/

    /* Para pantallas pequeñas, caben 10 instrucciones en el dit */
    
    sprintf(aux, "result%03ld.html", Ciclo);
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */
    
    /*** HTML INTRO ***/
    
    imprime_w3css ("Resultados");
    
    /* Barra de navegación */
	imprime_nav2_css ("result");
	fprintf(f_salida, "<br><br>\n");

    fprintf(f_salida, "<div class=\"w3-row \">\n");
    fprintf(f_salida, "<div class=\"w3-col w3-container l8\">\n"); 

    /*** Cronograma de ejecución ***/
    
    imprime_dit (MAX_INSTRUC, "result");
	fprintf(f_salida, "<br>\n");
        
    /*** Datapath ***/
    dibuja_datapath();
	fprintf(f_salida, "<br>\n");
    fprintf(f_salida, "</div>\n");
    
    fprintf(f_salida, "<div class=\"w3-col w3-container l2\">\n");

    /*** Registros ***/
	imprime_int_regs_col ();
    fprintf(f_salida, "</div>\n");


    fprintf(f_salida, "<div class=\"w3-col w3-container l2\">\n"); 

    /*** Memoria ***/
	imprime_Dmem_col ();

    fprintf(f_salida, "</div>\n");
    fprintf(f_salida, "</div>\n");
    
	fprintf(f_salida, "<br>\n");

	/*** Final ***/
	imprime_footer_css ();
	
    
    fclose(f_salida);
    
} /* end imprime_css */



/***************************************************************
 *
 * Func: imprime_inicio
 *
 * Desc: Imprime la configuracion
 *
 **************************************************************/

void imprime_inicio ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char		aux[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "index.html");
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */

    /*** HTML INTRO ***/
    
    imprime_intro ("Estado inicial");

	/*** Navegación ***/

	imprime_nav1();
    fprintf(f_salida, "<br><br>\n");
    
    

    /*** Configuración ***/
    
    imprime_conf ();
    fprintf(f_salida, "<br>\n");
    


    /*** Memorias ***/

    fprintf(f_salida, "<table>\n"); 

 
    fprintf(f_salida, "<tr valign=\"top\">\n");
    fprintf(f_salida, "<td>\n");

    /*** Contenido de la memoria de datos ***/
	
	imprime_Dmem_col ();
		
    fprintf(f_salida, "</td>\n");
    fprintf(f_salida, "<td>\n");
	
    /*** Contenido de la memoria de instrucciones ***/
	
	imprime_Imem_col ();

    fprintf(f_salida, "</td>\n");
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table><br>\n"); 

    
 	/*** Final ***/
	imprime_footer ();
	

    fclose(f_salida);

} /* end imprime_inicio */


/***************************************************************
 *
 * Func: imprime_inicio
 *
 * Desc: Imprime la configuracion
 *
 **************************************************************/

void imprime_inicio_css ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/

    char		aux[128];

    /*************************************/
    /*  Function body                    */
    /*************************************/

    sprintf(aux, "index.html");
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */

    /*** HTML INTRO ***/
    
    imprime_w3css ("Inicio");
    
    /* Barra de navegación */
	imprime_nav1_css ();
	fprintf(f_salida, "<br><br>\n");


       
    /*** Configuración ***/
    fprintf(f_salida, "<div class=\"w3-row w3-container\">\n"); 
    imprime_conf ();
	fprintf(f_salida, "<br>\n");
	fprintf(f_salida, "</div>\n\n");




    /*** Memorias ***/
    fprintf(f_salida, "<div class=\"w3-row \">\n");
 
    /*** Contenido de la memoria de datos ***/
    fprintf(f_salida, "<div class=\"w3-col w3-container w3-quarter \">\n"); 
	
	imprime_Dmem_col ();
		
    fprintf(f_salida, "</div>\n");
	
    /*** Contenido de la memoria de instrucciones ***/
    fprintf(f_salida, "<div class=\"w3-col w3-container w3-quarter \">\n"); 
	
	imprime_Imem_col ();

    fprintf(f_salida, "</div>\n");
    fprintf(f_salida, "</div>\n");
	fprintf(f_salida, "<br>\n\n");

    
	/*** Final ***/
	imprime_footer_css ();
	

    fclose(f_salida);

} /* end imprime_inicio */


/***************************************************************
 *
 * Func: imprime_final
 *
 * Desc: Imprime la configuracion y resultados finales
 *
 **************************************************************/

void imprime_final ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
	
    char		aux[128];
	
    /*************************************/
    /*  Function body                    */
    /*************************************/
	
    sprintf(aux, "final.html");
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */
	
    /*** HTML INTRO ***/
    
    imprime_intro ("Resultados");

	/*** Navegación ***/

	imprime_nav1();
    fprintf(f_salida, "<br><br>\n");
	
    /*** Resultados de la ejecucion ***/
    fprintf(f_salida, "<table>\n");
    fprintf(f_salida, "<tr>\n");
 	fprintf(f_salida, "<td colspan=\"3\" bgcolor=\"%s\" align=\"center\">Resultados</td>\n", BG_HEADER);
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_DIR1);
    fprintf(f_salida, "  <td>Ciclos</td>\n");
    fprintf(f_salida, "  <td>Instrucciones&nbsp;&nbsp;</td>\n");
    fprintf(f_salida, "  <td>CPI</td>\n");
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_DIR2);
    fprintf(f_salida, "  <td>%ld</td>\n", Ciclo);
    fprintf(f_salida, "  <td>%ld</td>\n", Instrucciones);
    fprintf(f_salida, "  <td>%1.2f</td>\n", (float) Ciclo/Instrucciones);
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table><br>\n");
    
    
    /*** Configuración ***/
    
    imprime_conf ();
    fprintf(f_salida, "<br>\n");

    
    /*** Bancos de registros ***/
    
    fprintf(f_salida, "<table>\n");
    
    /* Banco de registros enteros */
    
    imprime_int_regs ();
    fprintf(f_salida, "<br>\n");

	
    /*** Memorias ***/

    fprintf(f_salida, "<table>\n"); 

 
    fprintf(f_salida, "<tr valign=\"top\">\n");
    fprintf(f_salida, "<td>\n");

    /*** Contenido de la memoria de datos ***/
	
	imprime_Dmem_col ();
		
    fprintf(f_salida, "</td>\n");
    fprintf(f_salida, "<td>\n");
	
    /*** Contenido de la memoria de instrucciones ***/
	
	imprime_Imem_col ();

    fprintf(f_salida, "</td>\n");
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table><br>\n"); 

    
 	/*** Final ***/
	imprime_footer ();
	
	
    fclose(f_salida);
	
} /* end imprime_final */

/***************************************************************
 *
 * Func: imprime_final
 *
 * Desc: Imprime la configuracion y resultados finales
 *
 **************************************************************/

void imprime_final_css ()
{
    /*************************************/
    /*  Local variables                  */
    /*************************************/
	
    char		aux[128];
	
    /*************************************/
    /*  Function body                    */
    /*************************************/
	
    sprintf(aux, "final.html");
    f_salida= fopen(aux, "w");
    if (f_salida == NULL) {
        fprintf(stderr, "Error creando %s\n", aux);
        exit(1);
    } /* endif */
	
    /*** HTML INTRO ***/
    
    imprime_w3css ("Final");
    
    /* Barra de navegación */
	imprime_nav1_css ();
	fprintf(f_salida, "<br><br>\n");

    fprintf(f_salida, "<div class=\"w3-row w3-container\">\n");
    /*** Resultados de la ejecucion ***/
    
    fprintf(f_salida, "<table>\n");
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_DIT2);
    fprintf(f_salida, "  <td>Ciclos&nbsp;&nbsp;</td>\n");
    fprintf(f_salida, "  <td>Instrucciones&nbsp;&nbsp;</td>\n");
    fprintf(f_salida, "  <td>CPI&nbsp;&nbsp;</td>\n");
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "<tr bgcolor=\"%s\">\n",BG_DIT1);
    fprintf(f_salida, "  <td>%ld</td>\n", Ciclo);
    fprintf(f_salida, "  <td>%ld</td>\n", Instrucciones);
    fprintf(f_salida, "  <td>%1.2f</td>\n", (float) Ciclo/Instrucciones);
    fprintf(f_salida, "</tr>\n");
    fprintf(f_salida, "</table><br>\n");
    fprintf(f_salida, "</div>\n\n");

       
    /*** Configuración ***/
    fprintf(f_salida, "<div class=\"w3-row w3-container\">\n"); 
    imprime_conf ();
	fprintf(f_salida, "<br>\n");
	fprintf(f_salida, "</div>\n\n");

	
    
    fprintf(f_salida, "<div class=\"w3-row w3-container\">\n"); 

    
    /* Banco de registros enteros */
    
    fprintf(f_salida, "<div class=\"w3-col w3-quarter\">\n"); 
    imprime_int_regs_col ();
	fprintf(f_salida, "</div>\n\n");


    /*** Contenido de la memoria de datos ***/

    fprintf(f_salida, "<div class=\"w3-col w3-quarter\">\n"); 
    imprime_Dmem_col ();
    fprintf(f_salida, "</div>\n\n");
	
		
    /*** Contenido de la memoria de instrucciones ***/
	
    fprintf(f_salida, "<div class=\"w3-col w3-quarter\">\n"); 
	imprime_Imem_col ();
    fprintf(f_salida, "</div>\n\n");

    fprintf(f_salida, "</div>\n\n");
	
	fprintf(f_salida, "<br>\n");

	/*** Final ***/
	imprime_footer_css ();
	
	
    fclose(f_salida);
	
} /* end imprime_final */
