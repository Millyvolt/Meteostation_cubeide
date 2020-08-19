/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "main.h"
#include "delay.h"
#include "hc_12.h"



volatile uint8_t buf_info[100], cnt_info=0;


void LED_init(void);


/*			ToDo
 *
 * (�������� ����� ���������� ����� �������������� �����)
 *
 *
 *
 *
 */


int main(void)
{
	LED_init();
	delay_init(TIM2);
	hc12_init(USART_1);


	for(;;)
	{
		GPIOC->BSRR |= LED_green_set;
		delay_ms(500);
		GPIOC->BSRR |= LED_green_reset;
		delay_ms(500);

//		hc12_info(USART_1);
//		sprintf(buffer, "%ld.%ld C \n", T / 100, (uint32_t)T % 100);
		USART_Tx(USART_1, (uint8_t*)"hello");
//		delay_ms(40);
	}
}


void LED_init(void)
{
	//configure PC13 on output push-pull 2MHz (blinking LED)
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13_1;
	GPIOC->CRH &= ~GPIO_CRH_CNF13_0;
}


void USART1_IRQHandler()
{
	uint8_t t;

	//need to check receive flag in status register

	t = USART1->DR;

	#ifdef	DEBUG_ON
	USART_Tx_byte(USART_2, t);
	#endif //DEBUG_ON

	if(t)			//received symbol not null
		buf_info[cnt_info++] = t;
	else
		cnt_info = 0;

	if(cnt_info > 100)
		cnt_info = 0;

}



