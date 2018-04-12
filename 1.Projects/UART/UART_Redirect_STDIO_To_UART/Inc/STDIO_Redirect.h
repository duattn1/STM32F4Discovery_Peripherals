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

extern USART_TypeDef *USARTPortToRedirect;

extern uint8_t getChar(USART_TypeDef *UARTX);
extern void sendChar(USART_TypeDef *UARTX, uint8_t character);

/** @brief Overload printing a character form STDIO stream
 *
 *  @param c The character to be sent
 *  @param stream The STRIO stream
 *
 *  @return int The printed character
 */
int fputc(int c, FILE * stream);

/** @brief Overload getting a character form STDIO stream
 *
 *  @param stream The STRIO stream
 *
 *  @return int The received character
 */
int fgetc(FILE * stream);

#endif /* STDIO_REDIRECT_H_ */
