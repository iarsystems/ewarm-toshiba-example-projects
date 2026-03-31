/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : main.c
 *  Description : This example project shows how to use the IAR Embedded
 * Workbench for ARM to develop code for Toshiba TMPM373 family
 * microcontrollers. It is developed for Toshiba TMPM373 Eval Board.
 *  The example toggle PG0 (pin 2) with period ~420ms.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 03.06.2011
 *       Author      : Stanimir Bonev
 *       Description : Adapted for TMPM373 Eval board
 *
 *
 *    $Revision: 4200 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm373fwdug.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void clock_init (void)
{
  /* (1) Selct external OSC pins mode */
  PMCR = 0;
  PMPUP = 0;
  PMPDN = 0;
  PMIE = 0;
  /* (2) Set warm-up time for the external oscillator - 1ms*/
  CGOSCCR_bit.WUODR = 2710>>2;
  /* (3) Switch over from the port M to oscillator connection pins. */
  CGOSCCR_bit.HOSCON = 1;
  /* (4) Enable the external oscillator. */
  CGOSCCR_bit.XEN1 = 1;
  /* (5) Specify the external oscillator clock as source clock for warm-up counter. */
  CGOSCCR_bit.WUPSEL1 = 0;
  CGOSCCR_bit.WUPSEL2 = 1;
  /* (6) Start warm-up and waits till the end of warm-up */
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF);
  /* (7) Switch the system clock to the OSC. */
  CGOSCCR_bit.OSCSEL = 1;
  /* (8) Set high speed gear and per. div */
  CGSYSCR_bit.GEAR = 0;   /* fgear 1:1*/
  CGSYSCR_bit.PRCK = 4;   /* 1:6*/
  CGSYSCR_bit.FPSEL = 0;  /* per. clock from fgear*/
  /* (9) Enable Pll */
  CGOSCCR_bit.PLLON = 1;
  /* (10) Wait warm-up time > 200us */
  CGOSCCR_bit.WUODR = 3000>>2;
  CGOSCCR_bit.WUPSEL1 = 0;
  CGOSCCR_bit.WUPSEL2 = 1;
  CGOSCCR_bit.WUEON = 1;
  while(CGOSCCR_bit.WUEF);
  /* (11) Swicth to PLL clock */
  CGPLLSEL_bit.PLLSEL = 1;
}

int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  /* clock init */
  clock_init();

  /* Stop WDT */
  WDMOD_bit.WDTE = 0;
  WDCR = 0xB1;
  /* Enable WDT interrupt */
  WDMOD_bit.RESCR = 0;
  /* Set WDT period - 2^25/fsys = 419.43 ms*/
  WDMOD_bit.WDTP = 5;
  /* Start WDT*/
  WDMOD_bit.WDTE = 1;
  WDCR = 0x4E;

  // Init PG0 (pin 2)
  PGFR1_bit.PG0F1 = 0;  /* GPIO */
  PGOD_bit.PG0OD = 0;   /* Push Pull */
  PGCR_bit.PG0C = 1;    /* Output */

  while(1)
  {
  }
}

void NMI_ISR(void)
{
  /*  Toggle PG0 */
  PGDATA ^= 1;
  WDCR = 0x4E;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"
/* TMPM330 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
