#include "ut_utilities.h"

uint32_t readRegister(volatile uint32_t *address){
	return *address;
}
