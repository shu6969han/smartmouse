#include "bsp_flash.h"

void BSP_Flash_WriteHalfWord( uint32_t FlashPageAddr, uint16_t FlashSectorIndex, int16_t *HalfWord_Content, uint16_t Length  );
void BSP_Flash_ReadHalfWord ( uint32_t FlashPageAddr, int16_t *RD_FlashBuffer, uint16_t Length );

/**
  * @brief  Gets the sector of a given address
  * @param  Address: Flash address
  * @retval The sector of a given address
  */
  
#define USE_BUFF_CCM  
#define CCM_BASE            0x10000000
#define BUFF_FLASH_BASE     CCM_BASE + 0x10000
#define BUFF_FLASH_SIZE     0x4000                 //16k bytes

#ifdef USE_BUFF_CCM
    uint8_t Buff_Flash[BUFF_FLASH_SIZE]  __attribute__((at(BUFF_FLASH_BASE )));
#endif


static uint32_t GetSector(uint32_t Address)
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
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }
    return sector;
}



void BSP_Flash_WriteHalfWord( uint32_t FlashPageAddr, uint16_t FlashSectorIndex, int16_t *HalfWord_Content, uint16_t Length  ) {

    uint16_t HalfWord_Count = 0;
    uint32_t PageAddr       = 0;

    PageAddr       = FlashPageAddr;
    
    FLASH_Unlock();
    FLASH_EraseSector( FlashSectorIndex, VoltageRange_3 );

    for( HalfWord_Count = 0; HalfWord_Count < Length; HalfWord_Count ++) {
        FLASH_ProgramHalfWord( PageAddr, *HalfWord_Content );
        PageAddr += 2;                                                      /* Each address is filled with a byte, so address should be added by 2 if it is programmed with half-word */
        HalfWord_Content ++;
    }

    FLASH_Lock();
}

void BSP_Flash_ReadHalfWord( uint32_t FlashPageAddr, int16_t *RD_FlashBuffer, uint16_t Length ) {

    uint16_t HalfWord_Count = 0;
    uint32_t PageAddr       = 0;

    PageAddr = FlashPageAddr;

    FLASH_Unlock();

    for( HalfWord_Count = 0; HalfWord_Count < Length; HalfWord_Count ++ ) {
        *RD_FlashBuffer = *((uint16_t*)(PageAddr));
        PageAddr += 2;
        RD_FlashBuffer ++;
    }

    FLASH_Lock();
    
}

u16 Flash_Write32BitData(uint32_t address, uint16_t length, uint32_t* data_32)
{
	uint16_t StartSector, EndSector,i;
	FLASH_Unlock(); //unlock first
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	StartSector = GetSector(address);  //get FLASH Sector number
	EndSector = GetSector(address+4*length);
	for (i = StartSector; i < EndSector; i += 8)  //add 8 per operation
	{
		if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE) while (1); //infinite loop when error 
	}
	for(i=0; i<length; i++)
	{
		if (FLASH_ProgramWord(address, data_32[i]) == FLASH_COMPLETE)   //put DATA_32 into address
		{
		    
		    if (*(uint32_t*)address != data_32[i])
      		{
        		/* Flash content doesn't match SRAM content */
        		return(1);
      		}
				address = address + 4; //32bit = 4 bytes
		}
		else
		{ 
			while (1);
		}
	}
	FLASH_Lock();  //read op can be executed when flash locked
	return (0);
}

/****************************************************************************
* Function:read length of 32bit data
* Input: address
*        length
*        int32_* data_32 : output data pointer
* Output:?
* Note:?
* How to use:?
****************************************************************************/
void Flash_Read32BitData(uint32_t address, uint16_t length, uint32_t* data_32)
{
	uint8_t i;
	for(i=0; i<length; i++)
	{
		data_32[i]=*(__IO int32_t*)address;
		address=address + 4;
	}
}


void Flash_EraseAddrSector(uint32_t address)
{
	uint16_t SectorNum;
	SectorNum = GetSector(address);
	FLASH_Unlock(); 
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	if (FLASH_EraseSector(SectorNum, VoltageRange_3) != FLASH_COMPLETE) while (1); //infinite loop when error 
	FLASH_Lock(); 
}

