/** @file MAX7219.h
 *  @brief Function prototypes for MAX7219
 *
 *  This contains the function prototypes for MAX7219
 *	and also macros, constants, variables needed.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */
 
#ifndef MAX7219_H_
#define MAX7219_H_

#include <stdint.h>
#include "stm32f407xx.h"

typedef struct{
	GPIO_TypeDef *port;
	uint8_t CS_Pin;
	uint8_t CLK_Pin;
	uint8_t MOSI_Pin;
} MAX7219_Pin;

extern MAX7219_Pin MAX7219;

void write_MAX7219_byte(uint8_t DATA);

void write_MAX7219(uint8_t address, uint8_t dat);

void init_MAX7219(void);

#endif /* MAX7219_H_ */
