
#ifndef MAIN_H_
#define MAIN_H_


#include "stm32f1xx.h"
#include "stm32_i2c.h"
#include "stm32_usart.h"


#define		STM32F103C8T6

#define SET_pin_set		GPIO_BSRR_BS11
#define SET_pin_reset	GPIO_BSRR_BR11

#define LED_red_off	GPIO_BSRR_BS12
#define LED_red_on	GPIO_BSRR_BR12



#endif /* MAIN_H_ */
