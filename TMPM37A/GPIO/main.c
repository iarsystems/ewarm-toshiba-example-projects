/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM37A
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM37A Evaluation Board.
 *
 *    It uses the GP Timer interrupt handler to toggle PJ5 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2015/Nov/16
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM37A
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "Toshiba\TMPM37A.h"
#include "system_TMPM37A.h"

#define PIN5		(0x0020)

#pragma section=".intvec"


void INTTB00_IRQHandler(void)
{
    static int step=0;
    NVIC_ClearPendingIRQ(INTTB00_IRQn);
    if (++step%64==0) {
      TSB_PJ->DATA ^= PIN5;
    }
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Setup LED port Output (PJ5)
  TSB_PJ->CR |= PIN5;
  TSB_PJ->PUP |= PIN5;
  TSB_PJ->IE &= ~PIN5;
  TSB_PJ->DATA |= PIN5;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTTB00_IRQn);
  TSB_TB0->EN = 0x80;
  TSB_TB0->RUN = 0;
  TSB_TB0->MOD = 0x042;
  TSB_TB0->RG1 = 0x8000;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTTB00_IRQn, 1);
  NVIC_EnableIRQ(INTTB00_IRQn);
  TSB_TB0->RUN = 0x5;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
