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


int main(void){		
	/* Init SPI3 as slave */
	GPIOInit(GPIOC, 10, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_HIGH_SPEED, GPIO_PUPDR_NOPULL, AF6);
	GPIOInit(GPIOC, 11, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_HIGH_SPEED, GPIO_PUPDR_NOPULL, AF6);
	GPIOInit(GPIOC, 12, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_HIGH_SPEED, GPIO_PUPDR_NOPULL, AF6);
	SPIInit(SPI3, SPI_SLAVE, SPI_CLOCK_DIV_2, SPI_2_LINE_UNIDIRECTION, SPI_FIRST_CLOCK, SPI_CK_TO_1, SPI_8BITS_DATA , SPI_MSB_FIRST);

	NVICSetup();
	
	while(1){
		
	}
}
