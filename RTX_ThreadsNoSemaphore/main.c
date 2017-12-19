#include "stm32f10x.h"
#include <cmsis_os.h>

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

uint16_t const cn = 100;	//ms delay

void flash_LED(const void *argu)
{
	uint32_t* pin, i;
	pin = (uint32_t*)argu;
	
	while(1)
	{
		for(i=0;i<5;i++)
		{
			LED_toggle(*pin);
			osDelay(cn);
			LED_toggle(*pin);
			osDelay(cn);
		}
		osThreadYield();
	}
}

osThreadId led_ID1, led_ID2, led_ID3, led_ID4;
osThreadDef (flash_LED, osPriorityNormal, 1, 0);
uint32_t const tmp[] = {9,10,11,12};							//PIN INDEX FOR GPIOA LEDs

int main(void)
{
	LED_init();
	osKernelInitialize();														//Initialise CMSIS-RTOS
	
	led_ID1 = osThreadCreate(osThread(flash_LED), (void *)tmp);
	led_ID2 = osThreadCreate(osThread(flash_LED), (void *)(tmp+1));
	led_ID2 = osThreadCreate(osThread(flash_LED), (void *)(tmp+2));
	led_ID3 = osThreadCreate(osThread(flash_LED), (void *)(tmp+3));

	osKernelStart();
}
