
#pragma once


#include "main.h"


#define	BME280_ADDRESS	0xEC

//register adresses
#define	ID_REG			0xD0
#define	CONFIG_BME		0xF5
#define	CTRL_HUM		0xF2
#define	CTRL_MEAS		0xF4
#define HUM_MSB			0xFD
#define TEMP_MSB		0xFA
#define PRESS_MSB		0xF7
#define CALIB_01		0x88
#define CALIB_25		0xA1
#define BME280_RESET	0xE0
#define CALIB_26		0xE1
#define CALIB_28		0xE3
#define CALIB_29		0xE4
#define CALIB_31		0xE6
#define CALIB_32		0xE7

#define	RESET_COMMAND	0xB6
#define	ID_VALUE		0x60


void BME280_read(I2C_TypeDef* I2C, int32_t* ptmpr, int32_t* phum, uint32_t* ppress);
void BME280_init(I2C_TypeDef* I2C);
void BME280_reset(I2C_TypeDef* I2C);
int32_t BME280_tmpr(void);
int32_t BME280_hum(void);
uint32_t BME280_press(void);

//extern void I2C_write_1b(I2C_num I2C_number, uint8_t address_slv, uint8_t address_reg, uint8_t data);
//extern uint8_t I2C_read_1b(I2C_num I2C_number, uint8_t address_slv, uint8_t address_reg, uint8_t *pdata);
//extern void I2C_read_2b(I2C_num I2C_number, uint8_t address_slv, uint8_t address_1st_reg, uint8_t* buf_Rx);
//extern void I2C_read_n_b(I2C_num I2C_number, uint8_t address_slv, uint8_t address_1st_reg, uint8_t num_of_bytes, uint8_t* buf_Rx);
//extern	void	USART_Tx(USART_num USART_number, uint8_t* buf);

extern	void xfprintf(void(*func)(unsigned char), const char*	fmt, ...);
extern	void	Debug_out(unsigned char c);


