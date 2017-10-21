#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "LED.h"

//Configure GPIO Pins
void LED_Configure(void)
{
	//SET PA9 as output
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable GPIOA
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	//Initialise Pin	
	GPIO_InitStructure.Pin = GPIO_PIN_5; 
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; 
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//Clear bit to sink and turn LED on
void LedOn(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

//Set bit to stop sink and turn LED off
void LedOff(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}
