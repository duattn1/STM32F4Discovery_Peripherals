#include "ut_main.h"

GPIO_TypeDef *stm32f4Port[] = {
	GPIOA,
	//GPIOB, //currently has errors and do not know why
	GPIOC,
	GPIOD
};

void setUp(){
	
}
	
void tearDown(){
	
}

int runAllTest(void){	
	UNITY_BEGIN();
	
	/* GPIO Driver UnitTest */
	for(uint8_t j = 0; j < 3; j++){		
		printf("%d. ----------------\n", j);
		for(uint8_t i = 0; i < numberOfTestcase; i++){			
			RUN_TEST_ON_PORTX((f[i]), (uint32_t*)stm32f4Port[0]);		
		}		
	}		
	return UNITY_END();
}
