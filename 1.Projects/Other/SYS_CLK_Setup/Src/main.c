#include "stm32f4xx.h"
#include "GPIO_driver.h"

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
	/* Flash settings (see RM0090 rev9, p80) */
	FLASH->ACR =
            FLASH_ACR_LATENCY_5WS               /* 6 CPU cycle wait */
          | FLASH_ACR_PRFTEN                    /* enable prefetch */
          | FLASH_ACR_ICEN                      /* instruction cache enable */
          | FLASH_ACR_DCEN;                     /* data cache enable */
	
	/* Configure clocks
	* Max SYSCLK: 168MHz
	* Max AHB:  SYSCLK
	* Max APB1: SYSCLK/4 = 48MHz
	* Max APB2: SYSCLK/2 = 86MHz
	* + enable sys clock output 2 with clock divider = 4 
	*/
	RCC->CFGR =
          0x0                           /* Clock output 2 is SYSCLK (RCC_CFGR_MCO2) */
        | ( 0x6 << 27)                  /* Clock output divider */
        | RCC_CFGR_PPRE2_DIV2           /* APB2 prescaler */
        | RCC_CFGR_PPRE1_DIV4;          /* APB2 prescaler */
	
	/* Clock control register */
	RCC->CR = RCC_CR_HSEON;         /* Enable external oscillator */

	/* Wait for locked external oscillator */
	while((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

	/* PLL config */
	RCC->PLLCFGR =
          RCC_PLLCFGR_PLLSRC_HSE                /* PLL source */
        | (4 << 0)                              /* PLL input division */
        | (168 << 6)                            /* PLL multiplication */
        | (0 << 16)                             /* PLL sys clock division */
        | (7 << 24);                            /* PLL usb clock division =48MHz */

	/* crystal:  8MHz
	* PLL in:   2MHz (div 4)
	* PLL loop: 336MHz (mul 168)
	* PLL out:  168MHz (div 2)
	* PLL usb:  48MHz (div 7)
	*/

	/* Enable PLL */
	RCC->CR |= RCC_CR_PLLON;


	/* Wait for locked PLL */
	while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

	/* select system clock */
	RCC->CFGR &= ~RCC_CFGR_SW; /* clear */
	RCC->CFGR |= RCC_CFGR_SW_PLL;   /* SYSCLK is PLL */

	/* Wait for SYSCLK to be PPL */
	while((RCC->CFGR & RCC_CFGR_SW_PLL) != RCC_CFGR_SW_PLL){};

	/*Configure the LED on PD14 to test new system clock*/
	GPIOInit(GPIOD, 14, GPIO_MODER_OUTPUT, GPIO_OTYPER_PUSHPULL, GPIO_OSPEEDR_HIGH_SPEED, GPIO_PUPDR_NOPULL, GPIO_AFR_NO_ALTERNATE_FUNCTION);
	
	/* Configure SysTick interrupt every 1ms */
	SysTick_Config(168000000/1000);
	
	while(1){
		GPIOPinSet(GPIOD, 14);
		delay(5000);
		GPIOPinReset(GPIOD, 14);
		delay(5000);
	}
}
