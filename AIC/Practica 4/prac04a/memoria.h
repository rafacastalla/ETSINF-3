/*********************************************************************
 * 
 * Departamento de Informática de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio Sáez (ssaez@disca.upv.es)
 * 
 * File: memoria.h
 *  
 * Date: 
 * 
 * Description: 
 *    Contiene las estructuras para la tabla de símbolos
 *
 *********************************************************************/

#ifndef memoria_H
#define memoria_H

/***** Includes ***********************************************/

#include "tipos.h"

/***** Macros *************************************************/

#define EN_MEMORIA(dir, segmento) ((dir) >= (segmento).inicio && (dir) < (segmento).final)

/***** Prototypes *********************************************/

#include "memoria.hi"


#endif /* end memoria.h*/
