/*******************************************************************************
* File Name 		 : sd_spi.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SD Interface header
********************************************************************************/

#ifndef __SD_SPI_H
#define __SD_SPI_H

#ifdef SD_LL_SPI1_GLOBAL
#define SD_LL_SPI1_EXTERN
#else
#define SD_LL_SPI1_EXTERN  extern
#endif

#include "..\typedef.h"

#define SD_DLY_1MSEC       1000

/*************************************************************************
 * Function Name: SdPowerOn
 * Parameters: none
 * Return: none
 *
 * Description: Set power off state
 *
 *************************************************************************/
void SdPowerOn (void);

/*************************************************************************
 * Function Name: SdPowerOff
 * Parameters: none
 * Return: none
 *
 * Description: Set power off state
 *
 *************************************************************************/
void SdPowerOff (void);

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
void SdChipSelect (Boolean Select);

/*************************************************************************
 * Function Name: SdPresent
 * Parameters: none
 * Return: Boolean - true cart present
 *                 - false cart no present
 *
 * Description: SD/MMC precent check
 *
 *************************************************************************/
Boolean SdPresent(void);

/*************************************************************************
 * Function Name: SdWriteProtect
 * Parameters: none
 * Return: Boolean - true cart is protected
 *                 - false cart no protected
 *
 * Description: SD/MMC Write protect check
 *
 *************************************************************************/
Boolean SdWriteProtect (void);

/*************************************************************************
 * Function Name: SdSetClockFreq
 * Parameters: uint32_t Frequency
 * Return: uint32_t
 *
 * Description: Set SPI ckl frequency
 *
 *************************************************************************/
uint32_t SdSetClockFreq (uint32_t Frequency);

/*************************************************************************
 * Function Name: SdInit
 * Parameters: none
 * Return: none
 *
 * Description: Init SPI, Cart Present, Write Protect and Chip select pins
 *
 *************************************************************************/
void SdInit (void);

/*************************************************************************
 * Function Name: SdTransferByte
 * Parameters: uint8_t ch
 * Return: uint8_t
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
uint8_t SdTransferByte (uint8_t ch);

/*************************************************************************
 * Function Name: SdSendBlock
 * Parameters: uint8_t *pData, int32_t Size
 *
 * Return: void
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
void SdSendBlock (uint8_t *pData, uint32_t Size);

/*************************************************************************
 * Function Name: SdReceiveBlock
 * Parameters: uint8_t *pData, int32_t Size
 *
 * Return: void
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
void SdReceiveBlock (uint8_t *pData, uint32_t Size);

/*************************************************************************
 * Function Name: SdDly_1ms
 * Parameters: uint32_t Delay
 * Return: none
 *
 * Description: Delay [msec]
 *
 *************************************************************************/
void SdDly_1ms (uint32_t Delay);

#endif // __SD_SPI_H
