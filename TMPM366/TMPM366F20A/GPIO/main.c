/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM366F20A family microcontrollers.
 *    It is developed for Toshiba TMPM366F20A Evaluation Board.
 *
 *    It uses the GP Timer interrupt handler to toggle PJ0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2015/Dec/09
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM366F20A
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "Toshiba\TMPM366F20A.h"
#include "system_TMPM366F20A.h"

#pragma section=".intvec"

#define PIN0		0x001


void INTTB0_IRQHandler(void)
{
    static int step=0;
    NVIC_ClearPendingIRQ(INTTB0_IRQn);
    if (++step%128==0) {
      TSB_PJ->DATA ^= PIN0;
    }
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Setup LED port Output (PJ0)
  TSB_PJ->CR |= PIN0;
  TSB_PJ->PUP |= PIN0;
  TSB_PJ->IE &= ~PIN0;
  TSB_PJ->DATA |= PIN0;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTTB0_IRQn);
  TSB_TB0->EN = 0x80;
  TSB_TB0->RUN = 0;
  TSB_TB0->MOD = 0x042;
  TSB_TB0->RG1 = 0x8000;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTTB0_IRQn, 1);
  NVIC_EnableIRQ(INTTB0_IRQn);
  TSB_TB0->RUN = 0x5;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
