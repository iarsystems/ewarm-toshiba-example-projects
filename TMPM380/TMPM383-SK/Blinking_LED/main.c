/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM383
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM383 Evaluation Board.
 *
 *    It uses the TMR interrupt handler to toggle PC0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2015/Apr/10
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM383-SK
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "TMPM383.h"
#include "system_TMPM383.h"

#pragma section=".intvec"


void INTTB00_IRQHandler(void)
{
    static int step=0;
    NVIC_ClearPendingIRQ(INTTB00_IRQn);
    if (++step%64==0) {
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
  TSB_PC->FR2 &= ~(1<<0);
  TSB_PC->FR3 &= ~(1<<0);
  TSB_PC->DATA |= (1<<0);

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
