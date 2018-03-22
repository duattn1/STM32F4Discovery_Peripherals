/** @file ut_GPIO_driver.c
 *  @brief Function implementation for the Unit testing of GPIO driver.
 *
 *  This contains the function implementation for the Unit testing of GPIO driver.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */

#include "ut_GPIO_driver.h"

void (*f[])(GPIO_TypeDef*) = {
	ut_GPIOInitNoAF_0,
	ut_GPIOInitNoAF_1,
	ut_GPIOInitNoAF_2,
	ut_GPIOInitNoAF_3,
	ut_GPIOInitAF_1,
	ut_GPIOInitAF_2,
	ut_GPIOInitAF_3,
	ut_GPIOInitAF_4,
	ut_GPIOInitAF_5,
	ut_GPIOInitAF_6,
	ut_GPIOInitAF_7,
	ut_GPIOInitAF_8,
	ut_GPIOInitAF_9,
	ut_GPIOInitAF_10,
	ut_GPIOInitAF_11
};

uint8_t numberOfTestcase = sizeof(f)/sizeof(int);

void ut_GPIOInitNoAF_0(GPIO_TypeDef *GPIOx){		
	tc_GPIOInit(GPIOx, 0, INPUT, PUSHPULL, LOWSPEED, NOPULL, NOAF);
}

void ut_GPIOInitNoAF_1(GPIO_TypeDef *GPIOx){		
	tc_GPIOInit(GPIOx, 1, OUTPUT, OPENDRAIN, MEDIUMSPEED, PULLUP, NOAF);	
}

void ut_GPIOInitNoAF_2(GPIO_TypeDef *GPIOx){		
	tc_GPIOInit(GPIOx, 2, ANALOG, PUSHPULL, HIGHSPEED, PULLDOWN, NOAF);	
}

void ut_GPIOInitNoAF_3(GPIO_TypeDef *GPIOx){		
	tc_GPIOInit(GPIOx, 3, INPUT, OPENDRAIN, VERYHIGHSPEED, NOPULL, NOAF);
}

/*
16 AF TCs
*/
void ut_GPIOInitAF_0(GPIO_TypeDef *GPIOx){		
	tc_GPIOInit(GPIOx, 0, ALTFUNCTION, PUSHPULL, LOWSPEED, NOPULL, AF0);
}

void ut_GPIOInitAF_1(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 1, ALTFUNCTION, OPENDRAIN, MEDIUMSPEED, PULLUP, AF1);
}

void ut_GPIOInitAF_2(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 2, ALTFUNCTION, PUSHPULL, HIGHSPEED, PULLDOWN, AF2);
}

void ut_GPIOInitAF_3(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 3, ALTFUNCTION, OPENDRAIN, VERYHIGHSPEED, NOPULL, AF3);
}

void ut_GPIOInitAF_4(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 4, ALTFUNCTION, PUSHPULL, LOWSPEED, PULLUP, AF4);
}

void ut_GPIOInitAF_5(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 5, ALTFUNCTION, OPENDRAIN, MEDIUMSPEED, PULLDOWN, AF5);
}

void ut_GPIOInitAF_6(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 6, ALTFUNCTION, PUSHPULL, HIGHSPEED, NOPULL, AF6);
}

void ut_GPIOInitAF_7(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 7, ALTFUNCTION, OPENDRAIN, VERYHIGHSPEED, PULLUP, AF7);
}

void ut_GPIOInitAF_8(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 8, ALTFUNCTION, PUSHPULL, LOWSPEED, PULLDOWN, AF8);
}

void ut_GPIOInitAF_9(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 9, ALTFUNCTION, OPENDRAIN, MEDIUMSPEED, NOPULL, AF9);
}

void ut_GPIOInitAF_10(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 10, ALTFUNCTION, PUSHPULL, HIGHSPEED, PULLUP, AF10);
}

void ut_GPIOInitAF_11(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 11, ALTFUNCTION, OPENDRAIN, VERYHIGHSPEED, PULLDOWN, AF11);
}

void ut_GPIOInitAF_12(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 12, ALTFUNCTION, PUSHPULL, LOWSPEED, NOPULL, AF12);
}

void ut_GPIOInitAF_13(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 13, ALTFUNCTION, OPENDRAIN, MEDIUMSPEED, PULLUP, AF13);
}

void ut_GPIOInitAF_14(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 14, ALTFUNCTION, PUSHPULL, HIGHSPEED, PULLDOWN, AF14);
}

void ut_GPIOInitAF_15(GPIO_TypeDef *GPIOx){	
	tc_GPIOInit(GPIOx, 15, ALTFUNCTION, OPENDRAIN, VERYHIGHSPEED, NOPULL, AF15);
}

void tc_GPIOInit(GPIO_TypeDef *GPIOx, uint8_t pinNumber, uint8_t mode, uint8_t type, uint8_t speedType, uint8_t pullType, uint8_t altFunction){
	
	GPIOInit(GPIOx, pinNumber, mode, type, speedType, pullType, altFunction);

	TEST_ASSERT_EQUAL_HEX32( mode << (2*pinNumber), 			(PIN_x_CONFIG_BY_2BIT_MASK << 2*pinNumber) & readRegister(&GPIOA->MODER));
	TEST_ASSERT_EQUAL_HEX32( type << pinNumber, 					(PIN_x_CONFIG_BY_1BIT_MASK << pinNumber) & readRegister(&GPIOA->OTYPER));
	TEST_ASSERT_EQUAL_HEX32( speedType << (2*pinNumber), 	(PIN_x_CONFIG_BY_2BIT_MASK << 2*pinNumber) & readRegister(&GPIOA->OSPEEDR));
	TEST_ASSERT_EQUAL_HEX32( pullType << (2*pinNumber) , 	(PIN_x_CONFIG_BY_2BIT_MASK << 2*pinNumber) & readRegister(&GPIOA->PUPDR));

	if(mode == ALTFUNCTION){
		if(pinNumber < 8){
		//GPIOx->AFR[0] &= ~(0x0f << (4 * pinNumber));
		//GPIOx->AFR[0] |= altFunction << (4 * pinNumber);
		TEST_ASSERT_EQUAL_HEX32( altFunction << (4*pinNumber) , 	(PIN_x_CONFIG_BY_4BIT_MASK << 4*pinNumber) & readRegister(&GPIOA->AFR[0]));
	} else {
		//GPIOx->AFR[1] &= ~(0x0f << (4 * pinNumber - 32));
		//GPIOx->AFR[1] |= altFunction << (4 * pinNumber - 32);
		TEST_ASSERT_EQUAL_HEX32( altFunction << (4*pinNumber - 32) , 	(PIN_x_CONFIG_BY_4BIT_MASK << (4*pinNumber - 32)) & readRegister(&GPIOA->AFR[1]));

	}
	}
}

void test(int x){	
	TEST_ASSERT_EQUAL_HEX32(x, 10);
}
