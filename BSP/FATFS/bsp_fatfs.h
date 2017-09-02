#ifndef __BSP_FATFS_H__
#define __BSP_FATFS_H__

#include "stm32f4xx.h"
#include "stdio.h"
#include "diskio.h"
#include "ff.h"
//#include "stm32f4xx_sdio.h"
//#include "stm324xg_eval_sdio_sd.h"
#include "bsp_sdio.h"


typedef struct tagBITMAPFILEHEADER { 
WORD    bfType; 
DWORD   bfSize; 
WORD    bfReserved1; 
WORD    bfReserved2; 
DWORD   bfOffBits; 
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{ 
DWORD      biSize; 
LONG        biWidth; 
LONG        biHeight; 
WORD       biPlanes; 
WORD       biBitCount; 
DWORD      biCompression; 
DWORD      biSizeImage; 
LONG        biXPelsPerMeter; 
LONG        biYPelsPerMeter; 
DWORD      biClrUsed; 
DWORD      biClrImportant; 
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD { 
BYTE    rgbBlue; 
BYTE    rgbGreen; 
BYTE    rgbRed; 
BYTE    rgbReserved; 
} RGBQUAD;

#endif

