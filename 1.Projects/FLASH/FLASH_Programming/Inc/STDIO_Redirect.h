/** @file STDIO_Redirect.h
 *  @brief Function prototypes for the STDIO redirect utilities.
 *
 *  This contains the function prototypes for the STDIO redirect utilities
 *	and also macros, constants, variables needed.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */

#ifndef STDIO_REDIRECT_H_
#define STDIO_REDIRECT_H_

#include "stm32f4xx.h"
#include <stdio.h>

extern USART_TypeDef *UARTPortToRedirect;

extern uint8_t getChar(USART_TypeDef *UARTX);
extern void sendChar(USART_TypeDef *UARTX, uint8_t character);

int fputc(int c, FILE * stream);

int fgetc(FILE * stream);

#endif /* STDIO_REDIRECT_H_ */
