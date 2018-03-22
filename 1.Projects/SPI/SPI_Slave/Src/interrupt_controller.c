/** @file interrupt_controller.c
 *  @brief Function implementation for the interrupt.
 *
 *  This contains the function implementation for the interrupt.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 

#include "interrupt_controller.h"

void NVICSetup(void){	
	SPIInterruptConfig();
	
	/* Set priority for interrupts */	
	NVIC_SetPriority(SPI3_IRQn, 0);
	
	/* Enable interrupts*/
	NVIC_EnableIRQ(SPI3_IRQn);
}

void SPIInterruptConfig(void){
	SPIxConfig(SPI3);
}	

void SPIxConfig(SPI_TypeDef *SPIx){
	
	/* Enable TXE and RXNE interrupt */
	SPIx->CR2 |= 1 << 6 | 1 << 7;
}


void SPI3_IRQHandler(void){
	uint8_t revChar = 0;
	while(!(SPI3->SR & (1 << 0)));
	revChar = (uint8_t)SPI3->DR;
	ITM_SendChar(0x000000FF &revChar);
}
