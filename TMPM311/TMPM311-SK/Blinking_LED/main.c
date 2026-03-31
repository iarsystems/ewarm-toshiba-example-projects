/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM311
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM311 Evaluation Board.
 *
 *    It uses the TMR interrupt handler to toggle PC4 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 06.11.2014
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM311-SK
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "TMPM311.h"

#pragma section=".intvec"

void INTT16A0_IRQHandler(void)
{
    static int step=0;
    NVIC_ClearPendingIRQ(INTT16A0_IRQn);
    if (++step%128==0) {
      TSB_PC->DATA ^= (1<<4);
    }
}

int main(void)
{
  //Set vector table location
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Setup LED port Output (PC4)
  TSB_PC->CR |= (1<<4);
  TSB_PC->PUP |= (1<<4);
  TSB_PC->IE &= ~(1<<4);
  TSB_PC->DATA |= (1<<4);

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTT16A0_IRQn);
  TSB_T16A0->EN = 0;
  TSB_T16A0->RUN = 0;
  TSB_T16A0->RG = 0x8000;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTT16A0_IRQn, 1);
  NVIC_EnableIRQ(INTT16A0_IRQn);
  TSB_T16A0->RUN = (1<<0);

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
