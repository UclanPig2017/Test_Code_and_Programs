/*
 * UART.c
 *
 *  Created on: 7 Oct 2017
 *      Author: Sulaymaan
 */

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "UART.h"


//Initialises USART2 in Transmit only mode
void UART_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	//Enable GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//Give USART 2 Control of Pins
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	//Configure GPIO Pins - TX + RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;		//GPIOA Pin2+3 Tx,Rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//Alternate Function
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//GPIO Pin Speed
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//Push-Pull Output
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;				//Pull-up resistors active
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Enable USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	//Configure UART
	//9600 Baud, 8 bit word, 1 stop bit, no parity.
	//Only need to transmit, no need to receive (TX only), no flow control
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	//Activate UART
	USART_Cmd(USART2, ENABLE);
}

//Sends characters one at a time until null.
void UART_send(uint8_t * str)
{
	//Transmit until end of string
	while(*str != 0)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){;} //Wait until transmit finished
		USART_SendData(USART2, *str);
		str++;
	}
}

void UART_sendBuf(uint8_t * str, uint8_t bufLen)
{
	int i;
	//Transmit until end of string
	for (i=0; i<bufLen; i++)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){;} //Wait until transmit finished
		//USART_SendData(USART2, *str);
		USART_SendData(USART2, 'T');
		str++;
	}
}

