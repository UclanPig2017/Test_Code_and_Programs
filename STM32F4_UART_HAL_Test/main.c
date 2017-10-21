/*Include Files*/
#include "stm32f4xx_hal.h"
#include "UART.h"
#include "SysTick_Delay.h"
#include "LED.h"

uint8_t TestStr[14] = "Hello World \n\r";

int main(void)
{
	//Configure SysTick, USB UART and LED Pin (Pin A5)
	Timer_Configure();
	UART_Configure();
	LED_Configure();
	
	while(1)
	{
		//Transmit Hello World
		UART_sendBuf(TestStr, 14);
		LedOn();
		//Toggle LED, 1 second
		delay_ms(500);
		LedOff();
		delay_ms(500);
	}
}
