/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM037
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM037FWUG-SK Evaluation Board.
 *
 *    It uses the interrupt handler to toggle PE0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 20.04.2012
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM037FWUG-SK
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include "TMPM037.h"
#include "system_TMPM037.h"


void INTT16A0_IRQHandler(void)
{
	static int step=0;
	NVIC_ClearPendingIRQ(INTT16A0_IRQn);
	if (++step%128==0) {
	  TSB_PE->DATA ^= (1<<0);
	}
}


int main(void)
{
  // Setup LED port Output (PE0)
  TSB_PE->CR |= (1<<0);
  TSB_PE->PUP |= (1<<0);
  TSB_PE->IE &= ~(1<<0);
  TSB_PE->DATA |= (1<<0);

  // Setup Timer0 for periodic interrupt
	NVIC_DisableIRQ(INTT16A0_IRQn);
  TSB_T16A0->EN = 0;
  TSB_T16A0->RUN = 0;
  TSB_T16A0->RG = 0x8000;

	// Enable interrupt for Timer
	NVIC_SetPriority(INTT16A0_IRQn, 1);
	NVIC_EnableIRQ(INTT16A0_IRQn);
  TSB_T16A0->RUN = (1<<0);

  while(1)
  {}
}

