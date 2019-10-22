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
 * ALLOCATION OF MEMORY
 *****************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/********* User defined Header Files *********/
#include "allocate_words.h"
#include "logger.h"

/********* Logger functions prototype declarations *********/
void log_string(char *string);
uint8_t log_status(void);

/********* LED functions prototype declarations *********/
void green_on(void);
void green_off(void);
void red_on(void);
void red_off(void);
void blue_on(void);
void blue_off(void);

/********* Memory allocation function definition *********/
uint32_t* allocate_words(size_t length)
{
	uint32_t* ptr;
	ptr = (uint32_t*)malloc(length);
	/************** Condition to check if memory allocation is successful ****************/
	if(ptr == NULL)
	{
		if(log_status())
		{
			log_string("\n\rMemory allocation unsuccessful!");
		}
		#ifdef FB
			blue_off();
			green_off();
			red_on();
		#endif
	}
	else
	{
		if(log_status())
		{
			log_string("\n\rMemory allocation successful!");
		}
	}
	return ptr;
}
