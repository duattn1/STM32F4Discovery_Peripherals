#include "../Inc/FLASH_driver.h"

uint32_t uwStartSector = 0;
uint32_t uwEndSector = 0;
uint32_t uwAddress = 0;
uint32_t uwSectorCounter = 0;

__IO uint32_t uwData32 = 0;
__IO uint32_t uwMemoryProgramStatus = 0;

uint8_t *utoa(const uint8_t *numbox, uint32_t num, uint32_t base){
    static uint8_t buf[32]={0};
    uint32_t i;
    uint32_t hex_num = sizeof(num) * 2;

    if(num==0){
        buf[30]='0';
        return &buf[30];
    }
    for(i=30; i >= 0&&hex_num; --hex_num,--i, num/=base)
        buf[i] = numbox [num % base];
    return buf+i+1;
}


void USART_printHex(uint32_t num){
    uint8_t *s;
    s = utoa("0123456789ABCDEF", num, 16);
    sendChar(USART3, *s);
}

void print_data(uint32_t uwStartAddress, uint32_t uwEndAddress)
{
  uint32_t uwAddress = uwStartAddress;
  int newline_count = 1;

  while (uwAddress < uwEndAddress)
  {
    uwData32 = *(__IO uint32_t*)uwAddress;
    USART_printHex(uwData32);
    if(newline_count %= 4){
      //USART1_puts(" ");
			sendChar(USART3, ' ');
		}
    else {
      //USART1_puts("\r\n");
			sendChar(USART3, 13); // \r
			sendChar(USART3, 10); // \n
		}
    uwAddress = uwAddress + 4;
    newline_count ++;
  }
  //USART1_puts("\r\n\r\n");
	sendChar(USART3, 13); // \r
	sendChar(USART3, 10); // \n
	sendChar(USART3, 13); // \r
	sendChar(USART3, 10); // \n
}


uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }
  else
  {
    sector = FLASH_Sector_11;  
  }
  return sector;
}

void FLASH_Unlock(void)
{
  if((FLASH->CR & FLASH_CR_LOCK) != 0) //RESET
  {
    /* Authorize the FLASH Registers access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
  }  
}

void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
  FLASH->SR = FLASH_FLAG;
}

void FLASH_OB_Unlock(void)
{
  if((FLASH->OPTCR & FLASH_OPTCR_OPTLOCK) != 0) //RESET
  {
    /* Authorizes the Option Byte register programming */
    FLASH->OPTKEYR = FLASH_OPT_KEY1;
    FLASH->OPTKEYR = FLASH_OPT_KEY2;
  }  
}

FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;
  
  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
  {
    flashstatus = FLASH_BUSY;
  }
  else 
  {  
    if((FLASH->SR & FLASH_FLAG_WRPERR) != (uint32_t)0x00)
    { 
      flashstatus = FLASH_ERROR_WRP;
    }
    else
    {
      if((FLASH->SR & (uint32_t)0xEF) != (uint32_t)0x00)
      {
        flashstatus = FLASH_ERROR_PROGRAM; 
      }
      else
      {
        if((FLASH->SR & FLASH_FLAG_OPERR) != (uint32_t)0x00)
        {
          flashstatus = FLASH_ERROR_OPERATION;
        }
        else
        {
          flashstatus = FLASH_COMPLETE;
        }
      }
    }
  }
  /* Return the FLASH Status */
  return flashstatus;
}



FLASH_Status FLASH_WaitForLastOperation(void)
{ 
  __IO FLASH_Status status = FLASH_COMPLETE;
   
  /* Check for the FLASH Status */
  status = FLASH_GetStatus();

  /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
     Even if the FLASH operation fails, the BUSY flag will be reset and an error
     flag will be set */
  while(status == FLASH_BUSY)
  {
    status = FLASH_GetStatus();
  }
  /* Return the operation status */
  return status;
}

void FLASH_OB_WRP1Config(uint32_t OB_WRP, FunctionalState NewState)
{ 
  FLASH_Status status = FLASH_COMPLETE;
    
  status = FLASH_WaitForLastOperation();

  if(status == FLASH_COMPLETE)
  { 
    if(NewState != DISABLE)
    {
      *(__IO uint16_t*)OPTCR1_BYTE2_ADDRESS &= (~OB_WRP);
    }
    else
    {
      *(__IO uint16_t*)OPTCR1_BYTE2_ADDRESS |= (uint16_t)OB_WRP;
    }
  }
}

void FLASH_OB_Lock(void)
{
  /* Set the OPTLOCK Bit to lock the FLASH Option Byte Registers access */
  FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
}
