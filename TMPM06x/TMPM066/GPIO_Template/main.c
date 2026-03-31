/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM066
 *    family microcontrollers.
 *
 *    It uses GP Timer interrupt handler to toggle PE0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 2015/Aug/20
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM066FWUG sample
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include "TMPM066.h"
#include "system_TMPM066.h"


void INT16A0_IRQHandler(void)
{
	static int step=0;
	NVIC_ClearPendingIRQ(INT16A0_IRQn);
	if (++step%128==0) {
	  TSB_PE->DATA ^= (1<<0);
	}
}

int main(void)
{
  // Enable clock for Timer0 (Clock to PE is ON by default)
  TSB_CG->FSYSENA |= (1<<11);

  // Setup LED port Output (PE0)
  TSB_PE->CR |= (1<<0);
  TSB_PE->PUP |= (1<<0);
  TSB_PE->IE &= ~(1<<0);
  TSB_PE->FR1 &= ~(1<<0);
  TSB_PE->DATA |= (1<<0);

  // Setup Timer0 for periodic interrupt
	NVIC_DisableIRQ(INT16A0_IRQn);
  TSB_T16A0->EN = 0;
  TSB_T16A0->RUN = 0;
  TSB_T16A0->RG = 0x8000;

	// Enable interrupt for Timer
	NVIC_SetPriority(INT16A0_IRQn, 1);
	NVIC_EnableIRQ(INT16A0_IRQn);
  TSB_T16A0->RUN = (1<<0);

  while(1)
  {}
}

