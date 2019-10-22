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
 * LOGGER
 *****************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdint.h>

/********* User defined Header Files *********/
#include "logger.h"

/********* Board specific Header Files *********/
#ifdef FB
	/*#include "board.h"
	#include "peripherals.h"
	#include "pin_mux.h"
	#include "clock_config.h"
	#include "MKL25Z4.h"*/
	#include "fsl_debug_console.h"
#endif

uint8_t flag = 0;	/* By default, logger is disabled */

/****************** Function to enable logger *******************/
void log_enable(void)
{
	flag = 1;	/* Logger enabled */

	#ifdef PC
		printf("\nLogger Enabled");
	#endif

	#ifdef FB
		PRINTF("Logger Enabled\n\r");
	#endif
}
/****************** Function to disable logger *******************/
void log_disable(void)
{
	flag = 0;	/* Logger disabled */

	#ifdef PC
		printf("\nLogger Disabled");
	#endif

	#ifdef FB
		PRINTF("\n\rLogger Disabled");
	#endif
}
/****************** Function to return the status of the logger *******************/
uint8_t log_status(void)
{
	if(flag == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#ifdef FB
	/****************** Function to output the data stored in an address location *******************/
	void log_data(uint32_t *ptr,uint8_t length)
	{
		uint8_t *temp = (uint8_t*)ptr;
		int8_t i;
		for(i = 0;i < length;i++)
		{
			PRINTF("Address: 0x%X \tData : 0x%X \n\r",&(temp[i]),temp[i]);
		}
	}
	/****************** Function to output a string *******************/
	void log_string(char *string)
	{
		PRINTF("%s",string);
	}
	/****************** Function to output a number *******************/
	void log_integer(uint32_t number)
	{
		PRINTF("%X",number);
	}

#endif

#ifdef PC
	/****************** Function to output the data stored in an address location *******************/
	void log_data(uint32_t *ptr,uint8_t length)
	{
		uint8_t *temp = (uint8_t*)ptr;
		int8_t i;
		for(i = 0;i < length;i++)
		{
			printf("\nAddress: 0x%X \tData : 0x%X",&(temp[i]),temp[i]);
		}
	}
	/****************** Function to output a string *******************/
	void log_string(char *string)
	{
		printf("%s",string);
	}
	/****************** Function to output a number *******************/
	void log_integer(uint32_t number)
	{
		printf("%X",number);
	}

#endif
