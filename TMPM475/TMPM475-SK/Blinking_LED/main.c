/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM475
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM475-SK Board.
 *
 *    It uses the TMR interrupt handler to toggle PA0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2015/Jan/19
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM475-SK
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "TMPM475.h"
#include "system_TMPM475.h"

#pragma section=".intvec"


#define LED1        (1<<0)
#define LED2        (1<<1)
#define LED3        (1<<2)
#define LED4        (1<<3)

#define LED_MASK    (LED1 | LED2 | LED3 | LED4 )

void INTTB00_IRQHandler(void)
{
    static int step=0;
    NVIC_ClearPendingIRQ(INTTB00_IRQn);
    if (++step%64==0) {
      TSB_PA->DATA ^= (LED1);
    }
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Setup LED port Output (PA0-PA3)
  TSB_PA->CR |= (LED_MASK);
  TSB_PA->PUP |= (LED_MASK);
  TSB_PA->IE &= ~(LED_MASK);
  TSB_PA->FR1 &= ~(LED_MASK);
  TSB_PA->DATA &= ~(LED_MASK);

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
