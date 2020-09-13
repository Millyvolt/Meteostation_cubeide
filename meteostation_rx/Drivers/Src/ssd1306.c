
#include "ssd1306.h"



extern void	USART_Tx(USART_num USART_number, uint8_t* buf);


static void Delay(uint16_t approximately_ms)
{
	for (int i = 0; i < approximately_ms * 500; i++) ;
}


extern const uint8_t FontTable[][5];


void Displ_init(I2C_TypeDef* I2C)
{

//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xA8);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0x3F);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xD3);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0x00);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0x40);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xA0);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xA1);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xC0);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xC8);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xDA);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0x02);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0x81);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0x7F);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xA4);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xA6);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0xD5);
//  	I2C_write_1b(I2Cx, 0x78, 0b00000000, 0x80);
   	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x8D);
  	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x14);
  	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0xAF);

}

void SSD1306_clear_page(I2C_TypeDef* I2C, uint8_t address)
{
#ifdef STM32F103C8T6
	
	uint32_t tmp32;

	//check BUSY
	while(I2C->SR2 & I2C_SR2_BUSY)
	{
	#ifdef	DEBUG_I2C
		USART_Tx(USART_2, (uint8_t*)" I2C (clear_page) is busy ");
		//delay here
	#endif	//DEBUG_I2C
		I2C->CR1 |= I2C_CR1_SWRST;
		delay_ms(10);
		I2C->CR1 &= ~I2C_CR1_SWRST;
		delay_ms(10);
		if(I2C==I2C1)
			I2C_init(I2C1);
		else if(I2C==I2C2)
			I2C_init(I2C2);
	}

	I2C->CR1 |= I2C_CR1_START;
	while (!(I2C->SR1 & I2C_SR1_SB)) ;
	I2C->DR = address;

	while(!(I2C->SR1 & I2C_SR1_ADDR));
	tmp32 = I2C->SR1;  	//clear
	(void)	tmp32;  		//ADDR
	tmp32 = I2C->SR2;  	//flag
	(void)	tmp32;  		//

	I2C->DR = WRITE_DATA_C0; 			//control byte - write data
	while(!(I2C->SR1 & I2C_SR1_BTF));

	for(uint8_t i = 0 ; i < 128 ; i++)
	{
		I2C->DR = 0x00;  		//data byte
		while(!(I2C->SR1 & I2C_SR1_BTF));
	}

	I2C->CR1 |= I2C_CR1_STOP;
		
#endif // STM32F103C8T6
}

void Displ_clear(I2C_TypeDef* I2C)
{
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_0);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x00);  	//set column start address higher nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x10);  	//set column start address lower nibble
	SSD1306_clear_page(I2C, SSD1306_ADDRESS);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_1);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x00); 	//set column start address higher nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x10); 	//set column start address lower nibble
	SSD1306_clear_page(I2C, SSD1306_ADDRESS);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_2);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x00); 	//set column start address higher nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x10); 	//set column start address lower nibble
	SSD1306_clear_page(I2C, SSD1306_ADDRESS);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_3);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x00); 	//set column start address higher nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x10); 	//set column start address lower nibble
	SSD1306_clear_page(I2C, SSD1306_ADDRESS);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_4);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x00); 	//set column start address higher nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x10); 	//set column start address lower nibble
	SSD1306_clear_page(I2C, SSD1306_ADDRESS);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_5);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x00); 	//set column start address higher nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x10); 	//set column start address lower nibble
	SSD1306_clear_page(I2C, SSD1306_ADDRESS);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_6);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x00); 	//set column start address higher nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x10); 	//set column start address lower nibble
	SSD1306_clear_page(I2C, SSD1306_ADDRESS);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_7);
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x00); 	//set column start address higher nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, 0x10); 	//set column start address lower nibble
	SSD1306_clear_page(I2C, SSD1306_ADDRESS);

}

void Send_data_dspl(uint8_t data, I2C_TypeDef* I2C)
{

	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_DATA, data);

}

void X_addr_dspl(uint8_t x_address, I2C_TypeDef* I2C)
{
	uint8_t a, b;

	a = x_address&0x0F;
	b = 0x10+((x_address&0xF0)>>4);

	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, a); 	//set column start address lower nibble
	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, b); 	//set column start address higher nibble

}

void Y_addr_dspl(uint8_t y_address, I2C_TypeDef* I2C)
{

	I2C_write_1b(I2C, SSD1306_ADDRESS, WRITE_COMM, PAGE_0 + y_address);

}

void	ssd1306_write(I2C_TypeDef* I2C, uint8_t *string)
{
	//I2C_write_1b(I2C_number, SSD1306_ADDRESS, WRITE_COMM, PAGE_5);
	
#ifdef STM32F103C8T6
	
	uint32_t tmp32;
	
	//check BUSY
	while(I2C->SR2 & I2C_SR2_BUSY)
	{
#ifdef	DEBUG_I2C
		USART_Tx(USART_2, (uint8_t*)" I2Cx (clear_page) is busy ");
		//delay here
#endif	//DEBUG_I2C
		I2C->CR1 |= I2C_CR1_SWRST;
		//delay
		Delay(10);
		I2C->CR1 &= ~I2C_CR1_SWRST;
		//delay
		Delay(10);
		I2C_init(I2C);
	}

	I2C->CR1 |= I2C_CR1_START;
	while (!(I2C->SR1 & I2C_SR1_SB)) ;
	I2C->DR = SSD1306_ADDRESS;

	while (!(I2C->SR1 & I2C_SR1_ADDR)) ;
	tmp32 = I2C->SR1;   	//clear
	(void)	tmp32;   		//ADDR
	tmp32 = I2C->SR2;   	//flag
	(void)	tmp32;   		//

	I2C->DR = WRITE_DATA_C0;  			//control byte - write data
	while(!(I2C->SR1 & I2C_SR1_BTF));

	while(*string)
		myputc2(*string++);

	I2C->CR1 |= I2C_CR1_STOP;
	
#endif // STM32F103C8T6
}

void	myputc2(uint8_t symbol)
{
	for (uint8_t i = 0; i < 5; i++)
	{
		I2C1->DR = FontTable[symbol][i];
		while (!(I2C1->SR1 & I2C_SR1_BTF)) ;
	}
}


