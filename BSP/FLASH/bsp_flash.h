#ifndef __BSP_FLASH_H__
#define __BSP_FLASH_H__

#include "stm32f4xx.h"
#include "stdio.h"
#include "stm32f4xx_flash.h"

/* Flash Page Definition --------------------------------------------------- */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector  0,  16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector  1,  16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector  2,  16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector  3,  16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector  4,  64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector  5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector  6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector  7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector  8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector  9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define LoaderFlagBase                  0x08007410 

#define APPLICATION_ADDRESS     ADDR_FLASH_SECTOR_4
#define PARAM_BASE          	ADDR_FLASH_SECTOR_3  //(uint32_t)0x08008000
#define MD5_SECTOR              PARAM_BASE + (uint32_t)0x00
#define FW_LENGTH_SECTOR        PARAM_BASE + (uint32_t)0x10
#define IAP_COUNT_SECTOR        PARAM_BASE + (uint32_t)0x14
#define RUN_READY_FLAG          PARAM_BASE + (uint32_t)0x18


void            BSP_Flash_WriteHalfWord         (uint32_t FlashPageAddr, uint16_t FlashSectorIndex, int16_t *HalfWord_Content, uint16_t Length);
void            BSP_Flash_ReadHalfWord          (uint32_t FlashPageAddr, int16_t *RD_FlashBuffer, uint16_t Length);
static uint32_t GetSector                       (uint32_t Address);
uint16_t        Flash_Write32BitData            (uint32_t address, uint16_t length, uint32_t* data_32);
void            Flash_Read32BitData             (uint32_t address, uint16_t length, uint32_t* data_32);
void            Flash_EraseAddrSector(uint32_t address);


#endif

