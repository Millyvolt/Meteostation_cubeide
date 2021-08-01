
#pragma once

#include "main.h"



#define	SSD1306_ADDRESS		0x78

#define	WRITE_COMM			0x00
#define	WRITE_DATA_C0		0x40	//continuation bit C0=0 -> in case of multiply write I2C - only data bytes
#define	WRITE_DATA			0xC0	//C0=1 -> if multiply write I2C - control byte and data byte (couples)

#define	NORMAL_DSPL			0xA6	//Set Normal/Inverse Display
#define	INVERSE_DSPL		0xA7	//
#define	ADDR_MODE			0x20		//Set memory addressing mode
#define	HORIZ_ADDR_MODE		0x00		//
#define	PAGE_0				0xB0
#define	PAGE_1				0xB1
#define	PAGE_2				0xB2
#define	PAGE_3				0xB3
#define	PAGE_4				0xB4
#define	PAGE_5				0xB5
#define	PAGE_6				0xB6
#define	PAGE_7				0xB7
#define	SET_START_LINE_0	0x40


void	Displ_init(I2C_TypeDef* I2C);
void	SSD1306_clear_page(I2C_TypeDef* I2C, uint8_t address);
void	Displ_clear(I2C_TypeDef* I2C);
void	Send_data_dspl(uint8_t data, I2C_TypeDef* I2C);
void	X_addr_dspl(uint8_t x_address, I2C_TypeDef* I2C);
void	Y_addr_dspl(uint8_t y_address, I2C_TypeDef* I2C);
void	ssd1306_write(I2C_TypeDef* I2C, uint8_t *string);
void	myputc2(uint8_t symbol);








