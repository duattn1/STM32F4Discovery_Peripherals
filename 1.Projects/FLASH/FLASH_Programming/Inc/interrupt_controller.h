#ifndef INTERRUPT_CONTROLLER_H_
#define INTERRUPT_CONTROLLER_H_

#include "stm32f407xx.h"
#include <stdint.h>
#include "../Inc/UART_driver.h"


#define USARTX_RXNE_INTERRUPT_ENABLE		(0x01 << 5)
#define USARTX_TC_INTERRUPT_ENABLE			(0x01 << 6)
#define USARTX_TXE_INTERRUPT_ENABLE			(0x01 << 7)


static volatile uint8_t receivedChar;

void NVICSetup(void);

void USARTInterruptConfig(void);

void USARTxConfig(USART_TypeDef *UARTx);

#endif /* INTERRUPT_CONTROLLER_H_ */
