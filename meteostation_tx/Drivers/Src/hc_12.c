
#include "hc_12.h"
#include "delay.h"



void	hc12_init(USART_num USART_number)
{
	//PA11 - output push-pull 10MHz (SET_pin) for HC-12
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRH &= ~GPIO_CRH_CNF11_0;
	GPIOA->CRH |= GPIO_CRH_MODE11_0;
	GPIOA->BSRR |= SET_pin_set;

	USART_init(USART_number);

//	__enable_irq();
	NVIC_EnableIRQ(USART1_IRQn);
}

void	hc12_info(USART_num USART_number)
{
	GPIOA->BSRR |= SET_pin_reset;
	delay_ms(200);
	USART_Tx(USART_1, (uint8_t*)"AT");
	delay_ms(20);
	USART_Tx(USART_1, (uint8_t*)"AT+RB");
	delay_ms(40);
	USART_Tx(USART_1, (uint8_t*)"AT+RC");
	delay_ms(40);
	USART_Tx(USART_1, (uint8_t*)"AT+RF");
	delay_ms(40);
	USART_Tx(USART_1, (uint8_t*)"AT+RP");
	delay_ms(200);
	GPIOA->BSRR |= SET_pin_set;
}


