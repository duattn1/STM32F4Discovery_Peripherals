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
#define GREENLED			12
#define ORANGELED			13
#define REDLED				14
#define BLUELED				15

#define APPLICATION_ADDRESS        0x08010000

volatile uint32_t ticks;

void delay(volatile uint32_t time)
{
  ticks = time;
  while(ticks !=0);
} 

void SysTick_Handler(void){
	if(ticks !=0)
	{
		ticks --;
	}	
}

int main(void){	
	SCB->VTOR = APPLICATION_ADDRESS;
	__enable_irq();
	
	GPIOInit(GPIOD, BLUELED, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_VERY_HIGH_SPEED, GPIO_PUPDR_NOPULL, GPIO_AFR_NO_ALTERNATE_FUNCTION);

	GPIOPinSet(GPIOD, BLUELED);
	/* Configure SysTick interrupt every 1ms */
	SysTick_Config(SystemCoreClock/1000);
	
	while(1){
		GPIOPinSet(GPIOD, BLUELED);
		delay(1000);
		GPIOPinReset(GPIOD, BLUELED);
		delay(1000);
	}	
}
