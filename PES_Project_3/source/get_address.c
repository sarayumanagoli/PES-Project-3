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
 * ADDRESS OF MEMORY
 *****************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdint.h>

/********* User defined Header Files *********/
#include "get_address.h"

/********* Address function definition *********/
uint32_t* get_address(uint32_t* base_addr, uint32_t* offset)
{
	uint8_t off = (*(uint8_t*)offset);	/* type casting to an 8 bit value to access byte values */
	uint8_t* temp = (uint8_t*)base_addr;
	return ((uint32_t*)&temp[off]);
}
