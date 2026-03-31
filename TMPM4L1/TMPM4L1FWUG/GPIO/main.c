/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM4L1FWUG family microcontrollers.
 *    It is developed for Toshiba TMPM4L1FWUG Evaluation Board.
 *
 *    It uses the GP Timer interrupt handler to toggle PC3 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2018/Jun/28
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM4L1FWUG
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "io_macros.h"
#include "TMPM4Lx.h"
#include "system_TMPM4Lx.h"

#pragma section=".intvec"

#define LED_PIN   (1<<3u)

void INTT32A00_AT_CT_IRQHandler(void)
{
  // Clear interrupt edge
  TSB_IB->IMC008 |= (1u<<6);
  NVIC_ClearPendingIRQ(INTT32A00_AT_CT_IRQn);
  TSB_PC->DATA ^= LED_PIN;
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Enable clock to all modules
  TSB_CG->PROTECT = 0x00C1;
  TSB_CG->FSYSENA |= 0xFFFFFFFF;

  // Setup LED port Output (PC3)
  TSB_PC->CR |= LED_PIN;
  TSB_PC->PUP |= LED_PIN;
  TSB_PC->IE &= ~LED_PIN;
  TSB_PC->FR1 &= ~LED_PIN;
  TSB_PC->FR2 &= ~LED_PIN;
  TSB_PC->FR3 &= ~LED_PIN;
  TSB_PC->FR4 &= ~LED_PIN;
  TSB_PC->DATA |= LED_PIN;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTT32A00_AT_CT_IRQn);
  TSB_T32A0->RUNA = 0;
  while(TSB_T32A0->RUNA & (1u<<4)); //Wait until RUNFLGA==1
  TSB_T32A0->CRA = (7<<28) | (3<<8) | 1;
  TSB_T32A0->RGA1 = 0x8000;
  TSB_T32A0->RELDA = 0x8000;

  // Enable interrupt for Timer
  TSB_IB->IMC008 = 0xC7;
  NVIC_SetPriority(INTT32A00_AT_CT_IRQn, 1);
  NVIC_EnableIRQ(INTT32A00_AT_CT_IRQn);
  // Start Timer
  TSB_T32A0->RUNA = 0x03;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
