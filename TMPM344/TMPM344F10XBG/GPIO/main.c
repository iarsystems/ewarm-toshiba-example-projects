/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM344F10XBG family microcontrollers.
 *    It is developed for Toshiba TMPM344F10XBG Evaluation Board.
 *
 *    It uses the GP Timer interrupt handler to toggle PC0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2018/Jul/24
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM344F10XBG
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "io_macros.h"
#include "TMPM344.h"
#include "system_TMPM344.h"

#pragma section=".intvec"

#define LED_PIN   (1<<0u)

void INTTB0_IRQHandler(void)
{
  // Clear interrupt edge
  NVIC_ClearPendingIRQ(INTTB0_IRQn);
  TSB_PC->DATA ^= LED_PIN;
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Setup LED port Output (PC0)
  TSB_PC->CR |= LED_PIN;
  TSB_PC->IE &= ~LED_PIN;
  TSB_PC->FR1 &= ~LED_PIN;
  TSB_PC->DATA |= LED_PIN;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTTB0_IRQn);
  TSB_TB0->EN = 0x80;
  TSB_TB0->RUN = 0;
  TSB_TB0->MOD = (1<<3) | 7;
  TSB_TB0->CR = 0;
  TSB_TB0->IM = 0x05;
  TSB_TB0->RG1 = 0xF000;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTTB0_IRQn, 1);
  NVIC_EnableIRQ(INTTB0_IRQn);
  // Start Timer
  TSB_TB0->RUN = 0x05;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
