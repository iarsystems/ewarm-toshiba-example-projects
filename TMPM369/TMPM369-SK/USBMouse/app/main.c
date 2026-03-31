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
 *    It implements USB HID mouse.
 *
 *  Jumpers:
 *   JP1 - Opened
 *   JP2 - Closed
 *
 *    History :
 *    1. Date        : 20.01.2012
 *       Author      : Stanimir Bonev
 *       Description : Initial Revision
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "includes.h"

/* Private define ------------------------------------------------------------*/
#pragma section=".intvec"

#define MOUSE_DELTA           5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile int Tick;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
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

/*************************************************************************
 * Function Name: DelayResolution100us
 * Parameters: Int32U Dly
 *
 * Return: none
 *
 * Description: Delay ~ (arg * 100us)
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

/*
Main
*/
int main(void)
{
/*Buttons_t ButtCtrl*/
Int8S X = 0, Y = 0;
Int8U Buttons = 0, ButtonsHold = 0;

  /*Watch dog timer disable*/
  WDMOD = 0x00;
  WDCR = 0xB1;

  InitClock(&CG_clkinit);

  /*
  LED init
  */
  INIT_LEDS();
  /*
  Keys init
  */
  JS_INIT();
  /*Set vector table location*/
  VTOR  = (unsigned int)__segment_begin(".intvec");
  /*Init USB*/
  HidInit();
  /*Sys tick start. 50 times per second*/
  SysTickStart(50);

  /* LCD Init */
  HD44780_PowerUpInit();

  /* Show message on the LCD */
  HD44780_StrShow(1, 1,  "  IAR Systems   ");
  HD44780_StrShow(1, 2,  "    USB Hid     ");

  while(1)
  {
    if(Tick)
    {
      Tick = 0;
      if(UsbCoreReq(UsbCoreReqDevState) == UsbDevStatusConfigured)
      {

        if(!(JS_LEFT & JS_LEFT_PORT))
        {
          X -= MOUSE_DELTA;
          Buttons |= 1;
        }

        if(!(JS_RIGHT & JS_RIGHT_PORT))
        {
          X += MOUSE_DELTA;
        }

        if(!(JS_UP & JS_UP_PORT))
        {
          Y -= MOUSE_DELTA;
          Buttons |= 1;
        }

        if(!(JS_DOWN & JS_DOWN_PORT))
        {
          Y += MOUSE_DELTA;
        }


        if(!(JS_CENTER & JS_CENTER_PORT))
        {
          Buttons |= 1U;
        }
        else
        {
          Buttons &= ~1U;
        }

        if(Y || X  || Buttons || (ButtonsHold ^ Buttons))
        {
          //UsbWakeUp();  // wake-up
          // Send report
          HidMouseSendReport(X,Y,Buttons);
          ButtonsHold = Buttons;
          Y = X = Buttons = 0;
        }
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
