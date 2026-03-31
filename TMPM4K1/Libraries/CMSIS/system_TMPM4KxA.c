/**
 *******************************************************************************
 * @file    system_TMPM4KxA.c
 * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer Source File for the
 *          TOSHIBA 'TMPM4KxA' Device Series 
 * @version V0.0.0.2
 * $Date:: 2018-05-07 #$
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA MICROELECTRONICS CORPORATION 2018 All rights reserved
 *******************************************************************************
 */

#include "TMPM4KxA.h"

/*-------- <<< Start of configuration section >>> ----------------------------*/

/* Semi-Independent Watchdog Timer (SIWDT) Configuration */
#define SIWD_SETUP              (1U)                      /* 1:Disable SIWD, 0:Enable SIWD */
#define SIWDEN_Val              (0x00000000UL)            /* SIWD Disable */
#define SIWDCR_Val              (0x000000B1UL)            /* SIWD Disable code */

/* Clock Generator (CG) Configuration */
#define CLOCK_SETUP             (1U)                      /* 1:External HOSC, 0: Internal HOSC */
#define SYSCR_Val               (0x00000000UL)
#define OSCCR_Val               (0x00000102UL) /* OSCCR<IHOSC1EN> = 0, <EOSCEN> = 01, OSCCR<OSCSEL> = 1 */

#define STBYCR_Val              (0x00000000UL)

#define CG_6M_MUL_13_328_FPLL   (0x001C6535UL<<8U)      /* fPLL = 6MHz * 13.328   */
#define CG_8M_MUL_10_FPLL       (0x00246028UL<<8U)      /* fPLL = 8MHz * 10       */
#define CG_10M_MUL_8_FPLL       (0x002E6020UL<<8U)      /* fPLL = 10MHz * 8       */
#define CG_12M_MUL_6_656_FPLL   (0x0036EA1AUL<<8U)      /* fPLL = 12MHz * 6.656   */

#define CG_6M_MUL_20_FPLL1		(0x001C5028UL<<8U)		/* fPLL = 6MHz * 20 	  */
#define CG_8M_MUL_15_FPLL1		(0x0026501EUL<<8U)		/* fPLL = 8MHz * 15		  */
#define CG_10M_MUL_12_FPLL1		(0x002E5018UL<<8U)		/* fPLL = 10MHz * 12	  */
#define CG_12M_MUL_10_FPLL1  	(0x0036D014UL<<8U)		/* fPLL = 12MHz * 10	  */

#define CG_PLL0SEL_PLL0ON_SET                  ((uint32_t)0x00000001)
#define CG_PLL0SEL_PLL0ON_CLEAR                ((uint32_t)0xFFFFFFFE)
#define CG_PLL0SEL_PLL0SEL_SET                 ((uint32_t)0x00000002)
#define CG_PLL0SEL_PLL0SEL_CLEAR               ((uint32_t)0xFFFFFFFD)

#define CG_PLL1SEL_PLL1ON_SET				   ((uint32_t)0x00000001)
#define CG_PLL1SEL_PLL1ON_CLEAR				   ((uint32_t)0xFFFFFFFE)
#define CG_PLL1SEL_PLL1SEL_SET				   ((uint32_t)0x00000002)
#define CG_PLL1SEL_PLL1SEL_CLEAR			   ((uint32_t)0xFFFFFFFD)

#define CG_OSCCR_IHOSC1EN_CLEAR              ((uint32_t)0xFFFFFFFE)
#define CG_OSCCR_EOSCEN_SET                  ((uint32_t)0x00000002)
#define CG_OSCCR_OSCSEL_SET                  ((uint32_t)0x00000100)

#define CG_WUPHCR_WUON_START_SET             ((uint32_t)0x00000001)
#define CG_WUPHCR_WUCLK_SET                  ((uint32_t)0x00000100)

#define PLL0SEL_Ready            CG_10M_MUL_8_FPLL
#define PLL1SEL_Ready			 CG_10M_MUL_12_FPLL1

#define PLL0SEL_Val              (PLL0SEL_Ready|0x00000003UL)
#define PLL0SEL_MASK             (0xFFFFFF00UL)

/*-------- <<< End of configuration section >>> ------------------------------*/

/*-------- DEFINES -----------------------------------------------------------*/
/* Define clocks */
#define EOSC_6M                 (6000000UL)
#define EOSC_8M                 (8000000UL)
#define EOSC_10M                (10000000UL)
#define EOSC_12M                (12000000UL)
#define IOSC_10M                (10000000UL)
#define EXTALH                  EOSC_10M        /* External high-speed oscillator freq */
#define IXTALH                  IOSC_10M        /* Internal high-speed oscillator freq */
#define EOSC_6M_PLLON           (79968750UL)    /* 6.00MHz * 53.3125 / 4 */
#define EOSC_8M_PLLON           (80000000UL)    /* 8.00MHz * 40.0000 / 4 */
#define EOSC_10M_PLLON          (80000000UL)    /* 10.00MHz * 32.0000 / 4 */
#define EOSC_12M_PLLON          (79875000UL)    /* 12.00MHz * 26.6250 / 4 */

/* Configure Warm-up time */
#define HZ_1M                  (1000000UL)
#define WU_TIME_EXT            (5000UL)          /* warm-up time for EXT is 5ms   */
#define INIT_TIME_PLL          (100UL)           /* Initial time for PLL is 100us */
#define LOCKUP_TIME_PLL        (400UL)           /* Lockup time for PLL is 400us  */
#define WUPHCR_WUPT_EXT        ((uint32_t)(((((uint64_t)WU_TIME_EXT * EXTALH / HZ_1M) - 16UL) /16UL) << 20U)) /* OSCCR<WUPT11:0> = warm-up time(us) * EXTALH / 16 */
#if (CLOCK_SETUP)
  #define WUPHCR_INIT_PLL      ((uint32_t)(((((uint64_t)INIT_TIME_PLL * EXTALH / HZ_1M) - 16UL) /16UL) << 20U))
  #define WUPHCR_LUPT_PLL      ((uint32_t)(((((uint64_t)LOCKUP_TIME_PLL * EXTALH / HZ_1M) - 16UL) /16UL) << 20U))
#else
  #define WUPHCR_INIT_PLL      ((uint32_t)(((((uint64_t)INIT_TIME_PLL * IXTALH / HZ_1M) - 16UL) /16UL) << 20U))
  #define WUPHCR_LUPT_PLL      ((uint32_t)(((((uint64_t)LOCKUP_TIME_PLL * IXTALH / HZ_1M) - 16UL) /16UL) << 20U))
#endif

#if (CLOCK_SETUP)               /* Clock(external) Setup */
/* Determine core clock frequency according to settings */
/* System clock is high-speed clock*/
  #if (OSCCR_Val & (1U<<8U))
    #define CORE_TALH (EXTALH)
  #else
    #define CORE_TALH (IXTALH)
  #endif

  #if ((PLL0SEL_Val & (1U<<1U)) && (PLL0SEL_Val & (1U<<0U)))   /* If PLL selected and enabled */
    #if   (CORE_TALH == EOSC_6M)         /* If input is 6MHz */
      #if ((PLL0SEL_Val & PLL0SEL_MASK) == (CG_6M_MUL_13_328_FPLL))
        #define __CORE_CLK   EOSC_6M_PLLON                               /* output clock is 79.968MHz */
      #else                                      /* fc -> reserved */
        #define __CORE_CLK   (0U)
      #endif                          /* End input is 6MHz */
    #elif (CORE_TALH == EOSC_8M)       /* If input is 8MHz */
      #if ((PLL0SEL_Val & PLL0SEL_MASK) == (CG_8M_MUL_10_FPLL))
        #define __CORE_CLK   EOSC_8M_PLLON                               /* output clock is 80MHz */
      #else                                     /* fc -> reserved */
        #define __CORE_CLK   (0U)
      #endif                          /* End input is 8MHz */
    #elif (CORE_TALH == EOSC_10M)      /* If input is 10MHz */
      #if ((PLL0SEL_Val & PLL0SEL_MASK) == CG_10M_MUL_8_FPLL)
        #define __CORE_CLK   EOSC_10M_PLLON                              /* output clock is 80MHz */
      #else                                     /* fc -> reserved */
        #define __CORE_CLK   (0U)
      #endif                          /* End input is 10MHz */
    #elif (CORE_TALH == EOSC_12M)      /* If input is 12MHz */
      #if ((PLL0SEL_Val & PLL0SEL_MASK) == CG_12M_MUL_6_656_FPLL)
        #define __CORE_CLK   EOSC_12M_PLLON                              /* output clock is 79.875MHz */
      #else                                    /* fc -> reserved */
        #define __CORE_CLK   (0U)
      #endif                          /* End input is 12MHz    */
    #else                             /* input clock not known */
      #define __CORE_CLK   (0U)
      #error "Core Oscillator Frequency invalid!"
    #endif                          /* End switch input clock */
  #else                                                         /* If PLL not used */
    #define __CORE_CLK   (CORE_TALH)
  #endif

  #if   ((SYSCR_Val & 7U) == 0U)      /* Gear -> fc                         */
    #define __CORE_SYS   (__CORE_CLK)
  #elif ((SYSCR_Val & 7U) == 1U)      /* Gear -> fc/2                       */
    #define __CORE_SYS   (__CORE_CLK / 2U)
  #elif ((SYSCR_Val & 7U) == 2U)      /* Gear -> fc/4                       */
    #define __CORE_SYS   (__CORE_CLK / 4U )
  #elif ((SYSCR_Val & 7U) == 3U)      /* Gear -> fc/8                       */
    #define __CORE_SYS   (__CORE_CLK / 8U)
  #elif ((SYSCR_Val & 7U) == 4U)      /* Gear -> fc/16                      */
    #define __CORE_SYS   (__CORE_CLK / 16U)
  #else                               /* Gear -> reserved                   */
    #define __CORE_SYS   (0U)
  #endif

#else
  #define __CORE_SYS   (IXTALH)

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
    uint32_t regval = 0U;
    uint32_t oscsel = 0U;
    uint32_t pll0sel = 0U;
    uint32_t pll0on = 0U;
    /* Determine clock frequency according to clock register values */
    /* System clock is high-speed clock */
    regval = TSB_CG->OSCCR;
    oscsel = regval & CG_OSCCR_OSCSEL_SET;
    if (oscsel) {  /* If system clock is External high-speed oscillator freq */
        CoreClock = EXTALH;
    } else {                    /* If system clock is Internal high-speed oscillator freq */
        CoreClock = IXTALH;
    }
    regval = TSB_CG->PLL0SEL;
    pll0sel = regval & CG_PLL0SEL_PLL0SEL_SET;
    pll0on = regval & CG_PLL0SEL_PLL0ON_SET;
    if (pll0sel && pll0on) {                        /* If PLL enabled  */
        if (CoreClock == EOSC_6M) {      /* If input is 6MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == CG_6M_MUL_13_328_FPLL) {
                CoreClockInput = EOSC_6M_PLLON;                /* output clock is 79.968MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else if (CoreClock == EOSC_8M) {      /* If input is 8MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == CG_8M_MUL_10_FPLL) {
                CoreClockInput = EOSC_8M_PLLON;                /* output clock is 80MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else if (CoreClock == EOSC_10M) {      /* If input is 10MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == CG_10M_MUL_8_FPLL) {
                CoreClockInput = EOSC_10M_PLLON;               /* output clock is 80MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else if (CoreClock == EOSC_12M) {      /* If input is 12MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == CG_12M_MUL_6_656_FPLL) {
                CoreClockInput = EOSC_12M_PLLON;               /* output clock is 79.875MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else {
            CoreClockInput = 0U;
        }
    } else {                                       /* If PLL not used */
        CoreClockInput = CoreClock;
    }

    switch (TSB_CG->SYSCR & 7U) {
    case 0U:                                 /* Gear -> fc */
        SystemCoreClock = CoreClockInput;
        break;
    case 1U:                                 /* Gear -> fc/2 */
        SystemCoreClock = CoreClockInput / 2U;
        break;
    case 2U:                                 /* Gear -> fc/4 */
        SystemCoreClock = CoreClockInput / 4U;
        break;
    case 3U:                                 /* Gear -> fc/8 */
        if (CoreClockInput >= EOSC_8M) {
            SystemCoreClock = CoreClockInput / 8U;
        } else {
            SystemCoreClock = 0U;
        }
        break;
    case 4U:                                 /* Gear -> fc/16 */
        if (CoreClockInput > EOSC_12M) {
            SystemCoreClock = CoreClockInput / 16U;
        } else {
            SystemCoreClock = 0U;
        }
        break;
    case 5U:
    case 6U:
    case 7U:
        SystemCoreClock = 0U;
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
#if (SIWD_SETUP)                  /* Watchdog Setup */
    /* SIWD Disable */
    TSB_SIWD0->EN = SIWDEN_Val;
    TSB_SIWD0->CR = SIWDCR_Val;
#else
    /* SIWD Enable (Setting after a Reset) */
#endif

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)   /* FPU setting */
  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif

#if (CLOCK_SETUP)               /* Clock(external) Setup */
    TSB_CG->SYSCR = SYSCR_Val;

    TSB_CG->WUPHCR = (WUPHCR_WUPT_EXT | CG_WUPHCR_WUCLK_SET);
    TSB_CG->OSCCR |= CG_OSCCR_EOSCEN_SET;
    TSB_CG->WUPHCR = (WUPHCR_WUPT_EXT | CG_WUPHCR_WUCLK_SET | CG_WUPHCR_WUON_START_SET);
    while (TSB_CG_WUPHCR_WUEF) {
		;
    }                           /* Warm-up */

    TSB_CG->OSCCR |= CG_OSCCR_OSCSEL_SET;
    while (!TSB_CG_OSCCR_OSCF) {
        ;
    }                         /* Confirm CGOSCCR<OSCF>="1" */
    TSB_CG->OSCCR &= CG_OSCCR_IHOSC1EN_CLEAR ;

    TSB_CG->WUPHCR = (WUPHCR_INIT_PLL | CG_WUPHCR_WUCLK_SET);
    TSB_CG->PLL0SEL &= CG_PLL0SEL_PLL0SEL_CLEAR;    /* PLL-->fOsc */
    TSB_CG->PLL0SEL &= CG_PLL0SEL_PLL0ON_CLEAR;
    TSB_CG->PLL0SEL = PLL0SEL_Ready;
    TSB_CG->WUPHCR = (WUPHCR_INIT_PLL | CG_WUPHCR_WUCLK_SET | CG_WUPHCR_WUON_START_SET);
    while (TSB_CG_WUPHCR_WUEF) {
        ;
    }                           /* Warm-up */

    TSB_CG->WUPHCR = (WUPHCR_LUPT_PLL | CG_WUPHCR_WUCLK_SET);
    TSB_CG->PLL0SEL |= CG_PLL0SEL_PLL0ON_SET;    /* PLL enabled */
    TSB_CG->STBYCR = STBYCR_Val;
    TSB_CG->WUPHCR = (WUPHCR_LUPT_PLL | CG_WUPHCR_WUCLK_SET | CG_WUPHCR_WUON_START_SET);
    while (TSB_CG_WUPHCR_WUEF) {
        ;
    }                           /* Lockup */
    TSB_CG->PLL0SEL |= CG_PLL0SEL_PLL0SEL_SET;
    while (!TSB_CG_PLL0SEL_PLL0ST) {
        ;
    }                        /*Confirm CGPLL0SEL<PLL0ST> = "1" */

	TSB_CG->WUPHCR = (WUPHCR_INIT_PLL | CG_WUPHCR_WUCLK_SET);
    TSB_CG->PLL1SEL &= CG_PLL1SEL_PLL1SEL_CLEAR;    /* PLL-->fOsc */
    TSB_CG->PLL1SEL &= CG_PLL1SEL_PLL1ON_CLEAR;
    TSB_CG->PLL1SEL = PLL1SEL_Ready;
    TSB_CG->WUPHCR = (WUPHCR_INIT_PLL | CG_WUPHCR_WUCLK_SET | CG_WUPHCR_WUON_START_SET);
    while (TSB_CG_WUPHCR_WUEF) {
        ;
    }       

	TSB_CG->WUPHCR = (WUPHCR_LUPT_PLL | CG_WUPHCR_WUCLK_SET);
	TSB_CG->PLL1SEL |=  CG_PLL1SEL_PLL1ON_SET;	/* PLL1 enabled */
    TSB_CG->WUPHCR = (WUPHCR_LUPT_PLL | CG_WUPHCR_WUCLK_SET | CG_WUPHCR_WUON_START_SET);
    while (TSB_CG_WUPHCR_WUEF) {
        ;
    } /* Warm-up */

	TSB_CG->PLL1SEL |= CG_PLL1SEL_PLL1SEL_SET;

#endif
}
