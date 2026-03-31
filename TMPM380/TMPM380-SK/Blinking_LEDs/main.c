/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2010
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded Workbench for ARM
 *    to develop code for Toshiba TMPM380 family microcontrollers. It is developed for
 *    IAR TMPM380-SK Eval Board.
 *
 *    This example shows basic use of System Timer, interrupts and I/O ports
 *
 *    History :
 *    1. Date        : 03.2010
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm380fxfg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "led.h"
#include "nvic.h"


/* Private define ------------------------------------------------------------*/
#define FOSC1 10000000UL
#define FOSC2 10000000UL
#define FS    32768UL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile int Tick;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*
Get High speed clock
retruns High speed clock in Hz
*/
uint32_t GetFc(void)
{
uint32_t clock = (CGOSCCR_bit.OSCSEL)?FOSC1:FOSC2;
  if(CGPLLSEL_bit.PLLSEL  && CGOSCCR_bit.PLLON) return clock*4;
  return clock;
}
/*
Get Sys Frequency
retruns system frequency in Hz
*/
uint32_t GetFsys(void)
{
  
  if(CGCKSEL_bit.SYSCKFLG) return FS;
    
  uint32_t clock = GetFc();

  switch(CGSYSCR_bit.GEAR)
  {
  case 4:
    return clock /= 2;
  case 5:
    return clock /= 4;
  case 6:
    return clock /= 8;
  case 7:
    return clock /= 16;
  }
  
  return clock;
}
/*
Start Sys tick Timer
Parameter: Ticks per second
*/
void SysTickStart(uint32_t Tick)
{
volatile uint32_t dummy;

  dummy = SYSTICKCSR;
  /*Set period*/  
  SYSTICKRVR = (GetFsys())/Tick;
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
uint32_t cntr = 0;
  /*Watch dog timer disable*/
  WDMOD = 0x20;
  WDCR = 0xB1;
  /*Set vector table location*/
  VTOR  = (unsigned int)__segment_begin(".intvec");
  /*Init Leds*/
  LED_Init();
  /*System tick 160 times per second (6.25ms)*/
  SysTickStart(160);
  /*Main loop*/
  while(1)
  {
    if(Tick)
    {
      Tick = 0;
      cntr++;
      if(!(cntr & 0xF))
      {/*enter here every 100ms (6.25ms * 16)*/
        
        /*running light*/
        LED_WriteBuff(~(1<<((cntr>>4)&0x7)), 0);
                           
        char s[15];
        /*convert cntr/16 to decimal str*/
        sprintf(s,"%3d",cntr>>4);
        int index  = strlen(s);
        /*Display the decimal value on segment leds
         (low 3 digits only)*/
        for(int i = 1; 3 >= i ; i++)
        {
          char ch;
          if(0x30 <= (ch = s[--index]))
          {
            ch -=0x30;
          }
          else
          {
            ch-=0x20;
          }
  
          LED_WriteBuff(_7ledchar[ch], i);
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
  /*LED update*/
  LED_Control();
}

