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
#include "unit_test.h"

/********* Board specific Header Files *********/
#ifdef FB
	#include "board.h"
	#include "peripherals.h"
	#include "pin_mux.h"
	#include "clock_config.h"
	#include "MKL25Z4.h"
	#include "fsl_debug_console.h"
	#include "led.h"
#endif

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
uint8_t* display_memory(uint32_t* loc, size_t length);
uint32_t* get_address(uint32_t* base_addr, uint32_t* offset);

/********* Pattern functions prototype declarations *********/
void gen_pattern(uint8_t* pattern, size_t length, int8_t seed);
uint32_t* verify_pattern(uint32_t* loc, size_t length, int8_t seed);

/********* Logger functions prototype declarations *********/
void log_enable(void);
void log_disable(void);
uint8_t log_status(void);
void log_data(uint32_t *ptr,uint8_t length);
void log_string(char *string);
void log_integer(uint8_t number);

/********* LED functions prototype declarations *********/
void led_init(void);
void green_on(void);
void green_off(void);
void red_on(void);
void red_off(void);
void blue_on(void);
void blue_off(void);
void unit_test(void);

/********* Main function *********/
int main(void)
{
	#ifdef FB
    	BOARD_InitBootPins();
    	BOARD_InitBootClocks();
    	BOARD_InitBootPeripherals();
    	BOARD_InitDebugConsole();
    	led_init();
    	green_off();
    	red_off();
    	blue_off();
    	blue_on();
	#endif

    	log_enable();
    	//log_disable();
    	uint8_t *disp;		/* Pointer for displaying memory contents */
    	uint32_t *p;		/* Pointer for storing address of pattern mismatches */
    	size_t length = 16;	/* Number of bytes to be allocated */
    	int8_t seed = 5;	/* Seed value for pattern generation */

    	/************ Memory allocation *************/
    	uint32_t *ptr = allocate_words(length);

    	/************ Pattern write to memory *************/
    	mem_status status = write_pattern(ptr,length,seed);
    	if(status == 0)
    	{
    		if(log_status())
    		{
    			log_string("\n\rPattern write successful!");
    		}

    		/********** Displaying the memory ***********/
    		disp = display_memory(ptr,length);
    		if(log_status())
    		{
   				log_string("\n\rThe memory values are:");
 			}
 			for(int8_t i = 0;i < length;i++)
    	    {
    		    if(log_status())
    		    {
    		    	log_string(" 0x");
    		   		log_integer(disp[i]);
    		    }
    		}

 			/********** Verifying the memory ***********/
 		    p = verify_pattern(ptr,length,seed);
 		    if(p == NULL)
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rPattern Verified!");
 		    	}
 		    }
 		    else
 		   	{
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rPattern verification failed!");
 		    	}
 		    }

 		    /********** Writing 0xFFEE to the memory ***********/
 		    status = write_memory(ptr,0xFF);
 		    if(status == 0)
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rData write successful!");
 		    	}
 		    }
 		    else if(status == 1)
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rData write failed!");
	    		}
				#ifdef FB
	    			blue_off();
	    			green_off();
	    			red_on();
				#endif
 		    }
 		    uint32_t offset = 1;
 		    uint32_t *ptr1 = get_address(ptr,&offset);
 		    status = write_memory(ptr1,0xEE);
 		    if(status == 0)
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rData write successful!");
 		    	}
 		    }
 		    else if(status == 1)
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rData write failed!");
	    		}
				#ifdef FB
 		    		blue_off();
 		    		green_off();
 		    		red_on();
				#endif
 		    }

    		/********** Displaying the memory ***********/
    		disp = display_memory(ptr,length);
    		if(log_status())
    		{
   				log_string("\n\rThe memory values are:");
 			}
 			for(int8_t i = 0;i < length;i++)
    	    {
    		    if(log_status())
    		    {
    		    	log_string(" 0x");
    		   		log_integer(disp[i]);
    		    }
    		}

  			/********** Verifying the memory ***********/
  		    p = verify_pattern(ptr,length,seed);
  		    if(p == NULL)
  		    {
  		    	if(log_status())
  		    	{
  		    		log_string("\n\rPattern Verified!");
  		    	}
  		    }
  		    else
  		   	{
  		    	if(log_status())
  		    	{
  		    		log_string("\n\rPattern verification failed!");
  		    	}
  		    }
    	}
    	else if(status == 1)
    	{
    		if(log_status())
    		{
    			log_string("\n\rPattern write failed!");
    		}
			#ifdef FB
    			blue_off();
    			green_off();
    			red_on();
			#endif
    	}

    	/************ Pattern write to memory *************/
    	status = write_pattern(ptr,length,seed);
    	if(status == 0)
    	{
    		if(log_status())
    		{
    			log_string("\n\rPattern write successful!");
    		}

    		/********** Displaying the memory ***********/
    		disp = display_memory(ptr,length);
    		if(log_status())
    		{
   				log_string("\n\rThe memory values are:");
 			}
 		    for(int8_t i = 0;i < length;i++)
    	    {
    		    if(log_status())
    		    {
    			   	log_string(" 0x");
    				log_integer(disp[i]);
    			}
    		}

 			/********** Verifying the memory ***********/
 		    p = verify_pattern(ptr,length,seed);
 		    if(p == NULL)
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rPattern Verified!");
 		    	}
 		    }
 		    else
 		   	{
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rPattern verification failed!");
 		    	}
 		    }

 		    /********** Inverting the memory ***********/
 		    status = invert_block(ptr,4);
 		    if(status == 0)
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rMemory has been inverted successfully!");
 		    	}
 		    }
 		    else
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rMemory could not be inverted!");
 		    	}

				#ifdef FB
 		    		blue_off();
 		    		green_off();
 		    		red_on();
				#endif
 		   	}

    		/********** Displaying the memory ***********/
    		disp = display_memory(ptr,length);
    		if(log_status())
    		{
   				log_string("\n\rThe memory values are:");
 			}
 			for(int8_t i = 0;i < length;i++)
    	    {
    		    if(log_status())
    		    {
    		    	log_string(" 0x");
    		   		log_integer(disp[i]);
    		    }
    	   }

  		    /********** Verifying the memory ***********/
  		  	p = verify_pattern(ptr,length,seed);
  		   	if(p == NULL)
  		    {
  		    	if(log_status())
  		    	{
  		    		log_string("\n\rPattern Verified!");
  		    	}
  		    }
  		    else
  		    {
  		   		if(log_status())
  		   		{
  		   			log_string("\n\rPattern verification failed!");
  	    		}
  	    	}

 		    /********** Inverting the memory ***********/
 		    status = invert_block(ptr,4);
 		    if(status == 0)
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rMemory has been inverted successfully!");
 		    	}
 		    }
 		    else
 		    {
 		    	if(log_status())
 		    	{
 		    		log_string("\n\rMemory could not be inverted!");
 		    	}

				#ifdef FB
 		    		blue_off();
 		    		green_off();
 		    		red_on();
				#endif
 		   	}

    		/********** Displaying the memory ***********/
    		disp = display_memory(ptr,length);
    		if(log_status())
    		{
   				log_string("\n\rThe memory values are:");
 			}
 			for(int8_t i = 0;i < length;i++)
    	    {
    		    if(log_status())
    		    {
    		    	log_string(" 0x");
    		   		log_integer(disp[i]);
    		    }
    	   }

  		   /********** Verifying the memory ***********/
  		   p = verify_pattern(ptr,length,seed);
  		   if(p == NULL)
  		   {
  		    	if(log_status())
  		    	{
  		    		log_string("\n\rPattern Verified!");
  		    	}
  		   }
  		   else
  		   {
  		   		if(log_status())
  		   		{
  		   			log_string("\n\rPattern verification failed!");
  	    		}
  	       }
    	}
    	else if(status == 1)
    	{
    		if(log_status())
    		{
    			log_string("\n\rPattern write failed!");
    		}

			#ifdef FB
    			blue_off();
    			green_off();
    			red_on();
			#endif
    	}

    	/************ Freeing the allocated memory *************/
    	free_words(ptr);

		#ifdef FB
    		blue_off();
    		green_on();
		#endif

    	/************ Testing the various memory suites [1] *************/
    	unit_test();

    return 0 ;
}

/***************************************** References **************************************************
[1] https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/

********************************************************************************************************/
