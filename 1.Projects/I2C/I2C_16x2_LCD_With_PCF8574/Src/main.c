/** @file main.c
 *  @brief Application main function
 *
 *  This is the main place to control the application.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 
 
#include "stm32f407xx.h"
#include "../Inc/GPIO_driver.h"
#include "../Inc/PCF8574.h"

/* STM32F4 Discovery LED on Port D */
#define GREENLED			12
#define ORANGELED			13
#define REDLED				14
#define BLUELED				15

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
	GPIOInit(GPIOD, REDLED, OUTPUT, PUSHPULL, VERYHIGHSPEED, NOPULL, NOAF);
	
	/* Configure SysTick interrupt every 1ms */
	SysTick_Config(SystemCoreClock/1000);
	
	while(1){
		GPIOPinSet(GPIOD, REDLED);
		delay(1000);
		GPIOPinReset(GPIOD, REDLED);
		delay(1000);
	}	
	
	return 0;
}
