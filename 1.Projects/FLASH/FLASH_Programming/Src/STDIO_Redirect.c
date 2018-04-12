/** @file STDIO_Redirect.c
 *  @brief Function implementation for the STDIO redirect utilities.
 *
 *  This contains the function implementation for the STDIO redirect utilities.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 
 
#include "STDIO_Redirect.h"

struct __FILE
{
  int dummyVar; //Just for the sake of redefining __FILE, we won't we using it anyways ;)
};

FILE __stdout;
FILE __stdin;

/** @brief Overload printing a character form STDIO stream
 *
 *  @param c The character to be sent
 *  @param stream The STRIO stream
 *
 *  @return int
 */
int fputc(int c, FILE * stream){
	sendChar(UARTPortToRedirect, c);
	return c;
}

/** @brief Overload getting a character form STDIO stream
 *
 *  @param stream The STRIO stream
 *
 *  @return int
 */
int fgetc(FILE * stream){
	char c = getChar(UARTPortToRedirect);
	sendChar(UARTPortToRedirect, c); //print out the received characters
	return c;
}
