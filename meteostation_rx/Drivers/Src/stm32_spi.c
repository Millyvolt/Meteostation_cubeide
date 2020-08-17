
#include "stm32_spi.h"


extern void	USART_Tx(USART_num USART_number, uint8_t* buf);


void	SPI_init(SPI_num SPI_number)		//SPI1
{
#ifdef STM32F103C8T6
	
	//enable peripherals
	switch(SPI_number)
	{
	case SPI_1:
		
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN;
		
		// PA4 > SPI1_NSS,  PA5 > SPI1_SCK, PA6 > SPI1_MISO,  PA7 > SPI1_MOSI
		GPIOA->CRL |= GPIO_CRL_MODE4 | GPIO_CRL_CNF4_1 |	\
		GPIO_CRL_MODE5 | GPIO_CRL_CNF5_1 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1;
		GPIOA->CRL &= ~(GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0 | GPIO_CRL_CNF7_0);
		//PA6 configured input floating (reset state)
	
		GPIOA->CRL &= ~(GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0 | GPIO_CRL_CNF7_0);
		GPIOA->CRL &= ~(GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0 | GPIO_CRL_CNF7_0);

//		RCC->APB2RSTR |= RCC_APB2RSTR_IOPARST;
//		Delay(20);
//		RCC->APB2RSTR &= ~RCC_APB2RSTR_IOPARST;
		
		SPI1->CR1 |= SPI_CR1_MSTR;
		SPI1->CR2 |= SPI_CR2_SSOE;
		
		break;
	case SPI_2:
		break;
	default:
		break;
	}
	
#endif // STM32F103C8T6	
}
void  SPI_master(SPI_num SPI_number, uint8_t *data_Tx, uint8_t *data_Rx, uint8_t n_data_bytes)
{
#ifdef STM32F103C8T6

	uint32_t t_out = 400;	//~2ms on 8MHh
	
	switch(SPI_number)
	{
	case SPI_1:
		
		SPI1->CR1 |= SPI_CR1_SPE;
	
		SPI1->DR = data_Tx[0];
	
		for (uint8_t i = 1; i < n_data_bytes; i++)
		{
			while (!(SPI1->SR & SPI_SR_TXE)) 
			{
//				if (!t_out--)
//				{
//				#ifdef DEBUG_MODE
//					USART_Tx(USART_2, (uint8_t*)" SPI1 TXE timeout ");		  
//				#endif // DEBUG_MODE
//					t_out = 400;
//					RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
//					Delay(20);
//					RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
//					//SPI1 init
//					SPI1->CR1 |= SPI_CR1_MSTR;
//					SPI1->CR2 |= SPI_CR2_SSOE;
					////break;
					//return;
//				}
			}
			SPI1->DR = data_Tx[i];
			while (!(SPI1->SR & SPI_SR_RXNE)) ;
			data_Rx[i - 1] = SPI1->DR;
		}
	
		while (!(SPI1->SR & SPI_SR_RXNE))
		{
			if (!t_out--)
			{
			#ifdef DEBUG_MODE
				USART_Tx(USART_2, (uint8_t*)" SPI1 RXNE timeout ");		  
			#endif // DEBUG_MODE
				//t_out = 400;
//				RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
//				Delay(20);
//				RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
//				//SPI1 init
//				SPI1->CR1 |= SPI_CR1_MSTR;
//				SPI1->CR2 |= SPI_CR2_SSOE;
				break;
			}
		}
	
		data_Rx[n_data_bytes - 1] = SPI1->DR;
		while (!(SPI1->SR & SPI_SR_TXE)) ;
		while (SPI1->SR & SPI_SR_BSY) ; //need timeout?
	
		SPI1->CR1 &= ~SPI_CR1_SPE;
		
		break;
	case SPI_2:
		break;
	default:
		break;
	}
	
#endif // STM32F103C8T6	
}



