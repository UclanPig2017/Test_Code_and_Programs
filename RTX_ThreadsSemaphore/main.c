#include "stm32f10x.h"
#include <cmsis_os.h>

uint32_t const N = 4; //No. of LEDs
osThreadId Tid[N];		//Thread handles
osSemaphoreId sem;		//ID of semaphore
osSemaphoreDef (sem);		//ID of semaphore
uint16_t const cn = 30;	//ms delay

typedef struct led{
	uint32_t pin;
	uint32_t coef;
	}LED;

	LED led[N];

void LED_init(void)
{
	RCC->APB2ENR |= 1UL<<2;
	GPIOA->CRH = 0x33322222;
	GPIOA->ODR |= 0xFF<<9;
}

void LED_toggle(uint32_t n)
{
	GPIOA->ODR ^= 1UL<<n;
}


void flash_LED(const void *argu)
{
	uint8_t i;
	LED* tmp = (LED*)argu;
	
	while(1)
	{
		osSemaphoreWait(sem, osWaitForever);
		for(i=0;i<50;i++)
		{
			LED_toggle(tmp->pin);
			osDelay(cn*tmp->coef);
		}
		osSemaphoreRelease(sem);
	}
}

osThreadDef (flash_LED, osPriorityNormal, 1, 0);

int main(void)
{
	uint32_t i;
	LED_init();
	
	for(i=0;i<N;i++)
	{
		led[i].pin = 9UL + i;													//Pin index for LED
		led[i].coef = 1UL + i;												//Coefficient for flashing period
		Tid[i] = osThreadCreate(osThread(flash_LED), (void*)(led+i));
	}
	sem = osSemaphoreCreate(osSemaphore(sem),2);			//Create Semaphore
	osKernelInitialize();														//Initialise CMSIS-RTOS
	osKernelStart();
}
