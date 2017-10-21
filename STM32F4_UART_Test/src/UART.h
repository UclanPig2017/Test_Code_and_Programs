/*
 * UART.h
 *
 *  Created on: 7 Oct 2017
 *      Author: Sulaymaan
 */

#ifndef UART_H_
#define UART_H_
#endif /* UART_H_ */

//Definition of uint8_t for USART
typedef unsigned          char uint8_t;

//Function Prototypes for USART1 Interfacing
void UART_Configure(void);
void UART_send(uint8_t * str);
void UART_sendBuf(uint8_t * str, uint8_t bufLen);

