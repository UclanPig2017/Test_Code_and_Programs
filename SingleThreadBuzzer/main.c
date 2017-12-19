#include "stm32f10x.h"
#include <cmsis_os.h>

void Buzzer_Init(void)
{
	RCC->APB2ENR |= 1UL<<3;
	GPIOB->CRL = 0x33222222;
	GPIOB->ODR |= 0xFF << 6;
}

void PB6_on(void)
{
	GPIOB->ODR |= 1UL<< 6;
}

void PB6_off(void)
{
	GPIOB->ODR &= ~(1UL<< 6);
}

uint16_t const cn = 2;
void sound_PB6_T1 (const void *argu)
{
	while(1)
	{
		PB6_on();
		osDelay(cn);		//delay in ms
		PB6_off();
		osDelay(cn);		//delay in ms
	}
}

osThreadId T1;			//Define thread handles
osThreadDef(sound_PB6_T1, osPriorityNormal, 1, 0);

int main (void)
{
	Buzzer_Init();																				//Initialise LED
	osKernelInitialize();																	//Initialise CMSIS-RTOS
	T1 = osThreadCreate(osThread(sound_PB6_T1), NULL);		//Create Thread
	osKernelStart();																			//Start thread execution
}
