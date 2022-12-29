/*
 * DEV_Config.h
 *
 *  Created on: 29 déc. 2022
 *      Author: adumoulin
 */

/**
 * data
**/


#include <stdio.h>

#define DEBUG   1
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#if DEBUG
	#define Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
	#define Debug(__info,...)
#endif
