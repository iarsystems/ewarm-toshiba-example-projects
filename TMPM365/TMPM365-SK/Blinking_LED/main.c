/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM365
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM365FYXBG Evaluation Board.
 *
 *    It uses the WDT to display LED port in incremental order.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 15.02.2012
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM365-SK
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <Toshiba\iotmpm365FYXBG.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define EHOSC  12000000UL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = 80MHz
*/
void InitClock(void)
{
  /*Enable CG registers write*/
  CGPROTECT = 0xC1;
  /*External oscilator enable*/
  CGOSCCR_bit.EHOSCSEL = 1;
  CGOSCCR_bit.XEN1 = 1;
  /*Selects warm-up counter by external oscillator*/
  CGOSCCR_bit.WUODR = 256; /*wait some clocks from external oscilatior*/
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*select external oscilator as clock*/
  CGOSCCR_bit.OSCSEL = 1;
  /*Disable PLL*/
  CGPLLSEL_bit.PLLSEL = 0;
  CGOSCCR_bit.PLLON = 0;
  /*multiplying by 8*/
  CGPLLSEL_bit.PLLSET = 0x381E;
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
  CGUSBCTL_bit.USBCLKSEL = 0;
  CGUSBCTL_bit.USBCLKEN = 1;
}


int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");
  WDMOD = 0;
  WDCR  = 0xB1;

  // Setup PLL controller
  InitClock();

  // Setup LED port Output (PC2)
  PCIE_bit.PC2IE = 0;
  PCFR1_bit.PC2F1 = 0;
  PCCR_bit.PC2C = 1;

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
    PCDATA_bit.PC2 ^= 1;
    printf("Count = 0x%02x, PC2 Port data = %d\n", (i/16)%256, PCDATA_bit.PC2);
  }
  ++i;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TMPM365 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
