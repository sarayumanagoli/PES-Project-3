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
 * MEMORY FUNCTIONS
 *****************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/********* User defined Header Files *********/
#include "mem_func.h"
#include "pat_gen.h"
#include "logger.h"

/********* Error code definitions *********/
typedef enum mem_status
{
    SUCCESS,
    FAILED
} mem_status;

/********* Pattern functions prototype declarations *********/
void gen_pattern(int8_t* pattern, size_t length, int8_t seed);

/********* LED functions prototype declarations *********/
void log_string(char *string);
uint8_t log_status(void);

/********* Memory data write function definition *********/
mem_status write_memory(uint32_t* loc, uint8_t value)
{
	if(loc == NULL)
	{
		if(log_status())
		{
			log_string("\n\rMemory location unavailable.");
		}
		return FAILED;
	}
	uint8_t* temp = (uint8_t*)loc;
	*temp = value;
	return SUCCESS;
}

/********* Memory pattern write function definition *********/
mem_status write_pattern(uint32_t* loc, size_t length, int8_t seed)
{
	if(loc == NULL)
	{
		if(log_status())
		{
			log_string("\n\rMemory location unavailable.");
		}
		return FAILED;
	}
	int8_t pattern[length];
	int8_t i;
	gen_pattern(pattern,length,seed);
	uint8_t* temp = (uint8_t*)loc;
	for(i = 0;i < length;i++)
	{
		temp[i] = pattern[i];
	}
	if(i == length)
	{
		return SUCCESS;
	}
	else
	{
		return FAILED;
	}
}

/********* Memory inversion function definition *********/
mem_status invert_block(uint32_t* loc, size_t length)
{
	if(loc == NULL)
	{
		if(log_status())
		{
			log_string("\n\rMemory location unavailable.");
		}

		return FAILED;
	}
	int8_t i;
	uint8_t *temp = (uint8_t*)loc;
	for(i=0;i<length;i++)
	{
		temp[i] = temp[i]^(0xFF);
	}
	if(i == length)
	{
		return SUCCESS;
	}
	else
	{
		return FAILED;
	}
}
