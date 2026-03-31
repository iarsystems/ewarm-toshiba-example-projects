/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : drv_nvic.c
 *    Description : Toshiba TMPM440 Nested Vectored Interrupt Control
 *
 *    History :
 *    1. Date        : June 2011
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    2. Date        : 7.2013
 *       Author      : Santosh Pawar
 *       Description : Ported to Toshiba TMPM440
 *
 *    $Revision: 41 $
 **************************************************************************/
/** include files **/
#include <stdint.h>
#include <Toshiba\iotmpm440FxXBG.h>
#include <assert.h>
#include "drv_nvic.h"

/** local definitions **/

/** default settings **/

/** external functions **/
#pragma section=".intvec"

/** external data **/

/** internal functions **/

/** public data **/

/** private data **/
static uint32_t CriticalSecCntr;

/** public functions **/
/*************************************************************************
 * Function Name:   EntrCritSection
 * Parameters:      none
 * Return:          none
 *
 * Description:     Enter critical mode
 *
 *************************************************************************/
void EntrCritSection(void)
{
  if(CriticalSecCntr == 0)
  {
    asm("CPSID i");
  }
  // avoid lost of one count in case of simultaneously calling from both places
  ++CriticalSecCntr;
}

/*************************************************************************
 * Function Name:   ExtCritSection
 * Parameters:      none
 * Return:          none
 *
 * Description:     Exit from critical mode
 *
 *************************************************************************/
void ExtCritSection(void)
{
  if(--CriticalSecCntr == 0)
  {
    asm("CPSIE i");
  }
}

/*************************************************************************
 * Function Name:   Default_Handler
 * Parameters:      none
 * Return:          none
 *
 * Description:     Default Interrupt Handler
 *
 *************************************************************************/
void Default_Handler(void)
{
  /* Do nothing */
}

/*************************************************************************
 * Function Name:   NVIC_Init
 * Parameters:      none
 * Return:          none
 *
 * Description:     Setup Interrupt controller
 *
 *************************************************************************/
void NVIC_Init(void)
{
  /* Setup vector table */
  VTOR  = (unsigned int)__segment_begin(".intvec");

}

/*************************************************************************
 * Function Name:   NVIC_EnableIRQ
 * Parameters:      IntNumber - Interrupt number
 * Return:          none
 *
 * Description:     Enable interrupt at NVIC
 *
 *************************************************************************/
void NVIC_EnableIRQ(uint32_t IntNumber)
{
volatile unsigned long * pNVIC_SetEn = &SETENA0;

  assert((INT_0 <= IntNumber) && (INT_TCTBT >= IntNumber));
  IntNumber -= INT_0;

  pNVIC_SetEn += IntNumber/32;
  *pNVIC_SetEn = (1UL<<(IntNumber%32));
}

/*************************************************************************
 * Function Name:   NVIC_DisableIRQ
 * Parameters:      IntNumber - Interrupt number
 * Return:          none
 *
 * Description:     Disable interrupt at NVIC
 *
 *************************************************************************/
void NVIC_DisableIRQ(uint32_t IntNumber)
{
volatile unsigned long * pNVIC_ClrEn = &CLRENA0;

  assert((INT_0 <= IntNumber) && (INT_TCTBT >= IntNumber));
  IntNumber -= INT_0;

  pNVIC_ClrEn += IntNumber/32;
  *pNVIC_ClrEn = (1UL<<(IntNumber%32));
}

/*************************************************************************
 * Function Name:   NVIC_ClearPendingIRQ
 * Parameters:      IntNumber - Interrupt number
 * Return:          none
 *
 * Description:     Clear pending interrupt at NVIC
 *
 *************************************************************************/
void NVIC_ClearPendingIRQ(uint32_t IntNumber)
{
volatile unsigned long * pNVIC_ClrPend = &CLRPEND0;

  assert((INT_0 <= IntNumber) && (INT_TCTBT >= IntNumber));
  IntNumber -= INT_0;

  pNVIC_ClrPend += IntNumber/32;
  *pNVIC_ClrPend = (1UL<<(IntNumber%32));
}


/*************************************************************************
 * Function Name:   NVIC_SetPriority
 * Parameters:      IntNumber - Interrupt number,
 *                  Priority - Interrupt priority
 * Return:          none
 *
 * Description:     Sets Interrupt priority
 *
 *************************************************************************/
void NVIC_SetPriority(uint32_t IntNumber, uint8_t Priority)
{
volatile uint8_t * pNVIC_IntPri = (uint8_t *)&IP0;

  assert((INT_0 <= IntNumber) && (INT_TCTBT >= IntNumber));
  IntNumber -= INT_0;
  pNVIC_IntPri += IntNumber;
  *pNVIC_IntPri = Priority;
}

/*************************************************************************
 * Function Name:   NVIC_SetTrigMode
 * Parameters:      IntNumber - Interrupt number,
 *                  mode - Interrupt triggger mode
 * Return:          none
 *
 * Description:     Sets Interrupt triggger mode
 *
 *************************************************************************/
void NVIC_SetTrigMode(uint32_t IntNumber, int_trg_mode_t mode)
{
  assert((INT_0 <= IntNumber) && (INT_TCTBT >= IntNumber));
  switch (IntNumber) {
  case INT_0:
    CGIMCGA_bit.INT00EN = 1;
    CGIMCGA_bit.EMCG00 = mode;
    break;
  case INT_1:
    CGIMCGA_bit.INT01EN = 1;
    CGIMCGA_bit.EMCG01 = mode;
    break;
  case INT_2:
    CGIMCGA_bit.INT02EN = 1;
    CGIMCGA_bit.EMCG02 = mode;
    break;
  case INT_3:
    CGIMCGA_bit.INT03EN = 1;
    CGIMCGA_bit.EMCG03 = mode;
    break;

  case INT_4:
    CGIMCGB_bit.INT04EN = 1;
    CGIMCGB_bit.EMCG04 = mode;
    break;
  case INT_5:
    CGIMCGB_bit.INT05EN = 1;
    CGIMCGB_bit.EMCG05 = mode;
    break;
  case INT_6:
    CGIMCGB_bit.INT06EN = 1;
    CGIMCGB_bit.EMCG06 = mode;
    break;
  case INT_7:
    CGIMCGB_bit.INT07EN = 1;
    CGIMCGB_bit.EMCG07 = mode;
    break;

  case INT_8:
    CGIMCGC_bit.INT08EN = 1;
    CGIMCGC_bit.EMCG08 = mode;
    break;
  case INT_9:
    CGIMCGC_bit.INT09EN = 1;
    CGIMCGC_bit.EMCG09 = mode;
    break;
  case INT_A:
    CGIMCGC_bit.INT0AEN = 1;
    CGIMCGC_bit.EMCG0A = mode;
    break;
  case INT_B:
    CGIMCGC_bit.INT0BEN = 1;
    CGIMCGC_bit.EMCG0B = mode;
    break;

  case INT_C:
    CGIMCGD_bit.INT0CEN = 1;
    CGIMCGD_bit.EMCG0C = mode;
    break;
  case INT_D:
    CGIMCGD_bit.INT0DEN = 1;
    CGIMCGD_bit.EMCG0D = mode;
    break;
  case INT_E:
    CGIMCGD_bit.INT0EEN = 1;
    CGIMCGD_bit.EMCG0E = mode;
    break;
  case INT_F:
    CGIMCGD_bit.INT0FEN = 1;
    CGIMCGD_bit.EMCG0F = mode;
    break;

  case INT_10:
    CGIMCGE_bit.INT10EN = 1;
    CGIMCGE_bit.EMCG10 = mode;
    break;
  case INT_11:
    CGIMCGE_bit.INT11EN = 1;
    CGIMCGE_bit.EMCG11 = mode;
    break;
  case INT_12:
    CGIMCGE_bit.INT12EN = 1;
    CGIMCGE_bit.EMCG12 = mode;
    break;
  case INT_13:
    CGIMCGE_bit.INT13EN = 1;
    CGIMCGE_bit.EMCG13 = mode;
    break;

  case INT_14:
    CGIMCGF_bit.INT14EN = 1;
    CGIMCGF_bit.EMCG14 = mode;
    break;
  case INT_15:
    CGIMCGF_bit.INT15EN = 1;
    CGIMCGF_bit.EMCG15 = mode;
    break;
  case INT_KWUPA:
    CGIMCGF_bit.INT16EN = 1;
    CGIMCGF_bit.EMCG16 = mode;
    break;
  case INT_KWUPB:
    CGIMCGF_bit.INT17EN = 1;
    CGIMCGF_bit.EMCG17 = mode;
    break;

  case INT_KSCAN:
    CGIMCGG_bit.INT18EN = 1;
    CGIMCGG_bit.EMCG18 = mode;
    break;
  case INT_RTC:
    CGIMCGG_bit.INT19EN = 1;
    CGIMCGG_bit.EMCG19 = mode;
    break;
  case INT_PHC00:
    CGIMCGG_bit.INT1AEN = 1;
    CGIMCGG_bit.EMCG1A = mode;
    break;
  case INT_PHC01:
    CGIMCGG_bit.INT1BEN = 1;
    CGIMCGG_bit.EMCG1B = mode;
    break;

  case INT_PHC0EVRY:
    CGIMCGH_bit.INT1CEN = 1;
    CGIMCGH_bit.EMCG1C = mode;
    break;
  case INT_PHC10:
    CGIMCGH_bit.INT1DEN = 1;
    CGIMCGH_bit.EMCG1D = mode;
    break;
  case INT_PHC11:
    CGIMCGH_bit.INT1EEN = 1;
    CGIMCGH_bit.EMCG1E = mode;
    break;
  case INT_PHC1EVRY:
    CGIMCGH_bit.INT1FEN = 1;
    CGIMCGH_bit.EMCG1F = mode;
    break;

  default:
    break;
  }
}

/*************************************************************************
 * Function Name:   NVIC_ClearTrigIRQ
 * Parameters:      IntNumber - Interrupt number,
 * Return:          none
 *
 * Description:     Clear Interrupt triggger status
 *
 *************************************************************************/
void NVIC_ClearTrigIRQ(uint32_t IntNumber)
{
  assert((INT_0 <= IntNumber) && (INT_TCTBT >= IntNumber));

  if ((INT_0 <= IntNumber) && (INT_RTC >= IntNumber)) {
    CGICRCG_bit.ICRCG = IntNumber-INT_0;
  }
  else if ((INT_PHC00 <= IntNumber) && (INT_PHC1EVRY >= IntNumber)) {
    CGICRCG_bit.ICRCG = 0x1A + IntNumber-INT_PHC00;
  }
}
/** private functions **/
