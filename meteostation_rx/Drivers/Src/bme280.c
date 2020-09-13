
#include "bme280.h"
#include "delay.h"



int32_t t_fine;
uint8_t	buf_adc[8];
uint8_t buf_calib01_25[25];
uint8_t buf_calib26_32[7];


/*				Todo
 *		Reading tmpr, hum and pressure by one I2C transaction;
 *
 *
 *
 *
 */



int32_t BME280_tmpr(void)
{

	int32_t adc_T, var1, var2, T;
	uint16_t dig_T1;
	int16_t dig_T2, dig_T3;

	adc_T = (((int32_t)buf_adc[3])<<16) + (((int32_t)buf_adc[4])<<8) + (int32_t)buf_adc[5];
	adc_T &= 0x00FFFFFF;
	adc_T >>= 4;

	dig_T1 = (uint16_t)buf_calib01_25[0] + (((uint16_t)buf_calib01_25[1])<<8);
	dig_T2 = (uint16_t)buf_calib01_25[2] + (((uint16_t)buf_calib01_25[3])<<8);
	dig_T3 = (uint16_t)buf_calib01_25[4] + (((uint16_t)buf_calib01_25[5])<<8);

	var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) *
			((int32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;

}

int32_t BME280_hum(void)
{

	int32_t v_x1_u32r, adc_H;
	uint8_t dig_H1, dig_H3;
	int16_t dig_H2, dig_H4, dig_H5;
	int8_t dig_H6;

	adc_H = ((int32_t)buf_adc[6]<<8) + (int32_t)buf_adc[7];

	dig_H1 = buf_calib01_25[24];
	dig_H2 = (int16_t)buf_calib26_32[0] + (((int16_t)buf_calib26_32[1])<<8);
	dig_H3 = buf_calib26_32[2];
	dig_H4 = (((int16_t)buf_calib26_32[3])<<4) + (((int16_t)buf_calib26_32[4])&0x0F);
	dig_H5 = (((int16_t)buf_calib26_32[4])>>4) + (((int16_t)buf_calib26_32[5])<<4);
	dig_H6 = buf_calib26_32[6];

	v_x1_u32r = (t_fine - ((int32_t)76800));
	v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) +
			((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) * (((v_x1_u32r *
			((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
			((int32_t)dig_H2) + 8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (uint32_t)(v_x1_u32r>>12);

}

uint32_t BME280_press(void)
{

	int32_t adc_P;
	uint16_t dig_P1;
	int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

	adc_P = (((int32_t)buf_adc[0])<<16) + (((int32_t)buf_adc[1])<<8) + (int32_t)buf_adc[2];
	adc_P &= 0x00FFFFFF;
	adc_P >>= 4;

	dig_P1 = (uint16_t)buf_calib01_25[6] + (((uint16_t)buf_calib01_25[7])<<8);
	dig_P2 = (uint16_t)buf_calib01_25[8] + (((uint16_t)buf_calib01_25[9])<<8);
	dig_P3 = (uint16_t)buf_calib01_25[10] + (((uint16_t)buf_calib01_25[11])<<8);
	dig_P4 = (uint16_t)buf_calib01_25[12] + (((uint16_t)buf_calib01_25[13])<<8);
	dig_P5 = (uint16_t)buf_calib01_25[14] + (((uint16_t)buf_calib01_25[15])<<8);
	dig_P6 = (uint16_t)buf_calib01_25[16] + (((uint16_t)buf_calib01_25[17])<<8);
	dig_P7 = (uint16_t)buf_calib01_25[18] + (((uint16_t)buf_calib01_25[19])<<8);
	dig_P8 = (uint16_t)buf_calib01_25[20] + (((uint16_t)buf_calib01_25[21])<<8);
	dig_P9 = (uint16_t)buf_calib01_25[22] + (((uint16_t)buf_calib01_25[23])<<8);

	int64_t var1, var2, p;
	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)dig_P6;
	var2 = var2 + ((var1*(int64_t)dig_P5)<<17);
	var2 = var2 + (((int64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
	if (var1 == 0)
	{
	return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);
	return (uint32_t)p;

}

void BME280_init(I2C_TypeDef* I2C)
{
	uint8_t data;

	//set filter and stby duration
	data = 0b10000000;	//set  stby duration 500ms
	I2C_write_1b(I2C, BME280_ADDRESS, CONFIG_BME, data);

	//normal mode launch
	data = 0b00000001;	//set humidity oversampling *1
	I2C_write_1b(I2C, BME280_ADDRESS, CTRL_HUM, data);
	data = 0b00100111;	//set temperature and pressure oversampling both *1 and turn on normal mode
	I2C_write_1b(I2C, BME280_ADDRESS, CTRL_MEAS, data);

}

void BME280_reset(I2C_TypeDef* I2C)
{

	I2C_write_1b(I2C, BME280_ADDRESS, BME280_RESET, RESET_COMMAND);
	//delay?

}

void BME280_read(I2C_TypeDef* I2C, int32_t* ptmpr, int32_t* phum, uint32_t* ppress)
{
	delay_ms(1); //without delays not working
	I2C_read_n_b(I2C, BME280_ADDRESS, PRESS_MSB, 8, buf_adc);
	delay_ms(1);
	I2C_read_n_b(I2C, BME280_ADDRESS, CALIB_01, 25, buf_calib01_25);
	delay_ms(1);
	I2C_read_n_b(I2C, BME280_ADDRESS, CALIB_26, 8, buf_calib26_32);
	
#ifdef DEBUG_MODE
	
	char buf_usb[30];
	int32_t tmpr, hum;
	uint32_t press;
	
	tmpr = BME280_tmpr();
	//sprintf(buf_usb, " %ld.%ld C ", tmpr/100, tmpr%100);
	xfprintf(Debug_out, " %ld.%ld C ", tmpr / 100, tmpr % 100);
	//USART_Tx(USART_2, (uint8_t*)buf_usb);

	hum = BME280_hum();
	//sprintf(buf_usb, " %ld.%ld %% ", hum/1024, hum%1024);
	xfprintf(Debug_out, " %ld.%ld %% ", hum / 1024, hum % 1024);
	//USART_Tx(USART_2, (uint8_t*)buf_usb); 

	press = BME280_press();
	//sprintf(buf_usb, " %ld.%ld hPa      ", press/25600, press%25600);
	xfprintf(Debug_out, " %ld.%ld hPa      ", press / 25600, press % 25600);
	//USART_Tx(USART_2, (uint8_t*)buf_usb);
	
#endif // DEBUG_MODE
	
	*ptmpr = BME280_tmpr();
	*phum = BME280_hum();
	*ppress = BME280_press();
}








