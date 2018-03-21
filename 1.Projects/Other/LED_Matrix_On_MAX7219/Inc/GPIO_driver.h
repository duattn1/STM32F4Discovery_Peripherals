/** @file GPIO_driver.h
 *  @brief Function prototypes for the GPIO driver.
 *
 *  This contains the function prototypes for the GPIO driver
 *	and also macros, constants, variables needed.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */
 
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include <stdint.h>
#include "stm32f407xx.h"

#define NOAF 					0

/* GPIO output mode */
#define INPUT 						0x00
#define OUTPUT 						0x01
#define ALTFUNCTION 			0x02
#define ANALOG 						0x03

/* GPIO ouput type */
#define PUSHPULL 					0x00
#define OPENDRAIN 				0x01

/* GPIO ouput speed */
#define LOWSPEED 					0x00
#define MEDIUMSPEED 			0x01
#define HIGHSPEED 				0x02
#define VERYHIGHSPEED 		0x03

/* GPIO pull-up pull-down */
#define NOPULL 						0x00
#define PULLUP 						0x01
#define PULLDOWN					0x02

/* GPIO AF mode */
typedef enum{
	AF0 =		0x00,
	AF1 =		0x01,
	AF2 = 	0x02,
	AF3 =		0x03,
	AF4 =		0x04,
	AF5 =		0x05,
	AF6 =		0x06,
	AF7 =		0x07,
	AF8 =		0x08,
	AF9 =		0x09,
	AF10 =	0x0A,
	AF11 =	0x0B,
	AF12 =	0x0C,
	AF13 =	0x0D,
	AF14 =	0x0E,
	AF15 =	0x0F
} AF_Mode;


/* GPIO clock enable Macro functions */
#define _GPIOA_CLK_ENABLE() 				(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define _GPIOB_CLK_ENABLE() 				(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN)
#define _GPIOC_CLK_ENABLE() 				(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN)
#define _GPIOD_CLK_ENABLE() 				(RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN)

/** @brief Configure a GPIO pin.
 *
 *  @param GPIOx The address of GPIO port whose pin to be configured.
 *  @param pinNumber The pin to be configured.
 *  @param mode The mode of the pin.
 *  @param type The output type of the pin.
 *  @param speedType The output speed of the pin.
 *  @param pullType Selection the pull-up/pull-down with the pin.
 *  @param altFunction The alternative function configuration of the pin when mode is AF.
 *
 *  @return void.
 */
void GPIOInit(GPIO_TypeDef *GPIOx, uint8_t pinNumber, uint8_t mode, uint8_t type, uint8_t speedType, uint8_t pullType, uint8_t altFunction);

/** @brief Read a GPIO pin.
 *
 *  @param GPIOx The address of GPIO port whose pin to be read.
 *  @param pinNumber The pin to be read.
 *
 *  @return uint8_t.
 */
uint8_t GPIOReadFromPin(GPIO_TypeDef *GPIOx, uint8_t pinNumber);

/** @brief Set a GPIO pin.
 *
 *  @param GPIOx The address of GPIO port whose pin to be set.
 *  @param pinNumber The pin to be set.
 *
 *  @return void.
 */
void GPIOPinSet(GPIO_TypeDef *GPIOx, uint8_t pinNumber);

/** @brief Reset a GPIO pin.
 *
 *  @param GPIOx The address of GPIO port whose pin to be reset.
 *  @param pinNumber The pin to be reset.
 *
 *  @return void.
 */
void GPIOPinReset(GPIO_TypeDef *GPIOx, uint8_t pinNumber);

/** @brief Write to a GPIO port.
 *
 *  @param GPIOx The address of GPIO port to be written.
 *  @param value The value to be written.
 *
 *  @return void.
 */
void GPIOWriteToPort(GPIO_TypeDef *GPIOx, uint32_t value);


/** @brief Lock config registers of a GPIO pin.
 *
 *  @param GPIOx The address of GPIO port whose config register to be lock.
 *  @param pinNumber The pin to be written.
 *
 *  @return uint32_t.
 */
uint32_t GPIOPinConfigLock(GPIO_TypeDef *GPIOx, uint8_t pinNumber);

#endif /* GPIO_DRIVER_H_ */
