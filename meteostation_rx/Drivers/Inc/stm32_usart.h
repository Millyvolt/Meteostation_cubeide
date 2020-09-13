
#pragma once


#include "main.h"


#define	UART_BAUDRATE_9600
//#define	UART_BAUDRATE_57600
//#define	UART_BAUDRATE_115200
//#define	UART_BAUDRATE_256000	//not working on PCLK1_2=8MHz


//typedef	enum
//{
//	USART_1,
//	USART_2,
//	USART_3
//}USART_num;


void	USART_init(USART_TypeDef* USART);
void	USART_Tx(USART_TypeDef* USART, uint8_t* buf);
void	USART_Tx_byte(USART_TypeDef* USART, uint8_t byte);
void	USART_Rx(USART_TypeDef* USART);


