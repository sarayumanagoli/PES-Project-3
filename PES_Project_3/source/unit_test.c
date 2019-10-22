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
/***********************************************************************************
 * UNIT TESTING [1]
 ***********************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/********* User defined Header Files *********/
#include "allocate_words.h"
#include "free_words.h"
#include "pat_gen.h"
#include "mem_func.h"
#include "get_address.h"
#include "display_memory.h"
#include "logger.h"
#include "uCUnit.h"

/********* Error code definitions *********/
typedef enum mem_status
{
    SUCCESS,
    FAILED
} mem_status;

/********* Memory Function prototype declarations *********/
uint32_t* allocate_words(size_t length);
void free_words(uint32_t *src);
mem_status write_memory(uint32_t* loc, uint8_t value);
mem_status invert_block(uint32_t* loc, size_t length);
mem_status write_pattern(uint32_t* loc, size_t length, int8_t seed);
uint32_t* get_address(uint32_t* base_addr, uint32_t* offset);

/********* Pattern functions prototype declarations *********/
uint32_t* verify_pattern(uint32_t* loc, size_t length, int8_t seed);

/********* Logger functions prototype declarations *********/
void log_enable(void);
void log_disable(void);

/********* Unit Test function definition *********/
void unit_test(void)
{
		log_disable();
    	size_t length = 16;
    	int8_t seed = 5;
    	uint32_t *p;

    	/************ Memory allocation *************/
    	uint32_t *ptr = allocate_words(length);

    	/************ Pattern write to memory *************/
    	mem_status status = write_pattern(ptr,length,seed);
    	UCUNIT_Init(); /* initialize framework */
    	UCUNIT_TestcaseBegin("Pattern Write to Memory");
    	UCUNIT_CheckIsEqual(status, 0);
    	UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		p = verify_pattern(ptr,length,seed);
		UCUNIT_TestcaseBegin("Pattern Verification after writing a new pattern");
		UCUNIT_CheckIsNotNull(p);
		UCUNIT_TestcaseEnd();

		/********** Writing 0xFFEE to the memory ***********/
		status = write_memory(ptr,0xFF);
		UCUNIT_TestcaseBegin("First Data (0xFF) Write to Memory");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();
		uint32_t offset = 1;
	    uint32_t *ptr1 = get_address(ptr,&offset);
	    status = write_memory(ptr1,0xEE);
		UCUNIT_TestcaseBegin("Second Data (0xEE) Write to Memory");
		UCUNIT_CheckIsEqual(status, 1);
		UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		p = verify_pattern(ptr,length,seed);
		UCUNIT_TestcaseBegin("Pattern Verification after changing the data in memory");
		UCUNIT_CheckIsNotNull(p);
		UCUNIT_TestcaseEnd();

    	/************ Pattern write to memory *************/
    	status = write_pattern(ptr,length,seed);
    	UCUNIT_TestcaseBegin("Pattern Write to Memory");
    	UCUNIT_CheckIsEqual(status, 0);
    	UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		p = verify_pattern(ptr,length,seed);
		UCUNIT_TestcaseBegin("Pattern Verification after writing a new pattern");
		UCUNIT_CheckIsNull(p);
		UCUNIT_TestcaseEnd();

	    /********** Inverting the memory ***********/
	    status = invert_block(ptr,4);
    	UCUNIT_TestcaseBegin("Inverting Memory");
    	UCUNIT_CheckIsEqual(status, 0);
    	UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		p = verify_pattern(ptr,length,seed);
		UCUNIT_TestcaseBegin("Pattern Verification after inverting a block of memory");
		UCUNIT_CheckIsNull(p);
		UCUNIT_TestcaseEnd();

	    /********** Inverting the memory ***********/
	    status = invert_block(ptr,4);
    	UCUNIT_TestcaseBegin("Inverting Memory back again into original form");
    	UCUNIT_CheckIsEqual(status, 0);
    	UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		p = verify_pattern(ptr,length,seed);
		UCUNIT_TestcaseBegin("Pattern Verification after 2nd inversion of the same block of memory");
		UCUNIT_CheckIsNull(p);
		UCUNIT_TestcaseEnd();

		/************ Freeing the allocated memory *************/
		free_words(ptr);

		/* Finish all the tests */
		UCUNIT_WriteSummary();
		UCUNIT_Shutdown();
}

/***************************************** References **************************************************
[1] https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/

********************************************************************************************************/
