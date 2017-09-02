/**===================== BSP Configuration Header ============================
 *
 * Copyright (C) 2013 DJI Innovations. All rights reserved.
 *  
 * @Date    :    27. Dec 2013
 * @Revision:    V1.00
 * @Author  :    Leo Zhou (leo.zhou@dji.com)
 * @Project :    DJI Vision Dept. VL200 Project
 *
 * ============================================================================ */
 
// TODO: To organize the whole project and add essential configuration options.

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __BSP_CONFIG_H__
#define __BSP_CONFIG_H__

#include "stm32f4xx.h"
#include <stdbool.h>

#define CFG_HARDWARE_VERSION    "WM610_VL200_V4"        /*!< most 16 Bytes include '\0' */
#define CFG_FIRMWARE_VERSION_BYTE1   1
#define CFG_FIRMWARE_VERSION_BYTE2   0
#define CFG_FIRMWARE_VERSION_BYTE3   0
#define CFG_FIRMWARE_VERSION_BYTE4   1
#define CFG_FIRMWARE_VERSION    ((CFG_FIRMWARE_VERSION_BYTE1<<24)|(CFG_FIRMWARE_VERSION_BYTE2<<16)|(CFG_FIRMWARE_VERSION_BYTE3<<8)|(CFG_FIRMWARE_VERSION_BYTE4))

// <h> Hardware Board Configuration
// <e> Board Version Configuration
//  <o> Board Version Selection <0=> Old Board ( 8MHz External Oscillator)
//                              <1=> New Board (12MHz External Oscillator)
#define __BOARD_VERSION          1
#if ( __BOARD_VERSION == 1 ) 
    #define __NEW_BOARD__
#else
    #define __OLD_BOARD__
#endif
// </e>
// </h>

// <h> Communication Platform (A2 or NAZA)
// <e> Communication Type
//  <i> Please refer to "New Communication Protocol for A2" for more information
//  <o> Communication Platform Selection <0=> NAZA Platform (Old CAN Protocol)
//                                       <1=> A2 Platform (New CAN Protocol)
//                                       <2=> Unified Platform (Unified Protocol)
#define __COMM_PLATFORM_VERSION  2
#if (__COMM_PLATFORM_VERSION == 0)
    #define __OLD_CAN_PROTOCOL__
#elif (__COMM_PLATFORM_VERSION == 1)
    #define __NEW_CAN_PROTOCOL__
#elif (__COMM_PLATFORM_VERSION == 2)
    #define __UNIFIED_PROTOCOL__
#endif
// </e>
// </h>

// <h> GPS Parameter
//  <i> Here defines the type of the GPS
//  <e> GPS Type Selection
//      <o> GPS Type <0=> NAZA Reform uBlox GPS (old package with new protocol in NAZA reform)
//                   <1=> NAZA Old uBlox GPS (old package with old protocol)
//                   <2=> A2 Glonass GPS Format (new package with new protocol)
#define __GPS_VERSION_NBR     0
#if   (__GPS_VERSION_NBR == 0)
    #define __NAZA_REFORM_UBLOX_GPS__
#elif (__GPS_VERSION_NBR == 1)
    #define __NAZA_OLD_UBLOX_GPS__
#elif (__GPS_VERSION_NBR == 2)
    #define __A2_GLONASS_GPS__
#endif
//  </e>
//      <o> Use VL200 to simulate GPS <0=> Disable
//                                    <1=> Enable
#define __SIM_GPS_FLAG        0
#if   (__SIM_GPS_FLAG == 1)
    #define __SIM_GPS_ENABLE__
#endif
// </h>

/** @DMAChannelDistribution ----------------------------------------------------------- */
/** @DCMI:   DMA2_CHANNEL1_STREAM1 (DCMI   RX)
    @USART1: DMA2_CHANNEL4_STREAM7 (USART1 TX)  <Optional for Debug>
    @UART4:  DMA1_CHANNEL4_STREAM4 (UART4  TX)
    @USART3: DMA1_CHANNEL4_STREAM3 (USART3 TX)
 **------------------------------------------------------------------------------------ */

typedef enum {
    FALSE  = 0,
    TRUE   = 1,
    False  = 0,
    True   = 1
} General_OP_Status_TypeDef;

/* Image Buffer Settings --------------------------------------------------------------- */
#define __USE_THREE_IMAGE
// #define __USE_FOUR_IMAGE

/* Image Size Settings For Optical Flow Algorithm */
/* User-specified settings ---------------------- */
#define OPT_IMAGE_WIDTH             120u
#define OPT_IMAGE_HEIGHT            120u
#define OPT_IMAGE_COLUMN_BIN        2u
#define OPT_IMAGE_ROW_BIN           2u


/* Different Transmission Target and Setting ------------------------------------------ */
#define PC                         
//#define MATLAB                     
//#define CONTROLLER  

#if defined(PC)
    #define TIM5_Report_Period     20000
#elif defined(MATLAB)
    #define TIM5_Report_Period     50000
#else
    #define TIM5_Report_Period     33000
#endif

/* Gyroscope and accelerometer configuration */
#define MPU6050

/* CAN Communication Definition */
#define NAZA_Platform
// #define A2_Platform


typedef enum {
    PC_USART3_DMA_DEPTH         = 44,
    MATLAB_USART3_DMA_DEPTH     = 32,
    CONTROLLER_USART3_DMA_DEPTH = 39
} USART3_DMA_DEPTH_TypeDef;

#define APB1_Clock                                      SystemCoreClock / 4
#define APB2_Clock                                      SystemCoreClock / 2
#define AHB_Clock                                       SystemCoreClock

#define TIM1_RSV_Prescaler                             (uint16_t)((APB2_Clock * 2) / 1000000 - 1)
#define TIM2_IR_Prescaler                              (uint16_t)((APB1_Clock * 2) / 4000000 - 1)
#define TIM3_Ultra_Prescaler                           (uint16_t)((APB1_Clock * 2) / 1000000 - 1)

#if defined (__NEW_BOARD__)
#define TIM3_CAN_Process_Prescaler                     (uint16_t)((APB1_Clock * 2) / 10000   - 1)
#endif

#define TIM4_Statis_Prescaler                          (uint16_t)((APB1_Clock * 2) / 10000   - 1)
#define TIM5_COM_Prescaler                             (uint16_t)((APB1_Clock * 2) / 1000000 - 1) 
#define TIM7_I2C_DMA_Prescaler                         (uint16_t)((APB1_Clock * 2) / 1000000 - 1)
#define TIM8_System_Prescaler                          (uint16_t)((APB2_Clock * 2) / 1000000 - 1)


#define I2C2_EV_PreemptionPriority                      0
#define I2C2_EV_SubPriority                             1

#define I2C2_ERR_PreemptionPriority                     0
#define I2C2_ERR_SubPriority                            0

#define I2C2_DMA_Write_PreemptionPriority				0
#define I2C2_DMA_Write_SubPriority						2

#define I2C2_DMA_Read_PreemptionPriority                0
#define I2C2_DMA_Read_SubPriority                       2

#define DCMI_DMA_PreemptionPriority						0      /* MT9V034 */
#define DCMI_DMA_SubPriority							3

#define DCMI_PreemptionPriority						    0      /* Camera Priority */
#define DCMI_SubPriority								4

#define Gyro_DMA_Request_PreemptionPriority             0      /* TIMER7 */
#define Gyro_DMA_Request_SubPriority                    5

#define CAN1_PreemptionPriority							0
#define CAN1_SubPriority								5

#define CAN1_MsgProcPreemptionPriority                  0
#define CAN1_MsgProcSubPriority                         7

#if defined(__NEW_BOARD__)
    #define USART1_Ultrasonic_PreemptionPriority         	0      /* Ultrasonic: USART1 */
    #define USART1_Ultrasonic_SubPriority					6
#elif defined(__OLD_BOARD__)
    #define EXTI0_Ultrasonic_PreemptionPriority         	0      /* Ultrasonic: USART1 */
    #define EXTI0_Ultrasonic_SubPriority					6
#endif

#define USART1_PreemptionPriority						1
#define USART1_SubPriority								0
#define USART1_TX_DMA_PreemptionPriority    			1
#define USART1_TX_DMA_SubPriority						7

#define USART3_TX_DMA_PreemptionPriority    			1
#define USART3_TX_DMA_SubPriority						1
#define USART3_RX_PreemptionPriority                    0
#define USART3_RX_SubPriority                           7

#define UART4_PreemptionPriority						1      /* Image Report Priority */
#define UART4_SubPriority								2
#define UART4_TX_DMA_PreemptionPriority    		    	1
#define UART4_TX_DMA_SubPriority						3

#define USART2_PreemptionPriority						1      /* TODO: */
#define USART2_SubPriority								2

#define USART2_TX_DMA_PreemptionPriority			    1
#define USART2_TX_DMA_SubPriority						3

#ifdef __OLD_BOARD__
#define EXP_PWM_PreemptionPriority						1      /* EXTI */
#define EXP_PWM_SubPriority								4
#endif

#define TIM8_EXP_Load_PreemptionPriority                1
#define TIM8_EXP_Load_SubPriority                       4

#define COM_timer_PreemptionPriority					1      /* Timer 5 */
#define COM_timer_SubPriority							5

#define IR_PWM_PreemptionPriority						1      /* Timer 2 */
#define IR_PWM_SubPriority								6

#define Sys_timer_PreemptionPriority					1      /* SysTick: Timer 8 1us */
#define Sys_timer_SubPriority							6

#define Statistic_PreemptionPriority                    1
#define Statistic_SubPriority                           6

#endif


