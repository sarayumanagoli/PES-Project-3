/******************************************************************************
*                                                                             *
*                       PRINCIPLES OF EMBEDDED SOFTWARE                       *
*                   PROJECT 3 - Memory Functions and Tests                    *
*   Project By:GITANJALI SURESH (GISU9983) & SARAYU MANAGOLI (SAMA2321)       *
*                   Cross Platform IDE: MCUXpresso IDE v11                    *
*                   Compiler: MinGW/GNU gcc v8.2.0 (PC version)               *
*                       Cross-Compiler: ARM GCC (FB version)                  *
*                                                                             *
*******************************************************************************/
/*****************************************************************************
 * DISPLAY OF MEMORY CONTENTS
 *****************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdint.h>

/********* User defined Header Files *********/
#include "display_memory.h"

/********* Display function definition *********/
uint8_t* display_memory(uint32_t* loc, size_t length)
{
	uint8_t *disp;
	uint8_t *temp = (uint8_t *)loc;
	disp = temp;
	for(int i=0;i<length;i++)
	{
	    *(disp+i) = *(temp+i);
    }
    return disp;
}
