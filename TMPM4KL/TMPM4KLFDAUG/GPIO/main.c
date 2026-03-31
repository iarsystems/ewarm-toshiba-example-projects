/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM4KL family microcontrollers.
 *    It is developed for Toshiba TMPM4KLFDAUG Evaluation Board.
 *
 *    It uses the T32A Timer interrupt handler to toggle PB0-PB3 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2018/Jan/10
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM4KNFYFG
 *    3. Date        : 2020/Sep/23
 *       Author      : Shimizu
 *       Description : Adapted for TMPM4KLFWAFG
 *    4. Date        : 2022/Sep/13
 *       Author      : Urabe
 *       Description : Adapted for TMPM4KLFDAUG
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "io_macros.h"
#include "TMPM4KyA.h"
#include "system_TMPM4KyA.h"

#pragma section=".intvec"

#define LED_PIN   0x0F

__IO_REG32(VTOR,   0xE000ED08,__READ_WRITE);

void INTT32A00AC_IRQHandler(void)
{
  NVIC_ClearPendingIRQ(INTT32A00AC_IRQn);
  TSB_PB->DATA ^= LED_PIN;
}

int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  // Enable clock to all modules
  TSB_CG->FSYSMENA |= 0xFFFFFFFF;
  TSB_CG->FSYSMENB |= 0xFFFFFFFF;

  // Setup LED port Output (PB0-PB3)
  TSB_PB->CR |= LED_PIN;
  TSB_PB->PUP |= LED_PIN;
  TSB_PB->PDN &= ~LED_PIN;
  TSB_PB->FR4 &= ~LED_PIN;
  TSB_PB->IE &= ~LED_PIN;
  TSB_PB->DATA |= LED_PIN;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTT32A00AC_IRQn);
  TSB_T32A0->RUNA = 1;
  TSB_T32A0->CRA = (7<<28) | 1;
  TSB_T32A0->RGA0 = 0x8000;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTT32A00AC_IRQn, 1);
  NVIC_EnableIRQ(INTT32A00AC_IRQn);
  // Start Timer
  TSB_T32A0->RUNA = 0x03;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
