/** @file main.c
 *  @brief Application main function
 *
 *  This is the main place to control the application.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 
 
#include "stm32f407xx.h"
#include "../Inc/GPIO_driver.h"
#include "../Inc/SPI_driver.h"
#include "../Inc/interrupt_controller.h"


int main(void){		
	GPIOInit(GPIOC, 10, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF6);
	GPIOInit(GPIOC, 11, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF6);
	GPIOInit(GPIOC, 12, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF6);
	SPIInit(SPI3, SPI_SLAVE, SPI_CLOCK_DIV_2, SPI_2_LINE_UNIDIRECTION, SPI_FIRST_CLOCK, SPI_CK_TO_1, SPI_8BITS_DATA , SPI_MSB_FIRST);

	NVICSetup();
	
	while(1){
		
	}
}
