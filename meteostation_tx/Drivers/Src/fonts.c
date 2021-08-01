
#include "fonts.h"
#include "ssd1306.h"



void PrintString(uint8_t *string, I2C_TypeDef* I2C)
{
	while(*string)
		myputc(*string++, I2C);
}

void myputc(uint8_t symbol, I2C_TypeDef* I2C)
{
	if (symbol == '\n')
	{
		x_adr = 0;
		y_adr += 1;
		X_addr_dspl(x_adr, I2C);
		Y_addr_dspl(y_adr, I2C);
	}
	else
	{
		for (uint8_t i = 0; i < 5; i++)
			Send_data_dspl(FontTable[symbol][i], I2C);
		x_adr += 6;
		X_addr_dspl(x_adr, I2C);
	}
}

void PrintChar(unsigned char c)
{
	myputc((uint8_t)c, I2C_DSPL);
}



