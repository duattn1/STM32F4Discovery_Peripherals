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


int fputc(int c, FILE * stream){
	sendChar(USARTPortToRedirect, c);
	return c;
}


int fgetc(FILE * stream){
	char c = getChar(USARTPortToRedirect);
	sendChar(USARTPortToRedirect, c); //print out the received characters
	return c;
}
