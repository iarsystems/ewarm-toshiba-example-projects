/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM061
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM061FWFG-SK Evaluation Board.
 *
 *    It uses the WDT to toggle PE4 port pin data.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 20.04.2012
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM061FWFG-SK
 *
 *
 *    $Revision: 1925 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <Toshiba\iotmpm061fwfg.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define EHOSC  16000000UL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = 16MHz
*/
void InitClock(void)
{
  /*Select internal oscilator as clock*/
  CGOSCCR_bit.XEN2 = 1;
  CGOSCCR_bit.OSCSEL = 0;
  /*External oscilator enable*/
  CGOSCCR_bit.HOSCON = 1;
  CGOSCCR_bit.XEN1 = 1;
  /*Selects warm-up counter by external oscillator*/
  CGOSCCR_bit.WUPT = 256; /*wait some clocks from external oscilatior*/
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*select external oscilator as clock*/
  CGOSCCR_bit.OSCSEL = 1;
  CGOSCCR_bit.XEN2 = 0;
  /*Set Prescalers*/
  CGSYSCR_bit.GEAR = 0;
  CGSYSCR_bit.PRCK = 1;
  CGSYSCR_bit.FPSEL0 = 0;
  CGSYSCR_bit.FPSEL1 = 1;
}


int main(void)
{
  /*Disable WDT0*/
  WD0MOD = 0;
  WD0CR  = 0xB1;

  /*Disable WDT1*/
  WD1MOD = 0;
  WD1CR  = 0xB1;

  // Setup PLL controller
  InitClock();

  // Setup LED port Output (PE4)
  PEIE_bit.PE4IE = 0;
  PEFR1_bit.PE4F1 = 0;
  PEFR2_bit.PE4F2 = 0;
  PEPUP_bit.PE4UP = 1;
  PECR_bit.PE4C = 1;

  WD0MOD = 0xA0;
  WD0CR  = 0x4E;

  while(1)
  {}
}

void NMI_ISR(void)
{
static unsigned int i;
  if (((++i)%10)==0) {
    PEDATA_bit.PE4 ^= 1;
  }
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TMPM061 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
