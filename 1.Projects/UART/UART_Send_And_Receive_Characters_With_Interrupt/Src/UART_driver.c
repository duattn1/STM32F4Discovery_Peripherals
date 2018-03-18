/** @file UART_driver.h
 *  @brief Function implementation for the UART driver.
 *
 *  This contains the function inplementation for the UART driver
 *	and also macros, constants, variables needed.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */
 
#include "../Inc/UART_driver.h"

void UARTInit(USART_TypeDef *UARTX, uint8_t wordLength, uint8_t stopBitNumber, uint8_t parityEnable, uint8_t oversampling, uint32_t baudrate){
	/* Turn on the clock for the UART to be configured */
	if(UARTX == USART1) _USART1_CLK_ENABLE();
	else if(UARTX == USART2) _USART2_CLK_ENABLE();
	else if(UARTX == USART3) _USART3_CLK_ENABLE();
	else if(UARTX == UART4) _UART4_CLK_ENABLE();
	else if(UARTX == UART5) _UART5_CLK_ENABLE();
	else if(UARTX == USART6) _USART6_CLK_ENABLE();
	
	/* Configure length of data bits */
	UARTX->CR1 |= wordLength << 12;
	
	/* Configure number of stop bit(s) */
	UARTX->CR2 &= ~(0x03 << 12);
	UARTX->CR2 |= stopBitNumber << 12;
	/* Configure parity check */
	UARTX->CR1 |= parityEnable << 10;	
	/* Configure oversampling rate */
	UARTX->CR1 |= oversampling << 15;

	/**
	 *	Configure baudrate
	 *	Bit [3:0] is for fraction setup
	 *	Bit [15:4] is for mantissa setup
	 */
	if(UARTX == USART1 || UARTX == USART6){ 
		uint16_t mantissa, fraction;
		fraction = baudrateFractionCal(APB2_CLK_SPEED, baudrate, oversampling);
		mantissa = baudrateMantissaCal(APB2_CLK_SPEED, baudrate, oversampling);		
		UARTX->BRR |= fraction << 0;
		UARTX->BRR |= mantissa << 4;
	} else { 
		uint16_t mantissa, fraction;
		fraction = baudrateFractionCal(APB1_CLK_SPEED, baudrate, oversampling);
		mantissa = baudrateMantissaCal(APB1_CLK_SPEED, baudrate, oversampling);		
		UARTX->BRR |= fraction << 0;
		UARTX->BRR |= mantissa << 4;
	}
	
	/* Enable transmission */
	UARTX->CR1 |= 1 << 3;
	/* Enable reception */
	UARTX->CR1 |= 1 << 2;
	/* Enable UART */
	UARTX->CR1 |= 1 << 13;
}

void sendChar(USART_TypeDef *UARTX, uint8_t character){
    while(!(UARTX->SR & USART_FLAG_TXE)); //Make sure that there is no data in the Transmit Data Register before write to DR
    UARTX->DR = character;
}

void sendString(USART_TypeDef *UARTX, char text[], int length){
    uint8_t i = 0;
    while(length--){
        sendChar(UARTX, text[i++]);
    }
}

uint8_t getChar(USART_TypeDef *UARTX){
    while(!(UARTX->SR & USART_FLAG_RXNE));
    return (uint8_t)UARTX->DR;
}

uint8_t* getString(USART_TypeDef *UARTX){
    uint8_t i = 0;
    static uint8_t *buff;
    uint8_t character = 0;
		do {
			character = getChar(UARTX);
			buff[i++] = character;
		}
    while(character != '\n');
    return buff;
}

uint16_t baudrateMantissaCal(uint32_t srcClk, uint32_t baudrate, uint8_t oversampling){
	uint16_t mantissa;
	mantissa = srcClk/(8*(2 - oversampling)*baudrate);
	return mantissa;
}

//duat: fraction must be more exact
uint16_t baudrateFractionCal(uint32_t srcClk, uint32_t baudrate, uint8_t oversampling){
	uint16_t remain;
	float fraction, roundedFraction;
	remain = srcClk%(8*(2 - oversampling)*baudrate);
	fraction = (float)remain/(8*(2 - oversampling)*baudrate);
	roundedFraction = fraction * 16;
	//to round the Fraction
	if((((uint16_t)(roundedFraction*10) - 10*(uint16_t)roundedFraction)) % 10 >= 5) roundedFraction = roundedFraction + 1;
	
	return (uint16_t)roundedFraction;
}
