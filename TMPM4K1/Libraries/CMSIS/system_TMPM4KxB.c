/**
 *******************************************************************************
 * @file    system_TMPM4KxB.c
 * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer Source File.\n
 * 
 * @version V1.0.0
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * Copyright(C) Toshiba Electronic Device Solutions Corporation 2024
 *******************************************************************************
 */

#include "TMPM4KxB.h"

/*-------- DEFINES -----------------------------------------------------------*/
/* Define clocks */
#define SYS_CG_GEAR_FC_1            (0x00000000UL)      /*!< CG fc register value */
#define SYS_CG_GEAR_FC_2            (0x00000001UL)      /*!< CG fc/2 register value */
#define SYS_CG_GEAR_FC_4            (0x00000002UL)      /*!< CG fc/4 register value */
#define SYS_CG_GEAR_FC_8            (0x00000003UL)      /*!< CG fc/8 register value */
#define SYS_CG_GEAR_FC_16           (0x00000004UL)      /*!< CG fc/16 register value */
#define SYS_CG_PRCK_FC_1            (0x00000000UL)      /*!< CG PhiT0 fc register value */
#define SYS_CG_PRCK_FC_2            (0x00000100UL)      /*!< CG PhiT0 fc/2 register value */
#define SYS_CG_PRCK_FC_4            (0x00000200UL)      /*!< CG PhiT0 fc/4 register value */
#define SYS_CG_PRCK_FC_8            (0x00000300UL)      /*!< CG PhiT0 fc/8 register value */
#define SYS_CG_PRCK_FC_16           (0x00000400UL)      /*!< CG PhiT0 fc/16 register value */
#define SYS_CG_PRCK_FC_32           (0x00000500UL)      /*!< CG PhiT0 fc/32 register value */
#define SYS_CG_PRCK_FC_64           (0x00000600UL)      /*!< CG PhiT0 fc/64 register value */
#define SYS_CG_PRCK_FC_128          (0x00000700UL)      /*!< CG PhiT0 fc/128 register value */
#define SYS_CG_PRCK_FC_256          (0x00000800UL)      /*!< CG PhiT0 fc/256 register value */
#define SYS_CG_PRCK_FC_512          (0x00000900UL)      /*!< CG PhiT0 fc/512 register value */

#define SYS_CG_PLL0SEL_PLL0ON_SET   ((uint32_t)0x00000001)

#define SYS_CG_6M_MUL_40_FPLL       (0x001C1028UL << 8U)    /* fPLL =  6MHz * 20        */
#define SYS_CG_8M_MUL_30_FPLL       (0x0024501EUL << 8U)    /* fPLL =  8MHz * 15        */
#define SYS_CG_10M_MUL_24_FPLL      (0x002E9018UL << 8U)    /* fPLL = 10MHz * 12        */
#define SYS_CG_12M_MUL_20_FPLL      (0x0036D014UL << 8U)    /* fPLL = 12MHz * 10        */
#define SYS_CG_24M_MUL_10_FPLL      (0x006D190AUL << 8U)    /* fPLL = 24MHz * 5         */
#define SYS_CG_6M_MUL_53_3125_FPLL  (0x001C2535UL << 8U)    /* fPLL =  6MHz * 13.328125 */
#define SYS_CG_8M_MUL_40_FPLL       (0x00246028UL << 8U)    /* fPLL =  8MHz * 10        */
#define SYS_CG_10M_MUL_32_FPLL      (0x002EA020UL << 8U)    /* fPLL = 10MHz *  4        */
#define SYS_CG_12M_MUL_26_6250_FPLL (0x0036EA1AUL << 8U)    /* fPLL = 12MHz *  6.65625  */
#define SYS_CG_24M_MUL_13_3125_FPLL (0x006D1A5DUL << 8U)    /* fPLL = 24MHz * 3.328125  */

/* Clock Generator (CG) Configuration */
#ifdef TRM_SETUP
    #define CLOCK_SETUP             (0U)                      /* 1:External HOSC, 0: Internal HOSC */
    #define PLL_SETUP               (0U)                      /* 1:PLL used, 0: PLL not used */
    #define SYSCR_GEAR_Val          (0x00000000)
    #define SYSCR_PRCK_Val          (0x00000000)
#else
    #define CLOCK_SETUP             (1U)                      /* 1:External HOSC, 0: Internal HOSC */
    #define PLL_SETUP               (1U)                      /* 1:PLL used, 0: PLL not used */
    #define SYSCR_GEAR_Val          (SYS_CG_GEAR_FC_1)
    #define SYSCR_PRCK_Val          (SYS_CG_PRCK_FC_1)
#endif

#define CG_PRCK_MASK            ((uint32_t)0x00000F00)    /*!< CG PRCK mask */
#define CG_PRCKST_MASK          ((uint32_t)0x0F000000)    /*!< CG PRCKST mask */

#define STBYCR_Val              (0x00000000UL)
/* Define clocks */
#define IOSC_10M                (10000000UL)
#define IXTALH                  IOSC_10M                    /* Internal high-speed oscillator freq */



#define CG_PLL0SEL_FPLL         ((uint32_t)0x00000002)      /*!< CG PLL0SEL fPLL */
#define CG_PLL0SEL_FOSC         ((uint32_t)0x00000000)      /*!< CG PLL0SEL fosc */

#define PLL0SEL_MASK            (0xFFFFFF00UL)              /*!< CG PLL mask */

#define SYS_CG_PLL0SEL_PLL0ON_CLEAR             ((uint32_t)0xFFFFFFFE)
#define SYS_CG_PLL0SEL_PLL0SEL_SET              ((uint32_t)0x00000002)
#define SYS_CG_PLL0SEL_PLL0SEL_CLEAR            ((uint32_t)0xFFFFFFFD)
#define SYS_CG_PLL0SEL_PLL0ST                   ((uint32_t)0x00000004)

#define CG_OSCSEL_EHOSC         ((uint32_t)0x00000100)      /*!< CG OSCSEL EHOSC */

#define SYS_CG_OSCCR_IHOSC1EN_CLEAR         ((uint32_t)0xFFFFFFFE)
#define SYS_CG_OSCCR_OSCF                   ((uint32_t)0x00000200)
#define SYS_CG_OSCCR_OSCSEL_SET             ((uint32_t)0x00000100)
#define SYS_CG_OSCCR_EOSCEN_SET             ((uint32_t)0x00000002)

/* Configure Warm-up time */
#define HZ_1M                   (1000000UL)
#define WU_TIME_EXT             (5000UL)                    /* warm-up time for EXT is 5ms   */
#define WU_TIME_INT             (1634UL)                    /* warm-up time for INT is 163.4us x 10 */
#define WU_TIME_INT_MIN         (0x03C << 20U)              /* minimum warm-up time for INT */
#define CGWUPHCR_WUEF_R_DONE    ((uint32_t)0x00000000)      /*!< WUEF    :[R]    :Done    */

/* Warm-up setting value */
/* EOSC OSCCR<WUPT11:0> = (warm-up time(us) * EXTALH - 16) / 16 */
#define WUPHCR_WUPT_EXT         ((uint32_t)(((((uint64_t)WU_TIME_EXT * EXTALH / HZ_1M) - 16UL) /16UL) << 20U))
/* IOSC OSCCR<WUPT11:0> = ((warm-up time(us) - 63.3us) * IXTALH - 41) / 16 */
#define WUPHCR_WUPT_INT         ((uint32_t)(((((uint64_t)(WU_TIME_INT - 633UL) * (IXTALH / 10) / HZ_1M) - 41UL) / 16UL) << 20U))
#define SYS_CG_WUPHCR_WUEF                  ((uint32_t)0x00000002)
#define SYS_CG_WUPHCR_WUON_START_SET        ((uint32_t)0x00000001)
#if (CLOCK_SETUP)
    #define CG_WUPHCR_WUCLK_SET                ((uint32_t)0x00000100)
    #define WUPHCR_INIT_PLL     ((uint32_t)(((((uint64_t)INIT_TIME_PLL * EXTALH / HZ_1M) - 16UL) /16UL) << 20U))
    #define WUPHCR_LUPT_PLL     ((uint32_t)(((((uint64_t)LOCKUP_TIME_PLL * EXTALH / HZ_1M) - 16UL) /16UL) << 20U))
    #define PLL0SEL_Ready          SYS_CG_10M_MUL_24_FPLL
#else
    #define CG_WUPHCR_WUCLK_SET                ((uint32_t)0x00000000)
    #define WUPHCR_INIT_PLL     ((uint32_t)(((((uint64_t)((INIT_TIME_PLL * 10) - 633UL) * (IXTALH / 10) / HZ_1M) - 41UL) /16UL) << 20U))
    #define WUPHCR_LUPT_PLL     ((uint32_t)(((((uint64_t)((LOCKUP_TIME_PLL * 10) - 633UL) * (IXTALH /10) / HZ_1M) - 41UL) /16UL) << 20U))
    #define PLL0SEL_Ready          SYS_CG_10M_MUL_24_FPLL
#endif

#define SIWD_SETUP              (1U)                      /* 1:Disable SIWD, 0:Enable SIWD */
#define SIWDEN_Val              (0x00000000UL)            /* SIWD Disable */
#define SIWDCR_Val              (0x000000B1UL)            /* SIWD Disable code */

#if (PLL_SETUP)
    #define PLL0SEL_Val         (PLL0SEL_Ready|0x00000003UL)
#else
    #define PLL0SEL_Val         (0x00000000UL)
#endif

#define IOSC_10M_DIV2_PLLON     (120000000UL)    /* 10.00MHz * 24.0000 / 2 */
#define IOSC_10M_DIV4_PLLON     (80000000UL)     /* 10.00MHz * 32.0000 / 4 */

#define EOSC_6M                 (6000000UL)
#define EOSC_8M                 (8000000UL)
#define EOSC_10M                (10000000UL)
#define EOSC_12M                (12000000UL)
#define EOSC_24M                (24000000UL)
#define EXTALH                  EOSC_10M        /* External high-speed oscillator freq */
#define EOSC_6M_DIV2_PLLON      (120000000UL)   /* 6.00MHz  * 40.0000 / 2 */
#define EOSC_8M_DIV2_PLLON      (120000000UL)   /* 8.00MHz  * 30.0000 / 2 */
#define EOSC_10M_DIV2_PLLON     (120000000UL)   /* 10.00MHz * 24.0000 / 2 */
#define EOSC_12M_DIV2_PLLON     (120000000UL)   /* 12.00MHz * 20.0000 / 2 */
#define EOSC_24M_DIV2_PLLON     (120000000UL)   /* 24.00MHz * 10.0000 / 2 */
#define EOSC_6M_DIV4_PLLON      (79970000UL)    /* 6.00MHz  * 53.3125 / 4 */
#define EOSC_8M_DIV4_PLLON      (80000000UL)    /* 8.00MHz  * 40.0000 / 4 */
#define EOSC_10M_DIV4_PLLON     (80000000UL)    /* 10.00MHz * 32.0000 / 4 */
#define EOSC_12M_DIV4_PLLON     (79880000UL)    /* 12.00MHz * 26.6250 / 4 */
#define EOSC_24M_DIV4_PLLON     (79880000UL)    /* 24.00MHz * 13.3125 / 4 */

#define FIXED_6MHz              (6000000UL)     /* 6.00MHz */
#define FIXED_8MHz              (8000000UL)     /* 8.00MHz */
#define FIXED_10MHz             (10000000UL)    /* 10.00MHz */
#define FIXED_12MHz             (12000000UL)    /* 12.00MHz */
#define FIXED_24MHz             (24000000UL)    /* 24.00MHz */
#define FIXED_40MHz             (40000000UL)    /* 40.00MHz */
#define FIXED_80MHz             (80000000UL)    /* 80.00MHz */
#define FIXED_120MHz            (120000000UL)   /* 120.00MHz */

#define INIT_TIME_PLL           (100UL)          /* Initial time for PLL is 100us */
#define LOCKUP_TIME_PLL         (400UL)          /* Lockup time for PLL is 400us  */

/* Determine core clock frequency according to settings */
/* System clock is high-speed clock*/
#if (CLOCK_SETUP)
  #define CORE_TALH (EXTALH)
#else
  #define CORE_TALH (IXTALH)
#endif

#if ((PLL0SEL_Val & (1U<<1U)) && (PLL0SEL_Val & (1U<<0U)))  /* If PLL selected and enabled */
    #if   (CORE_TALH == EOSC_6M)        /* If input is 6MHz */
        #if ((PLL0SEL_Val & PLL0SEL_MASK) == (SYS_CG_6M_MUL_40_FPLL))
            #define __CORE_CLK   EOSC_6M_DIV2_PLLON                               /* output clock is 120MHz */
        #elif ((PLL0SEL_Val & PLL0SEL_MASK) == (SYS_CG_6M_MUL_53_3125_FPLL))
            #define __CORE_CLK   EOSC_6M_DIV4_PLLON                               /* output clock is 79.97MHz */
        #else                                      /* fc -> reserved */
            #define __CORE_CLK   (0U)
        #endif                          /* End input is 6MHz */
    #elif (CORE_TALH == EOSC_8M)        /* If input is 8MHz */
        #if ((PLL0SEL_Val & PLL0SEL_MASK) == (SYS_CG_8M_MUL_30_FPLL))
            #define __CORE_CLK   EOSC_8M_DIV2_PLLON                             /* output clock is 120MHz */
        #elif ((PLL0SEL_Val & PLL0SEL_MASK) == (SYS_CG_8M_MUL_40_FPLL))
            #define __CORE_CLK   EOSC_8M_DIV4_PLLON                             /* output clock is 80MHz */
        #else                                     /* fc -> reserved */
            #define __CORE_CLK   (0U)
        #endif                          /* End input is 8MHz */
    #elif (CORE_TALH == EOSC_10M)       /* If input is 10MHz */
        #if ((PLL0SEL_Val & PLL0SEL_MASK) == SYS_CG_10M_MUL_24_FPLL)
            #define __CORE_CLK   EOSC_10M_DIV2_PLLON                            /* output clock is 120MHz */
        #elif ((PLL0SEL_Val & PLL0SEL_MASK) == (SYS_CG_10M_MUL_32_FPLL))
            #define __CORE_CLK   EOSC_10M_DIV4_PLLON                            /* output clock is 80MHz */
        #else                                     /* fc -> reserved */
            #define __CORE_CLK   (0U)
        #endif                          /* End input is 10MHz */
    #elif (CORE_TALH == EOSC_12M)       /* If input is 12MHz */
        #if ((PLL0SEL_Val & PLL0SEL_MASK) == SYS_CG_12M_MUL_20_FPLL)
            #define __CORE_CLK   EOSC_12M_DIV2_PLLON                            /* output clock is 120MHz */
        #elif ((PLL0SEL_Val & PLL0SEL_MASK) == (SYS_CG_12M_MUL_26_6250_FPLL))
            #define __CORE_CLK   EOSC_12M_DIV4_PLLON                            /* output clock is 79.88MHz */
        #else                                    /* fc -> reserved */
            #define __CORE_CLK   (0U)
        #endif                          /* End input is 12MHz    */
    #elif (CORE_TALH == EOSC_24M)       /* If input is 24MHz */
        #if ((PLL0SEL_Val & PLL0SEL_MASK) == SYS_CG_24M_MUL_10_FPLL)
            #define __CORE_CLK   EOSC_12M_DIV2_PLLON                            /* output clock is 120MHz */
        #elif ((PLL0SEL_Val & PLL0SEL_MASK) == (SYS_CG_24M_MUL_13_3125_FPLL))
            #define __CORE_CLK   EOSC_12M_DIV4_PLLON                            /* output clock is 79.88MHz */
        #else                                    /* fc -> reserved */
            #define __CORE_CLK   (0U)
        #endif                          /* End input is 24MHz    */
    #elif (CORE_TALH == IOSC_10M)       /* If input is 10MHz */
        #if ((PLL0SEL_Val & PLL0SEL_MASK) == SYS_CG_10M_MUL_24_FPLL)
            #define __CORE_CLK   IOSC_10M_DIV2_PLLON                            /* output clock is 120MHz */
        #elif ((PLL0SEL_Val & PLL0SEL_MASK) == (SYS_CG_10M_MUL_32_FPLL))
            #define __CORE_CLK   IOSC_10M_DIV4_PLLON                            /* output clock is 80MHz */
        #else                                    /* fc -> reserved */
            #define __CORE_CLK   (0U)
        #endif                          /* End input is 12MHz    */
    #else                                                   /* input clock not known */
        #define __CORE_CLK   (0U)
        #error "Core Oscillator Frequency invalid!"
    #endif                                                  /* End switch input clock */
#else                                                       /* If PLL not used */
    #define __CORE_CLK   (CORE_TALH)
#endif

#if   ((SYSCR_GEAR_Val & 7U) == 0U)      /* Gear -> fc                         */
  #define __CORE_SYS   (__CORE_CLK)
#elif ((SYSCR_GEAR_Val & 7U) == 1U)      /* Gear -> fc/2                       */
  #define __CORE_SYS   (__CORE_CLK / 2U)
#elif ((SYSCR_GEAR_Val & 7U) == 2U)      /* Gear -> fc/4                       */
  #define __CORE_SYS   (__CORE_CLK / 4U )
#elif ((SYSCR_GEAR_Val & 7U) == 3U)      /* Gear -> fc/8                       */
  #define __CORE_SYS   (__CORE_CLK / 8U)
#elif ((SYSCR_GEAR_Val & 7U) == 4U)      /* Gear -> fc/16                      */
  #define __CORE_SYS   (__CORE_CLK / 16U)
#else                               /* Gear -> reserved                   */
  #define __CORE_SYS   (0U)
#endif


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
#ifndef TRM_SETUP               /* Not TRM project */
    uint32_t CoreClock = 0U;
    uint32_t CoreClockInput = 0U;
    uint32_t regval = 0U;
    uint32_t oscsel = 0U;
    uint32_t pll0sel = 0U;
    uint32_t pll0on = 0U;
    /* Determine clock frequency according to clock register values */
    /* System clock is high-speed clock */
    regval = TSB_CG->OSCCR;
    oscsel = regval & CG_OSCSEL_EHOSC;
    if (oscsel) {  /* If system clock is External high-speed oscillator freq */
        CoreClock = EXTALH;
    } else {                    /* If system clock is Internal high-speed oscillator freq */
        CoreClock = IXTALH;
    }
    regval = TSB_CG->PLL0SEL;
    pll0sel = regval & CG_PLL0SEL_FPLL;
    pll0on = regval & SYS_CG_PLL0SEL_PLL0ON_SET;
    if (pll0sel && pll0on) {                        /* If PLL enabled  */
        if (CoreClock == EOSC_6M) {      /* If input is 6MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_6M_MUL_40_FPLL) {
                CoreClockInput = EOSC_6M_DIV2_PLLON;            /* output clock is 120MHz */
            } else if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_6M_MUL_53_3125_FPLL) {
                CoreClockInput = EOSC_6M_DIV4_PLLON;            /* output clock is 79.97MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else if (CoreClock == EOSC_8M) {      /* If input is 8MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_8M_MUL_30_FPLL) {
                CoreClockInput = EOSC_8M_DIV2_PLLON;            /* output clock is 120MHz */
            } else if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_8M_MUL_40_FPLL) {
                CoreClockInput = EOSC_8M_DIV4_PLLON;            /* output clock is 80MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else if (CoreClock == EOSC_10M) {      /* If input is 10MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_10M_MUL_24_FPLL) {
                CoreClockInput = EOSC_10M_DIV2_PLLON;           /* output clock is 120MHz */
            } else if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_10M_MUL_32_FPLL) {
                CoreClockInput = EOSC_10M_DIV4_PLLON;           /* output clock is 80MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else if (CoreClock == EOSC_12M) {      /* If input is 12MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_12M_MUL_20_FPLL) {
                CoreClockInput = EOSC_12M_DIV2_PLLON;           /* output clock is 120MHz */
            } else if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_12M_MUL_26_6250_FPLL) {
                CoreClockInput = EOSC_12M_DIV4_PLLON;           /* output clock is 79.88MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else if (CoreClock == EOSC_24M) {      /* If input is 24MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_24M_MUL_10_FPLL) {
                CoreClockInput = EOSC_24M_DIV2_PLLON;           /* output clock is 120MHz */
            } else if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_24M_MUL_13_3125_FPLL) {
                CoreClockInput = EOSC_24M_DIV4_PLLON;           /* output clock is 79.88MHz */
            } else {
                CoreClockInput = 0U;    /* fc -> reserved */
            }
        } else if (CoreClock == IOSC_10M) {      /* If input is 10MHz */
            if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_10M_MUL_24_FPLL) {
                CoreClockInput = IOSC_10M_DIV2_PLLON;           /* output clock is 120MHz */
            } else if ((TSB_CG->PLL0SEL & PLL0SEL_MASK) == SYS_CG_10M_MUL_32_FPLL) {
                CoreClockInput = IOSC_10M_DIV4_PLLON;           /* output clock is 80MHz */
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
        SystemCoreClock = CoreClockInput / 8U;
        break;
    case 4U:                                 /* Gear -> fc/16 */
        SystemCoreClock = CoreClockInput / 16U;
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
#else
    SystemCoreClock = __CORE_SYS;
#endif               /* Not TRM project */
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
    SCB->CPACR |= ((3UL << (10*2))|(3UL << (11*2)));  /* set CP10 and CP11 Full Access */
#endif

#if (CLOCK_SETUP)               /* Clock(external) Setup */
    TSB_CG->SYSCR |= SYSCR_GEAR_Val;
    TSB_CG->SYSCR |= SYSCR_PRCK_Val;
    TSB_CG->OSCCR |= SYS_CG_OSCCR_EOSCEN_SET;
    TSB_CG->WUPHCR = (WUPHCR_WUPT_EXT | CG_WUPHCR_WUCLK_SET);
    TSB_CG->WUPHCR = (WUPHCR_WUPT_EXT | CG_WUPHCR_WUCLK_SET | SYS_CG_WUPHCR_WUON_START_SET);
    while (TSB_CG->WUPHCR & SYS_CG_WUPHCR_WUEF) {
        /* no processing */
    }                           /* Warm-up */
    TSB_CG->OSCCR |= SYS_CG_OSCCR_OSCSEL_SET;
    while (!(TSB_CG->OSCCR & SYS_CG_OSCCR_OSCF)) {
        /* no processing */
    }                         /* Confirm CGOSCCR<OSCF>="1" */
#else
    /* Internal HOSC Enable (Setting after a Reset) */
#endif

#if (PLL_SETUP)
#if (CLOCK_SETUP)               /* Clock(external) Setup */
    TSB_CG->WUPHCR = (WUPHCR_INIT_PLL | CG_WUPHCR_WUCLK_SET);
#else
    TSB_CG->WUPHCR = (WUPHCR_INIT_PLL);
#endif
    TSB_CG->PLL0SEL &= SYS_CG_PLL0SEL_PLL0SEL_CLEAR;    /* PLL-->fOsc */
    TSB_CG->PLL0SEL &= SYS_CG_PLL0SEL_PLL0ON_CLEAR;
    TSB_CG->PLL0SEL = PLL0SEL_Ready;
#if (CLOCK_SETUP)               /* Clock(external) Setup */
    TSB_CG->WUPHCR = (WUPHCR_INIT_PLL | CG_WUPHCR_WUCLK_SET | SYS_CG_WUPHCR_WUON_START_SET);
#else
    TSB_CG->WUPHCR = (WUPHCR_INIT_PLL | SYS_CG_WUPHCR_WUON_START_SET);
#endif

    while (TSB_CG->WUPHCR & SYS_CG_WUPHCR_WUEF) {
        /* no processing */
    }                           /* Warm-up */

#if (CLOCK_SETUP)               /* Clock(external) Setup */
    TSB_CG->WUPHCR = (WUPHCR_LUPT_PLL | CG_WUPHCR_WUCLK_SET);
#else
    TSB_CG->WUPHCR = (WUPHCR_LUPT_PLL);
#endif
    TSB_CG->PLL0SEL |= SYS_CG_PLL0SEL_PLL0ON_SET;    /* PLL enabled */
    TSB_CG->STBYCR = STBYCR_Val;

#if (CLOCK_SETUP)               /* Clock(external) Setup */
    TSB_CG->WUPHCR = (WUPHCR_LUPT_PLL | CG_WUPHCR_WUCLK_SET | SYS_CG_WUPHCR_WUON_START_SET);
#else
    TSB_CG->WUPHCR = (WUPHCR_LUPT_PLL | SYS_CG_WUPHCR_WUON_START_SET);
#endif
    while (TSB_CG->WUPHCR & SYS_CG_WUPHCR_WUEF) {
        /* no processing */
    }                           /* Warm-up */

    TSB_CG->PLL0SEL |= SYS_CG_PLL0SEL_PLL0SEL_SET;
    while (!(TSB_CG->PLL0SEL & SYS_CG_PLL0SEL_PLL0ST)) {
        /* no processing */
    }                        /*Confirm CGPLL0SEL<PLL0ST> = "1" */
#else
    TSB_CG->STBYCR = STBYCR_Val;    /* PLL not used */
#endif/* PLL_SETUP */

#if (CLOCK_SETUP)               /* Clock(external) Setup */
    /* Internal high-speed oscillator1 is disable. */
    TSB_CG->OSCCR &= SYS_CG_OSCCR_IHOSC1EN_CLEAR;
#endif
}
