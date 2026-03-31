/*******************************************************************************
* File Name 		 : sd_spi_mode.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SD Interface header
********************************************************************************/

#ifndef __SD_SPI_MODE_H
#define __SD_SPI_MODE_H

#include "..\typedef.h"
#include "disk.h"

#ifdef SD_SPI_MODE_GLOBAL
#define SD_SPI_MODE_EXTERN
#else
#define SD_SPI_MODE_EXTERN  extern
#endif

#define SD_DISK_LUN       0
#define SD_DEF_BLK_SIZE   512
#define IdentificationModeClock   (200KHZ)

/*************************************************************************
 * Function Name: SdStatusUpdate
 * Parameters: none
 *
 * Return: none
 *
 * Description: Update status of SD/MMC card
 *
 *************************************************************************/
void SdStatusUpdate (void);

/*************************************************************************
 * Function Name: SdDiskInit
 * Parameters:  none
 *
 * Return: none
 *
 * Description: Init MMC/SD disk
 *
 *************************************************************************/
void SdDiskInit (void);

/*************************************************************************
 * Function Name: SdDiskInfo
 * Parameters:  uint8_t *pData, DiskInfoType_t DiskInfoType
 *
 * Return: int32_t
 *
 * Description: Return pointer to Info structure of the disk
 * (Inquiry or Format capacity)
 *
 *************************************************************************/
int32_t SdDiskInfo (uint8_t *pData, DiskInfoType_t DiskInfoType);

/*************************************************************************
 * Function Name: SdGetDiskCtrlBkl
 * Parameters:  none
 *
 * Return: pDiskCtrlBlk_t
 *
 * Description: Return pointer to status structure of the disk
 *
 *************************************************************************/
pDiskCtrlBlk_t SdGetDiskCtrlBkl (void);

/*************************************************************************
 * Function Name: SdDiskIO
 * Parameters: uint8_t *pData,int32_t BlockStart,
 *             int32_t BlockNum, DiskIoRequest_t IoRequest
 *
 * Return: DiskStatusCode_t
 *
 * Description: MMC/SD disk I/O
 *
 *************************************************************************/
DiskStatusCode_t SdDiskIO (uint8_t *pData,uint32_t BlockStart,
                              uint32_t BlockNum, DiskIoRequest_t IoRequest);

#endif // __SD_SPI_MODE_H
