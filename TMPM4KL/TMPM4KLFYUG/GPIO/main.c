/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM4KLFYUG family microcontrollers.
 *    It is developed for Toshiba TMPM4KLFYUG Evaluation Board.
 *
 *    It uses the GP Timer interrupt handler to toggle PC0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2018/Jan/10
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM4KLFYUG
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "io_macros.h"
#include "TMPM4KL.h"
#include "system_TMPM4Ky.h"

#pragma section=".intvec"

#define LED_PIN   0x01

__IO_REG32(VTOR,   0xE000ED08,__READ_WRITE);

void INTT32A00AC_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(INTT32A00AC_IRQn);
    TSB_PC->DATA ^= LED_PIN;
}

int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  // Enable clock to all modules
  TSB_CG->FSYSMENA |= 0xFFFFFFFF;
  TSB_CG->FSYSMENB |= 0xFFFFFFFF;

  // Setup LED port Output (PC0)
  TSB_PC->CR |= LED_PIN;
  TSB_PC->PUP |= LED_PIN;
  TSB_PC->PDN &= ~LED_PIN;
  TSB_PC->FR1 &= ~LED_PIN;
  TSB_PC->FR2 &= ~LED_PIN;
  TSB_PC->FR4 &= ~LED_PIN;
  TSB_PC->FR5 &= ~LED_PIN;
  TSB_PC->FR6 &= ~LED_PIN;
  TSB_PC->IE &= ~LED_PIN;
  TSB_PC->DATA |= LED_PIN;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTT32A00AC_IRQn);
  TSB_T32A0->RUNA = 1;
  TSB_T32A0->CRA = (7<<28) | 1;
  TSB_T32A0->RGA0 = 0x8000;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTT32A00AC_IRQn, 1);
  NVIC_EnableIRQ(INTT32A00AC_IRQn);
  // Start Timer
  TSB_T32A0->RUNA = 0x03;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
