/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "stm32f10x.h"
void hardware_init(void);
extern int Init_Thread1(void);
extern int Init_Thread2(void);

int delay_config = 180;

/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	hardware_init();
	Init_Thread1();
	Init_Thread2();
	
  osKernelStart ();                         // start thread execution 
}

void hardware_init(void)
{
	//Initialisation Structures
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//Enable GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Enable GPIOA Pins 9, 10 as Output LEDs
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Enable GPIOA pin 5 and 6 as input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Configure Interrupts
	EXTI_InitStructure.EXTI_Line = EXTI_Line5 | EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//Activate Interrupts
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)		//Push Button 1 pressed
  {
		delay_config = 50;
		EXTI_ClearITPendingBit(EXTI_Line5);	
	}
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)		//Push Button 2 pressed
  {
		delay_config = 180;
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
