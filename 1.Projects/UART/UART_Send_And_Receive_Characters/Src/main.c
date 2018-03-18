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
#include "../Inc/UART_driver.h"


int main(void){		
	/* Configure PB10 as TX and PB11 as RX */
	GPIOInit(GPIOB, 10, ALTFUNCTION, PUSHPULL, VERYHIGHSPEED, NOPULL, AF7);
	GPIOInit(GPIOB, 11, ALTFUNCTION, PUSHPULL, VERYHIGHSPEED, NOPULL, AF7);		
	
	UARTInit(USART3, IS_8_BITS_DATA, IS_1_STOP_BIT, DISABLE_PARITY, OVER_BY_16, 9600);		
	
	sendString(USART3, "con heo", 7);
	
	
	
	while(1){
		
	}
	return 0;
}
