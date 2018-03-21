/** @file MAX7219.h.c
 *  @brief Function implementation for MAX7219.h
 *
 *  This contains the function implementation for MAX7219.h
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 

#include "../Inc/MAX7219.h"
#include "../Inc/GPIO_driver.h"

void write_MAX7219_byte(uint8_t DATA) 
{   
	GPIOPinReset(MAX7219.port, MAX7219.CS_Pin);	
	for(uint8_t i = 8; i >= 1; i--)
	{		  
		GPIOPinReset(MAX7219.port, MAX7219.CLK_Pin);	
		if(DATA & 0x80){ // Extracting a bit data
			GPIOPinSet(MAX7219.port, MAX7219.MOSI_Pin);
		} else{
			GPIOPinReset(MAX7219.port, MAX7219.MOSI_Pin);
		}		
		DATA = DATA << 1;
		GPIOPinSet(MAX7219.port, MAX7219.CLK_Pin);	
	}                                 
}

void write_MAX7219(uint8_t address, uint8_t dat)
{
	GPIOPinReset(MAX7219.port, MAX7219.CS_Pin);
	write_MAX7219_byte(address);           //address,code of LED
	write_MAX7219_byte(dat);               //data,figure on LED 
	GPIOPinSet(MAX7219.port, MAX7219.CS_Pin);
}

void init_MAX7219(void)
{
	write_MAX7219(0x09, 0x00);       //decoding :BCD
	write_MAX7219(0x0a, 0x03);       //brightness 
	write_MAX7219(0x0b, 0x07);       //scanlimit;8 LEDs
	write_MAX7219(0x0c, 0x01);       //power-down mode:0,normal mode:1
	write_MAX7219(0x0f, 0x00);       //test display:1;EOT,display:0
}
