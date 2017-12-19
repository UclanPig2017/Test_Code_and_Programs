#include "stm32f10x.h"
//#include "stm32f10x_EXTI.h"
//#include "stm32f10x_GPIO.h"
#include "stdio.h"

void EXTI_Configure(void);
void GPIO_Configure(void);
void Timer_Configure(void);

int count, x;

//Set timer settings - count 1ms
void Timer_Configure()
{
  SysTick_Config(SystemCoreClock/1000);	//sets reload, clksource, tickint, enable
}
//Automatically increment x after 1ms
void SysTick_Handler(void)		
{
  x++;	//incremented when Systick Interrupt is called
	if (x==1000)
	{
		x = 0;
		printf("Frequency is %d \n", count);
		count = 0;
	}
}

void EXTI_Configure(void)
{
	//SET PA5 & PA6 as Inputs 
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//Enable GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Initialise Pins	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Configure Interrupts
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//Activate Interrupts
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void GPIO_Configure(void)
{
	//Initialise Peripherals
	//SET PA9 as output
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Initialise Pin	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
	int i;
	Timer_Configure();
	EXTI_Configure();
	GPIO_Configure();
	while(1)
	{
		printf("Hello!\n");
		GPIOA->ODR ^= 1UL<<10;
		for (i=0; i<0x8FFFFF; i++){;}
	}
}

void EXTI9_5_IRQHandler(void)
{
	uint32_t mask = 1<<9;
	if (EXTI_GetITStatus(EXTI_Line5) != RESET )
	{
		GPIOA->ODR ^= mask;
		count++;
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}
