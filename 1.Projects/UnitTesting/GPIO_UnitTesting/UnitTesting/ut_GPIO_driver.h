#ifndef UT_GPIO_DRIVER_H_
#define UT_GPIO_DRIVER_H_

#include "unity/unity.h"
#include "utilities/ut_utilities.h"
#include "../Inc/GPIO_driver.h"

//void x(GPIO_TypeDef *GPIOx);

extern void (*f[])(GPIO_TypeDef*);
extern uint8_t numberOfTestcase;

typedef enum{
	PIN_x_CONFIG_BY_1BIT_MASK 		= 0x00000001, //0x01	
	PIN_x_CONFIG_BY_2BIT_MASK 		= 0x00000003, //0x03
	PIN_x_CONFIG_BY_4BIT_MASK			= 0x0000000F	//0x0F
} Mask;

void ut_GPIOInitNoAF_0(GPIO_TypeDef *GPIOx);
void ut_GPIOInitNoAF_1(GPIO_TypeDef *GPIOx);
void ut_GPIOInitNoAF_2(GPIO_TypeDef *GPIOx);
void ut_GPIOInitNoAF_3(GPIO_TypeDef *GPIOx);
/*
16 AF TCs

*/
void ut_GPIOInitAF_0(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_1(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_2(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_3(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_4(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_5(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_6(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_7(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_8(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_9(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_10(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_11(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_12(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_13(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_14(GPIO_TypeDef *GPIOx);
void ut_GPIOInitAF_15(GPIO_TypeDef *GPIOx);
	
void tc_GPIOInit(GPIO_TypeDef *GPIOx, uint8_t pinNumber, uint8_t mode, uint8_t type, uint8_t speedType, uint8_t pullType, uint8_t altFunction);
//void test(int x);

#endif /* UT_GPIO_DRIVER_H_ */
