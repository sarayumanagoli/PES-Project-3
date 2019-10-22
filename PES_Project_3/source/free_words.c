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
 * FREEING ALLOCATED MEMORY
 *****************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/********* User defined Header Files *********/
#include "free_words.h"
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

/********* Memory freeing function definition *********/
void free_words(uint32_t *src)
{
	/************** Condition to check the availability of memory ****************/
	if(src == NULL)
	{
		if(log_status())
		{
			log_string("\n\rWarning: Trying to free unallocated memory!");
		}
		free(src);
		#ifdef FB
			blue_off();
			green_off();
			red_on();
		#endif
	}
	else
	{
		free(src);

		if(log_status())
		{
			log_string("\n\rAllocated memory has been freed.");
		}
	}
}
