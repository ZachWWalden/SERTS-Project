
#include "cmsis_os.h"  // CMSIS RTOS header file
#include "Board_LED.h"
#include "UART_driver.h"
#include "stdint.h"                     // data type definitions
#include "stdio.h"                      // file I/O functions
#include "rl_usb.h"                     // Keil.MDK-Pro::USB:CORE
#include "rl_fs.h"                      // Keil.MDK-Pro::File System:CORE
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_audio.h"
#include "math.h"
#include "arm_math.h" // header for DSP library
#include <stdio.h>

// LED constants
#define LED_Green   0
#define LED_Orange  1
#define LED_Red     2
#define LED_Blue    3

void Thread_1 (void const *arg);                           // function prototype for Thread_1
osThreadDef (Thread_1, osPriorityNormal, 1, 0);            // define Thread_1

void Init_Thread (void) {

	osThreadId id; // holds the returned thread create ID
	
	LED_Initialize(); // Initialize the LEDs
	UART_Init(); // Initialize the UART
	
  id = osThreadCreate (osThread (Thread_1), NULL);         // create the thread
  if (id == NULL) {                                        // handle thread creation
    // Failed to create a thread
  };
}

// Thread function
void Thread_1(void const *arg){
	int i = 0;
	int chooseEffect = 1;
		while(1){
			i = 0;
			if (chooseEffect == 0)
			{
				while(i<8)
				{
					LED_On(LED_Red);
					LED_Off(LED_Blue);
					osDelay (1 + 20 * i);
					LED_Off(LED_Red);
					LED_On(LED_Orange);
					osDelay (100 - 10 * i);
					LED_On(LED_Green);
					LED_Off(LED_Orange);
					osDelay (1 + 20 * i);
					LED_Off(LED_Green);
					LED_On(LED_Blue);
					osDelay (100 - 10 * i);
					i++;
					printf("i = %d\n", i);
				}
				while(i>0)
				{
					LED_On(LED_Red);
					LED_Off(LED_Blue);
					osDelay (1 + 20 * i);
					LED_Off(LED_Red);
					LED_On(LED_Orange);
					osDelay (100 - 10 * i);
					LED_On(LED_Green);
					LED_Off(LED_Orange);
					osDelay (1 + 20 * i);
					LED_Off(LED_Green);
					LED_On(LED_Blue);
					osDelay (100 - 10 * i);
					i--;
					printf("i = %d\n", i);
				}
			}
			if (chooseEffect == 1)
			{
				while(i<5)
				{
					//orange & green
					LED_On(LED_Red);
					LED_On(LED_Green);
					LED_Off(LED_Blue);
					LED_Off(LED_Orange);
					osDelay(20 + 30 * i);
					//green & blue
					LED_On(LED_Blue);
					LED_On(LED_Orange);
					LED_Off(LED_Red);
					LED_Off(LED_Green);
					osDelay(20 + 30 * i);
					i++;
				}
				osDelay(150);
				while(i > 0)
				{
					LED_On(LED_Red);
					LED_Off(LED_Blue);
					osDelay (20 + 30 * 1);
					LED_Off(LED_Red);
					LED_On(LED_Orange);
					osDelay (20 + 30 * 1);
					LED_On(LED_Green);
					LED_Off(LED_Orange);
					osDelay (20 + 30 * 1);
					LED_Off(LED_Green);
					LED_On(LED_Blue);
					osDelay (20 + 30 * 1);
					i--;
				}
			}

	}

}


