/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM440
 *    family microcontrollers.
 *    It is developed for IAR TMPM440-SK Evaluation Board.
 *
 *    It uses the WDT to display LED port in incremental order.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 15.08.2012
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM440-SK
 *
 *
 *    $Revision: 2824 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <Toshiba/iotmpm440FxXBG.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define EHOSC  10000000UL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = 100MHz
*/
void InitClock(void)
{
  /*Enable CG registers write*/
  CGPROTECT = 0xC1;
  /*External oscilator enable*/
  CGOSCCR_bit.EHOSCSEL = 1;
  CGOSCCR_bit.XEN1 = 1;
  /*Selects warm-up counter by external oscillator*/
  CGOSCCR_bit.WUPT = 256; /*wait some clocks from external oscilatior*/
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*select external oscilator as clock*/
  CGOSCCR_bit.OSCSEL = 1;
  /*Disable PLL*/
  CGPLLSEL_bit.PLL0SEL = 0;
  CGOSCCR_bit.PLL0ON = 0;
  /*multiplying by 10*/
  CGPLLSEL_bit.PLL0SET = 0x704D;
  /*start PLL*/
  CGOSCCR_bit.PLL0ON = 1;
  /*wait to lock 200us*/
  CGOSCCR_bit.WUPT = 200*EHOSC/1000000;
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*Set Prescalers*/
  CGSYSCR_bit.GEAR = 0;
  CGSYSCR_bit.PRCK = 1;
  CGSYSCR_bit.FPSEL0 = 1;
  CGSYSCR_bit.PSCSTOP = 0;
  /*selecet PLL as clock*/
  CGPLLSEL_bit.PLL0SEL = 1;
}


int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");
  WDMOD = 0;
  WDCR  = 0xB1;

  // Setup PLL controller
  InitClock();

  // Setup LED port Output (PAD0)
  PADIE = 0;
  PADFR1 = 0;
  PADCR = 0xFF;
  PADDATA = 0xFF;

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
  if (!(i%16)) {
    PADDATA_bit.PAD0 ^= 1;
  }
  ++i;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TMPM440 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
