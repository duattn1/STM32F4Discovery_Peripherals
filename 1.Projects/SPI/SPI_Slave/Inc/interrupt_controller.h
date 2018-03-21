#ifndef INTERRUPT_CONTROLLER_H_
#define INTERRUPT_CONTROLLER_H_

#include "stm32f407xx.h"
#include <stdint.h>
#include "../Inc/SPI_driver.h"


#define USARTX_RXNE_INTERRUPT_ENABLE		(0x01 << 5)
#define USARTX_TC_INTERRUPT_ENABLE			(0x01 << 6)
#define USARTX_TXE_INTERRUPT_ENABLE			(0x01 << 7)


static volatile uint8_t receivedChar;

void NVICSetup(void);

void SPIInterruptConfig(void);

void SPIxConfig(SPI_TypeDef *SPIx);

#endif /* INTERRUPT_CONTROLLER_H_ */
