/**
 * @filename I2C_driver.h
 * @description 
 * @author 
 */

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include <stm32f407xx.h>
#include <stdint.h>
#include "../Inc/GPIO_driver.h"

/** @defgroup I2C_duty_cycle_in_fast_mode 
  * @{
  */

#define I2C_DutyCycle_16_9              ((uint16_t)0x4000) /*!< I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_DutyCycle_2                 ((uint16_t)0xBFFF) /*!< I2C fast mode Tlow/Thigh = 2 */
#define IS_I2C_DUTY_CYCLE(CYCLE) (((CYCLE) == I2C_DutyCycle_16_9) || \
   
	 
#define CR1_CLEAR_MASK    ((uint16_t)0xFBF5)      /*<! I2C registers Masks */
#define FLAG_MASK         ((uint32_t)0x00FFFFFF)  /*<! I2C FLAG mask */
#define ITEN_MASK         ((uint32_t)0x07000000)  /*<! I2C Interrupt Enable mask */

void I2CInit(I2C_TypeDef* I2Cx, uint32_t clockSpeed, uint16_t mode, uint16_t dutyCycle, uint16_t firstOwnAddress, uint16_t ACKEnable, uint16_t addressType);


#endif
