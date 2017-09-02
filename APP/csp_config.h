/**===================== CSP Configuration Header ============================
 *
 * Copyright (C) 2013 DJI Innovations. All rights reserved.
 *  
 * @Date    :    27. Dec 2013
 * @Revision:    V1.00
 * @Author  :    Leo Zhou (leo.zhou@dji.com)
 * @Project :    DJI Vision Dept. VL200 Project
 *
 * ============================================================================ */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __CSP_CONFIG_H__
#define __CSP_CONFIG_H__

#include "stm32f4xx.h"
#include "bsp_config.h"

// <h> Configuration File Option
//   <o> Configuration Option <0=> Without Header File
//                            <1=> Use Header File
#define HeaderFileUsing          1
// </h>

// <h> System Clock Configuration ( F(sys) = ((F(hse) / PLLm) * PLLn) / PLLp )
/* ==================== System Clock Parameter Setting ====================== */
//   <o> External Oscillator Frequency (F(HSE))
#define HSE_Clock                12000000UL
//   <o> PLLM (PLLm: Division factor for the main PLL)
#define PLL_M_FACTOR             12
//   <o> PLLN (PLLn: Multiplication factor for the main PLL)
#define PLL_N_MULT_FACTOR        336
//   <o> PLLP (PLLp: Division factor for the main system clock)
#define PLL_P_SYSFACTOR          2
//   <o> PLLQ (PLLp: Division factor for USB OTG FS, SDIO and RNG)
#define PLL_Q_FACTOR             7

/* ==================== AHB\APB1\APB2 Parameter Setting ====================== */
#define HCLK_DIV_SEL(n)              \
    ((n = 0) ? RCC_CFGR_HPRE_DIV1   :\
     (n = 1) ? RCC_CFGR_HPRE_DIV2   :\
     (n = 2) ? RCC_CFGR_HPRE_DIV4   :\
     (n = 3) ? RCC_CFGR_HPRE_DIV8   :\
     (n = 4) ? RCC_CFGR_HPRE_DIV16  :\
     (n = 5) ? RCC_CFGR_HPRE_DIV64  :\
     (n = 6) ? RCC_CFGR_HPRE_DIV128 :\
     (n = 7) ? RCC_CFGR_HPRE_DIV256 :\
     (n = 8) ? RCC_CFGR_HPRE_DIV512 :\
     NULL)

//   <o> HCLK_DIV (AHB Clock Division Factor)   <0=> DIV_001
//                                              <1=> DIV_002  
//                                              <2=> DIV_004
//                                              <3=> DIV_008
//                                              <4=> DIV_016
//                                              <5=> DIV_064
//                                              <6=> DIV_128
//                                              <7=> DIV_256
//                                              <8=> DIV_512
#define HCLK_DIV_ID                     0

#if   ( HCLK_DIV_ID == 0 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV1
#elif ( HCLK_DIV_ID == 1 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV2
#elif ( HCLK_DIV_ID == 2 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV4
#elif ( HCLK_DIV_ID == 3 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV8
#elif ( HCLK_DIV_ID == 4 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV16
#elif ( HCLK_DIV_ID == 5 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV64
#elif ( HCLK_DIV_ID == 6 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV128
#elif ( HCLK_DIV_ID == 7 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV256
#elif ( HCLK_DIV_ID == 8 )
    #define HCLK_DIV_FACTOR             RCC_CFGR_HPRE_DIV512
#endif


#define PCLK2_DIV_SEL(n)              \
    ((n = 0) ? RCC_CFGR_PPRE2_DIV1   :\
     (n = 1) ? RCC_CFGR_PPRE2_DIV2   :\
     (n = 2) ? RCC_CFGR_PPRE2_DIV4   :\
     (n = 3) ? RCC_CFGR_PPRE2_DIV8   :\
     (n = 4) ? RCC_CFGR_HPRE2_DIV16  :\
     NULL)
//   <o> PCLK2_DIV (APB2 Clock Division Factor) <0=> DIV_001
//                                              <1=> DIV_002
//                                              <2=> DIV_004
//                                              <3=> DIV_008
//                                              <4=> DIV_016
#define PCLK2_DIV_ID                    1
#if   ( PCLK2_DIV_ID == 0 )
    #define PCLK2_DIV_FACTOR            RCC_CFGR_PPRE2_DIV1
#elif ( PCLK2_DIV_ID == 1 )
    #define PCLK2_DIV_FACTOR            RCC_CFGR_PPRE2_DIV2
#elif ( PCLK2_DIV_ID == 2 )
    #define PCLK2_DIV_FACTOR            RCC_CFGR_PPRE2_DIV4
#elif ( PCLK2_DIV_ID == 3 )
    #define PCLK2_DIV_FACTOR            RCC_CFGR_PPRE2_DIV8
#elif ( PCLK2_DIV_ID == 4 )
    #define PCLK2_DIV_FACTOR            RCC_CFGR_PPRE2_DIV16
#endif

#define PCLK1_DIV_SEL(n)              \
    ((n = 0) ? RCC_CFGR_PPRE1_DIV1   :\
     (n = 1) ? RCC_CFGR_PPRE1_DIV2   :\
     (n = 2) ? RCC_CFGR_PPRE1_DIV4   :\
     (n = 3) ? RCC_CFGR_PPRE1_DIV8   :\
     (n = 4) ? RCC_CFGR_HPRE1_DIV16  :\
     NULL)
//   <o> PCLK1_DIV (APB1 Clock Division Factor) <0=> DIV_001
//                                              <1=> DIV_002
//                                              <2=> DIV_004
//                                              <3=> DIV_008
//                                              <4=> DIV_016
#define PCLK1_DIV_ID                    2
#if   ( PCLK1_DIV_ID == 0 )
    #define PCLK1_DIV_FACTOR            RCC_CFGR_PPRE1_DIV1
#elif ( PCLK1_DIV_ID == 1 )
    #define PCLK1_DIV_FACTOR            RCC_CFGR_PPRE1_DIV2
#elif ( PCLK1_DIV_ID == 2 )
    #define PCLK1_DIV_FACTOR            RCC_CFGR_PPRE1_DIV4
#elif ( PCLK1_DIV_ID == 3 )
    #define PCLK1_DIV_FACTOR            RCC_CFGR_PPRE1_DIV8
#elif ( PCLK1_DIV_ID == 4 )
    #define PCLK1_DIV_FACTOR            RCC_CFGR_PPRE1_DIV16
#endif


// </h>

/* ======================== Clock Tree Definition ========================== */

#define System_Clock_Frequency   (( HSE_Clock / PLL_M_FACTOR ) * PLL_N_MULT_FACTOR ) / PLL_P_SYSFACTOR
#define AHB_Clock_Frequency       ( System_Clock_Frequency / ( 1 << HCLK_DIV_ID  ))
#define APB1_Clock_Frequency      ( System_Clock_Frequency / ( 1 << PCLK2_DIV_ID ))
#define APB2_Clock_Frequency      ( System_Clock_Frequency / ( 1 << PCLK1_DIV_ID ))

#if ( HeaderFileUsing == 1 )
    #define __USE_CONFIG_HEADER
#endif

#endif
// <<< end of configuration section >>>
