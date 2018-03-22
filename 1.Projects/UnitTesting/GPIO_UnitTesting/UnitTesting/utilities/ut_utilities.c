/** @file ut_utilities.c
 *  @brief Function implementation for the utilities used for Unit testing.
 *
 *  This contains the function implementation for the utilities used for Unit testing.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */

#include "ut_utilities.h"

uint32_t readRegister(volatile uint32_t *address){
	return *address;
}
