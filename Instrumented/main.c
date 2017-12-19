#include "stm32f10x.h"
#include "stdio.h"

void init(void);


void init(void)
{
	//Initialise Peripherals
	//SET PA9 as output
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Initialise Pin	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
	int i;
	init();
	while(1)
	{
		printf("Hello!\n");
		GPIOA->ODR ^= 1UL<<10;
		for (i=0; i<0x8FFFFF; i++){;}
	}
}
