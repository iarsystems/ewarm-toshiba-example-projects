/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : sd_ll_spi.c
 *    Description : SD/MMC low level SPI driver
 *
 *    History :
 *    1. Date        : January, 2012
 *       Author      : Stanimir Bonev
 *       Description : Initial revition
 *
 *    $Revision: 41 $
 **************************************************************************/
#include "includes.h"

/*************************************************************************
 * Function Name: SdPowerOn
 * Parameters: none
 * Return: none
 *
 * Description: Set power off state
 *
 *************************************************************************/
void SdPowerOn (void)
{
}
/*************************************************************************
 * Function Name: SdPowerOff
 * Parameters: none
 * Return: none
 *
 * Description: Set power off state
 *
 *************************************************************************/
void SdPowerOff (void)
{
}
/*************************************************************************
 * Function Name: SdChipSelect
 * Parameters: Boolean Select
 * Return: none
 *
 * Description: SD/MMC Chip select control
 * Select = true  - Chip is enable
 * Select = false - Chip is disable
 *
 *************************************************************************/
void SdChipSelect (Boolean Select)
{
  if(Select)
  {
    SD_PORT &= ~(SD_CS);
  }
  else
  {
    /*wait transmission ends*/
    while(SSP0SR_bit.BSY);
    SD_PORT |= (SD_CS);

    SdTranserByte(0xFF);
  }
}
/*************************************************************************
 * Function Name: SdPresent
 * Parameters: none
 * Return: Boolean - true cart present
 *                 - false cart no present
 *
 * Description: SD/MMC precent check
 *
 *************************************************************************/
Boolean SdPresent (void)
{
  return((SD_CP_PORT & SD_CP) == 0);
}

/*************************************************************************
 * Function Name: SdWriteProtect
 * Parameters: none
 * Return: Boolean - true cart is protected
 *                 - false cart no protected
 *
 * Description: SD/MMC Write protect check
 *
 *************************************************************************/
Boolean SdWriteProtect (void)
{
  return((SD_WP_PORT & SD_WP) != 0);
}

/*************************************************************************
 * Function Name: SdSetClockFreq
 * Parameters: Int32U Frequency
 * Return: Int32U
 *
 * Description: Set SPI ckl frequency
 *
 *************************************************************************/
Int32U SdSetClockFreq (Int32U Frequency)
{
Int32U Div;
Int32U PCLK = CG_GetClock(CLK_FSYS)/2;
  /*Disable SPI*/
  SSP1CR1_bit.SSE = 0;
  /**/
  SSP1CPSR = 2;
  /**/
  for(Div = 0; 256 > Div; Div++)
  {
    if(Frequency * (Div+1) > PCLK)
    {
      break;
    }
  }
  /*Set Divider*/
  SSP1CR0_bit.SCR = Div;
  /*Enable SPI*/
  SSP1CR1_bit.SSE = 1;
  /*Return real frequency*/
  return(PCLK/(Div+1));
}

/*************************************************************************
 * Function Name: SdInit
 * Parameters: none
 * Return: none
 *
 * Description: Init SPI, Cart Present, Write Protect and Chip select pins
 *
 *************************************************************************/
void SdInit (void)
{
volatile Int32U Dummy;

  /* Chip select */
  /*Set Pin to high level*/
  SD_PORT |= SD_CS;
  /*Make pin output*/
  SD_CR |= SD_CS;
  /* Cart present */
  /*Make pin input*/
  SD_CP_IE |= SD_CP;
  /* Write protect */
  /*Make pin input*/
  SD_WP_IE |= SD_WP;
  /*SPI pin configure*/
  /*Select Periferial function*/
  SD_FR |= SD_OUT | SD_IN | SD_CLK;
  SD_CR |= SD_OUT | SD_CLK;
  SD_IE |= SD_IN;

  /*SPI init*/
  /*Software reset*/
  SSP1CR0_bit.SPH = 0;        /*Captures data at the 1st clock edge*/
  SSP1CR0_bit.SPO = 0;        /*SP0CLK is in Low state*/
  SSP1CR0_bit.FRF = 0;        /*Frame format SPI*/
  SSP1CR0_bit.DSS = 7;        /*Data size select 8 bits*/
  SSP1CR1_bit.MS  = 0;        /*Device configured as a master*/
  SSP1CR1_bit.LBM = 0;        /*Normal serial port operation enabled*/

  SdSetClockFreq(IdentificationModeClock);

}

/*************************************************************************
 * Function Name: SdTranserByte
 * Parameters: Int8U ch
 * Return: Int8U
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
Int8U SdTranserByte (Int8U ch)
{
volatile Int8U read;

  while(SSP1SR_bit.BSY);

  SSP1DR = ch;
  while(SSP1SR_bit.BSY);

  read = SSP1DR & 0xFF;

  return read;
}

/*************************************************************************
 * Function Name: SdSendBlock
 * Parameters: pInt8U pData, Int32U Size
 *
 * Return: void
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
void SdSendBlock (pInt8U pData, Int32U Size)
{
  for(int cntr = 0; Size > cntr; cntr++)
  {
    SdTranserByte(*pData++);
  }
}

/*************************************************************************
 * Function Name: SdReceiveBlock
 * Parameters: pInt8U pData, Int32U Size
 *
 * Return: void
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
void SdReceiveBlock (pInt8U pData, Int32U Size)
{
volatile int dummy = 0xFF;

  for(int cntr = 0; Size > cntr; cntr++)
  {
    *pData++ = SdTranserByte(0xFF);
  }
}

/*************************************************************************
 * Function Name: SdDly_1ms
 * Parameters: Int32U Delay
 * Return: none
 *
 * Description: Delay [msec]
 *
 *************************************************************************/
void SdDly_1ms (Int32U Delay)
{
volatile Int32U i;
  for(;Delay;--Delay)
  {
    for(i = SD_DLY_1MSEC;i;--i);
  }
}
