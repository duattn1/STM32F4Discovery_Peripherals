/** @file main.c
 *  @brief Application main function
 *
 *  This is the main place to control the application.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 
 
#include "stm32f407xx.h"
#include "ut_main.h"

extern int runAllTest(void);

int main(void){		
	runAllTest();
	
	while(1){
	}
	return 0;
}
