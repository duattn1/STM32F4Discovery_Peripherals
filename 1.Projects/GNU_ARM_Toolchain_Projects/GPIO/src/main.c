#include "stm32f4xx_conf.h"

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


void initGPIO(void){
    //Enable GPIO clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	//Init PD14
	GPIOD->MODER |= GPIO_MODER_MODER14_0;			//Output mode
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT_14;			//Type = push/pull
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14;		//Speed = 100MHz
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR14;			//
}

int main(void)
{
    SysTick_Config(SystemCoreClock/1000);
    initGPIO();
    GPIOD->ODR |=  1 << 14;
    while(1)
    {
	//Blink LED on PD14
	GPIOD->ODR |=  1 << 14;
	delay(1000);
	GPIOD->ODR &=  0 << 14;
	delay(1000);
    }
}

/*
 * Dummy function to avoid compiler error
 */
void _init() {

}
