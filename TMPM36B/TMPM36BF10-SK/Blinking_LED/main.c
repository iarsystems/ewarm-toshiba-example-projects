/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM36B
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM36BF10FG Evaluation Board.
 *
 *    It uses the WDT to toggle LED on port PF0.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 13.05.2013
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM36B-SK
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <Toshiba\iotmpm36BF10FG.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define EHOSC  10000000UL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#if EHOSC == 16000000UL		/* For Xtal Clk source = 16MHz */
  #define PLLSET_HICLK		0x790F		/* 64MHz */
  #define PLLSET_LOWCLK		0x710B		/* 48MHz */
#elif EHOSC == 12000000UL	/* For Xtal Clk source = 12MHz */
  #define PLLSET_HICLK		0x7993		/* 60MHz */
  #define PLLSET_LOWCLK		0x790F		/* 48MHz */
#elif EHOSC == 10000000UL	/* For Xtal Clk source = 10MHz */
  #define PLLSET_HICLK		0x7817		/* 60MHz */
  #define PLLSET_LOWCLK		0x780F		/* 40MHz */
#else						/* For Xtal Clk source = 8MHz (default) */
  #define PLLSET_HICLK		0x789F		/* 64MHz */
  #define PLLSET_LOWCLK		0x7817		/* 48MHz */
#endif

/*
InitClock set CPU clock = 60MHz
	If low_clock = 0 -> CPU clock = 64MHz / 60MHz
	If low_clock = 1 -> CPU clock = 48MHz / 40MHz
*/
void InitClock(int low_clock)
{
  /*Enable CG registers write*/
  CGPROTECT = 0xC1;
  /*External oscilator enable*/
  CGOSCCR_bit.EHOSCSEL = 1;
  CGOSCCR_bit.XEN1 = 1;
  CGOSCCR_bit.WUPSEL2 = 1;
  CGOSCCR_bit.WUPSEL1 = 0;
  /*Selects warm-up counter by external oscillator*/
  CGOSCCR_bit.WUPT = 256; /*wait some clocks from external oscilatior*/
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*select external oscilator as clock*/
  CGOSCCR_bit.OSCSEL = 1;
  /*Disable PLL*/
  CGPLLSEL_bit.PLLSEL = 0;
  CGOSCCR_bit.PLLON = 0;
  /*set multiplyer*/
  if (low_clock) {
    CGPLLSEL_bit.PLLSET = PLLSET_LOWCLK;
  }
  else {
    CGPLLSEL_bit.PLLSET = PLLSET_HICLK;
  }
  /*start PLL*/
  CGOSCCR_bit.PLLON = 1;
  /*wait to lock 200us*/
  CGOSCCR_bit.WUPT = 200*EHOSC/1000000;
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
  InitClock(0);

  // Setup LED port Output (PF0)
  PFIE_bit.PF0IE = 0;
  PFFR1_bit.PF0F1 = 0;
  PFFR3_bit.PF0F3 = 0;
  PFCR_bit.PF0C = 1;

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
    PFDATA_bit.PF0 ^= 1;
    printf("Count = 0x%02x, PF0 Port data = %d\n", (i/16)%256, PFDATA_bit.PF0);
  }
  ++i;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TMPM36B Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
