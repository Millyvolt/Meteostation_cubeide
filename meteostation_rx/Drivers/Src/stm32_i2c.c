
#include "stm32_i2c.h"


extern void	USART_Tx(USART_num USART_number, uint8_t* buf);



#ifdef STM32F103C8T6

void	I2C_init(I2C_TypeDef* I2C)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	if(I2C==I2C1)
	{
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		//I2C1 GPIO config: PB6 - SCL, PB7 - SDA (alternate func open drain  50MHz)
		GPIOB->CRL |= GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1;
	}
	else if(I2C==I2C2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
		//I2C1 GPIO config: PB10 - SCL, PB11 - SDA (alternate func open drain  50MHz)
		GPIOB->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1 | GPIO_CRH_MODE11 | GPIO_CRH_CNF11_1;
	}

	I2C->CR1 |= I2C_CR1_ACK;
	I2C->CR2 |= I2C_CR2_FREQ_3;		//8MHz periph clk frequency
	I2C->CCR |= 0x0028;			//for I2C speed 100kHz on 8MHz periph clock
	I2C->TRISE |= 0x0009;
	I2C->CR1 |= I2C_CR1_PE;			//periph enable
}

void	I2C_write_1b(I2C_TypeDef* I2C, uint8_t address_slv, uint8_t address_reg, uint8_t data)
{
	uint32_t tmp32;
	
		//check BUSY
	while(I2C->SR2 & I2C_SR2_BUSY)
	{
		I2C->CR1 |= I2C_CR1_SWRST;
		delay_ms(10);
	#ifdef	DEBUG_I2C
		USART_Tx(USART_2, (uint8_t*)" I2C (write_1b) busy ");
		//delay here
	#endif	//DEBUG_I2C
		I2C->CR1 &= ~I2C_CR1_SWRST;
		//delay
		I2C_init(I2C);
		delay_ms(10);
	}

	I2C->CR1 |= I2C_CR1_START;
	while (!(I2C->SR1 & I2C_SR1_SB)) ;
	I2C->DR = address_slv;

	while (!(I2C->SR1 & I2C_SR1_ADDR)) ;
	tmp32 = I2C->SR1;	//clear
	(void)	tmp32;		//ADDR
	tmp32 = I2C->SR2;	//flag
	(void)	tmp32;		//

	I2C->DR = address_reg;
	while (!(I2C->SR1 & I2C_SR1_BTF)) ;
	I2C->DR = data;
	while (!(I2C->SR1 & I2C_SR1_BTF)) ;

	I2C->CR1 |= I2C_CR1_STOP;
}

void	I2C_read_n_b(I2C_TypeDef* I2C, uint8_t address_slv, uint8_t address_1st_reg, uint8_t num_of_bytes, uint8_t* buf_Rx)
{
	uint8_t adr, j=0;
	uint32_t tmp32;
	
	//check BUSY
	while(I2C->SR2 & I2C_SR2_BUSY)
	{
#ifdef	DEBUG_I2C
		USART_Tx(USART_2, (uint8_t*)" I2Cx (read_n_b) is busy ");
		//delay here
#endif	//DEBUG_I2C

		I2C->CR1 |= I2C_CR1_SWRST;
		//delay
		I2C->CR1 &= ~I2C_CR1_SWRST;
		//delay
		I2C_init(I2C);
	}

	I2C->CR1 |= I2C_CR1_START;
	while (!(I2C->SR1 & I2C_SR1_SB)) ;
	I2C->DR = address_slv;

	while (!(I2C->SR1 & I2C_SR1_ADDR)) ;	//need timeout?
	tmp32 = I2C->SR1;  	//clear
	(void)	tmp32;  		//ADDR
	tmp32 = I2C->SR2;  	//flag
	(void)	tmp32;  		//

	I2C->DR = address_1st_reg;
	while (!(I2C->SR1 & I2C_SR1_BTF)) ;
	I2C->CR1 |= I2C_CR1_START;
	while (!(I2C->SR1 & I2C_SR1_SB)) ;

	adr = address_slv | 0b00000001; 			//address | receive bit = 1
	I2C->DR = adr;

	while (!(I2C->SR1 & I2C_SR1_ADDR)) ;	//need timeout?
	tmp32 = I2C->SR1;   	//clear
	(void)	tmp32;   		//ADDR
	tmp32 = I2C->SR2;   	//flag
	(void)	tmp32;   		//

	for(uint8_t i = num_of_bytes ; i > 3 ; i--, j++)
	{
		while (!(I2C->SR1 & I2C_SR1_RXNE)) ;
		buf_Rx[j] = I2C->DR;
	}

	while (!(I2C->SR1 & I2C_SR1_RXNE)) ;
	while (!(I2C->SR1 & I2C_SR1_BTF)) ;
	I2C->CR1 &= ~I2C_CR1_ACK;		//no acknowledge
	buf_Rx[j++] = I2C->DR;
	I2C->CR1 |= I2C_CR1_STOP;
	buf_Rx[j++] = I2C->DR;
	while (!(I2C->SR1 & I2C_SR1_RXNE)) ;
	buf_Rx[j] = I2C->DR;

	I2C->CR1 |= I2C_CR1_ACK;		//acknowledge
}

#endif	//STM32F103C8T6


//uint8_t I2C_read_1b(I2C_TypeDef *I2Cx, uint8_t address_slv, uint8_t address_reg, uint8_t *pdata)
//{
//
//	uint8_t adr;
//	char buffer[50];
//	uint8_t i = 20, n_tacts_in_us = SystemCoreClock / 1000000, temp = n_tacts_in_us; 	//for timeout
//
//	while(LL_I2C_IsActiveFlag_BUSY(I2Cx))
//	{
//		LL_I2C_EnableReset(I2Cx);
//		HAL_Delay(3);
//		LL_I2C_DisableReset(I2Cx);
//		HAL_Delay(3);
//		I2C_init(I2Cx);
//		if (I2Cx == I2C1)
//			CDC_Transmit_FS((uint8_t*)"BUSY=1 in I2C_read_1b(), reset I2C1\n", 36);
//		else if (I2Cx == I2C2)
//			CDC_Transmit_FS((uint8_t*)"BUSY=1 in I2C_read_1b(), reset I2C2\n", 36);
//		HAL_Delay(3);
//		busy_counter++;
//		if (busy_counter >= 30)
//		{
//			busy_counter = 0;
//			return I2C_ERROR_BUSY;
//		}
//	}
//
//	LL_I2C_GenerateStartCondition(I2Cx);
//	while (!(LL_I2C_IsActiveFlag_SB(I2Cx))) ;
//
//	LL_I2C_TransmitData8(I2Cx, address_slv);
//	while (!(LL_I2C_IsActiveFlag_ADDR(I2Cx)))
//	{
//		//200*4 us TIMEOUT, where 4 - mininum tacts for 1 iteration of while cycle
//		temp--;
//		if (!temp)
//		{
//			i--;
//			temp = n_tacts_in_us;
//		}
//		if (!i)
//		{
//			CDC_Transmit_FS((uint8_t*)"I2C timeout in I2C_read_1b 1st\n", 31);
//			//HAL_Delay(20);
//			I2C_timeouts++;
//			sprintf(buffer, "I2C timeouts = %d\n", I2C_timeouts);
//			CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
//			return I2C_ERROR_ADDR;
//			//break;
//		}
//	}
//	LL_I2C_ClearFlag_ADDR(I2Cx);
//
//	LL_I2C_TransmitData8(I2Cx, address_reg);
//	while (!(LL_I2C_IsActiveFlag_BTF(I2Cx))) ;
//	LL_I2C_GenerateStartCondition(I2Cx);
//	while (!(LL_I2C_IsActiveFlag_SB(I2Cx))) ;
//
//	adr = address_slv | 0b00000001; 			//address | receive bit
//	LL_I2C_TransmitData8(I2Cx, adr);
//
//	while (!(LL_I2C_IsActiveFlag_ADDR(I2Cx)))		//this sequence for 1 byte reading
//		{
//			temp--;
//			if (!temp)
//			{
//				i--;
//				temp = n_tacts_in_us;
//			}
//			if (!i)
//			{
//				CDC_Transmit_FS((uint8_t*)"I2C timeout in I2C_read_1b 2nd\n", 31);
//				//HAL_Delay(20);
//				I2C_timeouts++;
//				sprintf(buffer, "I2C timeouts = %d\n", I2C_timeouts);
//				CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
//				return I2C_ERROR_ADDR;
//				//break;
//			}
//		}
//	LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK); 	//
//	LL_I2C_ClearFlag_ADDR(I2Cx); 					//
//	LL_I2C_GenerateStopCondition(I2Cx); 				//
//	while(!(LL_I2C_IsActiveFlag_RXNE(I2Cx))); 		//
//	*pdata =  LL_I2C_ReceiveData8(I2Cx); 			//
//
//	LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_ACK);
//
//	CDC_Transmit_FS((uint8_t*)"I2C_read_1b() OK\n", 17);
//	return I2C_OK;
//}
//
//void I2C_read_2b(I2C_TypeDef *I2Cx, uint8_t address_slv, uint8_t address_1st_reg, uint8_t* buf_Rx)
//{
//	/*		After using this function next ONE I2C transaction wont working	 */
//
//	uint8_t adr;
//	char buffer[50];
//	uint8_t i = 200, n_tacts_in_us = SystemCoreClock / 1000000, temp = n_tacts_in_us; 	//for timeout
//
//	while(LL_I2C_IsActiveFlag_BUSY(I2Cx))
//	{
//		LL_I2C_EnableReset(I2Cx);
//		HAL_Delay(20);
//		LL_I2C_DisableReset(I2Cx);
//		HAL_Delay(10);
//		I2C_init(I2Cx);
//		if (I2Cx == I2C1)
//			CDC_Transmit_FS((uint8_t*)"BUSY=1 in I2C_read_2b(), reset I2C1\n", 36);
//		else if (I2Cx == I2C2)
//			CDC_Transmit_FS((uint8_t*)"BUSY=1 in I2C_read_2b(), reset I2C2\n", 36);
//	}
//
//	LL_I2C_GenerateStartCondition(I2Cx);
//	while (!(LL_I2C_IsActiveFlag_SB(I2Cx))) ;
//
//	LL_I2C_TransmitData8(I2Cx, address_slv);
//	while (!(LL_I2C_IsActiveFlag_ADDR(I2Cx)))
//	{
//		//200*4 us TIMEOUT, where 4 - mininum tacts for 1 iteration of while cycle
//		temp--;
//		if (!temp)
//		{
//			i--;
//			temp = n_tacts_in_us;
//		}
//		if (!i)
//		{
//			CDC_Transmit_FS((uint8_t*)"I2C 1st ADDR timeout in I2C_read_2b\n", 36);
//			//HAL_Delay(20);
//			I2C_timeouts++;
//			sprintf(buffer, "I2C timeouts = %d\n", I2C_timeouts);
//			CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
//			return;
//			//break;
//		}
//	}
//	LL_I2C_ClearFlag_ADDR(I2Cx);
//
//	LL_I2C_TransmitData8(I2Cx, address_1st_reg);
//	while (!(LL_I2C_IsActiveFlag_BTF(I2Cx))) ;
//	LL_I2C_GenerateStartCondition(I2Cx);
//	while (!(LL_I2C_IsActiveFlag_SB(I2Cx))) ;
//
//	adr = address_slv | 0b00000001; 			//address | receive bit
////	LL_I2C_TransmitData8(I2Cx, adr);
//
//	LL_I2C_EnableBitPOS(I2Cx);
//	LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_ACK);
//
//	LL_I2C_TransmitData8(I2Cx, adr);
//	while (!(LL_I2C_IsActiveFlag_ADDR(I2Cx)))		//this sequence for 1 byte reading
//		{
//			temp--;
//			if (!temp)
//			{
//				i--;
//				temp = n_tacts_in_us;
//			}
//			if (!i)
//			{
//				CDC_Transmit_FS((uint8_t*)"I2C 2nd ADDR timeout in I2C_read_2b\n", 36);
//				//HAL_Delay(20);
//				I2C_timeouts++;
//				sprintf(buffer, "I2C timeouts = %d\n", I2C_timeouts);
//				CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
//				return;
//				//break;
//			}
//		}
//	LL_I2C_ClearFlag_ADDR(I2Cx);
//
//	LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK);
//	while (!(LL_I2C_IsActiveFlag_BTF(I2Cx))) ;
//	LL_I2C_GenerateStopCondition(I2Cx);
//
//	buf_Rx[0] = LL_I2C_ReceiveData8(I2Cx);
//	buf_Rx[1] = LL_I2C_ReceiveData8(I2Cx);
//
//	LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_ACK);
//	LL_I2C_DisableBitPOS(I2Cx);
//
//}
