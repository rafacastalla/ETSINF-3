
/**************************************************************************
 * 
 * Departamento de Inform‡tica de Sistema y Computadores (DISCA)
 * Universidad PolitŽcnica de Valencia.                         
 * 
 * Author: Sergio S‡ez (ssaez@disca.upv.es)
 *	   Pedro L—pez (plopez@gap.upv.es)
 * 
 * File: main.c
 *  
 * Description: 
 *    M—dulo principal del simulador
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
#include <getopt.h>

#include "main.h"

/*** Definiciones Externas *************************************************/

#include "tipos.h"
#include "instrucciones.h"
#include "presentacion-html.h"
#include "presentacion-txt.hi"
#include "mips.hi"

extern void ensamblador (FILE*);

/*** Variables Globales ****************************************************/

extern int pos_datos;

/*** Variables Locales *****************************************************/

//static instruccion_t	ultima_intruc;
//static word		ultimo_PC;

/*** Funciones Locales *****************************************************/


/***************************************************************
 *
 * Func: inicializa_mips
 *
 * Desc: Inicializa las estructuras del mips
 *
 **************************************************************/

static void inicializa_mips (  
    )

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int		i;
    instruccion_t instr;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /* Registros */

    PC = 0;

    for (i=0; i<TAM_REGISTROS; i++)
    {
        Rint[i].valor= 0;
    } /* endfor */

    /* Memoria de datos */

    for (i=0; i< TAM_MEMO_DATOS; i+= sizeof(word))
    {
        MD.mdword[dir_dword(i)]= 0;
    } /* endfor */

    /* Memoria de instrucciones */

    for (i=0; i<TAM_MEMO_INSTRUC; i++)
    {
        MI[i].codop= OP_TRAP;	/* Cuando el programa encuentre una
				   instruccion del tipo TRAP 0
				   terminará */
        MI[i].tipo= FormatoI;
        MI[i].Rdestino= 0;
        MI[i].Rfuente1= 0;
        MI[i].Rfuente2= 0;
        MI[i].inmediato= 0;
    } /* endfor */

    /* Registros intermedios */

    instr.codop= OP_NOP;
    instr.tipo= FormatoR;
    instr.Rdestino= 0;
    instr.Rfuente1= 0;
    instr.Rfuente2= 0;
    instr.inmediato= 0;

    IF_ID.IR = instr;
    IF_ID.NPC = 0;  
    IF_ID.iPC = -1;  
    IF_ID.orden = 0;  

    ID_EX.IR = instr;
    ID_EX.NPC = 0;
    ID_EX.Ra = 0;
    ID_EX.Rb = 0;
    ID_EX.Imm = 0;
    ID_EX.iPC = -1;  
    ID_EX.orden = -1;  

    EX_MEM.IR = instr;
    EX_MEM.ALUout = 0;
    EX_MEM.data = 0;
    EX_MEM.cond = NO;
    EX_MEM.iPC = -1;  
    EX_MEM.orden = -1;  

    MEM_WB.IR = instr;
    MEM_WB.ALUout = 0;
    MEM_WB.MEMout = 0;
    MEM_WB.iPC = -1;  
    MEM_WB.orden = -1;  
 
    IFstall = NO;
    IDstall = NO;
  
} /* end inicializa_mips */


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

static int ejecutar_codigo (  
    )

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int		RC;	/* Valor de retorno */

    boolean	final = NO;
    boolean OVF_HTML = NO;
    boolean OVF_TXT = NO;

/*  boolean	html = NO; */
  
    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    RC= 0;
  
    /*** Inicializacion del computador */

    Ciclo= 0;
    estat.instrucciones =0;
    // Instrucciones=0;
    orden= 1;

    if (salida == html)
    {
		if (w3css_flag)
        	imprime_inicio_css();
        else
			imprime_inicio();
    }

    if (salida == html_final)
    {
		if (w3css_flag)
        	imprime_inicio_css();
        else
			imprime_inicio();
    }

	

    /*** Bucle principal */

    while (!final)
    {
        /*** Enteros ******************************/

        /*** Fase: WB **************/

        final = fase_escritura ();

        /*** Fase: MEM **************/

        fase_memoria ();

        /*** Fase: EX *************/

        fase_ejecucion ();

        /*** Fase: ID **************/

        fase_decodificacion ();

        /*** Fase: IF ***********/

        fase_busqueda();
	
        /* Incrementa el número de ciclos ejecutados */

        Ciclo++;
        estat.ciclos++;
        
        if (Ciclo >= MAX_CICLOS_TOTAL) {
            fprintf(stderr, "ATENCION: Numero de ciclos %ld excesivo\n Ejecucion detenida\n", Ciclo);
        	final = SI;
        }


        if ((salida==html) && (Ciclo >= MAX_CICLOS_HTML) && !OVF_HTML) {
            fprintf(stderr, "ATENCION: Numero de ciclos %ld excesivo\n No se generan mas archivos html\n", Ciclo);
			OVF_HTML = SI;
        } ;
        
        
         if ((salida != html) && (Ciclo >= MAX_CICLOS_TXT) && !OVF_TXT) {
         fprintf(stderr, "ATENCION: Numero de ciclos %ld excesivo\n No se muestran mas ciclos\n", Ciclo);
         OVF_TXT = SI;
         } ;

        

        /*** Imprime el estado -- interfaz de texto  */
        if ((salida == res_ciclo)  && (!OVF_TXT)) {
            imprime_etapas_txt ();
            imprime_reg_txt ();
            imprime_memdatos_txt ();
        }	

        /*** Imprime el estado de los operadores, etc.  */
        
        if ((salida==html) && (!OVF_HTML))
        {
        	actualiza_crono ();
     		if (w3css_flag)
        		imprime_css ();
        	else {
            	imprime_estado ();
            	imprime_estado_datapath();
        		imprime_crono ();
            	//imprime_datapath ();
            }
        }

 
        impulso_reloj();


    } /* endwhile */

    if (salida == res_tiempo) {
        //        imprime_inicio_txt(;
        imprime_final_txt();
        //        imprime_reg_txt ();
        //        imprime_memdatos_txt ();
    }

    
    if (salida == res_final) {
        imprime_final_txt();
        imprime_reg_txt ();
        imprime_memdatos_txt ();
    }	

    if (salida == html) 
    {
     	if (w3css_flag)
     		imprime_final_css();
       	else 
       		imprime_final();
    }

    if (salida == html_final) 
    {
     	if (w3css_flag)
        	imprime_final_css();
		else
			imprime_final();
    }
 
    return (RC);

} /* end ejecutar_codigo */

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

int main (  
    int	argc,
    char*	argv[]
    )

{
    /*************************************/
    /*  Variables locales                */
    /*************************************/

    int		RC;	/* Valor de retorno */

    char *	uso=
    "%s [-n] [-s s.resultado] [-d r.datos] [-c r.control] -f fichero.s\n"
    //        "\tsalida    ciclo final html(*)\n"
    "\ts.resultado tiempo final ciclo html(*) html-final\n"
    "\ts.resultado tiempo final ciclo html(*) html-final\n"
    "\tr.datos     n:ninguno, p:parada(*), c:cortocircuito\n"
    "\tr.control   p:parada(*), t:p-n-taken, 3:ds=3, 2:ds=2, 1:ds=1\n"
    "\tfichero     nombre del fichero en ensamblador\n"
    "\t-n	       no borrar archivos html\n";

    boolean	hay_fichero = 0;
    boolean borrar_html = 1;
  
    FILE*		f_entrada= NULL;

    /*************************************/
    /*  Cuerpo función                   */
    /*************************************/

    /*** Lectura de parametros */

    solucion_riesgos_datos = parada;
    solucion_riesgos_control = stall;
    salida = html;
  
  
    /* Flag set by Ô--verboseÕ. */
   // static int w3css_flag=1;
    
    int c;
    
    while (1)
    {
        static struct option long_options[] =
        {
            /* These options set a flag. */
            {"no-w3css", no_argument, &w3css_flag, 0},
            /* These options don't set a flag.
             We distinguish them by their indices. */
            {"help",   no_argument, 0, '?'},
            {"no-borrar-html", no_argument, 0, 'n'},
            {"salida", required_argument, 0, 's'},
            {"rdatos", required_argument, 0, 'd'},
            {"rcontrol", required_argument, 0, 'c'},
            {"programa", required_argument, 0, 'f'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;
        
        c = getopt_long (argc, argv, "?s:d:c:f:n",
                         long_options, &option_index);
        
        /* Detect the end of the options. */
        if (c == -1)
            break;
        
        switch (c)
        {
            case '?':
                fprintf(stderr, uso, argv[0]);
                exit(1);
                break;
                
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;
                
            case 'c':
				if (strncmp(optarg,"p",1) == 0) {
                    solucion_riesgos_control = stall;
                } else if (strncmp(optarg,"t",1) == 0) {
                    solucion_riesgos_control = pnt;
                } else if (strncmp(optarg,"3",1) == 0) {
                    solucion_riesgos_control = ds3;
                } else if (strncmp(optarg,"2",1) == 0) {
                    solucion_riesgos_control = ds2;
                } else if (strncmp(optarg,"1",1) == 0) {
                    solucion_riesgos_control = ds1;
                } else {
                    fprintf(stderr, "Error en argumento %s %s\n", "-c",optarg);
                    fprintf(stderr, uso, argv[0]);
                    exit(1);
                }
                break;
                
            case 'd':
                if (strncmp(optarg,"n",1) == 0) {
                    solucion_riesgos_datos = ninguno;
                } else if (strncmp(optarg,"p",1) == 0) {
                    solucion_riesgos_datos = parada;
                } else if (strncmp(optarg,"c",1) == 0) {
                    solucion_riesgos_datos = cortocircuito;
                } else {
                    fprintf(stderr, "Error en argumento %s %s\n", "-d",optarg);
                    fprintf(stderr, uso, argv[0]);
                    exit(1);
                }
                break;
                
            case 'f':
                f_entrada= fopen(optarg, "r");
                sprintf(nombre_fich,"%s",optarg);
                hay_fichero = 1;
                if (f_entrada == NULL)
                {
                    fprintf(stderr, "Error abriendo fichero %s\n", nombre_fich);
                    fprintf(stderr, uso, argv[0]);
                    exit(1);
                }
                break;
                
                
                
            case 's':
                if (strncmp(optarg,"tiempo",6) == 0) {
                    salida = res_tiempo;
                } else if (strncmp(optarg,"ciclo",5) == 0) {
                    salida = res_ciclo;
                } else if (strncmp(optarg,"final",5) == 0) {
                    salida = res_final;
                } else if (strncmp(optarg,"html",10) == 0) {
                    salida = html;
                } else if (strncmp(optarg,"html-final",10) == 0) {
                    salida = html_final;
                } else {
                    fprintf(stderr, "Error en argumento %s %s\n", "-s", optarg);
                    fprintf(stderr, uso, argv[0]);
                    exit(1);
                }
                break;
                
            case 'n':
                borrar_html = 0;
            	break;
                
            default:
                abort ();
        }
    }
    
    /* Instead of reporting Ô--verboseÕ
     and Ô--briefÕ as they are encountered,
     we report the final status resulting from them. */
//    if (w3css_flag)
//        puts ("w3css flag is set");
    
    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        while (optind < argc)
            fprintf(stderr, "Error en argumento %s\n",argv[optind++]);
        fprintf(stderr, uso, argv[0]);
        exit(1);
    }
    

    if (!hay_fichero)
    {
        fprintf(stderr, "Falta fichero en ensamblador\n");
        fprintf(stderr, uso, argv[0]);
        exit(1);
    }

    if (borrar_html)
    {
    	system("rm *.html 2>/dev/null");
    }

    
    switch (salida) {
      case html:
             fprintf(stdout, "\nSalida html: Ciclo a ciclo");
             break;
      case html_final:
             fprintf(stdout, "\nSalida html: Resultados finales");
             break;
      case res_tiempo:
            fprintf(stdout, "\nSalida texto: Tiempo ejecucion");
            break;
      case res_ciclo:
             fprintf(stdout, "\nSalida texto: Ciclo a ciclo");
             break;
      case res_final :
             fprintf(stdout, "\nSalida texto: Resultados finales");
    };
 

    switch (solucion_riesgos_datos) {
      case ninguno:
             fprintf(stdout, "\nRiesgos de datos: Ninguno");
             break;
      case parada:
             fprintf(stdout, "\nRiesgos de datos: Ciclos de parada");
             break;
      case cortocircuito:   
             fprintf(stdout, "\nRiesgos de datos: Cortocircuito");
    };


    switch (solucion_riesgos_control) {
      case ds3:
             fprintf(stdout, "\nRiesgos de control: Salto retardado (DS=3)");
             break;
      case ds2:
             fprintf(stdout, "\nRiesgos de control: Salto retardado (DS=2)");
             break;
      case ds1:
             fprintf(stdout, "\nRiesgos de control: Salto retardado (DS=1)");
             break;
      case pnt:
             fprintf(stdout, "\nRiesgos de control: Predict-not-taken");
             break;
      case parada:   
             fprintf(stdout, "\nRiesgos de control: Ciclos de parada");
    };


    fprintf(stdout, "\n\n");
    
    /*** Inicializacion de estructuras */

    inicializa_mips ();

    /*** Carga el codigo en lenguaje ensamblador */

    ensamblador (f_entrada);

    /*** Llama al bucle principal */

    RC= ejecutar_codigo ();

    return (RC);

} /* end main */

