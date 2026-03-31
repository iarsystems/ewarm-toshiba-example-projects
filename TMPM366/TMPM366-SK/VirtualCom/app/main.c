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
 *     It implements USB CDC (Communication Device Class) device and installs
 *    it like a Virtual COM port. The UART2 is used for physical implementation
 *    of the RS232 port.
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
Int8U Buffer[100];
pInt8U pBuffer;
Int32U Size,TranSize;
cg_clkinit_t clkinit;
Boolean CdcConfigureStateHold;

#if CDC_DEVICE_SUPPORT_LINE_CODING > 0
CDC_LineCoding_t CDC_LineCoding;
UartLineCoding_t UartLineCoding;
#endif // CDC_DEVICE_SUPPORT_LINE_CODING > 0

#if CDC_DEVICE_SUPPORT_LINE_STATE > 0

UartLineEvents_t      UartLineEvents ;
SerialState_t   SerialState;
#endif // CDC_DEVICE_SUPPORT_LINE_STATE > 0

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
  
   /* Init USB */
  UsbCdcInit();
  CdcConfigureStateHold = !IsUsbCdcConfigure();

  while(1)
  {
    if (IsUsbCdcConfigure())
    {
      // Data from USB
      Size = UsbCdcRead(Buffer,sizeof(Buffer)-1);
      if(Size)
      {
        LED_ON(LED1);
#ifdef DATA_LOGGING
        Buffer[Size] = 0;
        printf("> %s\n",Buffer);
#endif // DATA_LOGGING
        TranSize = 0;
        pBuffer = Buffer;
        do
        {
          Size -= TranSize;
          pBuffer += TranSize;
          TranSize = UartWrite(pBuffer,Size);
        }
        while(Size != TranSize);
        LED_OFF(LED1);
     }

      // Data from UART1
      Size = UartRead(Buffer,sizeof(Buffer)-1);
      if(Size)
      {
        LED_ON(LED2);
#ifdef DATA_LOGGING
        Buffer[Size] = 0;
        printf("< %s\n",Buffer);
#endif  // DATA_LOGGING
        while(!UsbCdcWrite(Buffer,Size));
        LED_OFF(LED2);
      }

      // Get line and modem events from UART
#if CDC_DEVICE_SUPPORT_LINE_STATE > 0
      // Get line events - BI, FE, PE, OE
      UartLineEvents = UartGetUartLineEvents();
      if(UartLineEvents.Data)
      {
        SerialState.Data = 0;
        // Line events report BI, PE, FE and OE
        SerialState.bBreak = FALSE;
        SerialState.bFraming = UartLineEvents.bFE;
        SerialState.bOverRun = UartLineEvents.bOE;
        SerialState.bParity = UartLineEvents.bPE;
        // Send events
        UsbCdcReportSerialCommState(SerialState);
      }
#endif // CDC_DEVICE_SUPPORT_LINE_STATE > 0
    }
    else
    {
      if(CdcConfigureStateHold == TRUE)
      {
        CdcConfigureStateHold = FALSE;
      }
    }

    // UART line coding - Baud rate, number of the stop bits,
    // number of bits of the data word and parity type
#if CDC_DEVICE_SUPPORT_LINE_CODING > 0
    if(UsbCdcIsNewLineCodingSettings())
    {
      CDC_LineCoding = UsbCdcGetLineCodingSettings();
      // Update the baud rate
      UartLineCoding.dwDTERate = CDC_LineCoding.dwDTERate;
      // Update the stop bits number
      UartLineCoding.bStopBitsFormat = CDC_LineCoding.bCharFormat?UART_TWO_STOP_BIT:UART_ONE_STOP_BIT;
      // Update the parity type
      switch(CDC_LineCoding.bParityType)
      {
      case 0:
        UartLineCoding.bParityType = UART_NO_PARITY;
        break;
      case 1:
        UartLineCoding.bParityType = UART_ODD_PARITY;
        break;
      case 2:
        UartLineCoding.bParityType = UART_EVEN_PARITY;
        break;
      case 3:
        UartLineCoding.bParityType = UART_FORCE_1_PARITY;
        break;
      case 4:
        UartLineCoding.bParityType = UART_FORCE_0_PARITY;
        break;
      }
      // Update the word width
      UartLineCoding.bDataBits = (UartWordWidth_t)((CDC_LineCoding.bDataBits - 5)<<5);
      // Set UART line coding
      UartSetLineCoding(UartLineCoding);
    }
#endif // CDC_DEVICE_SUPPORT_LINE_CODING > 0
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
