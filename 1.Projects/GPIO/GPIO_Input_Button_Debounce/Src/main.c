/** @file main.c
 *  @brief Application main function
 *
 *  This is the main place to control the application.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 
 
#include "stm32f407xx.h"
#include "GPIO_driver.h"

/* STM32F4 Discovery LED on Port D */
#define GREEN_LED				12
#define ORANGE_LED			13
#define RED_LED					14
#define BLUE_LED				15
/* STM32F4 Discovery user button on Port A */
#define USER_BUTTON			0

int main(void){		
	volatile uint8_t buttonPressed = 0;
	volatile uint16_t pressedLevel = 0;
	volatile uint16_t releasedLevel = 0;
	volatile uint16_t threshold = 3000;
	volatile uint8_t LEDState = 0;
  
	GPIOInit(GPIOA, USER_BUTTON, GPIO_MODER_INPUT, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_HIGH_SPEED, GPIO_PUPDR_NOPULL, GPIO_AFR_NO_ALTERNATE_FUNCTION);
	GPIOInit(GPIOD, RED_LED, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_HIGH_SPEED, GPIO_PUPDR_NOPULL, GPIO_AFR_NO_ALTERNATE_FUNCTION);
	
	while(1)
	{		
		if(GPIOA->IDR & 0x01)
		{
			if(buttonPressed == 0)
			{
				if(pressedLevel > threshold)
				{
					if(LEDState == 0)
					{
						LEDState = 1;
						//GPIOD->BSRR |= GPIO_BSRR_BS_14;  
						GPIOPinSet(GPIOD, RED_LED);
					} else 
					{
						LEDState = 0;
						//GPIOD->BSRR |= GPIO_BSRR_BR_14; 
						GPIOPinReset(GPIOD, RED_LED);						
					}
					buttonPressed = 1;
				} else
				{
					pressedLevel++;
					releasedLevel = 0;
				}
			}
		} else
		{
			if(buttonPressed == 1)
			{
				if(releasedLevel> threshold)
				{				
					buttonPressed = 0;
				} else
				{
					releasedLevel++;					
					pressedLevel = 0;
				}
			}
		}
	}
}
