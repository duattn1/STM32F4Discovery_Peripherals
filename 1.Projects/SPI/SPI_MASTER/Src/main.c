/** @file main.c
 *  @brief Application main function
 *
 *  This is the main place to control the application.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 
 
#include "stm32f407xx.h"
#include "GPIO_driver.h"
#include "SPI_driver.h"
#include "interrupt_controller.h"

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

int main(void){	
	/* Configure SysTick interrupt every 1ms */
	SysTick_Config(SystemCoreClock/1000);
	
	GPIOInit(GPIOC, 10, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF6);
	GPIOInit(GPIOC, 11, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF6);
	GPIOInit(GPIOC, 12, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF6);

	SPIInit(SPI3, SPI_MASTER, SPI_CLOCK_DIV_2, SPI_2_LINE_UNIDIRECTION, SPI_FIRST_CLOCK, SPI_CK_TO_1, SPI_8BITS_DATA , SPI_MSB_FIRST);

	NVICSetup();
	while(1){
		SPISend(SPI3, 's');
		delay(500);
		SPISend(SPI3, 't');
		delay(500);
	}
}
