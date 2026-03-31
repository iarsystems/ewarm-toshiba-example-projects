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
 *    1. Date        : 20.01.2012
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
#include "includes.h"

#pragma section=".intvec"
#pragma location="USB_DMA_RAM"

/* Private define ------------------------------------------------------------*/
#define TIMER_TICK_PER_SEC   2
#define UPDATE_SHOW_DLY       ((Int32U)(0.5 * TIMER_TICK_PER_SEC))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#pragma data_alignment=4
__no_init Int8U Lun0Buffer[512];

static volatile int Tick;

const cg_clkinit_t CG_clkinit = {
  .gear = GEAR_FC,
  .fcsel = FCSEL_FPLL,
  .pfsel = FPSEL_FC,
  .prck = PRCK_2,
  .fosc = FOSCSEL_EXTOSC,
  .pll_enable = CG_ENABLE,
  .pllmul = PLLSET_16MHZ_80MHZ,
  .lposc = CG_ENABLE,
  .usbl_clk_sel = CLK_USBPLL,
  .usbpll_enable = CG_ENABLE,
  .usbpllmul = PLLSET_16MHZ,
};

const Int8U HexToCharStr [] = "0123456789ABCDEF";

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

void DelayResolution100us(Int32U Dly)
{
  for(; Dly; Dly--)
  {
    for(volatile Int32U j = DLY_100US; j; j--)
    {
    }
  }
}

int main(void)
{
Int32U Dly = UPDATE_SHOW_DLY;
DiskStatusCode_t StatusHold = (DiskStatusCode_t) -1;
Int8U Message[17];
Int32U Tmp, Tmp1;
Boolean nZerro;

  /*Watch dog timer disable*/
  WDMOD = 0x00;
  WDCR = 0xB1;
  /*Init Clocks*/
  InitClock(&CG_clkinit);
  /*LED init*/
  INIT_LEDS();

  /*Set vector table location*/
  VTOR  = (unsigned int)__segment_begin(".intvec");

  /*Init SCSI module*/
  ScsiInit();

  /* LUNs Init*/
  LunInit(SD_DISK_LUN,SdDiskInit,SdGetDiskCtrlBkl,SdDiskIO);

  /* Init SD card driver
     SCSI init push init SD driver message for an each LUN*/
  for(Int32U i = 0; i < SCSI_LUN_NUMB; i++)
  {
    /* Implement LUNs messages */
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

  /* LCD Powerup init */
  HD44780_PowerUpInit();
  /* Show messages on LCD */
  HD44780_StrShow(1, 1,  "IAR Systems ARM ");
  HD44780_StrShow(1, 2,  "USB Mass Storage");


  while(1)
  {
    for(Int32U i = 0; i < SCSI_LUN_NUMB; i++)
    {
      /* Implement LUNs messages */
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
      /* Update MMC/SD card status */
      SdStatusUpdate();
      if(Dly-- == 0)
      {
        /* LCD show */
        Dly = UPDATE_SHOW_DLY;
        /* Current state of MMC/SD show */
        pDiskCtrlBlk_t pSD_DiskCtrlBlk = SdGetDiskCtrlBkl();
        if(StatusHold != pSD_DiskCtrlBlk->DiskStatus)
        {

          StatusHold = pSD_DiskCtrlBlk->DiskStatus;
          switch (pSD_DiskCtrlBlk->DiskStatus)
          {
          case DiskCommandPass:
            switch(pSD_DiskCtrlBlk->DiskType)
            {
            case DiskMMC:
              strcpy((char*)Message,"MMC Card - ");
              break;
            case DiskSD_Spec1_x:
            case DiskSD_Spec2_0:
              strcpy((char*)Message,"SD Card - ");
              break;
            default:
              strcpy((char*)Message,"Card - ");
            }
            /* Calculate MMC/SD size [MB] */
            Tmp  = pSD_DiskCtrlBlk->BlockNumb * pSD_DiskCtrlBlk->BlockSize;
            Tmp  = Tmp/1000000;
            Tmp1 = Tmp/1000;
            nZerro = FALSE;
            if(Tmp1)
            {
              Message[strlen((char*)Message)+1] = 0;
              Message[strlen((char*)Message)]   = HexToCharStr[Tmp1];
              Tmp %= 1000;
              nZerro = TRUE;
            }
            Tmp1 = Tmp/100;
            if(Tmp1 || nZerro)
            {
              Message[strlen((char*)Message)+1] = 0;
              Message[strlen((char*)Message)]   = HexToCharStr[Tmp1];
              Tmp %= 100;
              nZerro = TRUE;
            }
            Tmp1 = Tmp/10;
            if(Tmp1 || nZerro)
            {
              Message[strlen((char*)Message)+1] = 0;
              Message[strlen((char*)Message)]   = HexToCharStr[Tmp1];
              Tmp %= 10;
              nZerro = TRUE;
            }
            if(Tmp || nZerro)
            {
              Message[strlen((char*)Message)+1] = 0;
              Message[strlen((char*)Message)]   = HexToCharStr[Tmp];
            }
            strcat((char*)Message,"MB");
            for(Int32U i = strlen((char*)Message); i < 16; ++i)
            {
              Message[i] = ' ';
            }
            Message[strlen((char*)Message)+1] = 0;
            break;
          default:
            strcpy((char*)Message,"Pls, Insert Card");
          }
          HD44780_StrShow(1, 2, (pInt8S)Message);
        }
      }
    }
  }
}

/* Sys tick handler Set Tick flag. LED update */
void SysTick_Handler(void)
{
volatile uint32_t dummy;
  dummy = SYSTICKCSR;
  /*Sys tick*/
  Tick = 1;
}
