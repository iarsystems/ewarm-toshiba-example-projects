/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded
 *    Workbench for ARM to develop code for Toshiba TMPM364 family 
 *    microcontrollers. It is developed for IAR TMPM364-SK Eval Board.
 *
 *    This example shows basic use of System Timer, interrupts and I/O ports
 *
 * Press PSW1 button to stop counting.
 * Press PSW2 button to start counting.
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
#include <Toshiba\iotmpm364f10fg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "includes.h"
/* Private define ------------------------------------------------------------*/
#define DLY_100US  350
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
cg_clkinit_t clocks;
char vrstr[16];

  /*Watch dog timer disable*/
  WDMOD = 0x00;
  WDCR = 0xB1;
  /**/
  clocks.gear = GEAR_FC;
  clocks.fcsel = FCSEL_FPLL;
  clocks.pfsel = FPSEL_FGEAR;
  clocks.ft0sel = FT0SEL_2;
  clocks.fsyssel = FSYSSEL_FGEAR;
  clocks.pll_enable  = CG_ENABLE;
  clocks.pllmul = PLLSET_MUL_4;

  InitClock(&clocks);
  /*
  LED init
  */
  INIT_LEDS;
  /*
  Keys init
  */
  INIT_BUTTONS;
  /*Init LCD Pins*/
  HD44780_IO_Init();
  /*Power up LCD*/
  if(HD44780_OK != HD44780_PowerUpInit())
  {
    return 1;
  }
  /*Set vector table location*/
  VTOR  = (unsigned int)__segment_begin(".intvec");
  /*System tick 20 times per second*/
  SysTickStart(20);
  
  HD44780_StrShow(1,1,(const HD44780_STRING_DEF *) "   IAR SYSTEMS  ");
  HD44780_StrShow(1,2,(const HD44780_STRING_DEF *) "                ");
  /*
  ADC init
  */
  CGSYSCR_bit.FCSTOP = 0;   /*Enable ADC Clock*/
  ADCLK_bit.ADCLK = 4;      /*ADC Clock Fc/16*/
  ADCLK_bit.TSH = 13;       /*A/D sample hold time 512 conversion clocks*/
  ADMOD1_bit.VREFON = 1;    /*Enable Vref*/
  DelayResolution100us(1);  
  ADMOD0_bit.SCAN = 0;            /*Fixed channel mode*/
  ADMOD0_bit.REPEAT = 0;          /*Single conversion mode*/
  ADMOD0_bit.ITM = 0;             /*Generate interrupt once every single conversion*/
  ADMOD1_bit.ADCH = VR2_CHANNEL;  /*Select VR2 Channel*/

  /*VR2 Pin init as Analog input*/
  VR2_IE &= ~VR2;
  
  /*Start Conversion*/
  ADMOD0_bit.ADS = 1;
  /*Main loop*/
  while(1)
  {
    if(Tick)
    {
      unsigned short result = ADREG08;
      Tick = 0;
      if(result & 0x1)
      {
        sprintf(vrstr,"VR2=%3d%%",(result>>6)*100/1023);  /*convert result*/
        HD44780_StrShow(5,2,(const HD44780_STRING_DEF *)vrstr);
        ADMOD0_bit.ADS = 1;
      }
    }
  }
}
/*
Sys tick handler
Set Tick flag
*/

void SysTick_Handler(void)
{
volatile uint32_t dummy;
  dummy = SYSTICKCSR;  
  /*Sys tick*/
  Tick = 1;
}

/*************************************************************************
 * Function Name: DelayResolution100us
 * Parameters: Int32U Dly
 * Return: void
 *
 * Description: Delay Dly * [100us]
 *		
 *************************************************************************/
void DelayResolution100us(Int32U Dly)
{
  for(; Dly; Dly--)
  {
    for(volatile Int32U j = DLY_100US; j; j--)
    {
    }
  }
}
