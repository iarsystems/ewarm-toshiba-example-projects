/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    T5DR0 microcontrollers.
 *    It is developed for Toshiba T5DR0 Evaluation Board.
 *
 *    It uses the TB3 Timer interrupt handler to toggle PC0-PC2 port pin data.
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
 *       Description : Adapted for TMPM4KHFWAUG
 *    4. Date        : 2023/Nov/23
 *       Author      : Urabe
 *       Description : Adapted for TMPM4K1FxB
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "io_macros.h"
#include <TMPM4K1B.h>
#include "system_TMPM4KxB.h"

#pragma section=".intvec"

#define PIN 0x07

__IO_REG32(VTOR,   0xE000ED08,__READ_WRITE);

void INTT32A00AC_IRQHandler(void)
{
  NVIC_ClearPendingIRQ(INTT32A00AC_IRQn);
  TSB_T32A0->STA = 0x00000001;
  TSB_PC->DATA ^=PIN;
  TSB_T32A0->RUNA |= 1;

}

int main(void)
{
#if 1
  VTOR  = (unsigned int)__segment_begin(".intvec");

  // Enable clock to all modules
  TSB_CG->PROTECT=0x000000C1;
  TSB_CG->FSYSENA |= 0x02000004;


  // Setup port Output (PC0-PC2)
  TSB_PC->CR |= PIN;
  TSB_PC->PUP |= PIN;
  TSB_PC->FR4 &= ~PIN;
  TSB_PC->FR5 &= ~PIN;
  TSB_PC->IE &= ~PIN;
  TSB_PC->DATA |=PIN;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTT32A00AC_IRQn);

  //Timer Mode(Common)
  TSB_T32A0->MOD = 0x00000000;
  TSB_T32A0->CRA = 0x00000000;
  TSB_T32A0->RELDA = 0x00004000;
  TSB_T32A0->IMA = 0x00000001;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTT32A00AC_IRQn, 1);
  NVIC_EnableIRQ(INTT32A00AC_IRQn);

  __enable_interrupt();

  //start Timer
  TSB_T32A0->RUNA = 0x00000003;

  while(1)
  {
  }
#endif

}