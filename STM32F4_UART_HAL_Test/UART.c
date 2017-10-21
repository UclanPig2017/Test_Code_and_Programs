#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_usart.h"
#include "UART.h"

//USART Handler
UART_HandleTypeDef  huart2;


//Initialises USART1 in Transmit only mode
void UART_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable GPIOA and USART
	__HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART2_CLK_ENABLE();
	
	//Configure GPIO Pins - TX
	GPIO_InitStructure.Pin = GPIO_PIN_2; 
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; 
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	//RX
	GPIO_InitStructure.Pin = GPIO_PIN_3; 
	GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Configure UART
	//9600 Baud, 8 bit word, 1 stop bit, no parity.
	//Only need to transmit, no need to receive (TX only), no flow control
	huart2.Instance        = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = USART_WORDLENGTH_8B;
	huart2.Init.StopBits = USART_STOPBITS_1;
	huart2.Init.Parity = USART_PARITY_NONE ;
	huart2.Init.Mode = USART_MODE_TX;
	
	//Activate UART
	HAL_UART_Init(&huart2);
}

//Sends characters one at a time until null.
void UART_send(uint8_t * str)
{
	//Transmit until end of string
	while(*str != 0)
	{
		//while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;} //Wait until transmit finished
		//USART_SendData(USART1, *str);
		HAL_UART_Transmit(&huart2, (uint8_t*)str, 1, 5);
		str++;
	}
}

void UART_sendBuf(uint8_t * str, uint8_t bufLen)
{
	int i;
	//Transmit until end of string
	for (i=0; i<bufLen; i++)
	{		
		//while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;} //Wait until transmit finished
		//USART_SendData(USART1, *str);
		HAL_UART_Transmit(&huart2, (uint8_t*)str, 1, 5);
		str++;
	}
}
