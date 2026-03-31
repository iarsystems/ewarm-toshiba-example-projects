/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM46B
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM46B Evaluation Board.
 *
 *    It uses the TMR interrupt handler to toggle PC0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 08.12.2014
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM46B-SK
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "TMPM46B.h"
#include "system_TMPM46B.h"

#pragma section=".intvec"


void INTTB0_IRQHandler(void)
{
    static int step=0;
    NVIC_ClearPendingIRQ(INTTB0_IRQn);
    if (++step%128==0) {
      TSB_PC->DATA ^= (1<<0);
    }
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Setup LED port Output (PC0)
  TSB_PC->CR |= (1<<0);
  TSB_PC->PUP |= (1<<0);
  TSB_PC->IE &= ~(1<<0);
  TSB_PC->DATA |= (1<<0);

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
