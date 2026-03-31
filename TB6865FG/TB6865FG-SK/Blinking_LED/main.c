/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TB6865FG
 *    family microcontrollers.
 *    It is developed for Toshiba TB6865FG-SK Evaluation Board.
 *
 *    It uses the WDT to toggle PG0 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 08.05.2012
 *       Author      : Santosh Pawar
 *       Description : Adapted for TB6865FG-SK
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <Toshiba\iotb6865fg.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define EHOSC  20000000UL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = 20MHz
*/
void InitClock(void)
{
  /*Enable CG registers write*/
  CGPROTECT = 0xC1;
  /*External oscilator enable*/
  CGOSCCR_bit.XEN1 = 1;
  /*Selects warm-up counter by external oscillator*/
  CGOSCCR_bit.WUODR = 256; /*wait some clocks from external oscilatior*/
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*select external oscilator as clock*/
  CGOSCCR_bit.OSCSEL = 1;
  CGOSCCR_bit.XEN2 = 0;
  /*start PLL*/
  CGOSCCR_bit.PLLON = 1;
  /*wait to lock 200us*/
  CGOSCCR_bit.HWUPSEL = 1;
  CGOSCCR_bit.WUODR = 200UL*(EHOSC/1000000UL);
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*Set Prescalers*/
  CGSYSCR_bit.GEAR = 0;
  CGSYSCR_bit.PRCK = 1;
  CGSYSCR_bit.FPSEL = 1;
}


int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");
  WDMOD = 0;
  WDCR  = 0xB1;

  // Setup PLL controller
  InitClock();

  // Setup LED port Output (PG0)
  PGIE_bit.PG0IE = 0;
  PGFR1_bit.PG0F1 = 0;
  PGCR_bit.PG0C = 1;

  WDMOD = 0xA0;
  WDCR  = 0x4E;

  while(1)
  {
	;
  }
}

void NMI_ISR(void)
{
static unsigned int i;
  PGDATA_bit.PG0 ^= 1;
  ++i;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TB6865FG Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
