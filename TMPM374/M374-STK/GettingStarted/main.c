/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : main.c
 *  Description : This example project shows how to use the IAR Embedded
 * Workbench for ARM to develop code for Toshiba TMPM374 family
 * microcontrollers. It is developed for Toshiba M374-STK Board.
 *  The example toggles LED3 - LED5  with period ~420ms.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 03.06.2011
 *       Author      : Stanimir Bonev
 *       Description : Adapted for TMPM373 Eval board
 *    3. Date        : 09.2011
 *       Author      : Stoyan Choynev
 *       Description : Adapted for Toshiba  M374-STK board
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm374fwug.h>
#include "drv_cg.h"
#include "drv_ioexp.h"
#include "board.h"

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main(void)
{
cg_clkinit_t clkinit;

  VTOR  = (unsigned int)__segment_begin(".intvec");

  /* Stop WDT */
  WDMOD_bit.WDTE = 0;
  WDCR = 0xB1;

  /*Init Clocks*/ 
  clkinit.gear = GEAR_FC;       /**/
  clkinit.fcsel = FCSEL_FPLL;   /**/
  clkinit.pfsel = FPSEL_FC;     /**/
  clkinit.prck = PRCK_1;
  clkinit.fosc = FOSCSEL_EXTOSC;
  clkinit.pll_enable = CG_ENABLE;
 
  InitClock(&clkinit);
  /*Init LEDs (IO Expander)*/
  LED_INIT;
  /*Turne on LED3 and LED5*/
  LED_ON(LED3|LED5);
  
  /* Enable WDT interrupt */
  WDMOD_bit.RESCR = 0;
  /* Set WDT period - 2^25/fsys = 419.43 ms*/
  WDMOD_bit.WDTP = 5;
  /* Start WDT*/
  WDMOD_bit.WDTE = 1;
  WDCR = 0x4E;

  while(1)
  {
  }
}

void NMI_Handler(void)
{
  /*  Toggle LEDs */
  LED_TGL(LED_MASK);
  WDCR = 0x4E;
}
