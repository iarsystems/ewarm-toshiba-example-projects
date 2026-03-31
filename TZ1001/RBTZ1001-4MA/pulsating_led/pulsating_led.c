/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2015
 *
 *    File name   : pulsating_led.c
 *    Description : Pulsating LED Example
 *
 *    History :
 *    1. Date        : November 2015
 *       Author      : Atanas Uzunov
 *       Description : Create
 *
 * DESCRIPTION
 * ===========
 * This example project shows how to use the IAR Embedded Workbench for ARM
 * to develop code for the Toshiba RBTZ1001. It shows basic initialization of
 * the Toshiba RBTZ1001 device. Also configures clock gatings, controls reset to
 * the modules, turns-on the stopped oscillators, and configures the voltage mode.
 * It uses AdvTMR module and configures its channels (2 and 3) in PWM mode.
 *
 * The result of the example is alternating red and green pulsing lights of LED1.
 *
 * COMPATIBILITY
 * =============
 * The Pulsating LED example project is compatible with Toshiba RBTZ1001-4MA board.
 * By default, the project is configured to use the I-Jet JTAG/SWD interface.
 *
 * CONFIGURATION
 * =============
 * Flash_Debug - The Progam is loaded to internal Flash. It uses the SPI XiP boot mode.
 * RAM_Debug - The Progam is loaded to RAM.
 *
 * Make sure that the following jumpers are correctly configured on the
 * RBTZ1001-4MA board:
 *
 *  Jumpers:
 *  JP1:
 *    BOOT_0 - open
 *    BOOT_1 - open
 *    BOOT_2 - open
 *    BOOT_4 - open
 *
 *    $Revision: 3186 $
 **************************************************************************/
#include <math.h>
#include "Toshiba\TZ10xx.h"

/* global variables */
volatile uint8_t flGetValue2 = 1, flGetValue3 = 1;
volatile uint16_t compare_val2, compare_val3;
uint8_t presc2, presc3;
float advcnt2, advcnt3;
uint8_t  dir2, dir3;
uint8_t  tswitch;

/*************************************************************************
 * Function Name: ADVTMR2_CMP_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: AdvTIM2 Compare Interrupt Handler
 *************************************************************************/
void ADVTMR2_CMP_IRQHandler(void)
{
  /* Update T2BGCOMPARE register */
  advtmr->T2BGCOMPARE = compare_val2;
  /* If some time elapsed, signal the main loop via flGetValue2
     to calculate new PWM duty */
  if (++presc2 & 0x04)
  {
    flGetValue2 = 1;
    presc2 = 0;
  }
  /* Clear the interrupt flag in the AdvTMR peripheral */
  advtmr->T2CMPINTCLR = 0;
}

/*************************************************************************
 * Function Name: ADVTMR2_CMP_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: AdvTIM3 Compare Interrupt Handler
 *************************************************************************/
void ADVTMR3_CMP_IRQHandler(void)
{
  /* Update T3BGCOMPARE register */
  advtmr->T3BGCOMPARE = compare_val3;
  /* If some time elapsed, signal the main loop via flGetValue3
     to calculate new PWM duty */
  if (++presc3 & 0x04)
  {
    flGetValue3 = 1;
    presc3 = 0;
  }
  /* Clear the interrupt flag in the AdvTMR peripheral */
  advtmr->T3CMPINTCLR = 0;
}

/*************************************************************************
 * Function Name: CalculateCompareValue
 * Parameters: uint8_t * direction - pointer to direction variable
 *             float * var         - pointer to the argument of the exp function
 *             volatile uint16_t * result - pointer to the result (new PWM duty)
 *
 * Return: none
 *
 * Description: Calculate new PWM duty value by an exponential function.
 *              Human perception is linear changing the LED's brightness.
 *************************************************************************/
void CalculateCompareValue(uint8_t * direction, float * var, volatile uint16_t * result)
{
float res;

  /* Update argument of the exp function */
  if (*direction)
    *var -= 0.1;
  else
    *var += 0.1;

  /* Calcualte the exp value */
  res = exp(*var);

  /* If upper limit of the argument is reached invert the direction
     set max PWM duty and exit */
  if(*var > 11)
  {
    *direction = 1;
    *result = UINT16_MAX - 1;
    return;
  }
  /* If lower limit of the argument is reached invert the direction
     set min PWM duty and exit */
  if(*var < 0)
  {
    *direction = 0;
    *result = 0;
    return;
  }
  /* Update the duty value variable for the PWM */
  *result = (uint16_t)res;
}

/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description: Main function
 *************************************************************************/
void main(void)
{
  /* Turn-on clock to PM power domain */
  pmulv->CG_OFF_POWERDOMAIN_b.CG_PM = 1;

  /* Turn-on clock to APB0 bus */
  pmulv->CG_OFF_PM_1_b.CG_mpierclk_h2hp0_hclk = 1;
  pmulv->CG_OFF_PM_1_b.CG_ppier0clk_h2pp0_hclk = 1;

  /* Release reset to APB0 bus */
  pmulv->SRST_OFF_PM_1_b.SRST_asyncrst_h2hp0_hrstn = 1;
  pmulv->SRST_OFF_PM_1_b.SRST_asyncrst_h2pp0_hrstn = 1;

  /* Turn-on clock to GCONF, GPIO1, AdvTMR ch2 and ch3 */
  pmulv->CG_OFF_PM_2_b.CG_ppier0clk_gpio1_pclk = 1;
  pmulv->CG_OFF_PM_2_b.CG_ppier0clk_gconf_pclk = 1;
  pmulv->CG_OFF_PM_1_b.CG_ppier0clk_advtmr_ch2_timclk = 1;
  pmulv->CG_OFF_PM_1_b.CG_ppier0clk_advtmr_ch3_timclk = 1;

  /* Release software reset to some peripherals */
  pmulv->SRST_OFF_PM_2_b.SRST_asyncrst_gconf_prstn = 1;
  pmulv->SRST_OFF_PM_2_b.SRST_asyncrst_gpio1_prstn = 1;
  pmulv->SRST_OFF_PM_1_b.SRST_asyncrst_advtmr_prstn = 1;

  /* Configire dynamic clock gating - GCONF */
  pmulv->DCG_PM_2_b.DCG_ppier0clk_gconf_pclk = 1;

  /* Configure pin function mode
     Set FMODE = 2(AdvTMR) for GPIO10 anf GPIO11 */
  gconf->FMODE_CFG0 &= ~((3<<20)|(3<<22));
  gconf->FMODE_CFG0 |=  ((2<<20)|(2<<22));

  /* Remove pull-up and pull-down at GPIO_3 */
  gconf->IO_CFG0_b.GPIO_3_PUD = 1;

  /* Configure AdvTMR ch.2 */
  advtmr->T2CONTROL = 0x0028;
  advtmr->T2LOAD = 0xFFFF;               /* Period of PWM */
  advtmr->T2BGLOAD = 0xFFFF;
  advtmr->T2COMPARE = 0x0000;            /* PWM duty cycle */
  advtmr->T2BGCOMPARE = 0x0000;
  advtmr->T2TFFZERO = 1;                 /* Toggle f-f with timer compare and timer load */
  advtmr->T2TFFINV = 0;
  advtmr->T2TFFEN = 1;                   /* Enable f-f */
  advtmr->T2IOSEL = 1;
  advtmr->T2CMPINTEN = 1;                /* Enable compare interrupt */
  advtmr->T2CMPEN = 1;                   /* Enable compare mode */
  advtmr->T2CONTROL = 0x00E8;            /* Enable timer, set clock divisor to 1/1 */

  /* Configure AdvTMR ch.3 */
  advtmr->T3CONTROL = 0x0028;
  advtmr->T3LOAD = 0xFFFF;               /* Period of PWM */
  advtmr->T3BGLOAD = 0xFFFF;
  advtmr->T3COMPARE = 0x0000;            /* PWM duty cycle */
  advtmr->T3BGCOMPARE = 0x0000;
  advtmr->T3TFFZERO = 1;                 /* Toggle f-f with timer compare and timer load */
  advtmr->T3TFFINV = 0;
  advtmr->T3TFFEN = 1;                   /* Enable f-f */
  advtmr->T3IOSEL = 1;
  advtmr->T3CMPINTEN = 1;                /* Enable compare interrupt */
  advtmr->T3CMPEN = 1;                   /* Enable compare mode */
  advtmr->T3CONTROL = 0x00E8;            /* Enable timer, set clock divisor to 1/1 */

  /* Enable NVIC Interrupts for ADVTMR2 and ADVTMR 3*/
  NVIC_EnableIRQ(ADVTMR2_CMP_IRQn);
  NVIC_EnableIRQ(ADVTMR3_CMP_IRQn);

  while(1)
  {
    /* If flag flGetValue2 is set in interrupt and this is the active LED
       then calculate new compare value */
    if (flGetValue2 && tswitch)
    {
      flGetValue2 = 0;
      CalculateCompareValue(&dir2, &advcnt2, &compare_val2);
      /* if full cycle is done, switch to the other LED */
      if (0 == compare_val2) tswitch = 0;
    }

    /* If flag flGetValue3 is set in interrupt and this is the active LED
       then calculate new compare value */
    if (flGetValue3 && !tswitch)
    {
      flGetValue3 = 0;
      CalculateCompareValue(&dir3, &advcnt3, &compare_val3);
      /* if full cycle is done, switch to the other LED */
      if (0 == compare_val3) tswitch = 1;
    }
  }
}
