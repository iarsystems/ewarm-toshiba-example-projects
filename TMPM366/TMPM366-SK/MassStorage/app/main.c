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
 *     It implements a MMC/SD card drive.
 *    The first free drive letters will be used. For example, if your PC
 *    configuration includes two hard disk partitions (in C:\ and D:\) and a CD-ROM
 *    drive (in E:\), the memory card drive will appear as F:\.
 *    LED8 will indicate drive activity.
 *    The example handles Standard SD and SDHD cards, but not SDXC cards.
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

#pragma location="USB_DMA_RAM"
#pragma data_alignment=4
__no_init Int8U Lun0Buffer[512];
/* Private define ------------------------------------------------------------*/
#define TIMER_TICK_PER_SEC   2
#define UPDATE_SHOW_DLY       ((Int32U)(0.5 * TIMER_TICK_PER_SEC))
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
Int32U Dly = UPDATE_SHOW_DLY;
DiskStatusCode_t StatusHold = (DiskStatusCode_t) -1;
char Message[50];
Int32U Tmp,Size;

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

  /* Init SCSI module */
  ScsiInit();

  /* LUNs Init*/
  LunInit(SD_DISK_LUN,SdDiskInit,SdGetDiskCtrlBkl,SdDiskIO);

  /*Init Uart*/
  UartInit();
  
  UartLineCoding.dwDTERate = 115200;
  UartLineCoding.bStopBitsFormat = UART_ONE_STOP_BIT;
  UartLineCoding.bParityType = UART_NO_PARITY;
  UartLineCoding.bDataBits =UART_WORD_WIDTH_8;
  UartSetLineCoding(UartLineCoding);
  
  /* Init SD card driver
     SCSI init push init SD driver message for an each LUN*/
  for(Int32U i = 0; i < SCSI_LUN_NUMB; i++)
  {
    // Implement LUNs messages
    if(LunImp(i))
    { /*LED 8 On*/
      LED_ON(LED8);
    }
    else
    { /*LED 8 Off*/
      LED_OFF(LED8);
    }
  }

  /*Sys tick start*/
  SysTickStart(TIMER_TICK_PER_SEC);
  
  strcpy(Message,"***************************\n\r");
  UartWrite((pInt8U)Message,strlen(Message));
  strcpy(Message,"*     IAR TMPM366 SK      *\n\r");
  UartWrite((pInt8U)Message,strlen(Message));
  strcpy(Message,"* USB MassStorage example *\n\r");
  UartWrite((pInt8U)Message,strlen(Message));
  strcpy(Message,"***************************\n\r");
  UartWrite((pInt8U)Message,strlen(Message));


  while(1)
  {
    for(Int32U i = 0; i < SCSI_LUN_NUMB; i++)
    {
      // Implement LUNs messages
      if(LunImp(i))
      { /*LED 8 On*/
        LED_ON(LED8);
      }
      else
      { /*LED 8 Off*/
        LED_OFF(LED8);
      }
    }
    if (Tick)
    {
      Tick = 0;
      // Update MMC/SD card status
      SdStatusUpdate();
      if(Dly-- == 0)
      {
        // LCD show
        Dly = UPDATE_SHOW_DLY;
        // Current state of MMC/SD show
        pDiskCtrlBlk_t pMMCDiskCtrlBlk = SdGetDiskCtrlBkl();
        if(StatusHold != pMMCDiskCtrlBlk->DiskStatus)
        {

          StatusHold = pMMCDiskCtrlBlk->DiskStatus;
          switch (pMMCDiskCtrlBlk->DiskStatus)
          {
          case DiskCommandPass:
            // Calculate MMC/SD size [MB]
            Size = (pMMCDiskCtrlBlk->BlockNumb * pMMCDiskCtrlBlk->BlockSize);
            Tmp  = Size/1000000;
            Tmp += ((Size%1000000)<1000000/2)?0:1;

            switch(pMMCDiskCtrlBlk->DiskType)
            {
            case DiskMMC:
              sprintf(Message,"MMC Card - %dMB      \r",Tmp);
              break;
            case DiskSD_Spec1_x:
            case DiskSD_Spec2_0:
              sprintf(Message,"SD Card - %dMB      \r",Tmp);
              break;
            default:
              sprintf(Message,"Card - %dMB      \r",Tmp);
            }
            Message[strlen(Message)+1] = 0;
            break;
          default:
            strcpy(Message,"Pls, Insert Card      \r");
          }
          UartWrite((pInt8U)Message,strlen(Message));
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
