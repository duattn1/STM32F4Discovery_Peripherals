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
#include "interrupt_controller.h"


int main(void){		
	/* Configure PB10 as TX and PB11 as RX */
	GPIOInit(GPIOB, USART3PortB.txPin, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_VERY_HIGH_SPEED, GPIO_PUPDR_NOPULL, AF7);
	GPIOInit(GPIOB, USART3PortB.rxPin, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_VERY_HIGH_SPEED, GPIO_PUPDR_NOPULL, AF7);		
	
	USARTInit(USART3, USART_CR1_8_BITS_DATA, USART_CR2_1_STOP_BIT, USART_CR1_DISABLE_PARITY, USART_CR1_OVER_BY_16, 9600);		
	
	NVICSetup();
	
	sendString(USART3, "start: ", 7);	
	
	while(1){
		
	}
}
