
#pragma once


#include "main.h"


typedef enum
{
	SPI_1,
	SPI_2
}SPI_num;


void	SPI_init(SPI_num SPI_number);
void  SPI_master(SPI_num SPI_number, uint8_t *data_Tx, uint8_t *data_Rx, uint8_t n_data_bytes);

extern void Delay(uint16_t approximately_ms);


