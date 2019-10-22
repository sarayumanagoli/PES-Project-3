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
 * PATTERN GENERATION AND VERIFICATION
 *****************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/********* User defined Header Files *********/
#include "pat_gen.h"
#include "get_address.h"
#include "logger.h"

/********* Memory Function prototype declarations *********/
uint32_t* get_address(uint32_t* base_addr, uint32_t* offset);

/********* Logger functions prototype declarations *********/
void log_string(char *string);
uint8_t log_status(void);
void log_integer(uint32_t number);

/********************** Pattern generation function definition ************************
 * The formula used for pattern generation is based on linear congruential generator
 * given as:
 *
 * 				X(n) = [a*[X(n-1)] + c]%m
 **************************************************************************************/
void gen_pattern(int8_t *pattern, size_t length, int8_t seed)
{
	int8_t i, a, c, m;
	a = 17;
	c = 42;
	m = 31;
	pattern[0] = seed;
	for(i=1;i<length;i++)
	{
	      pattern[i] = ((a*pattern[i-1]) + c)%m;
	}
}

/********* Pattern verification function definition *********/
uint32_t* verify_pattern(uint32_t* loc, size_t length, int8_t seed)
{
	int8_t pat[length];
	int8_t check = 0;
	uint32_t i;
	uint8_t* temp = (uint8_t*)loc;
	uint32_t* mismatch = (uint32_t*)malloc(length/4);
	gen_pattern(pat,length,seed);
	for(i=0;i<length;i++)
	{
		if(pat[i] != temp[i])
		{
			/******* Mismatch[] stores the addresses of locations where a mismatch if found ******/
			mismatch[i] = (uint32_t) get_address(loc,&i);
			if(log_status())
			{
				log_string("\n\rMismatch at 0x");
				log_integer(mismatch[i]);
			}
			check = 1;
		}
	}
	if(check == 0)
	{
	    free(mismatch);
		return NULL;
	}
	else
	{
	    return mismatch;
	}
}
