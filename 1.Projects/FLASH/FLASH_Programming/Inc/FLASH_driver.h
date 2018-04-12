/** @file FLASH_driver.h
 *  @brief Function prototypes for the FLASH driver.
 *
 *  This contains the function prototypes for the FLASH driver
 *	and also macros, constants, variables needed.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */

#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_

#include "stm32f407xx.h"
#include <stdint.h>
#include <stdio.h>
#include "../Inc/UART_driver.h"

/* Base address of the Flash sectors */ 
#define FLASH_SECTOR_0      ((uint32_t)0x08000000) /* Base address of Sector 0, 16 Kbytes   */
#define FLASH_SECTOR_1      ((uint32_t)0x08004000) /* Base address of Sector 1, 16 Kbytes   */
#define FLASH_SECTOR_2      ((uint32_t)0x08008000) /* Base address of Sector 2, 16 Kbytes   */
#define FLASH_SECTOR_3      ((uint32_t)0x0800C000) /* Base address of Sector 3, 16 Kbytes   */
#define FLASH_SECTOR_4      ((uint32_t)0x08010000) /* Base address of Sector 4, 64 Kbytes   */
#define FLASH_SECTOR_5      ((uint32_t)0x08020000) /* Base address of Sector 5, 128 Kbytes  */
#define FLASH_SECTOR_6      ((uint32_t)0x08040000) /* Base address of Sector 6, 128 Kbytes  */
#define FLASH_SECTOR_7      ((uint32_t)0x08060000) /* Base address of Sector 7, 128 Kbytes  */
#define FLASH_SECTOR_8      ((uint32_t)0x08080000) /* Base address of Sector 8, 128 Kbytes  */
#define FLASH_SECTOR_9      ((uint32_t)0x080A0000) /* Base address of Sector 9, 128 Kbytes  */
#define FLASH_SECTOR_10     ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 Kbytes */
#define FLASH_SECTOR_11     ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 Kbytes */


/* FLASH Keys */ 
#define FLASH_KEY1               	((uint32_t)0x45670123)
#define FLASH_KEY2               	((uint32_t)0xCDEF89AB)
#define FLASH_OPTKEY1           	((uint32_t)0x08192A3B)
#define FLASH_OPTKEY2          	 	((uint32_t)0x4C5D6E7F)


/* FLASH Flags */ 
#define FLASH_FLAG_EOP                 ((uint32_t)(1 << 0))  		/* End of operation */
#define FLASH_FLAG_OPERR               ((uint32_t)(1 << 1))  		/* Operation error */
#define FLASH_FLAG_WRPERR              ((uint32_t)(1 << 4)) 	 	/* Write protected */
#define FLASH_FLAG_PGAERR              ((uint32_t)(1 << 5)) 	 	/*Programming alignment error */
#define FLASH_FLAG_PGPERR              ((uint32_t)(1 << 6)) 	 	/*Programming parallelism error */
#define FLASH_FLAG_PGSERR              ((uint32_t)(1 << 7)) 	 	/*Programming Sequence error */
#define FLASH_FLAG_BSY                 ((uint32_t)(1 << 16))  	/* Busy */ 


/** @brief Unlock FLASH
 *
 *  @param none
 *
 *  @return void
 */
void FLASHUnlock(void);

/** @brief Read FLASH
 *
 *  @param startAddress The start address of FLASH to be read
 *  @param endAddress The end address of FLASH to be read
 *
 *  @return void
 */
void FLASHRead(uint32_t startAddress, uint32_t endAddress);

/** @brief Erase FLASH
 *
 *  @param none
 *
 *  @return void
 */
void FLASHEraseSector(void);

/** @brief Write to FLASH
 *
 *  @param startAddress The start address of FLASH to be written
 *  @param endAddress The end address of FLASH to be written
 *  @param buffer The array of data to be written
 *
 *  @return void
 */
void FLASHWrite(uint32_t startAddress, uint32_t endAddress, uint8_t buffer[]);

/** @brief Convert 2 characters to hex
 *
 *  @param char1 Firt character of the byte
 *  @param char2 Second character of the byte
 *
 *  @return uint8_t The converted byte
 */
uint8_t byteInterpret(uint8_t char1, uint8_t char2);

/** @brief Convert a character array into a hex array
 *
 *  @param charArray The character array
 *  @param hexArray The hex array
 *  @param charArrayLength The length of the character array
 *
 *  @return uint32_t The length of converted character array
 */
uint32_t charArrayToHexArray(uint8_t charArray[], uint8_t hexArray[], uint32_t charArrayLength);

#endif 
