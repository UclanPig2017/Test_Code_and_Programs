#define osObjectsPublic								//define objects in main module
#include "stdio.h"
#include "osObjects.h"								//RTOS object definitions
#include "stm32f10x.h"

void Thread1 (void const *argument);	//Function Prototypes
void Thread2 (void const *argument);
void Thread3 (void const *argument);


osThreadId led_ID1, led_ID2, led_ID3;
osThreadDef(Thread1, osPriorityAboveNormal, 2, 0);
osThreadDef(Thread2, osPriorityAboveNormal, 2, 0);
osThreadDef(Thread3, osPriorityAboveNormal, 2, 0);

int main(void)
{
	osKernelInitialize();							//Initialise CMSIS-RTOS
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRH = 0x44433334;
	GPIOA->ODR |= 0x1E00;
	
	//Create "thread" functions that start executing
	led_ID1 = osThreadCreate(osThread(Thread1),NULL);	//No Parameters
	led_ID2 = osThreadCreate(osThread(Thread2),NULL);	//No Parameters
	led_ID3 = osThreadCreate(osThread(Thread3),NULL);	//No Parameters

	printf("Leaving Main...\n");
	osKernelStart();															//Start Thread Execution
}

void Thread1 (void const *argument)
{
	int i;
	while(1)
	{
		printf("In Thread 1\n");
		GPIOA->ODR &= ~7UL<<9;
		for (i=0; i<0xFFFF; i++);						//Delay
		osThreadYield();											//Suspend Thread
	}
}

void Thread2 (void const *argument)
{
	int i;
	while(1)
	{
		printf("In Thread 2\n");
		GPIOA->ODR |= ~7UL<<9;
		for (i=0; i<0xFFFF; i++);						//Delay
		osThreadYield();											//Suspend Thread
	}
}

void Thread3 (void const *argument)
{
	int i;
	while(1)
	{
		printf("In Thread 3\n");
		GPIOA->ODR ^= ~1UL<<12;
		for (i=0; i<0x7FFF; i++);						//Delay
		osThreadYield();											//Suspend Thread
	}
}
