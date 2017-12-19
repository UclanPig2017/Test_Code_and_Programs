/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "stm32f10x.h"

extern int Init_Thread1 (void const *argument);
extern int Init_Thread2 (void const *argument);

/*
 * main: initialize and start the system
 */
 int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS

  // initialize peripherals here
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;				//ENABLE GPIOA
	GPIOA->CRH = 0x44433334;									//ENABLE GPIOA PINS 9-12 AS OUTPUTS
	GPIOA->ODR = 0;														//SET ALL PINS TO 0
	
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);
	Init_Thread1(NULL);
	Init_Thread2(NULL);

  osKernelStart ();                         // start thread execution 
}
