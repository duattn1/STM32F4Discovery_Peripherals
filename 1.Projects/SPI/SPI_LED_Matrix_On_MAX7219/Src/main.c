#include <stdio.h>
#include "stm32f407xx.h"
#include "../Inc/GPIO_driver.h"

typedef struct{
	GPIO_TypeDef *port;
	uint8_t CS_Pin;
	uint8_t CLK_Pin;
	uint8_t MOSI_Pin;
} MAX7219_Pin;

MAX7219_Pin max7219 = {GPIOA, 4, 5, 7};

const uint8_t characterLib[43][8]={
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0 
{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1 
{0x7E,0x02,0x02,0x7E,0x40,0x40,0x40,0x7E},//2 
{0x3E,0x02,0x02,0x3E,0x02,0x02,0x3E,0x00},//3  
{0x08,0x18,0x28,0x48,0xFE,0x08,0x08,0x08},//4 
{0x3C,0x20,0x20,0x3C,0x04,0x04,0x3C,0x00},//5 
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x00},//6 
{0x3E,0x22,0x04,0x08,0x08,0x08,0x08,0x08},//7  
{0x00,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8 
{0x3E,0x22,0x22,0x3E,0x02,0x02,0x02,0x3E},//9 
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//:
{0,0,0,0,0,0,0,0},//;
{0,0,0,0,0,0,0,0},//<
{0,0,0,0,0,0,0,0},//=
{0,0,0,0,0,0,0,0},//>
{0,0,0,0,0,0,0,0},//?	
{0,0,0,0,0,0,0,0},//@
{0x08,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},	//A 
{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x00},//B 
{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x00},//C 
{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x00},//D 
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E 
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F 
{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x3C,0x08,0x08,0x08,0x08,0x08,0x48,0x30},//J
{0x00,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
{0x00,0x42,0x62,0x52,0x4A,0x46,0x42,0x00},//N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
{0x00,0x1E,0x20,0x20,0x3E,0x02,0x02,0x3C},//S
{0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08},//T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
{0x00,0x49,0x49,0x49,0x49,0x2A,0x1C,0x00},//W
{0x00,0x41,0x22,0x14,0x08,0x14,0x22,0x41},//X
{0x41,0x22,0x14,0x08,0x08,0x08,0x08,0x08},//Y
{0x00,0x7F,0x02,0x04,0x08,0x10,0x20,0x7F},//Z
};

volatile uint32_t ticks;

void delay(volatile uint32_t time)
{
  ticks = time;
  while(ticks !=0);
} 

void SysTick_Handler(void){
	if(ticks !=0)
	{
		ticks --;
	}	
}


void write_Max7219_byte(uint8_t DATA) 
{   
	GPIOPinReset(max7219.port, max7219.CS_Pin);	
	for(uint8_t i = 8; i >= 1; i--)
	{		  
		GPIOPinReset(max7219.port, max7219.CLK_Pin);	
		if(DATA & 0x80){ // Extracting a bit data
			GPIOPinSet(max7219.port, max7219.MOSI_Pin);
		} else{
			GPIOPinReset(max7219.port, max7219.MOSI_Pin);
		}		
		DATA = DATA << 1;
		GPIOPinSet(max7219.port, max7219.CLK_Pin);	
	}                                 
}

void write_Max7219(uint8_t address, uint8_t dat)
{
	GPIOPinReset(max7219.port, max7219.CS_Pin);
	write_Max7219_byte(address);           //address,code of LED
	write_Max7219_byte(dat);               //data,figure on LED 
	GPIOPinSet(max7219.port, max7219.CS_Pin);
}

void init_MAX7219(void)
{
	write_Max7219(0x09, 0x00);       //decoding :BCD
	write_Max7219(0x0a, 0x03);       //brightness 
	write_Max7219(0x0b, 0x07);       //scanlimit;8 LEDs
	write_Max7219(0x0c, 0x01);       //power-down mode:0,normal mode:1
	write_Max7219(0x0f, 0x00);       //test display:1;EOT,display:0
}

void setup()
{
  
	//pinMode(Max7219_pinCLK,OUTPUT);
  //pinMode(Max7219_pinCS,OUTPUT);
  //pinMode(Max7219_pinDIN,OUTPUT);
	//
	//PA7 MOSI
	//PA6 MISO, but no need to use
	//PA4: CS
	//PA5: CLK
	GPIOInit(GPIOA, 4, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF5);
	GPIOInit(GPIOA, 5, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF5);
	GPIOInit(GPIOA, 7, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF5);	
  delay(500);
  init_MAX7219();
}

void writeChar(uint8_t charC){
	uint8_t i;
	for(i = 1; i < 9; i++)
		write_Max7219(i, characterLib[charC - '0'][i-1]);
		delay(500);
}

void writeString(uint8_t str[], uint8_t len){
	uint8_t i;
	for(i = 0; i < len; i++){
		writeChar(str[i]);		
	}
}

void shiftString(uint8_t str[], uint8_t len){
	uint8_t i, j;
	for(i = 0; i < 8*len; i++){
		for(j = 0; j < len; i++){
			
		}			
	}
}

int main(void) {
	uint8_t str[5] = {'T', 'R', 'O', 'N', 'G'};	
	uint8_t i, j;
	
	/* Configure SysTick interrupt every 1ms */
	SysTick_Config(SystemCoreClock/1000);
	
	setup();	
	
	while(1){
		writeString( str, 5);		
	}
	return 0;
}