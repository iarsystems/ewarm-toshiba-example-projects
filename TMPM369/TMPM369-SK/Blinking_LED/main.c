/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM369
 *    family microcontrollers.
 *    It is developed for Toshiba TMPM369FDFG Evaluation Board.
 *
 *    It uses the WDT to display LED port in incremental order.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 19.07.2010
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM369-SK
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include "board.h"
#include "drv_cg.h"
#include "drv_nvic.h"

#pragma section=".intvec"

const cg_clkinit_t CG_clkinit = {
  .gear = GEAR_FC,
  .fcsel = FCSEL_FPLL,
  .pfsel = FPSEL_FC,
  .prck = PRCK_1,
  .fosc = FOSCSEL_EXTOSC,
  .pll_enable = CG_ENABLE,
  .pllmul = PLLSET_16MHZ_80MHZ,
  .lposc = CG_ENABLE,
  .usbl_clk_sel = CLK_USBPLL,
  .usbpll_enable = CG_ENABLE,
  .usbpllmul = PLLSET_16MHZ,
};
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");
  WDMOD = 0;
  WDCR  = 0xB1;

  // Setup PLL controller
  // USB Host registers should not be accessed before PLL is set
  InitClock(&CG_clkinit);

  // Setup LED port Output (PC0-PC7)
  INIT_LEDS();

  WDMOD = 0xA0;
  WDCR  = 0x4E;

  while(1)
  {
  }
}

void NMI_Handler(void)
{
static unsigned int i;
  if (!(i%16)) {
    LED_PORT = i/16;
    printf("LED Data = 0x%02x\n", (i/16)%256);
  }
  ++i;
}
