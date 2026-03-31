/**
 *******************************************************************************
 * @file    TMPM311.h
 * @brief   CMSIS Cortex-M3 Core Peripheral Access Layer Header File for the
 *          TOSHIBA 'TMPM311' Device Series
 * @version V2.0.2.1 (Tentative)
 * @date    2014/09/05
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
 *******************************************************************************
 */

/** @addtogroup TOSHIBA_TX03_MICROCONTROLLER
  * @{
  */
  
/** @addtogroup TMPM311
  * @{
  */

#ifndef __TMPM311_H__
#define __TMPM311_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/** Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************************/
  NonMaskableInt_IRQn           = -14,       /*!< 2 Non Maskable Interrupt                                    */
  HardFault_IRQn                = -13,       /*!< 3 Cortex-M3 Hard Fault Interrupt                            */
  MemoryManagement_IRQn         = -12,       /*!< 4 Cortex-M3 Memory Management Interrupt                     */
  BusFault_IRQn                 = -11,       /*!< 5 Cortex-M3 Bus Fault Interrupt                             */
  UsageFault_IRQn               = -10,       /*!< 6 Cortex-M3 Usage Fault Interrupt                           */
  SVCall_IRQn                   = -5,        /*!< 11 Cortex-M3 SV Call Interrupt                              */
  DebugMonitor_IRQn             = -4,        /*!< 12 Cortex-M3 Debug Monitor Interrupt                        */
  PendSV_IRQn                   = -2,        /*!< 14 Cortex-M3 Pend SV Interrupt                              */
  SysTick_IRQn                  = -1,        /*!< 15 Cortex-M3 System Tick Interrupt                          */

/******  TMPM311 Specific Interrupt Numbers *******************************************************************/
  INTDSADA_IRQn                 = 0,         /*!< DSAD conversion complete interrupt (unitA)                  */
  INTDSADB_IRQn                 = 1,         /*!< DSAD conversion complete interrupt (unitB)                  */
  INTDSADC_IRQn                 = 2,         /*!< DSAD conversion complete interrupt (unitC)                  */
  INTDSADD_IRQn                 = 3,         /*!< DSAD conversion complete interrupt (unitD)                  */
  INT0_IRQn                     = 4,         /*!< Interrupt pin 0                                             */
  INT1_IRQn                     = 5,         /*!< Interrupt pin 1                                             */
  INTSSP0_IRQn                  = 6,         /*!< SSP0 interrupt                                              */
  INTRX0_IRQn                   = 7,         /*!< Serial0 reception interrupt                                 */
  INTTX0_IRQn                   = 8,         /*!< Serial0 transmission interrupt                              */
  INTTB0_IRQn                   = 9,         /*!< 16-bit TMRB0 compare match detection interrupt              */
  INTTB1_IRQn                   = 10,        /*!< 16-bit TMRB1 compare match detection interrupt              */
  INTTB2_IRQn                   = 11,        /*!< 16-bit TMRB2 compare match detection interrupt              */
  INTTB3_IRQn                   = 12,        /*!< 16-bit TMRB3 compare match detection interrupt              */
  INTCAP00_IRQn                 = 13,        /*!< 16-bit TMRB0 input capture 0 detection interrupt            */
  INTCAP01_IRQn                 = 14,        /*!< 16-bit TMRB0 input capture 1 detection interrupt            */
  INTCAP10_IRQn                 = 15,        /*!< 16-bit TMRB1 input capture 0 detection interrupt            */
  INTCAP11_IRQn                 = 16,        /*!< 16-bit TMRB1 input capture 1 detection interrupt            */
  INTT16A0_IRQn                 = 17,        /*!< 16-bit TMR16A0 match detection                              */
  INTDMAATC0_IRQn               = 18,        /*!< DMAC 0 transmission completion interrupt (unitA)            */
  INTDMAATC1_IRQn               = 19,        /*!< DMAC 1 transmission completion interrupt (unitA)            */
  INTDMAATC2_IRQn               = 20,        /*!< DMAC 2 transmission completion interrupt (unitA)            */
  INTDMAATC3_IRQn               = 21,        /*!< DMAC 3 transmission completion interrupt (unitA)            */
  INTDMAAERR_IRQn               = 22         /*!< DMAC transmissioni error interrupt (unitA)                  */
} IRQn_Type;

/** Processor and Core Peripheral Section */

/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __CM3_REV              0x0201       /*!< Cortex-M3 Core Revision                           */
#define __MPU_PRESENT             0         /*!< MPU present or not                                */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels           */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used      */

/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm3.h"                       /* Cortex-M3 processor and core peripherals            */
#include "system_TMPM311.h"                 /* TMPM311 System                                      */

/** @addtogroup Device_Peripheral_registers
  * @{
  */

/** Device Specific Peripheral registers structures */

/**
  * @brief Synchronous Serial Port (SSP)
  */
typedef struct
{
  __IO uint32_t CR0;               /*!< SSP Control Register 0                       */
  __IO uint32_t CR1;               /*!< SSP Control Register 1                       */
  __IO uint32_t DR;                /*!< SSP Data Register                            */
  __I  uint32_t SR;                /*!< SSP Status Register                          */
  __IO uint32_t CPSR;              /*!< SSP Clock Prescaler Register                 */
  __IO uint32_t IMSC;              /*!< SSP Interrupt Mask Set and Clear Register    */
  __I  uint32_t RIS;               /*!< SSP Raw Interrupt Status Register            */
  __I  uint32_t MIS;               /*!< SSP Masked Interrupt Status Register         */
  __O  uint32_t ICR;               /*!< SSP Interrupt Clear Register                 */
} TSB_SSP_TypeDef;

/**
  * @brief DMA Controller (DMA)
  */
typedef struct
{
  __I  uint32_t STATUS;            /*!< DMA Status Register                          */
  __O  uint32_t CFG;               /*!< DMA Configuration Register                   */
  __IO uint32_t CTRLBASEPTR;       /*!< DMA Control Data Base Pointer Register       */
  __I  uint32_t ALTCTRLBASEPTR;    /*!< DMA Channel Alternate Control Data Base Pointer Register*/
       uint32_t RESERVED0;
  __O  uint32_t CHNLSWREQUEST;     /*!< DMA Channel Software Request Register        */
  __IO uint32_t CHNLUSEBURSTSET;   /*!< DMA Channel Useburst Set Register            */
  __O  uint32_t CHNLUSEBURSTCLR;   /*!< DMA Channel Useburst Clear Register          */
  __IO uint32_t CHNLREQMASKSET;    /*!< DMA Channel Request Mask Set Register        */
  __O  uint32_t CHNLREQMASKCLR;    /*!< DMA Channel Request Mask Clear Register      */
  __IO uint32_t CHNLENABLESET;     /*!< DMA Channel Enable Set Register              */
  __O  uint32_t CHNLENABLECLR;     /*!< DMA Channel Enable Clear Register            */
  __IO uint32_t CHNLPRIALTSET;     /*!< DMA Channel Primary-Alternate Set Register   */
  __O  uint32_t CHNLPRIALTCLR;     /*!< DMA Channel Primary-Alternate Clear Register */
  __IO uint32_t CHNLPRIORITYSET;   /*!< DMA Channel Priority Set Register            */
  __O  uint32_t CHNLPRIORITYCLR;   /*!< DMA Channel Priority Clear Register          */
       uint32_t RESERVED1[3];
  __IO uint32_t ERRCLR;            /*!< DMA Bus Error Clear Register                 */
} TSB_DMA_TypeDef;

/**
  * @brief Temperature Sensor (TEMP)
  */
typedef struct
{
  __IO uint32_t EN;                /*!< Enable Register                              */
  __IO uint32_t CR;                /*!< Control Register                             */
} TSB_TEMP_TypeDef;

/**
  * @brief 24bit Delta Sigma AD Converter (DSAD)
  */
typedef struct
{
  __IO uint32_t CLK;               /*!< Conversion Clock Setting Register            */
  __IO uint32_t CR0;               /*!< Control Register 0                           */
  __IO uint32_t CR1;               /*!< Control Register 1                           */
  __IO uint32_t CR2;               /*!< Control Register 2                           */
  __IO uint32_t CR3;               /*!< Control Register 3                           */
  __IO uint32_t CR4;               /*!< Control Register 4                           */
  __IO uint32_t CR5;               /*!< Control Register 5                           */
       uint32_t RESERVED0[5];
  __IO uint32_t ADJ;               /*!< Adjust Register                              */
       uint32_t RESERVED1[3];
  __I  uint32_t ST;                /*!< Status Register                              */
  __I  uint32_t RES;               /*!< Result Register                              */
} TSB_DSAD_TypeDef;

/**
  * @brief 16-bit TimerA (T16A)
  */
typedef struct
{
  __IO uint32_t EN;                /*!< Enable Register                              */
  __IO uint32_t RUN;               /*!< RUN Register                                 */
  __IO uint32_t CR;                /*!< Control Register                             */
  __IO uint32_t RG;                /*!< Timer Register                               */
  __I  uint32_t CP;                /*!< Capture Register                             */
} TSB_T16A_TypeDef;

/**
  * @brief Interrupt Controller (INT)
  */
typedef struct
{
  __IO uint32_t CR0;               /*!< Control Register 0                           */
  __IO uint32_t CR1;               /*!< Control Register 1                           */
       uint32_t RESERVED0[15];
  __O  uint32_t CLR;               /*!< Interrupt Request Clear Register             */
  __IO uint32_t RESETF;            /*!< Reset Flag Register                          */
} TSB_INT_TypeDef;

/**
  * @brief Port A (PA)
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< Data Register                                */
  __IO uint32_t CR;                /*!< Output Control Register                      */
  __IO uint32_t FR1;               /*!< Function Register 1                          */
       uint32_t RESERVED0[8];
  __IO uint32_t PUP;               /*!< Pull-up Control Register                     */
       uint32_t RESERVED1[2];
  __IO uint32_t IE;                /*!< Input Control Register                       */
} TSB_PA_TypeDef;

/**
  * @brief Port B (PB)
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< Data Register                                */
  __IO uint32_t CR;                /*!< Output Control Register                      */
  __IO uint32_t FR1;               /*!< Function Register 1                          */
       uint32_t RESERVED0[8];
  __IO uint32_t PUP;               /*!< Pull-up Control Register                     */
       uint32_t RESERVED1[2];
  __IO uint32_t IE;                /*!< Input Control Register                       */
} TSB_PB_TypeDef;

/**
  * @brief Port C (PC)
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< Data Register                                */
  __IO uint32_t CR;                /*!< Output Control Register                      */
  __IO uint32_t FR1;               /*!< Function Register 1                          */
       uint32_t RESERVED0[8];
  __IO uint32_t PUP;               /*!< Pull-up Control Register                     */
  __IO uint32_t PDN;               /*!< Pull-down Control Register                   */
       uint32_t RESERVED1;
  __IO uint32_t IE;                /*!< Input Control Register                       */
} TSB_PC_TypeDef;

/**
  * @brief Port D (PD)
  */
typedef struct
{
  __IO uint32_t DATA;              /*!< Data Register                                */
  __IO uint32_t CR;                /*!< Output Control Register                      */
       uint32_t RESERVED0[9];
  __IO uint32_t PUP;               /*!< Pull-up Control Register                     */
       uint32_t RESERVED1[2];
  __IO uint32_t IE;                /*!< Input Control Register                       */
} TSB_PD_TypeDef;

/**
  * @brief 16-bit Timer/Event Counter (TB)
  */
typedef struct
{
  __IO uint32_t EN;                /*!< Enable Register                              */
  __IO uint32_t RUN;               /*!< RUN Register                                 */
  __IO uint32_t CR;                /*!< Control Register                             */
  __IO uint32_t MOD;               /*!< Mode Register                                */
  __IO uint32_t FFCR;              /*!< Flip-Flop Control Register                   */
  __I  uint32_t ST;                /*!< Status Register                              */
  __IO uint32_t IM;                /*!< Interrupt Mask Register                      */
  __I  uint32_t UC;                /*!< Up-counter Capture Register                  */
  __IO uint32_t RG0;               /*!< RG0 Timer Register                           */
  __IO uint32_t RG1;               /*!< RG1 Timer Register                           */
  __I  uint32_t CP0;               /*!< CP0 Capture Register                         */
  __I  uint32_t CP1;               /*!< CP1 Capture Register                         */
} TSB_TB_TypeDef;

/**
  * @brief SIO/UART (SC)
  */
typedef struct
{
  __IO uint32_t EN;                /*!< Enable Register                              */
  __IO uint32_t BUF;               /*!< Buffer Register                              */
  __IO uint32_t CR;                /*!< Control Register                             */
  __IO uint32_t MOD0;              /*!< Mode Control Register 0                      */
  __IO uint32_t BRCR;              /*!< Baud Rate Generator Control Register         */
  __IO uint32_t BRADD;             /*!< Baud Rate Generator Control Register 2       */
  __IO uint32_t MOD1;              /*!< Mode Control Register 1                      */
  __IO uint32_t MOD2;              /*!< Mode Control Register 2                      */
  __IO uint32_t RFC;               /*!< RX FIFO Configuration Register               */
  __IO uint32_t TFC;               /*!< TX FIFO Configuration Register               */
  __I  uint32_t RST;               /*!< RX FIFO Status Register                      */
  __I  uint32_t TST;               /*!< TX FIFO Status Register                      */
  __IO uint32_t FCNF;              /*!< FIFO Configuration Register                  */
} TSB_SC_TypeDef;

/**
  * @brief Watchdog Timer (WD)
  */
typedef struct
{
  __IO uint32_t MOD;               /*!< Mode Register                                */
  __O  uint32_t CR;                /*!< Control Register                             */
  __I  uint32_t FLG;               /*!< Flag Register                                */
} TSB_WD_TypeDef;

/**
  * @brief Clock Control (CG)
  */
typedef struct
{
  __IO uint32_t PROTECT;           /*!< Protect Register                             */
  __IO uint32_t OSCSEL;            /*!< High-speed oscillation select Register       */
  __I  uint32_t OSCSTF;            /*!< High-speed oscillation status Register       */
  __IO uint32_t CLKCR;             /*!< Clock Control Register                       */
       uint32_t RESERVED0[2];
  __IO uint32_t OSCEN;             /*!< Oscillation enable Register                  */
       uint32_t RESERVED1[2];
  __IO uint32_t WUHCR;             /*!< High-speed oscillation warm-up Control Register*/
} TSB_CG_TypeDef;


/* Memory map */
#define FLASH_BASE            (0x00000000UL)
#define RAM_BASE              (0x20000000UL)
#define PERI_BASE             (0x40000000UL)


#define TSB_SSP0_BASE              (PERI_BASE  + 0x0040000UL)
#define TSB_DMAA_BASE              (PERI_BASE  + 0x004C000UL)
#define TSB_TEMP_BASE              (PERI_BASE  + 0x005D000UL)
#define TSB_DSADA_BASE             (PERI_BASE  + 0x0067000UL)
#define TSB_DSADB_BASE             (PERI_BASE  + 0x0067400UL)
#define TSB_DSADC_BASE             (PERI_BASE  + 0x0067800UL)
#define TSB_DSADD_BASE             (PERI_BASE  + 0x0067C00UL)
#define TSB_T16A0_BASE             (PERI_BASE  + 0x008D000UL)
#define TSB_INT0_BASE              (PERI_BASE  + 0x00B8000UL)
#define TSB_PA_BASE                (PERI_BASE  + 0x00C0000UL)
#define TSB_PB_BASE                (PERI_BASE  + 0x00C0100UL)
#define TSB_PC_BASE                (PERI_BASE  + 0x00C0200UL)
#define TSB_PD_BASE                (PERI_BASE  + 0x00C0300UL)
#define TSB_TB0_BASE               (PERI_BASE  + 0x00C4000UL)
#define TSB_TB1_BASE               (PERI_BASE  + 0x00C4100UL)
#define TSB_TB2_BASE               (PERI_BASE  + 0x00C4200UL)
#define TSB_TB3_BASE               (PERI_BASE  + 0x00C4300UL)
#define TSB_SC0_BASE               (PERI_BASE  + 0x00E1000UL)
#define TSB_WD0_BASE               (PERI_BASE  + 0x00F2000UL)
#define TSB_CG0_BASE               (PERI_BASE  + 0x00F3000UL)


/* Peripheral declaration */
#define TSB_SSP0                   ((    TSB_SSP_TypeDef *)  TSB_SSP0_BASE)
#define TSB_DMAA                   ((    TSB_DMA_TypeDef *)  TSB_DMAA_BASE)
#define TSB_TEMP                   ((   TSB_TEMP_TypeDef *)  TSB_TEMP_BASE)
#define TSB_DSADA                  ((   TSB_DSAD_TypeDef *) TSB_DSADA_BASE)
#define TSB_DSADB                  ((   TSB_DSAD_TypeDef *) TSB_DSADB_BASE)
#define TSB_DSADC                  ((   TSB_DSAD_TypeDef *) TSB_DSADC_BASE)
#define TSB_DSADD                  ((   TSB_DSAD_TypeDef *) TSB_DSADD_BASE)
#define TSB_T16A0                  ((   TSB_T16A_TypeDef *) TSB_T16A0_BASE)
#define TSB_INT0                   ((    TSB_INT_TypeDef *)  TSB_INT0_BASE)
#define TSB_PA                     ((     TSB_PA_TypeDef *)    TSB_PA_BASE)
#define TSB_PB                     ((     TSB_PB_TypeDef *)    TSB_PB_BASE)
#define TSB_PC                     ((     TSB_PC_TypeDef *)    TSB_PC_BASE)
#define TSB_PD                     ((     TSB_PD_TypeDef *)    TSB_PD_BASE)
#define TSB_TB0                    ((     TSB_TB_TypeDef *)   TSB_TB0_BASE)
#define TSB_TB1                    ((     TSB_TB_TypeDef *)   TSB_TB1_BASE)
#define TSB_TB2                    ((     TSB_TB_TypeDef *)   TSB_TB2_BASE)
#define TSB_TB3                    ((     TSB_TB_TypeDef *)   TSB_TB3_BASE)
#define TSB_SC0                    ((     TSB_SC_TypeDef *)   TSB_SC0_BASE)
#define TSB_WD0                    ((     TSB_WD_TypeDef *)   TSB_WD0_BASE)
#define TSB_CG0                    ((     TSB_CG_TypeDef *)   TSB_CG0_BASE)


/* Bit-Band for Device Specific Peripheral Registers */
#define BITBAND_OFFSET (0x02000000UL)
#define BITBAND_PERI_BASE (PERI_BASE + BITBAND_OFFSET)
#define BITBAND_PERI(addr, bitnum) (BITBAND_PERI_BASE + (((uint32_t)(addr) - PERI_BASE) << 5) + ((uint32_t)(bitnum) << 2))



/* Synchronous Serial Port (SSP) */
#define TSB_SSP0_CR0_SPO                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->CR0,6)))
#define TSB_SSP0_CR0_SPH                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->CR0,7)))
#define TSB_SSP0_CR1_LBM                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->CR1,0)))
#define TSB_SSP0_CR1_SSE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->CR1,1)))
#define TSB_SSP0_CR1_MS                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->CR1,2)))
#define TSB_SSP0_CR1_SOD                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->CR1,3)))
#define TSB_SSP0_SR_TFE                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->SR,0)))
#define TSB_SSP0_SR_TNF                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->SR,1)))
#define TSB_SSP0_SR_RNE                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->SR,2)))
#define TSB_SSP0_SR_RFF                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->SR,3)))
#define TSB_SSP0_SR_BSY                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->SR,4)))
#define TSB_SSP0_IMSC_RORIM                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->IMSC,0)))
#define TSB_SSP0_IMSC_RTIM                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->IMSC,1)))
#define TSB_SSP0_IMSC_RXIM                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->IMSC,2)))
#define TSB_SSP0_IMSC_TXIM                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SSP0->IMSC,3)))
#define TSB_SSP0_RIS_RORRIS                       (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->RIS,0)))
#define TSB_SSP0_RIS_RTRIS                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->RIS,1)))
#define TSB_SSP0_RIS_RXRIS                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->RIS,2)))
#define TSB_SSP0_RIS_TXRIS                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->RIS,3)))
#define TSB_SSP0_MIS_RORMIS                       (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->MIS,0)))
#define TSB_SSP0_MIS_RTMIS                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->MIS,1)))
#define TSB_SSP0_MIS_RXMIS                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->MIS,2)))
#define TSB_SSP0_MIS_TXMIS                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SSP0->MIS,3)))
#define TSB_SSP0_ICR_RORIC                        (*((__O  uint32_t *)BITBAND_PERI(&TSB_SSP0->ICR,0)))
#define TSB_SSP0_ICR_RTIC                         (*((__O  uint32_t *)BITBAND_PERI(&TSB_SSP0->ICR,1)))


/* DMA Controller (DMA) */
#define TSB_DMAA_STATUS_MASTER_ENABLE             (*((__I  uint32_t *)BITBAND_PERI(&TSB_DMAA->STATUS,0)))
#define TSB_DMAA_CFG_MASTER_ENABLE                (*((__O  uint32_t *)BITBAND_PERI(&TSB_DMAA->CFG,0)))
#define TSB_DMAA_ERRCLR_ERR_CLR                   (*((__IO uint32_t *)BITBAND_PERI(&TSB_DMAA->ERRCLR,0)))


/* Temperature Sensor (TEMP) */
#define TSB_TEMP_EN_EN0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TEMP->EN,0)))
#define TSB_TEMP_EN_EN1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TEMP->EN,1)))
#define TSB_TEMP_CR_CR0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TEMP->CR,0)))


/* 24bit Delta Sigma AD Converter (DSAD) */
#define TSB_DSADA_CR1_MODEN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADA->CR1,0)))
#define TSB_DSADA_CR1_BIASEN                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADA->CR1,1)))
#define TSB_DSADA_CR2_ADS                         (*((__O  uint32_t *)BITBAND_PERI(&TSB_DSADA->CR2,0)))
#define TSB_DSADA_CR3_REPEAT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADA->CR3,0)))
#define TSB_DSADA_CR3_ADSYNC                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADA->CR3,8)))
#define TSB_DSADA_CR3_DSADHTG                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADA->CR3,12)))
#define TSB_DSADA_CR3_DSADHS                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADA->CR3,13)))
#define TSB_DSADA_CR5_DSADCH                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADA->CR5,0)))
#define TSB_DSADA_ADJ_ADJ                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADA->ADJ,0)))
#define TSB_DSADA_ST_ADBF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADA->ST,0)))
#define TSB_DSADA_ST_EOCF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADA->ST,1)))
#define TSB_DSADA_RES_ADRF                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADA->RES,0)))
#define TSB_DSADA_RES_ADOVR                       (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADA->RES,1)))

#define TSB_DSADB_CR1_MODEN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADB->CR1,0)))
#define TSB_DSADB_CR1_BIASEN                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADB->CR1,1)))
#define TSB_DSADB_CR2_ADS                         (*((__O  uint32_t *)BITBAND_PERI(&TSB_DSADB->CR2,0)))
#define TSB_DSADB_CR3_REPEAT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADB->CR3,0)))
#define TSB_DSADB_CR3_ADSYNC                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADB->CR3,8)))
#define TSB_DSADB_CR3_DSADHTG                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADB->CR3,12)))
#define TSB_DSADB_CR3_DSADHS                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADB->CR3,13)))
#define TSB_DSADB_CR5_DSADCH                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADB->CR5,0)))
#define TSB_DSADB_ADJ_ADJ                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADB->ADJ,0)))
#define TSB_DSADB_ST_ADBF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADB->ST,0)))
#define TSB_DSADB_ST_EOCF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADB->ST,1)))
#define TSB_DSADB_RES_ADRF                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADB->RES,0)))
#define TSB_DSADB_RES_ADOVR                       (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADB->RES,1)))

#define TSB_DSADC_CR1_MODEN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADC->CR1,0)))
#define TSB_DSADC_CR1_BIASEN                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADC->CR1,1)))
#define TSB_DSADC_CR2_ADS                         (*((__O  uint32_t *)BITBAND_PERI(&TSB_DSADC->CR2,0)))
#define TSB_DSADC_CR3_REPEAT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADC->CR3,0)))
#define TSB_DSADC_CR3_ADSYNC                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADC->CR3,8)))
#define TSB_DSADC_CR3_DSADHTG                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADC->CR3,12)))
#define TSB_DSADC_CR3_DSADHS                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADC->CR3,13)))
#define TSB_DSADC_CR5_DSADCH                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADC->CR5,0)))
#define TSB_DSADC_ADJ_ADJ                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADC->ADJ,0)))
#define TSB_DSADC_ST_ADBF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADC->ST,0)))
#define TSB_DSADC_ST_EOCF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADC->ST,1)))
#define TSB_DSADC_RES_ADRF                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADC->RES,0)))
#define TSB_DSADC_RES_ADOVR                       (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADC->RES,1)))

#define TSB_DSADD_CR1_MODEN                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADD->CR1,0)))
#define TSB_DSADD_CR1_BIASEN                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADD->CR1,1)))
#define TSB_DSADD_CR2_ADS                         (*((__O  uint32_t *)BITBAND_PERI(&TSB_DSADD->CR2,0)))
#define TSB_DSADD_CR3_REPEAT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADD->CR3,0)))
#define TSB_DSADD_CR3_ADSYNC                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADD->CR3,8)))
#define TSB_DSADD_CR3_DSADHTG                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADD->CR3,12)))
#define TSB_DSADD_CR3_DSADHS                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADD->CR3,13)))
#define TSB_DSADD_CR5_DSADCH                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADD->CR5,0)))
#define TSB_DSADD_ADJ_ADJ                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_DSADD->ADJ,0)))
#define TSB_DSADD_ST_ADBF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADD->ST,0)))
#define TSB_DSADD_ST_EOCF                         (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADD->ST,1)))
#define TSB_DSADD_RES_ADRF                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADD->RES,0)))
#define TSB_DSADD_RES_ADOVR                       (*((__I  uint32_t *)BITBAND_PERI(&TSB_DSADD->RES,1)))


/* 16-bit TimerA (T16A) */
#define TSB_T16A0_EN_HALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A0->EN,1)))
#define TSB_T16A0_RUN_RUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A0->RUN,0)))
#define TSB_T16A0_CR_CLK                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_T16A0->CR,0)))


/* Interrupt Controller (INT) */
#define TSB_INT0_CLR_CLR                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_INT0->CLR,0)))
#define TSB_INT0_RESETF_RSTF0                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_INT0->RESETF,0)))
#define TSB_INT0_RESETF_RSTF3                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_INT0->RESETF,3)))
#define TSB_INT0_RESETF_RSTF4                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_INT0->RESETF,4)))


/* Port A (PA) */
#define TSB_PA_DATA_PA0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,0)))
#define TSB_PA_DATA_PA1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,1)))
#define TSB_PA_DATA_PA2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,2)))
#define TSB_PA_DATA_PA3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,3)))
#define TSB_PA_DATA_PA4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,4)))
#define TSB_PA_DATA_PA5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,5)))
#define TSB_PA_DATA_PA6                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,6)))
#define TSB_PA_DATA_PA7                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->DATA,7)))
#define TSB_PA_CR_PA0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,0)))
#define TSB_PA_CR_PA1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,1)))
#define TSB_PA_CR_PA2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,2)))
#define TSB_PA_CR_PA3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,3)))
#define TSB_PA_CR_PA4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,4)))
#define TSB_PA_CR_PA5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,5)))
#define TSB_PA_CR_PA6C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,6)))
#define TSB_PA_CR_PA7C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->CR,7)))
#define TSB_PA_FR1_PA0F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->FR1,0)))
#define TSB_PA_FR1_PA1F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->FR1,1)))
#define TSB_PA_FR1_PA2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->FR1,2)))
#define TSB_PA_FR1_PA3F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->FR1,3)))
#define TSB_PA_FR1_PA4F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->FR1,4)))
#define TSB_PA_FR1_PA5F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->FR1,5)))
#define TSB_PA_FR1_PA6F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->FR1,6)))
#define TSB_PA_PUP_PA0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,0)))
#define TSB_PA_PUP_PA1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,1)))
#define TSB_PA_PUP_PA2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,2)))
#define TSB_PA_PUP_PA3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,3)))
#define TSB_PA_PUP_PA4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,4)))
#define TSB_PA_PUP_PA5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,5)))
#define TSB_PA_PUP_PA6UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,6)))
#define TSB_PA_PUP_PA7UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->PUP,7)))
#define TSB_PA_IE_PA0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,0)))
#define TSB_PA_IE_PA1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,1)))
#define TSB_PA_IE_PA2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,2)))
#define TSB_PA_IE_PA3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,3)))
#define TSB_PA_IE_PA4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,4)))
#define TSB_PA_IE_PA5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,5)))
#define TSB_PA_IE_PA6IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,6)))
#define TSB_PA_IE_PA7IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PA->IE,7)))


/* Port B (PB) */
#define TSB_PB_DATA_PB0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,0)))
#define TSB_PB_DATA_PB1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,1)))
#define TSB_PB_DATA_PB2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,2)))
#define TSB_PB_DATA_PB3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,3)))
#define TSB_PB_DATA_PB4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,4)))
#define TSB_PB_DATA_PB5                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,5)))
#define TSB_PB_DATA_PB6                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,6)))
#define TSB_PB_DATA_PB7                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->DATA,7)))
#define TSB_PB_CR_PB0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,0)))
#define TSB_PB_CR_PB1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,1)))
#define TSB_PB_CR_PB2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,2)))
#define TSB_PB_CR_PB3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,3)))
#define TSB_PB_CR_PB4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,4)))
#define TSB_PB_CR_PB5C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,5)))
#define TSB_PB_CR_PB6C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,6)))
#define TSB_PB_CR_PB7C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->CR,7)))
#define TSB_PB_FR1_PB0F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,0)))
#define TSB_PB_FR1_PB1F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,1)))
#define TSB_PB_FR1_PB2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,2)))
#define TSB_PB_FR1_PB3F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,3)))
#define TSB_PB_FR1_PB4F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,4)))
#define TSB_PB_FR1_PB5F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->FR1,5)))
#define TSB_PB_PUP_PB0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,0)))
#define TSB_PB_PUP_PB1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,1)))
#define TSB_PB_PUP_PB2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,2)))
#define TSB_PB_PUP_PB3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,3)))
#define TSB_PB_PUP_PB4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,4)))
#define TSB_PB_PUP_PB5UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,5)))
#define TSB_PB_PUP_PB6UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,6)))
#define TSB_PB_PUP_PB7UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->PUP,7)))
#define TSB_PB_IE_PB0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,0)))
#define TSB_PB_IE_PB1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,1)))
#define TSB_PB_IE_PB2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,2)))
#define TSB_PB_IE_PB3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,3)))
#define TSB_PB_IE_PB4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,4)))
#define TSB_PB_IE_PB5IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,5)))
#define TSB_PB_IE_PB6IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,6)))
#define TSB_PB_IE_PB7IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PB->IE,7)))


/* Port C (PC) */
#define TSB_PC_DATA_PC0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,0)))
#define TSB_PC_DATA_PC1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,1)))
#define TSB_PC_DATA_PC2                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,2)))
#define TSB_PC_DATA_PC3                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,3)))
#define TSB_PC_DATA_PC4                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->DATA,4)))
#define TSB_PC_CR_PC0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,0)))
#define TSB_PC_CR_PC1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,1)))
#define TSB_PC_CR_PC2C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,2)))
#define TSB_PC_CR_PC3C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,3)))
#define TSB_PC_CR_PC4C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->CR,4)))
#define TSB_PC_FR1_PC2F1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->FR1,2)))
#define TSB_PC_PUP_PC0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,0)))
#define TSB_PC_PUP_PC1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,1)))
#define TSB_PC_PUP_PC2UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,2)))
#define TSB_PC_PUP_PC3UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,3)))
#define TSB_PC_PUP_PC4UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PUP,4)))
#define TSB_PC_PDN_PC3DN                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->PDN,3)))
#define TSB_PC_IE_PC0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,0)))
#define TSB_PC_IE_PC1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,1)))
#define TSB_PC_IE_PC2IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,2)))
#define TSB_PC_IE_PC3IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,3)))
#define TSB_PC_IE_PC4IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PC->IE,4)))


/* Port D (PD) */
#define TSB_PD_DATA_PD0                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->DATA,0)))
#define TSB_PD_DATA_PD1                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->DATA,1)))
#define TSB_PD_CR_PD0C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->CR,0)))
#define TSB_PD_CR_PD1C                            (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->CR,1)))
#define TSB_PD_PUP_PD0UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PUP,0)))
#define TSB_PD_PUP_PD1UP                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->PUP,1)))
#define TSB_PD_IE_PD0IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->IE,0)))
#define TSB_PD_IE_PD1IE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_PD->IE,1)))


/* 16-bit Timer/Event Counter (TB) */
#define TSB_TB0_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->EN,6)))
#define TSB_TB0_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->EN,7)))
#define TSB_TB0_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->RUN,0)))
#define TSB_TB0_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->RUN,2)))
#define TSB_TB0_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,0)))
#define TSB_TB0_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,1)))
#define TSB_TB0_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,5)))
#define TSB_TB0_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->CR,7)))
#define TSB_TB0_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->MOD,3)))
#define TSB_TB0_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB0->MOD,6)))
#define TSB_TB0_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->FFCR,2)))
#define TSB_TB0_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->FFCR,3)))
#define TSB_TB0_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->FFCR,4)))
#define TSB_TB0_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->FFCR,5)))
#define TSB_TB0_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->IM,0)))
#define TSB_TB0_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->IM,1)))
#define TSB_TB0_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB0->IM,2)))

#define TSB_TB1_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->EN,6)))
#define TSB_TB1_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->EN,7)))
#define TSB_TB1_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->RUN,0)))
#define TSB_TB1_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->RUN,2)))
#define TSB_TB1_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,0)))
#define TSB_TB1_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,1)))
#define TSB_TB1_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,5)))
#define TSB_TB1_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->CR,7)))
#define TSB_TB1_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->MOD,3)))
#define TSB_TB1_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB1->MOD,6)))
#define TSB_TB1_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->FFCR,2)))
#define TSB_TB1_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->FFCR,3)))
#define TSB_TB1_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->FFCR,4)))
#define TSB_TB1_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->FFCR,5)))
#define TSB_TB1_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->IM,0)))
#define TSB_TB1_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->IM,1)))
#define TSB_TB1_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB1->IM,2)))

#define TSB_TB2_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->EN,6)))
#define TSB_TB2_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->EN,7)))
#define TSB_TB2_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->RUN,0)))
#define TSB_TB2_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->RUN,2)))
#define TSB_TB2_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,0)))
#define TSB_TB2_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,1)))
#define TSB_TB2_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,5)))
#define TSB_TB2_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->CR,7)))
#define TSB_TB2_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->MOD,3)))
#define TSB_TB2_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB2->MOD,6)))
#define TSB_TB2_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->FFCR,2)))
#define TSB_TB2_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->FFCR,3)))
#define TSB_TB2_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->FFCR,4)))
#define TSB_TB2_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->FFCR,5)))
#define TSB_TB2_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->IM,0)))
#define TSB_TB2_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->IM,1)))
#define TSB_TB2_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB2->IM,2)))

#define TSB_TB3_EN_TBHALT                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->EN,6)))
#define TSB_TB3_EN_TBEN                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->EN,7)))
#define TSB_TB3_RUN_TBRUN                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->RUN,0)))
#define TSB_TB3_RUN_TBPRUN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->RUN,2)))
#define TSB_TB3_CR_CSSEL                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,0)))
#define TSB_TB3_CR_TRGSEL                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,1)))
#define TSB_TB3_CR_TBSYNC                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,5)))
#define TSB_TB3_CR_TBWBF                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->CR,7)))
#define TSB_TB3_MOD_TBCLE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->MOD,3)))
#define TSB_TB3_MOD_TBCP                          (*((__O  uint32_t *)BITBAND_PERI(&TSB_TB3->MOD,6)))
#define TSB_TB3_FFCR_TBE0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->FFCR,2)))
#define TSB_TB3_FFCR_TBE1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->FFCR,3)))
#define TSB_TB3_FFCR_TBC0T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->FFCR,4)))
#define TSB_TB3_FFCR_TBC1T1                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->FFCR,5)))
#define TSB_TB3_IM_TBIM0                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->IM,0)))
#define TSB_TB3_IM_TBIM1                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->IM,1)))
#define TSB_TB3_IM_TBIMOF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_TB3->IM,2)))


/* SIO/UART (SC) */
#define TSB_SC0_EN_SIOE                           (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->EN,0)))
#define TSB_SC0_EN_BRCKSEL                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->EN,1)))
#define TSB_SC0_MOD0_RXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD0,5)))
#define TSB_SC0_MOD0_TB8                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD0,7)))
#define TSB_SC0_BRCR_BRADDE                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->BRCR,6)))
#define TSB_SC0_MOD1_TXE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD1,4)))
#define TSB_SC0_MOD2_WBUF                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,2)))
#define TSB_SC0_MOD2_DRCHG                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,3)))
#define TSB_SC0_MOD2_SBLEN                        (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,4)))
#define TSB_SC0_MOD2_TXRUN                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,5)))
#define TSB_SC0_MOD2_RBFLL                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,6)))
#define TSB_SC0_MOD2_TBEMP                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->MOD2,7)))
#define TSB_SC0_TST_TUR                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_SC0->TST,7)))
#define TSB_SC0_FCNF_CNFG                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,0)))
#define TSB_SC0_FCNF_RXTXCNT                      (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,1)))
#define TSB_SC0_FCNF_RFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,2)))
#define TSB_SC0_FCNF_TFIE                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,3)))
#define TSB_SC0_FCNF_RFST                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_SC0->FCNF,4)))


/* Watchdog Timer (WD) */
#define TSB_WD0_MOD_RESCR                         (*((__IO uint32_t *)BITBAND_PERI(&TSB_WD0->MOD,1)))
#define TSB_WD0_MOD_WDTE                          (*((__IO uint32_t *)BITBAND_PERI(&TSB_WD0->MOD,7)))
#define TSB_WD0_FLG_FLG                           (*((__I  uint32_t *)BITBAND_PERI(&TSB_WD0->FLG,0)))


/* Clock Control (CG) */
#define TSB_CG0_CLKCR_FPSEL                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG0->CLKCR,6)))
#define TSB_CG0_CLKCR_STICK                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG0->CLKCR,7)))
#define TSB_CG0_OSCEN_IHOSCEN                     (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG0->OSCEN,0)))
#define TSB_CG0_WUHCR_WUON                        (*((__O  uint32_t *)BITBAND_PERI(&TSB_CG0->WUHCR,0)))
#define TSB_CG0_WUHCR_WUEF                        (*((__I  uint32_t *)BITBAND_PERI(&TSB_CG0->WUHCR,1)))
#define TSB_CG0_WUHCR_WUCLK                       (*((__IO uint32_t *)BITBAND_PERI(&TSB_CG0->WUHCR,8)))

/** @} */ /* End of group Device_Peripheral_registers */

#ifdef __cplusplus
}
#endif

#endif  /* __TMPM311_H__ */

/** @} */ /* End of group TMPM311 */
/** @} */ /* End of group TOSHIBA_TX03_MICROCONTROLLER */
