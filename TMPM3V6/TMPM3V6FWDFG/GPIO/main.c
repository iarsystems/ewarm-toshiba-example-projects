/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2019
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM3V6 family microcontrollers.
 *    It is developed for Toshiba TMPM3V6FWDFG Evaluation Board.
 *
 *    It uses the TMRB Timer interrupt handler to toggle PG4-7 port pin data.
 *
 *    History :
 *    1. Date        : 03.2019
 *       Author      : shimizu
 *       Description : Initial Revision
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "TMPM3V6.h"
#include "system_TMPM3V6.h"

#pragma section=".intvec"

#define LED_PIN   0xf0

void INTTB00_IRQHandler(void)
{
    static int step=0;
    NVIC_ClearPendingIRQ(INTTB00_IRQn);
    if (++step%64==0) {
      TSB_PG->DATA ^= (LED_PIN);
    }
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Setup port Output (PG4-7)
  TSB_PG->CR |= LED_PIN;
  TSB_PG->PUP |= LED_PIN;
  TSB_PG->IE &= ~(LED_PIN);
  TSB_PG->DATA |= (LED_PIN);

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTTB00_IRQn);
  TSB_TB0->EN = 0x80;
  TSB_TB0->RUN = 0;
  TSB_TB0->MOD = 0x026;
  TSB_TB0->RG0 = 0x8000;

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
