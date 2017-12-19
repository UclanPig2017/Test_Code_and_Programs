#include "stm32f10x.h"
#include <cmsis_os.h>

const uint32_t N =2;			//N - no. of threads
uint8_t Flag[]={1,1};		//flags
uint8_t turn = 1;				//To record which task to run
uint16_t const cn = 2;

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

void task_0 (const void *argu)
{
	while(1)
	{
		Flag[0] = 1;													//TASK 0 WANTS ACCESS
		turn = 1;															//POLITELY GIVE CHANCE TO OTHER THREADS
		while ((Flag[1]))		//WAIT IF ANOTHER THREAD IS IN CS
		{
			if(turn==1)
			{
				Flag[0] = 0;										//TEMPORARILY GIVE UO
				while(turn!=0){}								//WAIT
				Flag[0] = 1;										//SHOUT FOR CS
			}
		}
		//CRITICAL SECTION
		PB6_on();					osDelay(cn);			//delay in ms
		PB6_off();				osDelay(cn);			//delay in ms
		
		Flag[0] = 0;												//FINISH ACCESS OF CS
	}
}

void task_1 (const void *argu)
{
	while(1)
	{
		Flag[1] = 1;													//TASK 0 WANTS ACCESS
		turn = 0;															//POLITELY GIVE CHANCE TO OTHER THREADS
		while ((Flag[0]))		//WAIT IF ANOTHER THREAD IS IN CS
		{
			if(turn==0)
			{
				Flag[1] = 0;										//TEMPORARILY GIVE UO
				while(turn!=1){}								//WAIT
				Flag[1] = 1;										//SHOUT FOR CS
			}
		}
		
		//CRITICAL SECTION
		PB6_on();					osDelay(cn*2);			//delay in ms
		PB6_off();				osDelay(cn*2);			//delay in ms
		
		Flag[1] = 0;												//FINISH ACCESS OF CS
	}
}

osThreadId T0, T1;			//Define thread handles
osThreadDef(task_0, osPriorityNormal, 1, 0);
osThreadDef(task_1, osPriorityNormal, 1, 0);


int main (void)
{
	Buzzer_Init();																				//Initialise LED
	osKernelInitialize();																	//Initialise CMSIS-RTOS
	T0 = osThreadCreate(osThread(task_0), NULL);		//Create Thread
	T1 = osThreadCreate(osThread(task_1), NULL);		//Create Thread
	osKernelStart();																			//Start thread execution
}
