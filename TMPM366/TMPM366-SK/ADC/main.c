/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded
 *    Workbench for ARM to develop code for Toshiba TMPM366 family 
 *    microcontrollers. It is developed for IAR TMPM366-SK Eval Board.
 *
 *    This example shows basic use of ADC and I/O ports
 *
 *    Slide VR1 potentiometer and observe the LEDs.
 *
 *    History :
 *    1. Date        : 01.2011
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm366fdfg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "arm_comm.h"
#include "board.h"
#include "drv_nvic.h"
#include "drv_cg.h"


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile int Tick;
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

#pragma section=".intvec"

int main(void)
{
cg_clkinit_t clkinit;
uint8_t cntr=0;

  /*Watch dog timer disable*/
  WDMOD = 0x00;
  WDCR = 0xB1;
  
  clkinit.gear = GEAR_FC;       /**/
  clkinit.fcsel = FCSEL_FPLL_2; /**/
  clkinit.pfsel = FPSEL_FC;     /**/
  clkinit.prck = PRCK_2;
  clkinit.fosc = FOSCSEL_EXTOSC;
  clkinit.pll_enable = CG_ENABLE;
  clkinit.pllmul = PLLSET_MUL_8; 

  InitClock(&clkinit);
  /*
  LED init
  */
  INIT_LEDS;
  /*
  ADC init
  */
  CGSYSCR_bit.FCSTOP = 0;/*Enable ADC Clock*/
  ADCLK_bit.ADCLK = 1;   /*ADCLOCK = Fc/2*/
  ADCLK_bit.ADSH = 4;    /*sample hold time = conversion clock * 80*/
  ADMOD1 = (1<<7);       /*Enable Vref*/
  ADMOD3_bit.SCAN = 0;   /*Fixed channel mode*/
  ADMOD3_bit.REPEAT = 0; /*Single conversion mode*/
  ADMOD2_bit.ADCH = VR1_CHANNEL;  /*Select VR1 Channel*/
  /*VR1 Pin init as Analog input*/
  VR1_IE &= ~VR1;
  /*Start Conversion*/
  ADMOD0_bit.ADS = 1;
  /*Set vector table location*/
  VTOR  = (unsigned int)__segment_begin(".intvec");
  /*System tick 20 times per second*/
  SysTickStart(20);
  /*Main loop*/
  while(1)
  {
    if(Tick)
    {
      Tick = 0;
      cntr++;
      ADMOD0_bit.ADS = 1;
      LED_PORT = (1<<((ADREG11_bit.ADR*8+2048)/4095))-1;
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
