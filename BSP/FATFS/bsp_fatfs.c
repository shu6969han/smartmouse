#include "bsp_fatfs.h"
#define SD_BLOCK_SIZE 512

DWORD get_fattime (void)
{
  return   ((DWORD)(2014) << 25) /* Fixed to Jan. 1, 2010 */
     | ((DWORD)8 << 21)
     | ((DWORD)13 << 16)
     | ((DWORD)14 << 11)
     | ((DWORD)30 << 5)
     | ((DWORD)0 >> 1);
}

DSTATUS disk_initialize (BYTE drv)
{
  while(SD_Init()!=0);  // SD_Init?SD????
  return 0;
}

DSTATUS disk_status (
 BYTE drv   /* Drive number (always 0) */
)
{
//    DSTATUS stat;
//	int result;
//    result = SD_GetState();

//    if (result != SD_CARD_ERROR)
//        stat = RES_OK;
//    else
//        stat = RES_ERROR;
//    
//    return stat;
    return RES_OK;
}

DRESULT disk_ioctl (
 BYTE drv,  /* Physical drive nmuber (0) */
 BYTE ctrl,  /* Control code */
 void *buff  /* Buffer to send/receive control data */
)
{
     DRESULT res;
  //*(DWORD*)buff = 128; 
    switch(ctrl)
    {
    case GET_BLOCK_SIZE:
        *(DWORD*)buff = 512;
        res = RES_OK;
        break;

    case GET_SECTOR_COUNT:
        *(DWORD*)buff = 1000/512*1000*1000*4;
        res = RES_OK;
        break;
    default:
        *(WORD*)buff = 512;
        res = RES_OK;
        break;
    }    
  return RES_OK; 
}
//#define CTRL_SYNC			0	/* Flush disk cache (for write functions) */
//#define GET_SECTOR_COUNT	1	/* Get media size (for only f_mkfs()) */
//#define GET_SECTOR_SIZE		2	/* Get sector size (for multiple sector size (_MAX_SS >= 1024)) */
//#define GET_BLOCK_SIZE		3	/* Get erase block size (for only f_mkfs()) */
//#define CTRL_ERASE_SECTOR	4	/* Force erased a block of sectors (for only _USE_ERASE) */

DRESULT disk_read (
 BYTE drv,   /* Physical drive nmuber (0) */
 BYTE *buff,   /* Pointer to the data buffer to store read data */
 DWORD sector,  /* Start sector number (LBA) */
 UINT count   /* Sector count (1..128) */
)
{  
    DRESULT res;
    int result;
    if (count > 1) {
        result = SD_ReadMultiBlocks(buff, sector * SD_BLOCK_SIZE, SD_BLOCK_SIZE, count);
        SD_WaitReadOperation();
        while(SD_GetStatus() != SD_TRANSFER_OK);
    }
    else {
        result = SD_ReadBlock(buff, sector * SD_BLOCK_SIZE, SD_BLOCK_SIZE);
        SD_WaitReadOperation();
        while(SD_GetStatus() != SD_TRANSFER_OK);
    }

    if (result != SD_OK) {
        res = RES_ERROR;
    }
    else
        res = RES_OK;
    // translate the reslut code here

    return res;
}

DRESULT disk_write (
 BYTE drv,   /* Physical drive nmuber (0) */
 const BYTE *buff, /* Pointer to the data to be written */
 DWORD sector,  /* Start sector number (LBA) */
 UINT count   /* Sector count (1..128) */
)
{
    DRESULT res;
    int result; 
    static uint32_t regCount = 0;
    regCount = count;
    if (count > 1) {
        
        result = SD_WriteMultiBlocks((BYTE*)buff, sector * SD_BLOCK_SIZE, SD_BLOCK_SIZE, regCount);
        SD_WaitWriteOperation();
        while(SD_GetStatus() != SD_TRANSFER_OK);

    }
    else {
        
        result = SD_WriteBlock((BYTE*)buff, sector * SD_BLOCK_SIZE, SD_BLOCK_SIZE);
        SD_WaitWriteOperation();
        while(SD_GetStatus() != SD_TRANSFER_OK);
    }
    
    if (result != SD_OK) {
        res = RES_ERROR;
    }
    else
        res = RES_OK;
    // translate the reslut code here

    return res;
}


