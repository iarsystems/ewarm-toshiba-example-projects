/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM4K4FYAUG family microcontrollers.
 *    It is developed for Toshiba TMPM4K4FYAUG Evaluation Board.
 *
 *    It uses the GP Timer interrupt handler to toggle PD0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2017/Sep/01
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM4K4FYAUG
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "io_macros.h"
#include "TMPM4K4A.h"
#include "system_TMPM4KxA.h"

#pragma section=".intvec"

#define LED_PIN   0x01

__IO_REG32(VTOR,   0xE000ED08,__READ_WRITE);

void INTT32A0AC_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(INTT32A0AC_IRQn);
    TSB_PD->DATA ^= LED_PIN;
}

int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  // Enable clock to all modules
  TSB_CG->FSYSENA |= 0xFFFFFFFF;
  TSB_CG->FSYSENB |= 0x000000FF;

  // Setup LED port Output (PD0)
  TSB_PD->CR |= LED_PIN;
  TSB_PD->PUP |= LED_PIN;
  TSB_PD->PDN &= ~LED_PIN;
  TSB_PD->IE &= ~LED_PIN;
  TSB_PD->DATA |= LED_PIN;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTT32A0AC_IRQn);
  TSB_T32A0->RUNA = 1;
  TSB_T32A0->CRA = (7<<28) | 1;
  TSB_T32A0->RGA0 = 0x8000;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTT32A0AC_IRQn, 1);
  NVIC_EnableIRQ(INTT32A0AC_IRQn);
  // Start Timer
  TSB_T32A0->RUNA = 0x03;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
