/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2014
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM351
 *    family microcontrollers. It is developed for TMPM351-SK Board.
 *    It uses the TIMER0 to toggle the LED port (PG0-PG1, PH0-PH5).
 *
 *    History :
 *    1. Date        : 09.06.2011
 *       Author      : Stanimir Bonev
 *       Description : Initioal version TMPM350-SK
 *    2. Date        : 20.01.2014
 *       Author      : Santosh Pawar
 *       Description : updated for TMPM351-SK
 *
 * Jumpers:
 *  E_JP7   - filled
 *  E_JP8   - filled
 *  E_JP9   - filled
 *  E_JP10  - filled
 *  E_JP11  - filled
 *  E_JP12  - filled
 *  E_JP13  - filled
 *  E_JP14  - filled
 *
 * Note: Use only core reset strategy!
 *
 *    $Revision: 45019 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <assert.h>
#include <intrinsics.h>
#include <Toshiba\iotmpm351f10tfg.h>
#include "arm_comm.h"

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define TICK_PER_SEC  10
#define MAIN_OSC_FREQ   ( 16000000ul)
#define SYS_FREQ        (144000000ul)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = 144MHz
*/
void InitClock(void)
{
  // nothing special. clock is setup by hardware
}

/*************************************************************************
 * Function Name: NVIC_IntEnable
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description: Enable interrup at NVIC
 *
 *
 *************************************************************************/
void NVIC_IntEnable(Int32U IntNumber)
{
volatile unsigned long * pNVIC_SetEn = &SETENA0;

  assert((INTERR <= IntNumber) && (INTEXC >= IntNumber));
  IntNumber -= INTERR;

  pNVIC_SetEn += IntNumber/32;
  *pNVIC_SetEn = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_IntDisable
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description: Disables interrup at NVIC
 *
 *
 *************************************************************************/
void NVIC_IntDisable(Int32U IntNumber)
{
volatile unsigned long * pNVIC_ClrEn = &CLRENA0;

  assert((INTERR <= IntNumber) && (INTEXC >= IntNumber));
  IntNumber -= INTERR;

  pNVIC_ClrEn += IntNumber/32;
  *pNVIC_ClrEn = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description:Clear pending interrupt at NVIC
 *
 *
 *************************************************************************/
void NVIC_ClrPend(Int32U IntNumber)
{
volatile unsigned long * pNVIC_ClrPend = &CLRPEND0;

  assert((INTERR <= IntNumber) && (INTEXC >= IntNumber));
  IntNumber -= INTERR;

  pNVIC_ClrPend += IntNumber/32;
  *pNVIC_ClrPend = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrup number, Interrupt Priority
 * Return: void
 *
 * Description:Sets Interrupt priority
 *
 *
 *************************************************************************/
void NVIC_IntPri(Int32U IntNumber, Int8U Priority)
{
volatile Int8U * pNVIC_IntPri = (Int8U *)&IP0;

  assert((INTERR <= IntNumber) && (INTEXC >= IntNumber));
  IntNumber -= INTERR;
  pNVIC_IntPri += IntNumber;
  *pNVIC_IntPri = Priority;
}

void INTCMP00_IRQHandler (void)
{
static unsigned int i;
  OUTG_bit.O0 = ~i&1;
  OUTG_bit.O1 = ~(i>>1);
  OUTH = (~i>>2)&0x3F;
  NVIC_ClrPend(INTCMP00);
  i++;
}


int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");
  /*Disable WDT*/
  WDTCTL = 1;
  WDTCMD = 0x5354;

  // Setup PLL controller
  InitClock();

  // Setup LED port Output (PG0-PG1,PH0-PH5)
  FNCSELG_bit.FS0 = 0;
  FNCSELG_bit.FS1 = 0;
  OUTG_bit.O0 = 1;
  OUTG_bit.O1 = 1;
  OENG_bit.OE0 = 1;
  OENG_bit.OE1 = 1;
  FNCSELH = 0;
  OUTH = 0x3F;
  OENH = 0x3F;

  // Init Timer 0
  // Stop and clear timer's counter
  TB00TRUN = 0;
  // div 1/2
  TB00TCR_bit.DIVSEL = 1;
  // Counter Clear Enable
  TB00CMP0CR_bit.CNTCLEN = 1;
  // Compare Enable
  TB00CMP0CR_bit.CPMEN = 1;
  TB00CMP0 = SYS_FREQ/(TICK_PER_SEC*2);
  // Enable NVIC TMR0 Interrupt
  NVIC_IntEnable(INTCMP00);
  NVIC_IntPri(INTCMP00,16);
  TB00TRUN_bit.DIVRUN = 1;
  TB00TRUN_bit.TBRUN = 1;

  __enable_interrupt();

  while(1)
  {
  }
}

