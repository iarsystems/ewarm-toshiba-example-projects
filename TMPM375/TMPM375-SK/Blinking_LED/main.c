/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM375
 *    family microcontrollers.
 *    It is developed for M375-SK Evaluation Board.
 *
 *    It uses the WDT to display User LED at port PG0/U0.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 04.03.2013
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM375-SK
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm375FSDMG.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define EHOSC  10000000UL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = 40MHz
*/
void InitClock(void)
{
  /*Disable PLL*/
  CGPLLSEL_bit.PLLSEL = 0;
  CGOSCCR_bit.PLLON = 0;
  /*External oscilator enable*/
  CGOSCCR_bit.WUPSEL1 = 0;
  CGOSCCR_bit.XEN1 = 1;
  /*Selects warm-up counter by external oscillator*/
  CGOSCCR_bit.WUODR = 256; /*wait some clocks from external oscillator*/
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*start PLL*/
  CGOSCCR_bit.PLLON = 1;
  /*wait to lock 200us*/
  CGOSCCR_bit.WUODR = 200*EHOSC/1000000;
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*Set Prescalers*/
  CGSYSCR_bit.GEAR = 0;
  CGSYSCR_bit.PRCK = 1;
  CGSYSCR_bit.FPSEL = 1;
  /*selecet PLL as clock*/
  CGPLLSEL_bit.PLLSEL = 1;
}


int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");
  WDMOD = 0;
  WDCR  = 0xB1;

  // Setup PLL controller
  InitClock();

  // Setup LED port Output (PG0/U0,V0,W0)
  PGIE_bit.PG0IE = 0;
  PGFR1_bit.PG0F1 = 0;
  PGCR_bit.PG0C = 1;

  PGIE_bit.PG2IE = 0;
  PGFR1_bit.PG2F1 = 0;
  PGCR_bit.PG2C = 1;

  PGIE_bit.PG4IE = 0;
  PGFR1_bit.PG4F1 = 0;
  PGCR_bit.PG4C = 1;

  WDMOD = 0xA0;
  WDCR  = 0x4E;

  while(1)
  {
	;
  }
}

void NMI_ISR(void)
{
static unsigned int i,k;
  if (!(i%16)) {
    PGDATA = ++k& 0x15;
  }
  ++i;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TMPM375 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
