/**
 *******************************************************************************
 * @file    system_TMPM311.c
 * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Source File for the
 *          TOSHIBA 'TMPM311' Device Series 
 * @version V2.0.2.1
 * @date    2014/09/01
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

#include "TMPM311.h"

/*-------- <<< Start of configuration section >>> ----------------------------*/

/* Watchdog Timer (WD) Configuration */
#define WD_SETUP                (1U)
#define WDMOD_Val               (0x00000000UL)
#define WDCR_Val                (0x000000B1UL)

/* Clock Generator (CG) Configuration */
#define CLOCK_SETUP             (1U)
#define CLKCR_Val               (0x00000000UL)
#define OSCSEL_Val              (0x00000001UL) /* Select external high-speed oscillator (EHOSC) /external clock input (EHCLKIN) */
#define OSCEN_Val               (0x00000002UL) 

#define CG_OSCEN_EHOSCEN_CLEAR               ((uint32_t)0xFFFFFFF9)
#define CG_OSCEN_EHOSCEN_EHOSC               ((uint32_t)0x00000002)
#define CG_OSCEN_EHOSCEN_EHCLKIN             ((uint32_t)0x00000004)
#define CG_OSCEN_IHOSCEN_CLEAR               ((uint32_t)0xFFFFFFFE)
#define CG_OSCEN_IHOSCEN_SET                 ((uint32_t)0x00000001)

#define CG_WUHCR_WUPT_CLEAR                  ((uint32_t)0xF000FFFF)

#define CG_OSCSTF_OSCF_IHOSC                 ((uint32_t)0x00000000)
#define CG_OSCSTF_OSCF_EHOSCEN               ((uint32_t)0x00000001)
    
#define WD_MOD_WDTE_SET                      ((uint32_t)0x00000080)

#define CG_CLKCR_GEAR_CLEAR                  ((uint32_t)0xFFFFFFFC)
#define CG_CLKCR_GEAR_0                      ((uint32_t)0x00000000)

/*-------- <<< End of configuration section >>> ------------------------------*/

/*-------- DEFINES -----------------------------------------------------------*/
/* Define clocks */
#define OSC_8M                  ( 8000000UL)
#define OSC_10M                 (10000000UL)
#define OSC_12M                 (12000000UL)
#define OSC_16M                 (16000000UL)
#define OSC_18M                 (18000000UL)
#define OSC_20M                 (20000000UL)
#define OSC_24M                 (24000000UL)
#define EXTALH                  OSC_8M     /* External high-speed oscillator freq */
//#define EXTALH                  OSC_20M     /* External high-speed oscillator freq */
#define EHCLKIN                 OSC_24M     /* External clcok input freq */
#define XTALH                   OSC_10M     /* Internal high-speed oscillator freq */

/* Configure Warm-up time */
#define HZ_1M                  (1000000UL)
#define WU_TIME_EXT            (5000UL)          /* warm-up time for EXT is 5ms   */
#define WUHCR_WUPT_EXT         ((WU_TIME_EXT * EXTALH / HZ_1M /20UL) << 16U) /* CG0WUHCR<WUPT[11:0]> = warm-up time(us) * EXTALH / 16 */

#if (CLOCK_SETUP)               /* Clock(external) Setup */
/* Determine core clock frequency according to settings */
/* System clock is high-speed clock*/
#if (OSCSEL_Val & 0x1UL)
  #if (OSCEN_Val & 0x2UL)
   #define __CORE_CLK (EXTALH)
  #elif (OSCEN_Val & 0x4UL)
   #define __CORE_CLK (EHCLKIN)
  #else  
   #define __CORE_CLK (0U)
  #endif
#elif (!(OSCSEL_Val & 0x3UL))
  #if (OSCEN_Val & 0x1UL)
   #define __CORE_CLK (XTALH)
  #else  
   #define __CORE_CLK (0U)
  #endif
#elif (OSCSEL_Val & 0x2UL)
  #if (OSCEN_Val & 0x2UL)
   #define CORE_TALH (EXTALH)
  #elif (OSCEN_Val & 0x4UL)
   #define CORE_TALH (EHCLKIN)
  #else  
   #define CORE_TALH (0U)
  #endif
#endif

#if ((CLKCR_Val & 7U) == 0U)                          /* Gear -> fc             */
  #define __CORE_SYS   (__CORE_CLK)
#elif ((CLKCR_Val & 7U) == 1U)                          /* Gear -> fc/2           */
  #define __CORE_SYS   (__CORE_CLK / 2U)
#elif ((CLKCR_Val & 7U) == 2U)                          /* Gear -> fc/4           */
  #define __CORE_SYS   (__CORE_CLK / 4U)
#elif ((CLKCR_Val & 7U) == 3U)                          /* Gear -> fc/8           */
  #define __CORE_SYS   (__CORE_CLK / 8U)
#elif ((CLKCR_Val & 7U) == 4U)                          /* Gear -> fc/16          */
  #define __CORE_SYS   (__CORE_CLK / 16U)
#else                                                   /* Gear -> reserved       */
  #define __CORE_SYS   (0U)
#endif

#else
  #define __CORE_SYS   (XTALH)
  
#endif                                                  /* clock Setup */

/* Clock Variable definitions */
uint32_t SystemCoreClock = __CORE_SYS;  /*!< System Clock Frequency (Core Clock) */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Update SystemCoreClock according register values.
 */
void SystemCoreClockUpdate(void)
{
    uint32_t CoreClock = 0U;
    uint32_t CoreClockInput = 0U;

    /* Determine clock frequency according to clock register values */
    /* System clock is high-speed clock */
    switch (TSB_CG0->OSCSTF) {
        case CG_OSCSTF_OSCF_IHOSC:
            CoreClock = XTALH;    /* fc source is Internal high-speed oscillator */
            break;
        case CG_OSCSTF_OSCF_EHOSCEN:
            if (TSB_CG0->OSCEN & CG_OSCEN_EHOSCEN_EHOSC) {
                CoreClock = EXTALH;  /* fc source is External high-speed oscillator (EHOSC) */
            } else if (TSB_CG0->OSCEN & CG_OSCEN_EHOSCEN_EHCLKIN) {
                CoreClock = EHCLKIN;  /* fc source is external clock input (EHCLKIN) */
            } else {
                /* Do nothing */
            }
            break;
        default:
            /* Do nothing */
            break;
    }
 
    switch (TSB_CG0->CLKCR & 7U) {
    case 0U:
        SystemCoreClock = CoreClockInput;                                    /* Gear -> fc  */
        break;                                                              
    case 1U:                                                                 /* Gear -> fc/2 */
        SystemCoreClock = CoreClockInput / 2U;
        break;
    case 2U:                                                                 /* Gear -> fc/4 */
        SystemCoreClock = CoreClockInput / 4U;
        break;
    case 3U:                                                                 /* Gear -> fc/8 */
        SystemCoreClock = CoreClockInput / 8U;
        break;
    case 4U:                                                                 /* Gear -> fc/16 */
        SystemCoreClock = CoreClockInput / 16U;
        break;
    default:
        SystemCoreClock = 0U;
        break;
    }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit(void)
{
#if (WD_SETUP)                  /* Watchdog Setup */
    while (TSB_WD0->FLG != 0U) {
    }                /* When writing to WDMOD or WDCR, confirm "0" of WDFLG<FLG>. */
    TSB_WD0->MOD = WDMOD_Val;
    if (!TSB_WD0_MOD_WDTE) {     /* If watchdog is to be disabled */
        TSB_WD0->CR = WDCR_Val;
    } else {
        /*Do nothing*/
    }
#endif

#if (CLOCK_SETUP)               /* Clock(external) Setup */

    /* The external high-speed oscillator(EHOSC) is used. */
    TSB_CG0->OSCEN |= CG_OSCEN_IHOSCEN_SET;	
    TSB_CG0->OSCEN &= CG_OSCEN_EHOSCEN_CLEAR;
    TSB_CG0->OSCEN |= CG_OSCEN_EHOSCEN_EHOSC;
//    TSB_CG0->OSCEN &= CG_OSCEN_IHOSCEN_CLEAR;
    TSB_CG0_WUHCR_WUCLK = 1U;
    TSB_CG0->WUHCR &= CG_WUHCR_WUPT_CLEAR;
    TSB_CG0->WUHCR |= WUHCR_WUPT_EXT;
    TSB_CG0_WUHCR_WUON = 1U;
    while (TSB_CG0_WUHCR_WUEF) {
    }                           /* Warm-up */   
    
    /* Set a division ratio of the clock gear. */
    TSB_CG0->CLKCR &= CG_CLKCR_GEAR_CLEAR;
    TSB_CG0->CLKCR |= CG_CLKCR_GEAR_0;
#endif
}
