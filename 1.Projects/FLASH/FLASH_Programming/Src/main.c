/** @file main.c
 *  @brief Application main function
 *
 *  This is the main place to control the application.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 
 
#include "stm32f4xx.h"
#include "../Inc/GPIO_driver.h"
#include "../Inc/UART_driver.h"
#include "../Inc/FLASH_driver.h"
#include "../Inc/interrupt_controller.h"

#define MAX_LENGTH 256

USART_TypeDef *UARTPortToRedirect = USART3;


uint8_t buffer[] = "\
0123456789ABCDEF\
0123456789ABCDEF\
0123456789ABCDEF\
0123456789ABCDEF\
0123456789ABCDEF\
FEDCBA9876543210";

void setupUART(){
	/* Configure PB10 as TX and PB11 as RX */
	GPIOInit(GPIOB, USART3PortB.txPin, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_VERY_HIGH_SPEED, GPIO_PUPDR_NOPULL, AF7);
	GPIOInit(GPIOB, USART3PortB.rxPin, GPIO_MODER_ALTERNATE_FUNCTION, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_VERY_HIGH_SPEED, GPIO_PUPDR_NOPULL, AF7);		
	
	USARTInit(USART3, USART_CR1_8_BITS_DATA, USART_CR2_1_STOP_BIT, USART_CR1_DISABLE_PARITY, USART_CR1_OVER_BY_16, 9600);		
	
	NVICSetup();
}


int main(void){		
	uint8_t hexData[MAX_LENGTH];
	uint32_t hexDataLength;	 
	
	setupUART();
	
	hexDataLength = charArrayToHexArray(buffer, hexData, sizeof(buffer));
	
	printf("start\r\n");
	
	FLASHRead(FLASH_SECTOR_11, FLASH_SECTOR_11 + 80);

	FLASHEraseSector();	
	FLASHRead(FLASH_SECTOR_11, FLASH_SECTOR_11 + 80);
	
	FLASHWrite(FLASH_SECTOR_11, FLASH_SECTOR_11 + hexDataLength, hexData);	
	FLASHRead(FLASH_SECTOR_11, FLASH_SECTOR_11 + 80);
	
	while(1){
		
	}
}
