/** @file GPIO_driver.c
 *  @brief Function implementation for the GPIO driver.
 *
 *  This contains the function implementation for the GPIO driver.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 

#include "../Inc/GPIO_driver.h"

void GPIOInit(GPIO_TypeDef *GPIOx, uint8_t pinNumber, uint8_t mode, uint8_t type, uint8_t speedType, uint8_t pullType, uint8_t altFunction){
	
	/* Turn on the clock for the GPIO whose pin to be configured */
	if(GPIOx == GPIOA)	_GPIOA_CLK_ENABLE();
	else if(GPIOx == GPIOB)	_GPIOB_CLK_ENABLE();
	else if(GPIOx == GPIOC)	_GPIOC_CLK_ENABLE();
	else if(GPIOx == GPIOD)	_GPIOD_CLK_ENABLE();
	
	/* Configure the pin mode */
	GPIOx->MODER &= ~(0x03 << (2*pinNumber));
	GPIOx->MODER |= mode << (2*pinNumber);
	
	/* Configure the pin output type */
	GPIOx->OTYPER |= type << pinNumber;
	
	/* Configure the pin output speed */
	GPIOx->OSPEEDR &= ~(0x03 << (2*pinNumber));
	GPIOx->OSPEEDR |= speedType << (2*pinNumber);
	
	/* Configure the pin pull-up/ pull-down */
	GPIOx->PUPDR &= ~(0x03 << (2*pinNumber));
	GPIOx->PUPDR |= pullType << (2*pinNumber);
	
	/**
	 *	Configure the pin alternate function if pin mode is AF 
	 *	Each pin has 4 bit to configure the alternate function.
	 *	Therefore, 16 pins of each port are configured with 4*16 = 64 bits 
	 *	(equals to 2 register: AFRL & AFRH) 
	 */
	if(pinNumber < 8){
		GPIOx->AFR[0] &= ~(0x0f << (4 * pinNumber));
		GPIOx->AFR[0] |= altFunction << (4 * pinNumber);
	} else {
		GPIOx->AFR[1] &= ~(0x0f << (4 * pinNumber - 32));
		GPIOx->AFR[1] |= altFunction << (4 * pinNumber - 32);
	}
}

uint8_t GPIOReadFromPin(GPIO_TypeDef *GPIOx, uint8_t pinNumber){
	uint8_t value;
	value = (GPIOx->IDR >> pinNumber) & 0x01;
	return value;
}

void GPIOPinSet(GPIO_TypeDef *GPIOx, uint8_t pinNumber){
	 GPIOx->BSRR |= 1 << pinNumber;
}

void GPIOPinReset(GPIO_TypeDef *GPIOx, uint8_t pinNumber){
	 GPIOx->BSRR |= 1 << (pinNumber + 16);
}

void GPIOWriteToPort(GPIO_TypeDef *GPIOx, uint32_t value){
	GPIOx->ODR &= ~0x00001111;
	GPIOx->ODR |= value;
}

uint32_t GPIOPinConfigLock(GPIO_TypeDef *GPIOx, uint8_t pinNumber){
	volatile uint32_t tmp = 0x00010000;
	tmp |= 1 << pinNumber;
	/* Set LCKK bit */
	GPIOx->LCKR = tmp;
	/* Reset LCKK bit */
	GPIOx->LCKR = (1 << pinNumber);
	/* Set LCKK bit */
	GPIOx->LCKR = tmp;
	/* Read LCKK bit*/
	tmp = GPIOx->LCKR;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
	return tmp;
}
