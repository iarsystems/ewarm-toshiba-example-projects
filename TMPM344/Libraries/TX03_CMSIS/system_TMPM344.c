/**
 *******************************************************************************
 * @file    system_TMPM344.c
 * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Source File for the
 *          TOSHIBA 'TMPM344' Device Series 
 * @version V2.0.2.6
 * @date    2018/03/30
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA MICROELECTRONICS CORPORATION 2018 All rights reserved
 *******************************************************************************
 */

#include "TMPM344.h"

/*-------- <<< Start of configuration section >>> ----------------------------*/

/* Watchdog Timer (WD) Configuration */
#define WD_SETUP                1U
#define WDMOD_Val               (0x00000000UL)
#define WDCR_Val                (0x000000B1UL)

/* Clock Generator (CG) Configuration */
#define CLOCK_SETUP             1U
#define SYSCR_Val               (0x00010000UL)
#define OSCCR_Val               (0x000E0104UL) /* OSCCR<OSCSEL> = 1, OSCCR<XEN2> = 0, OSCCR<XEN1> = 1, OSCCR<PLL0ON> = 1, <EHOSCSEL> = 1 */

#define OSCSEL_BITNUM           17U             /*OSCSEL bit number is Bit 17*/
#define PLL_USE_BITNUM          0U              /*PLLON bit number is bit 0*/
#define PLLON_BITNUM            2U              /*PLLON bit number is bit 2*/

#define CG_8M_MUL_8_FPLL        (0x00005A1EUL<<1U)
#define CG_8M_MUL_10_FPLL       (0x00006A26UL<<1U)
#define CG_8M_MUL_16_FPLL       (0x00005A3DUL<<1U)
#define CG_8M_MUL_20_FPLL       (0x00006A4DUL<<1U)

#define CG_10M_MUL_8_FPLL       (0x00005A1EUL<<1U)
#define CG_10M_MUL_10_FPLL      (0x00006A26UL<<1U)
#define CG_10M_MUL_16_FPLL      (0x00005A3DUL<<1U)
#define CG_10M_MUL_20_FPLL      (0x00006A4DUL<<1U)
#define CG_10M_MUL_22_FPLL      (0x00006A55UL<<1U)

#define CG_16M_MUL_8_FPLL       (0x00003A1DUL<<1U)
#define CG_16M_MUL_10_FPLL      (0x00002925UL<<1U)

#define CG_20M_MUL_8_FPLL       (0x00003A1DUL<<1U)
#define CG_20M_MUL_10_FPLL      (0x00002925UL<<1U)

#define PLLSEL_Ready            CG_10M_MUL_22_FPLL
#define PLLSEL_Val              (PLLSEL_Ready|1U)
#define PLLSEL_MASK             0x0000FFFEUL

/*-------- <<< End of configuration section >>> ------------------------------*/

/*-------- DEFINES -----------------------------------------------------------*/
/* Define clocks */
#define OSC_8M                  ( 8000000UL)
#define OSC_10M                 (10000000UL)
#define OSC_16M                 (16000000UL)
#define OSC_20M                 (20000000UL)
#define EXTALH                  OSC_10M     /* External high-speed oscillator freq */
#define XTALH                   OSC_10M     /* Internal high-speed oscillator freq */

/* Configure Warm-up time */
#define HZ_1M                   1000000UL
#define WU_TIME_EXT             5000UL          /* warm-up time for EXT is 5ms   */
#define WU_TIME_PLL             100UL           /* warm-up time for PLL is 100us */
#define OSCCR_WUODR_MASK        (0x000FFFFFUL)
#define OSCCR_WUODR_EXT         ((WU_TIME_EXT * EXTALH / HZ_1M /16U) << 20U) /* OSCCR<WUPODR11:0> = warm-up time(us) * EXTALH(MHz) / 16 */
#define OSCCR_WUODR_PLL         ((WU_TIME_PLL * EXTALH / HZ_1M /16U) << 20U)

#if (CLOCK_SETUP)               /* Clock(external) Setup */
/* Determine core clock frequency according to settings */
/* System clock is high-speed clock*/
#if (OSCCR_Val & (1U<<OSCSEL_BITNUM))
  #define CORE_TALH (EXTALH)
#else
  #define CORE_TALH (XTALH)
#endif

#if ((PLLSEL_Val & (1U<<PLL_USE_BITNUM)) && (OSCCR_Val & (1U<<PLLON_BITNUM)))      /* If PLL selected and enabled */
  #if (CORE_TALH == OSC_8M)                            /* If input is 8MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == (CG_8M_MUL_8_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 8U )            /* output clock is 64MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_8M_MUL_10_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 10U )           /* output clock is 80MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_8M_MUL_16_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 16U )           /* output clock is 128MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_8M_MUL_20_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 20U )           /* output clock is 160MHz */     
    #else                                                    /* fc -> reserved */
      #define __CORE_CLK_FPLL   (0U)
    #endif                                                   /* End input is 8MHz */
  #elif (CORE_TALH == OSC_10M)                         /* If input is 10MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == (CG_10M_MUL_8_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 8U )            /* output clock is 80MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_10M_MUL_10_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 10U )           /* output clock is 100MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_10M_MUL_16_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 16U )           /* output clock is 160MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_10M_MUL_20_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 20U )           /* output clock is 200MHz */      
    #elif ((PLLSEL_Val & PLLSEL_MASK) == (CG_10M_MUL_22_FPLL))
      #define __CORE_CLK_FPLL   (CORE_TALH * 22U )           /* output clock is 220MHz */      
    #else                                                    /* fc -> reserved */
      #define __CORE_CLK   (0U)
    #endif                                                   /* End input is 10MHz */
  #elif (CORE_TALH == OSC_16M)                         /* If input is 16MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == CG_16M_MUL_8_FPLL)
      #define __CORE_CLK_FPLL   (CORE_TALH * 8U )            /* output clock is 128MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == CG_16M_MUL_10_FPLL)
      #define __CORE_CLK_FPLL   (CORE_TALH * 10U )           /* output clock is 160MHz */
    #else                                                    /* fc -> reserved */
      #define __CORE_CLK_FPLL   (0U)
    #endif                                                   /* End input is 16MHz */
  #elif (CORE_TALH == OSC_20M)                         /* If input is 20MHz */
    #if ((PLLSEL_Val & PLLSEL_MASK) == CG_20M_MUL_8_FPLL)
      #define __CORE_CLK_FPLL   (CORE_TALH * 8U )            /* output clock is 160MHz */
    #elif ((PLLSEL_Val & PLLSEL_MASK) == CG_20M_MUL_10_FPLL)
      #define __CORE_CLK_FPLL   (CORE_TALH * 10U )           /* output clock is 200MHz */
    #else                                                    /* fc -> reserved        */
      #define __CORE_CLK_FPLL   (0U)
    #endif                                                   /* End input is 20MHz    */
  #else                                                /* input clock not known */
    #define __CORE_CLK_FPLL   (0U)
    #error "Core Oscillator Frequency invalid!"
  #endif                                                /* End switch input clock */
  #define __CORE_CLK          (__CORE_CLK_FPLL / 4U)    /* fPLL is divided by 4*/
#else
  #define __CORE_CLK   (CORE_TALH)
#endif

#if   ((SYSCR_Val & 7U) == 0U)                          /* Gear -> fc             */
  #define __CORE_SYS   (__CORE_CLK)
#elif ((SYSCR_Val & 7U) == 4U)                          /* Gear -> fc/2           */
  #define __CORE_SYS   (__CORE_CLK / 2U)
#elif ((SYSCR_Val & 7U) == 5U)                          /* Gear -> fc/4           */
  #define __CORE_SYS   (__CORE_CLK / 4U)
#elif ((SYSCR_Val & 7U) == 6U)                          /* Gear -> fc/8           */
  #define __CORE_SYS   (__CORE_CLK / 8U)
#elif ((SYSCR_Val & 7U) == 7U)                          /* Gear -> fc/16          */
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
{                               /* Get Core Clock Frequency */
    uint32_t CoreClock = 0U;
    uint32_t CoreClockInput = 0U;
    /* Determine clock frequency according to clock register values */
    /* System clock is high-speed clock */
    if (TSB_CG_OSCCR_OSCSEL) {  /* If system clock is External high-speed oscillator freq */
        CoreClock = EXTALH;
    } else {                    /* If system clock is Internal high-speed oscillator freq */
        CoreClock = XTALH;
    }
    if (TSB_CG_PLLSEL_PLL0SEL && TSB_CG_OSCCR_PLL0ON) {                        /* If PLL enabled  */
        if (CoreClock == OSC_8M) {                                          /* If input is 8MHz */
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_8M_MUL_8_FPLL) {     
                CoreClockInput = CoreClock * 8U;                             /* output clock is 64MHz */
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_8M_MUL_10_FPLL) {
                CoreClockInput = CoreClock * 10U;                            /* output clock is 80MHz */                
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_8M_MUL_16_FPLL) {
                CoreClockInput = CoreClock * 16U;                            /* output clock is 128MHz */                
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_8M_MUL_20_FPLL) {
                CoreClockInput = CoreClock * 20U;                            /* output clock is 160MHz */                
            } else {
                CoreClockInput = 0U;                                         /* fc -> reserved            */
            }
        } else if (CoreClock == OSC_10M) {                                  /* If input is 10MHz */
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_10M_MUL_8_FPLL) {     
                CoreClockInput = CoreClock * 8U;                             /* output clock is 80MHz */
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_10M_MUL_10_FPLL) {
                CoreClockInput = CoreClock * 10U;                            /* output clock is 100MHz */                
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_10M_MUL_16_FPLL) {
                CoreClockInput = CoreClock * 16U;                            /* output clock is 160MHz */                
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_10M_MUL_20_FPLL) {
                CoreClockInput = CoreClock * 20U;                            /* output clock is 200MHz */               
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_10M_MUL_22_FPLL) {
                CoreClockInput = CoreClock * 22U;                            /* output clock is 220MHz */               
            } else {
                CoreClockInput = 0U;                                         /* fc -> reserved */
            }
        } else if (CoreClock == OSC_16M) {                                  /* If input is 16MHz */
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_16M_MUL_8_FPLL) {
                CoreClockInput = CoreClock * 8U;                             /* output clock is 128MHz */
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_16M_MUL_10_FPLL) {
                CoreClockInput = CoreClock * 10U;                            /* output clock is 160MHz */               
            } else {
                CoreClockInput = 0U;                                         /* fc -> reserved */
            }
        } else if (CoreClock == OSC_20M) {                                  /* If input is 20MHz */
            if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_20M_MUL_8_FPLL) {
                CoreClockInput = CoreClock * 8U;                             /* output clock is 160MHz */               
            } else if ((TSB_CG->PLLSEL & PLLSEL_MASK) == CG_20M_MUL_10_FPLL) {
                CoreClockInput = CoreClock * 10U;                            /* output clock is 200MHz */
            } else {
                CoreClockInput = 0U;                                         /* fc -> reserved        */
            }
        } else {
            CoreClockInput = 0U;
        }
        CoreClockInput = CoreClockInput / 4U;                                /* fPLL is divided by 4*/
    } else {
        CoreClockInput = CoreClock;
    }
    switch (TSB_CG->SYSCR & 7U) {
    case 0U:
        SystemCoreClock = CoreClockInput;                                    /* Gear -> fc      */
        break;                                                              
    case 1U:
    case 2U:
    case 3U:                                                                 /* Gear -> reserved */
        SystemCoreClock = 0U;
        break;
    case 4U:                                                                 /* Gear -> fc/2     */
        SystemCoreClock = CoreClockInput / 2U;
        break;
    case 5U:                                                                 /* Gear -> fc/4     */
        SystemCoreClock = CoreClockInput / 4U;
        break;
    case 6U:                                                                 /* Gear -> fc/8     */
        SystemCoreClock = CoreClockInput / 8U;
        break;
    case 7U:                                                                 /* Gear -> fc/16     */
        if (CoreClockInput >= OSC_16M){
        SystemCoreClock = CoreClockInput / 16U;
      }else{
      	SystemCoreClock = 0U;
      }
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
    TSB_WD->MOD = WDMOD_Val;
    if (!TSB_WD_MOD_WDTE) {     /* If watchdog is to be disabled */
        TSB_WD->CR = WDCR_Val;
    }
#endif

#if (CLOCK_SETUP)               /* Clock(external) Setup */
    TSB_CG->SYSCR = SYSCR_Val;
    TSB_CG->OSCCR &= OSCCR_WUODR_MASK;
    TSB_CG->OSCCR |= OSCCR_WUODR_EXT;
    TSB_CG_OSCCR_EHOSCSEL = 1U;
    TSB_CG_OSCCR_XEN1 = 1U;
    TSB_CG_OSCCR_WUPSEL2 = 1U;
    TSB_CG_OSCCR_WUEON = 1U;
    TSB_CG->PLLSEL = PLLSEL_Ready;
    while (TSB_CG_OSCCR_WUEF) {
    }                           /* Warm-up */
    TSB_CG_OSCCR_OSCSEL = 1U;
    
    while (TSB_CG_RSTFLG_OSCFLF==0x0U) {}

    TSB_CG_OSCCR_XEN2 = 0U;

    TSB_CG->OSCCR &= OSCCR_WUODR_MASK;
    TSB_CG->OSCCR |= OSCCR_WUODR_PLL;
    TSB_CG_OSCCR_PLL0ON = 1U;    /* PLL enabled */
    TSB_CG_OSCCR_WUEON = 1U;
    while (TSB_CG_OSCCR_WUEF) {
    }                           /* Warm-up */

    TSB_CG->PLLSEL = PLLSEL_Val;
#endif
}
