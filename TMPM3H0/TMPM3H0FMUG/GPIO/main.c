/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM3H0FMUG family microcontrollers.
 *    It is developed for Toshiba TMPM3H0FMUG Evaluation Board.
 *
 *    It uses the GP Timer interrupt handler to toggle PB1 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2016/Mar/18
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM3H0FMUG
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "TMPM3Hx.h"
#include "system_TMPM3Hx.h"

#pragma section=".intvec"

#define LED_PIN   (1<<1)


void INTT32A00A_IRQHandler(void)
{
    // Clear interrupt status
    NVIC_ClearPendingIRQ(INTT32A00A_IRQn);
    TSB_T32A0->STA = 0xF;
    TSB_PB->DATA ^= LED_PIN;
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Enable clock to all modules
  TSB_CG->FSYSENA |= 0xFFFFFFFF;
  TSB_CG->FSYSENB |= 0x000000FF;

  // Setup LED port Output (PB1)
  TSB_PB->CR |= LED_PIN;
  TSB_PB->PUP |= LED_PIN;
  TSB_PB->IE &= ~LED_PIN;
  TSB_PB->FR1 &= ~LED_PIN;
  TSB_PB->FR4 &= ~LED_PIN;
  TSB_PB->FR5 &= ~LED_PIN;
  TSB_PB->FR6 &= ~LED_PIN;
  TSB_PB->DATA |= LED_PIN;

  // Setup Timer-A (16-Bit mode) for periodic interrupt
  NVIC_DisableIRQ(INTT32A00A_IRQn);
  TSB_T32A0->RUNA = 1;
  TSB_T32A0->CRA = (7<<28) | 0x6;
  TSB_T32A0->RELDA = 0x0000;
  TSB_T32A0->RGA1 = 0x8000;
  TSB_T32A0->IMA = 1<<0;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTT32A00A_IRQn, 1);
  NVIC_EnableIRQ(INTT32A00A_IRQn);
  // Start Timer
  TSB_T32A0->RUNA = 0x03;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
