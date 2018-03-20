/**
 * @filename I2C_driver.h
 * @description This libraries is a modification of source code of Nicholas Shrake, <shraken@gmail.com>
 * @author 
 */

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include <stm32f407xx.h>
#include "../Inc/GPIO_driver.h"
#include "../Inc/I2C_driver.h"

void init_I2C1(void);
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx);
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);
void I2C_stop(I2C_TypeDef* I2Cx);

#endif
