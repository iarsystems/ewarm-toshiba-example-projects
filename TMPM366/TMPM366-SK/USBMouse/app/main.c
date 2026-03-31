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
 *    It implements USB HID mouse.
 *
 *    PSW2 is the left button.
 *    PSW1 is the right button.
 *
 *    JP1 - Opened
 *    JP2 - Closed
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
#include "includes.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile int Tick;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#pragma section=".intvec"
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

#define MOUSE_DELTA           1
/*
Main
*/
int main(void)
{
/*Buttons_t ButtCtrl*/
Int8S X = 0, Y = 0;
Int8U Buttons = 0, ButtonsHold = 0;
cg_clkinit_t clkinit;

  /*Watch dog timer disable*/
  WDMOD = 0x00;
  WDCR = 0xB1;
  /*Init Clocks*/ 
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
  Keys init
  */
  INIT_BUTTONS;
  /*Set vector table location*/
  VTOR  = (unsigned int)__segment_begin(".intvec");
  /*Init USB*/
  HidInit();
  /*Sys tick start. 50 times per second*/
  SysTickStart(50);

  while(1)
  {
    if(Tick)
    {
      Tick = 0;
      if(UsbCoreReq(UsbCoreReqDevState) == UsbDevStatusConfigured)
      {
        {
          Y += MOUSE_DELTA;
        }

        {
          X += MOUSE_DELTA;
        }

        if((PSW2 & BUTTON_PORT))
        {
          Buttons &= ~1;
          LED_OFF(LED1);
        }
        else
        {
          Buttons |= 1;
          LED_ON(LED1);
        }

        if((PSW1 & BUTTON_PORT))
        {
          Buttons &=~2;
          LED_OFF(LED2);
       }
        else
        {
          Buttons |= 2;
          LED_ON(LED2);
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
