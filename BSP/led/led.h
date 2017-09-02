#ifndef __LED_H
#define __LED_H
#include <stm32f4xx.h>
#include "system.h"

//#define _VCCGND
#ifdef _VCCGND
#define LED0 PBout(9)	// DS0
#else
//LED端口定义
#define LED0 PGout(11)	// DS0
#define LED1 PGout(10)	// DS1	 
#endif

void LED_Init(void);//初始化		

#endif
