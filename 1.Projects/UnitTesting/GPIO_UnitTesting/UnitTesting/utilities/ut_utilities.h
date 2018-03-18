#ifndef UT_UTILITIES_H_
#define UT_UTILITIES_H_

#include <stdint.h>
//#define getName(var)  #var	//get name of variable, function

uint32_t readRegister(volatile uint32_t *address);

#endif /* UT_UTILITIES_H_ */

