/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba
 *    TMPM4GRF20FG family microcontrollers.
 *    It is developed for Toshiba TMPM4GRF20FG Evaluation Board.
 *
 *    It uses the GP Timer interrupt handler to toggle PE4-PE7 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2020/May/18
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM4GRF20FG
 *
 *
 *    $Revision: 64446 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include "io_macros.h"
#include "TMPM4Gx.h"
#include "system_TMPM4Gx.h"

#pragma section=".intvec"

#define LED_PIN   0xF0

__IO_REG32(VTOR,   0xE000ED08,__READ_WRITE);

void INTT32A00_A_CT_IRQHandler(void)
{
  volatile unsigned char dummy;
  // Clear INTNCLR and INTPCLR Flags
  TSB_IB->IMC000 |= 0x40;
  dummy = TSB_IB->IMC000; // Dummy read
  NVIC_ClearPendingIRQ(INTT32A00_A_CT_IRQn);
  TSB_PE->DATA ^= LED_PIN;
}

int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  TSB_CG->FSYSMENA |= (1u << 6);		// Enable clock for T32A ch00
  TSB_CG->FSYSMENB |= (1u << 6);		// Enable clock for Port-E

  // Setup LED port Output (PE4-PE7)
  TSB_PE->CR |= LED_PIN;
  TSB_PE->PUP |= LED_PIN;
  TSB_PE->IE &= ~LED_PIN;
  TSB_PE->FR1 &= ~LED_PIN;
  TSB_PE->FR2 &= ~LED_PIN;
  TSB_PE->FR3 &= ~LED_PIN;
  TSB_PE->FR4 &= ~LED_PIN;
  TSB_PE->FR5 &= ~LED_PIN;
  TSB_PE->FR6 &= ~LED_PIN;
  TSB_PE->FR8 &= ~LED_PIN;
  TSB_PE->DATA |= LED_PIN;

  // Setup Timer0 for periodic interrupt
  NVIC_DisableIRQ(INTT32A00_A_CT_IRQn);
  TSB_T32A0->RUNA = 1;
  TSB_T32A0->CRA = (7<<28) | 1;
  TSB_T32A0->RGA0 = 0x0000;

  // Enable interrupt for Timer
  NVIC_SetPriority(INTT32A00_A_CT_IRQn, 1);
  NVIC_EnableIRQ(INTT32A00_A_CT_IRQn);
  // Setup INTIF for INTT32A00A_IRQn line
  TSB_IB->IMC000 = 1;
  // Start Timer
  TSB_T32A0->RUNA = 0x03;

  __enable_interrupt();

  while(1)
  {
    ;
  }
}
