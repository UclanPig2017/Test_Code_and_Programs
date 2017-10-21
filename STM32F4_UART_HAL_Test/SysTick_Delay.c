#include "stm32f4xx_hal.h"
#include "SysTick_Delay.h"

uint16_t x=0;

//Set timer settings - count 1ms
void Timer_Configure()
{
  SysTick_Config(SystemCoreClock/1000);	//sets reload, clksource, tickint, enable
}

//Delay will reset x on call, and will run until x = user defined value
void delay_ms(int msDelay)
{
	for(x=0; x<msDelay;){;}
}

//Automatically increment x after 1ms
void SysTick_Handler(void)		
{
   x++;	//incremented when Systick Interrupt is called
}
