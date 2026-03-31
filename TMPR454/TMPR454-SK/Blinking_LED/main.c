/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPR454
 *    family microcontrollers.
 *    It is developed for Toshiba TMPR454F10TFG Evaluation Board.
 *
 *    It simply toggles LED port on PA7.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 23.07.2013
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPR454-SK
 *
 *
 *    $Revision: 1388 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <intrinsics.h>
#include <Toshiba/iotmpr454F10TFG.h>


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
InitClock set CPU clock = 160MHz
*/

int __low_level_init(void) {
  unsigned int *p;
  /* initialize all RAM section */
  /* clear RAM0  0x1000_0000-0x1000_8000 */
  for ( p = (unsigned int *)0x10000000; p < (unsigned int *)0x10008000; p++) {
    *p = 0;
  }
  
  /* clear RAM1 0x1002_0000-0x1002_8000 */
  for ( p = (unsigned int *)0x10020000; p < (unsigned int *)0x10028000; p++) {
    *p = 0;
  }
  
  /* clear SYSRAM 0x2000_0000-0x2000_4000 */
  for ( p = (unsigned int *)0x20000000; p < (unsigned int *)0x20004000; p++) {
    *p = 0;
  }  
  
  return 1;
}

void InitClock(void)
{
  // nothing special. clock is setup by hardware
}

void LED_Handler(void)
{
  static unsigned int i;
  if (!(i%4)) {
    PORTOUTA_bit.O7 = !PORTMONA_bit.I7;
  }
  ++i;
}


int main(void)
{
  __disable_irq();
  
  // Setup PLL controller
  InitClock();

  PORTFNCSELA_bit.FS7 = 0;
  PORTPUENA_bit.PU7 = 0;
  PORTPDENA_bit.PD7 = 1;
  PORTOENA_bit.OE7 = 1;
  PORTOUTA_bit.O7 = 1;

  while(1)
  {
    volatile long dmy;
    for (dmy=0; dmy<0x40000; dmy++);
    LED_Handler();
  }
}

