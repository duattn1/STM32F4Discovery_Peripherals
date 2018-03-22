/** @file ut_utilities.h
 *  @brief Function prototypes for the utilities used for Unit testing.
 *
 *  This contains the function prototypes for the utilities used for Unit testing
 *	and also macros, constants, variables needed.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */
 
#ifndef UT_UTILITIES_H_
#define UT_UTILITIES_H_

#include <stdint.h>

/** @brief read value from an address location
 *
 *  @param address The address need to return value.
 *
 *  @return uint32_t.
 */
uint32_t readRegister(volatile uint32_t *address);

#endif /* UT_UTILITIES_H_ */

