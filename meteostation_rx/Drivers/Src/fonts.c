
#include "fonts.h"


void PrintString(uint8_t *string, I2C_num I2C_number)
{
	while(*string)
		myputc(*string++, I2C_number);
}

void myputc(uint8_t symbol, I2C_num I2C_number)
{
	if (symbol == '\n')
	{
		x_adr = 0;
		y_adr += 1;
		X_addr_dspl(x_adr, I2C_1);
		Y_addr_dspl(y_adr, I2C_1);
	}
	else
	{
		for (uint8_t i = 0; i < 5; i++)
			Send_data_dspl(FontTable[symbol][i], I2C_number);
		x_adr += 6;
		X_addr_dspl(x_adr, I2C_number);
	}
}

void PrintChar(unsigned char c)
{
	myputc((uint8_t)c, I2C_1);
}



