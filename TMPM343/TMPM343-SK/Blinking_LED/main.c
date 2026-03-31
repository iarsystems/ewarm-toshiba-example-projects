/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM343
 *    family microcontrollers.
 *    It is developed for TMPM343-SK Evaluation Board.
 *
 *    It uses the WDT to display User LED at port PE0.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 04.03.2013
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM343-SK
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm343F10XBG.h>

#pragma section=".intvec"


#define EXT_CLK			10		/* 8/10/16/20 MHz */
#define PLL_PRESCALE	20		/* 8/10/16/20 */

/* Private define ------------------------------------------------------------*/
#define EHOSC  (EXT_CLK*1000000UL)

/* Private macro -------------------------------------------------------------*/
#if (EXT_CLK == 20)
  #if (PLL_PRESCALE == 10)
    #define DAT_PLL0SET		0x2925
  #else
    #define DAT_PLL0SET		0x3A1D
  #endif
#elif (EXT_CLK == 16)
  #if (PLL_PRESCALE == 10)
    #define DAT_PLL0SET		0x2925
  #else
    #define DAT_PLL0SET		0x3A1D
  #endif
#elif (EXT_CLK == 10)
  #if (PLL_PRESCALE == 20)
    #define DAT_PLL0SET		0x6A4D
  #elif (PLL_PRESCALE == 16)
    #define DAT_PLL0SET		0x5A3D
  #elif (PLL_PRESCALE == 10)
    #define DAT_PLL0SET		0x6A26
  #else
    #define DAT_PLL0SET		0x5A1E
  #endif
#else
  #if (PLL_PRESCALE == 20)
    #define DAT_PLL0SET		0x6A4D
  #elif (PLL_PRESCALE == 16)
    #define DAT_PLL0SET		0x5A3D
  #elif (PLL_PRESCALE == 10)
    #define DAT_PLL0SET		0x6A26
  #else
    #define DAT_PLL0SET		0x5A1E
  #endif
#endif

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = PLL_PRESCALE x EXT_CLK
*/
void InitClock(void)
{
  /*Disable PLL*/
  CGPLLSEL_bit.PLL0SEL = 0;
  CGOSCCR_bit.PLL0ON = 0;
  CGOSCCR_bit.OSCSEL = 0;
  /*External oscilator enable*/
  CGOSCCR_bit.EHOSCSEL = 1;
  CGOSCCR_bit.WUPSEL = 1;
  CGOSCCR_bit.XEN1 = 1;
  /*Selects warm-up counter by external oscillator*/
  CGOSCCR_bit.WUPT = 256; /*wait some clocks from external oscillator*/
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  CGOSCCR_bit.PLL0ON = 0;
  CGPLLSEL_bit.PLL0SET = DAT_PLL0SET;
  /*100us setup time delay*/
  CGOSCCR_bit.WUPT = 256;
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}

  /*start PLL*/
  CGOSCCR_bit.PLL0ON = 1;
  /*wait to lock 100us*/
  CGOSCCR_bit.WUPT = 100*EHOSC/1000000;
  /*Start warm up*/
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF)
  {}
  /*Set Prescalers*/
  CGSYSCR_bit.GEAR = 0;
  CGSYSCR_bit.PRCK = 1;
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

  // Setup LED port Output (PE0)
  PEIE_bit.PE0IE = 0;
  PEFR1_bit.PE0F1 = 0;
  PEFR2_bit.PE0F2 = 0;
  PEFR3_bit.PE0F3 = 0;
  PEFR4_bit.PE0F4 = 0;
  PECR_bit.PE0C = 1;


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
    PEDATA_bit.PE0 ^= 1;
  }
  ++i;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TMPM343 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
