/** @file interrupt_controller.h
 *  @brief Function prototypes for interrupt.
 *
 *  This contains the function prototypes for interrupt
 *	and also macros, constants, variables needed.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */
 
#ifndef INTERRUPT_CONTROLLER_H_
#define INTERRUPT_CONTROLLER_H_

#include "stm32f407xx.h"
#include <stdint.h>
#include "UART_driver.h"


#define USARTX_RXNE_INTERRUPT_ENABLE		(0x01 << 5)
#define USARTX_TC_INTERRUPT_ENABLE			(0x01 << 6)
#define USARTX_TXE_INTERRUPT_ENABLE			(0x01 << 7)


static volatile uint8_t receivedChar;

/** @brief setup NVIC for all interrupts
 *
 *  @param void.
 *
 *  @return void.
 */
void NVICSetup(void);

/** @brief configure all used USART interrupts in application.
 *
 *  @param void.
 *
 *  @return void.
 */
void USARTInterruptConfig(void);

/** @brief configure s specific USART interrupts.
 *
 *  @param UARTx The USART port to be configured.
 *
 *  @return void.
 */
void USARTxConfig(USART_TypeDef *UARTx);

#endif /* INTERRUPT_CONTROLLER_H_ */
