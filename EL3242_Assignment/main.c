/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "stm32F10x.h"

extern int Init_Output(void);
extern void Init_Timers(void);
//extern uint16_t sample; 

/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS

  // initialize peripherals here
	//Init LEDs
	RCC->APB2ENR |= (1UL<<2);	//Enable GPIOA Clock
	GPIOB->CRH = 0x44443334;	//Set PB9-11 as pushpull output
	
	//Init DAC
	RCC->APB1ENR |= 1UL<<29;
	DAC->DHR12R1 = 0;
	DAC->CR |=1UL<<0;
	
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);
	Init_Output();
	Init_Timers();

 //Start it up
  osKernelStart ();                         // start thread execution 
}
