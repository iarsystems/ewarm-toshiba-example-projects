/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM3HQF10BFG family microcontrollers.
 *    It is developed for Toshiba TMPM3HxFx Evaluation Board.
 *
 *    It uses the T32A Timer interrupt handler to toggle PK4-PK6 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2016/Mar/18
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM3HQFDFG
 *    3. Date        : 2020/July/16
 *       Author      : Shimizu
 *       Description : Adapted for TMPM3HNFDADFG
 *    4. Date        : 2022/July/7
 *       Author      : 
 *       Description : Adapted for TMPM3HQF10BFG
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "TMPM3HPB.h"

#pragma section=".intvec"

#define LED_PIN 0xf0

void INTT32A00A_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(INTT32A00A_IRQn);
    TSB_PK->DATA ^= LED_PIN;
}

int main(void)
{
  SCB->VTOR  = (unsigned int)__segment_begin(".intvec");

  // Enable clock to all modules
  TSB_CG->PROTECT = 0x00C1;
  TSB_CG->FSYSENA |= 0xFFFFFFFF;
  TSB_CG->FSYSENB |= 0xFFFFFFFF;

  // Setup LED port Output (PK4-PK7)
  TSB_PK->CR |= LED_PIN;
  TSB_PK->PUP |= LED_PIN;
  TSB_PK->IE &= ~LED_PIN;
  TSB_PK->FR1 &= ~LED_PIN;
  TSB_PK->FR2 &= ~LED_PIN;
  TSB_PK->FR3 &= ~LED_PIN;
  TSB_PK->FR4 &= ~LED_PIN;
  TSB_PK->FR6 &= ~LED_PIN;
  TSB_PK->DATA |= LED_PIN;

  // Setup TimerA for periodic interrupt
  NVIC_DisableIRQ(INTT32A00A_IRQn);
  TSB_T32A0->RUNA = 1;
  TSB_T32A0->CRA = (7<<28) | 1;
  TSB_T32A0->RGA0 = 0x8000;

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
