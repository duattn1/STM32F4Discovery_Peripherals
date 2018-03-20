#include "../Inc/interrupt_controller.h"


void NVICSetup(void){	
	USARTInterruptConfig();
	
	/* Set priority for interrupts */	
	NVIC_SetPriority(USART3_IRQn, 0);
	
	/* Enable interrupts*/
	NVIC_EnableIRQ(USART3_IRQn);
}

void USARTInterruptConfig(void){
	USARTxConfig(USART3);
}	

void USARTxConfig(USART_TypeDef *UARTx){
	
	/* Enable TXNE interrupt */
	UARTx->CR1 |= USARTX_RXNE_INTERRUPT_ENABLE;
}


void USART3_IRQHandler(void){			
	while(!(USART3->SR & USART_FLAG_RXNE));
	receivedChar = (uint8_t)USART3->DR;
	
	if(receivedChar){
		/* Check if user hit ENTER (13 in ASCII) then send NEWFEED character (10 in ASCII)*/
		if(receivedChar == 13){
			sendChar(USART3, 10);
		}
		sendChar(USART3, receivedChar);
	}
}
