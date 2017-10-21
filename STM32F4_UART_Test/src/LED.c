/*
 * LED.c
 *
 *  Created on: 10 Oct 2017
 *      Author: Sulaymaan
 */

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "LED.h"

/*LED Configure - Sets up Nucleo onboard LED for debugging*/
void LED_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//Configure GPIO Pins - LED2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;					//GPIOA Pin5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				//Alternate Function
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;			//GPIO Pin Speed
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//Push-Pull Output
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;				//Pull-up resistors active
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//Clear bit to sink and turn LED on
void LedOn(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
}

//Set bit to stop sink and turn LED off
void LedOff(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
}
