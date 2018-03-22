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
#include "UART_driver.h"

#define BUFFER_SIZE 256

int main(void){		
	uint8_t receivedChar = 0;
	
	/* Configure PB10 as TX and PB11 as RX */
	GPIOInit(GPIOB, USART3PortB.txPin, ALTFUNCTION, PUSHPULL, VERYHIGHSPEED, NOPULL, AF7);
	GPIOInit(GPIOB, USART3PortB.rxPin, ALTFUNCTION, PUSHPULL, VERYHIGHSPEED, NOPULL, AF7);		
	
	/* Init USART3 */
	UARTInit(USART3, IS_8_BITS_DATA, IS_1_STOP_BIT, DISABLE_PARITY, OVER_BY_16, 9600);		
	
	sendString(USART3, "start: ", 7);	
	
	while(1){
		receivedChar = getChar(USART3);
		if(receivedChar){
			sendChar(USART3, receivedChar);	
		}			
	}
	return 0;
}
