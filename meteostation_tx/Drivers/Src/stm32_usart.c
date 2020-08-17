
#include "stm32_usart.h"



void	Debug_out(unsigned char c);


void	USART_init(USART_num USART_number)
{
#ifdef STM32F103C8T6
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;    			//??
	
	switch(USART_number)
	{
	case USART_1:
		
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
		
		//GPIO config: USART1_TX (PA10) - alternate function output push-pull 50MHz
		GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
		GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
		//USART1_RX (PA10) - floating input (reset state)
		
#ifdef UART_BAUDRATE_9600
		USART1->BRR = 0x0341;       	//baud rate 9600 (if PCLK2=8MHz)
#endif // UART_BAUDRATE_9600
#ifdef UART_BAUDRATE_57600
		USART2->BRR = 0x008B;          	//baud rate 57600 (if PCLK1=8MHz)
#endif // UART_BAUDRATE_57600
#ifdef UART_BAUDRATE_115200
		USART2->BRR = 0x0045;           	//baud rate 115200 (if PCLK1=8MHz)
#endif // UART_BAUDRATE_115200
#ifdef UART_BAUDRATE_256000
		USART1->BRR = 0x001F;        	//baud rate 256000 (if PCLK2=8MHz)
#endif // UART_BAUDRATE_256000
		
		//enable interrupt for RX mode
		USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
		
		break;
		
	case USART_2:
		
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		
		//GPIO config: USART1_TX (PA2) - alternate function output push-pull 50MHz
		GPIOA->CRL |= GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1;
		GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
		//USART1_RX - (PA3) floating input (reset state)
		
#ifdef UART_BAUDRATE_9600
		USART2->BRR = 0x0341;        	//baud rate 9600 (if PCLK1=8MHz)
#endif // UART_BAUDRATE_9600
#ifdef UART_BAUDRATE_57600
		USART2->BRR = 0x008B;          	//baud rate 57600 (if PCLK1=8MHz)
#endif // UART_BAUDRATE_57600
#ifdef UART_BAUDRATE_115200
		USART2->BRR = 0x0045;           	//baud rate 115200 (if PCLK1=8MHz)
#endif // UART_BAUDRATE_115200
#ifdef UART_BAUDRATE_256000
		USART1->BRR = 0x001F;         	//baud rate 256000 (if PCLK2=8MHz)
#endif // UART_BAUDRATE_256000
		
		USART2->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;// | USART_CR1_RXNEIE;// | USART_CR1_TCIE;
		
		break;
		
	case USART_3:
		break;
	default:
		break;
	}
	
#endif // STM32F103C8T6
}
void	USART_Tx_byte(USART_num USART_number, uint8_t byte)
{
	//need to wait TXE=1??
	switch(USART_number)
	{
	case USART_1:
		USART1->DR = byte;
		while (!(USART1->SR & USART_SR_TXE)) ;
		break;
	case USART_2:
		USART2->DR = byte;
		while (!(USART2->SR & USART_SR_TXE)) ;
		break;
	case USART_3:
		break;
	default:
		break;
	}
}
void	USART_Tx(USART_num USART_number, uint8_t* buf)
{
	uint8_t i = 0;
	
	while (buf[i]) 
		USART_Tx_byte(USART_number, buf[i++]);		
}
void	USART_Rx(USART_num USART_number)
{
	
	
	switch (USART_number)
	{
	case USART_1:
		if (USART1->SR & USART_SR_RXNE)
		{
			uint8_t tmp, buf[2];
			USART1->SR &= ~USART_SR_RXNE;
			tmp = USART1->DR;
			buf[0] = tmp;
			buf[1] = 0;
			//USART_Tx(USART_number, (uint8_t*)"pressed:");
			//USART_Tx(USART_number, buf);
			USART_Tx(USART_2, buf);
		}
		break;
		
//		if (USART1->SR & USART_SR_RXNE)
//		{
//			uint8_t tmp, buf[2];
//			tmp = USART1->DR;
//			buf[0] = tmp;
//			buf[1] = 0;
//			//USART_Tx(USART_number, (uint8_t*)"pressed:");
//			//USART_Tx(USART_number, buf);
//			USART_Tx(USART_2, buf);
//		}
//		break;
	case USART_2:
		if (USART2->SR & USART_SR_RXNE)
		{
			uint8_t tmp, buf[2];
			tmp = USART2->DR;
			buf[0] = tmp;
			buf[1] = 0;
			USART_Tx(USART_number, (uint8_t*)"pressed:");
			USART_Tx(USART_number, buf);
		}
		break;
	case USART_3:
		break;
	default:
		break;
	}
}

void	Debug_out(unsigned char c)
{
	USART_Tx_byte(USART_2, c);
}


