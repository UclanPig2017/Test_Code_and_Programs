/*------------------------------------------
 *Code By:
 *				G20628140 - Sulaymaan Shaikh
 *				G20653557 - Sidney Ofosu-ottopah
*-------------------------------------------*/

/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 //Header files and predefined names
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "stm32F10x.h"
#define ARM_MATH_CM3
#include "arm_math.h"

//Functions
void hardware_init(void);
extern int Init_Output(void);
extern void Init_Timers(void);
extern int Init_Thread2(void);

//Global Variables
int delay_config = 100;
int toggle_period = 2;
int period_change = 0;


/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS

  hardware_init();
	
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);
	Init_Thread2();
	Init_Output();
	Init_Timers();
	
  osKernelStart ();                         // start thread execution 
}

void hardware_init(void)
{
	// initialize peripherals here
	
	//Initialisation Structures
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//Init LEDs
	RCC->APB2ENR |= (1UL<<2);	//Enable GPIOA Clock
	GPIOB->CRH = 0x44443334;	//Set PB9-11 as pushpull output
	
	//Init DAC
	RCC->APB1ENR |= 1UL<<29;
	DAC->DHR12R1 = 0;
	DAC->CR |=1UL<<0;
	
	//Enable GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Enable GPIOA Pin 10 as Output LEDs
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Enable GPIOA pin 5 as input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Configure Interrupts
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//Interrupt triggers when switch is pressed or depressed
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

//Trigger on press or depress
//Check if pressed or depressed by reading pin state
//If 0, pressed
//If 1, depressed
void EXTI9_5_IRQHandler(void)
{
	int pinOn;
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)		//Push Button 1 pressed
  {
		osDelay(5);																//Delay to account for bounce
		pinOn = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
		if (pinOn)
		{
			toggle_period = 2;
			period_change = 1;
			EXTI_ClearITPendingBit(EXTI_Line5);	
		}
		else if (pinOn == 0)
		{
			toggle_period = 5;
			period_change = 1;
			EXTI_ClearITPendingBit(EXTI_Line5);	
		}
	}
}
