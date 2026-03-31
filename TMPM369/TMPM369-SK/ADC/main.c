/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded
 *    Workbench for ARM to develop code for Toshiba TMPM369 family
 *    microcontrollers. It is developed for IAR TMPM369-SK Eval Board.
 *
 *    This example shows basic use of ADC and I/O ports.
 *
 *    LEDs displays the voltage applied to the PJ7 pin (J1-P16).
 *
 *    History :
 *    1. Date        : 19.01.2012
 *       Author      : Stanimir Bonev
 *       Description : Initial Revision
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "arm_comm.h"
#include "board.h"
#include "drv_nvic.h"
#include "drv_cg.h"


/* Private define ------------------------------------------------------------*/
#pragma section=".intvec"

// ADC PJ7/AINB11
#define ADC_CHANNEL     11
#define ADC_PIN_MASK    (1UL<<7)
#define ADC_IE          PJIE
#define ADC_CR          PJCR
#define ADC_DATA        ADBREG11_bit.ADR

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile int Tick;

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

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*
Start Sys tick Timer
Parameter: Ticks per second
*/
void SysTickStart(uint32_t tick)
{
volatile uint32_t dummy;

  dummy = SYSTICKCSR;
  /*Set period*/
  SYSTICKRVR = CG_GetClock(CLK_FSYS)/tick;
  /*Clock source - System Clock*/
  SYSTICKCSR_bit.CLKSOURCE = 1;
  /*Enable interrupt*/
  SYSTICKCSR_bit.TICKINT = 1;
  /*Start Sys Timer*/
  SYSTICKCSR_bit.ENABLE = 1;
}
/*
Stop Sys tick timer
*/
void SysTickStop(void)
{ /*Sys Tick timer disable*/
  SYSTICKCSR_bit.ENABLE = 0;
}

int main(void)
{
uint8_t cntr=0;

  /*Watch dog timer disable*/
  WDMOD = 0x00;
  WDCR = 0xB1;
  /*Set vector table location*/
  VTOR  = (unsigned int)__segment_begin(".intvec");

  InitClock(&CG_clkinit);
  /*
  LED init
  */
  INIT_LEDS();
  /*
  ADC init
  */
  CGSYSCR_bit.FCSTOP = 0;/*Enable ADC Clock*/
  ADBCLK_bit.ADCLK = 1;   /*ADCLOCK = Fc/2*/
  ADBCLK_bit.ADSH = 4;    /*sample hold time = conversion clock * 80*/
  ADBMOD1 = (1<<7);       /*Enable Vref*/
  ADBMOD3_bit.SCAN = 0;   /*Fixed channel mode*/
  ADBMOD3_bit.REPEAT = 0; /*Single conversion mode*/
  ADBMOD2_bit.ADCH = ADC_CHANNEL;  /*Select Channel*/
  /* Pin init as Analog input*/
  ADC_IE &= ~ADC_PIN_MASK;
  ADC_CR &= ~ADC_PIN_MASK;
  /*Start Conversion*/
  ADBMOD0_bit.ADS = 1;
  /*System tick 20 times per second*/
  SysTickStart(20);
  /*Main loop*/
  while(1)
  {
    if(Tick)
    {
      Tick = 0;
      cntr++;
      if(ADBMOD5_bit.EOCF)
      {
        LED_PORT = (1<<((ADC_DATA*8+2048)/4095))-1;
        ADBMOD0_bit.ADS = 1;
      }
    }
  }
}
/*
Sys tick handler
Set Tick flag. LED update
*/

void SysTick_Handler(void)
{
volatile uint32_t dummy;
  dummy = SYSTICKCSR;
  /*Sys tick*/
  Tick = 1;
}
