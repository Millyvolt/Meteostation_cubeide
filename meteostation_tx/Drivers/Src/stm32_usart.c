
#include "stm32_usart.h"



void	USART_init(USART_TypeDef* USART)
{
#ifdef STM32F103C8T6
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;    			//??
	
	if(USART==USART1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
		
		//GPIO config: USART1_TX (PA10) - alternate function output push-pull 50MHz
		GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
		GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
		//USART1_RX (PA10) - floating input (reset state)
	}
	else if(USART==USART2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		
		//GPIO config: USART1_TX (PA2) - alternate function output push-pull 50MHz
		GPIOA->CRL |= GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1;
		GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
		//USART1_RX - (PA3) floating input (reset state)
	}

	#ifdef UART_BAUDRATE_9600
			USART->BRR = 0x0341;       	//baud rate 9600 (if PCLK2=8MHz)
	#endif // UART_BAUDRATE_9600
	#ifdef UART_BAUDRATE_57600
			USART->BRR = 0x008B;          	//baud rate 57600 (if PCLK1=8MHz)
	#endif // UART_BAUDRATE_57600
	#ifdef UART_BAUDRATE_115200
			USART->BRR = 0x0045;           	//baud rate 115200 (if PCLK1=8MHz)
	#endif // UART_BAUDRATE_115200
	#ifdef UART_BAUDRATE_256000
			USART->BRR = 0x001F;        	//baud rate 256000 (if PCLK2=8MHz)
	#endif // UART_BAUDRATE_256000

	//enable interrupt for RX mode
	USART->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
	
#endif // STM32F103C8T6
}

void	USART_Tx_byte(USART_TypeDef* USART, uint8_t byte)
{
	//need to wait TXE=1??
	USART->DR = byte;
	while (!(USART->SR & USART_SR_TXE)) ;
}

void	USART_Tx(USART_TypeDef* USART, uint8_t* buf)
{
	uint8_t i = 0;
	
	while (buf[i]) 
		USART_Tx_byte(USART, buf[i++]);
}

void	USART_Rx(USART_TypeDef* USART)
{
	
	if(USART==USART1)
	{
		if (USART->SR & USART_SR_RXNE)
		{
			uint8_t tmp, buf[2];
			USART->SR &= ~USART_SR_RXNE;
			tmp = USART->DR;
			buf[0] = tmp;
			buf[1] = 0;
			//USART_Tx(USART, (uint8_t*)"pressed:");
			//USART_Tx(USART, buf);
			USART_Tx(USART2, buf);
		}
	}
	else if(USART==USART2)
	{
		if (USART->SR & USART_SR_RXNE)
		{
			uint8_t tmp, buf[2];
			tmp = USART->DR;
			buf[0] = tmp;
			buf[1] = 0;
			USART_Tx(USART, (uint8_t*)"pressed:");
			USART_Tx(USART, buf);
		}
	}
}


