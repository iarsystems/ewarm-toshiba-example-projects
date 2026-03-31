/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM461
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM461F10FG Evaluation Board.
 *
 *    It uses the WDT to display LED port on PD0 pin.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 23.09.2013
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM461-SK
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <Toshiba/iotmpm461FxxFG.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define EHOSC  16000000UL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = 96MHz
*/
void InitClock(void)
{
  /*Enable CG registers write*/
  CGPROTECT = 0xC1;
  CGOSCCR_bit.XEN1 = 1;
  CGOSCCR_bit.HOSCON = 1;
  CGOSCCR_bit.WUPSEL2 = 1;
  CGOSCCR_bit.WUPSEL1 = 0;
  /*Selects warm-up counter by external oscillator*/
  CGOSCCR_bit.WUPT = 256; /*wait some clocks from external oscilatior*/
  while(CGOSCCR_bit.WUPT != 256);
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF);
  /*select external oscilator as clock*/
  CGOSCCR_bit.OSCSEL = 1;
  while(!(CGOSCCR_bit.OSCF));

  /*Disable PLL*/
  CGPLLSEL_bit.PLLON = 0;
  /*multiplying by 10*/
  CGPLLSEL_bit.PLLSET = 0x6A16;
  /*wait to lock 150us*/
  CGOSCCR_bit.WUPT = 150*EHOSC/1000000;
  while(CGOSCCR_bit.WUPT != (150*EHOSC/1000000));
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF);
  /*start PLL*/
  CGPLLSEL_bit.PLLON = 1;
  
  /*wait to lock 200us*/
  CGOSCCR_bit.WUPT = 200*EHOSC/1000000;
  while(CGOSCCR_bit.WUPT != (200*EHOSC/1000000));
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF);
  /*Set Prescalers*/
  CGSYSCR_bit.GEAR = 0;
  CGSYSCR_bit.PRCK = 1;
  CGSYSCR_bit.FPSEL = 1;
  /*selecet PLL as clock*/
  CGPLLSEL_bit.PLLSEL = 1;
  while(!(CGPLLSEL_bit.PLLST));
}


int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");
  WDMOD = 0;
  WDCR  = 0xB1;

  // Setup PLL controller
  InitClock();

  // Setup LED port Output (PD0)
  PDIE_bit.PD0IE = 0;
  PDFR1_bit.PD0F1 = 0;
  PDFR2_bit.PD0F2 = 0;
  PDFR3_bit.PD0F3 = 0;
  PDCR_bit.PD0C = 1;
  PDDATA_bit.PD0 = 1;

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
    PDDATA_bit.PD0 ^= 1;
  }
  ++i;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TMPM461 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
