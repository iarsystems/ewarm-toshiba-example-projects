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
 *     It implements usb audio device class with one output.
 *
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
char Message[50];
cg_clkinit_t clkinit;
UartLineCoding_t UartLineCoding;

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
  /*Init Uart*/
  UartInit();
  
  UartLineCoding.dwDTERate = 115200;
  UartLineCoding.bStopBitsFormat = UART_ONE_STOP_BIT;
  UartLineCoding.bParityType = UART_NO_PARITY;
  UartLineCoding.bDataBits =UART_WORD_WIDTH_8;
  UartSetLineCoding(UartLineCoding);
  
  // Init Audio
  UsbAudioClassInit();
  
  strcpy(Message,"***************************\n\r");
  UartWrite((pInt8U)Message,strlen(Message));
  strcpy(Message,"*     IAR TMPM366 SK      *\n\r");
  UartWrite((pInt8U)Message,strlen(Message));
  strcpy(Message,"*  Audio Device example   *\n\r");
  UartWrite((pInt8U)Message,strlen(Message));
  strcpy(Message,"***************************\n\r");
  UartWrite((pInt8U)Message,strlen(Message));


  while(1)
  {
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
