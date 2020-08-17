
#include "stm32_rcc.h"


void	RCC_init(void)
{
#ifdef STM32F103C8T6
	
	//tacting from HSI 8000000Hz
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY)) ;
	
	//return CFGR register to reset state
	RCC->CFGR = 0;
	while (RCC->CFGR & RCC_CFGR_SWS_1) ;
	while (RCC->CFGR & RCC_CFGR_SWS_0) ;
	
	//turn off PLL
	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_PLLON);
	while (RCC->CR & RCC_CR_HSERDY) ;
	while (RCC->CR & RCC_CR_PLLRDY) ;
	
	SystemCoreClockUpdate();
	
#endif	//STM32F103C8T6
}


