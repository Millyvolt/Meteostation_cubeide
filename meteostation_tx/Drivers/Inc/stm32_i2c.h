
#pragma once


#include "main.h"
#include "delay.h"



//typedef enum
//{
//	I2C_1,
//	I2C_2
//}I2C_num;
	

void	I2C_init(I2C_TypeDef* I2C);
void	I2C_write_1b(I2C_TypeDef* I2C, uint8_t address_slv, uint8_t address_reg, uint8_t data);

//this function reads more then 2 bytes
void	I2C_read_n_b(I2C_TypeDef* I2C, uint8_t address_slv, uint8_t address_1st_reg, uint8_t num_of_bytes, uint8_t* buf_Rx);

//extern	void	Delay(uint16_t approximately_ms);

//uint8_t I2C_read_1b(I2C_TypeDef *I2Cx, uint8_t address_slv, uint8_t address_reg, uint8_t *pdata);
//void I2C_read_2b(I2C_TypeDef *I2Cx, uint8_t address_slv, uint8_t address_1st_reg, uint8_t* buf_Rx);
