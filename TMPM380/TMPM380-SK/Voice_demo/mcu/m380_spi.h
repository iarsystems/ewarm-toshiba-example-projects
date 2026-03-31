/*******************************************************************************
* File Name 		 : m380_spi.h
* Version			 : V1.0
* Date				 : 2010/02/xx
* Description		 : SIP header
********************************************************************************/

#ifndef __M380_SPI_H
#define __M380_SPI_H

#include "..\typedef.h"

#define SSPCR1_SOD		(1<<3)
#define SSPCR1_MS		(1<<2)
#define SSPCR1_SSE		(1<<1)

#define SSPSR_BSY		(1<<4)	/* Busy Flag */
#define SSPSR_RFF		(1<<3)	/* Receive FIFO full */
#define SSPSR_RNE		(1<<2)	/* Receive FIFO empty */
#define SSPSR_TNF		(1<<1)	/* Transmit FIFO full */
#define SSPSR_TFE		(1<<0)	/* Transmit FIFO empty */

#define SSPDMACR_TXDMAE		(1<<1)	/* Transmit FIFO DMA control */
#define SSPDMACR_RXDMAE		(1<<0)	/* Receive FIFO DMA control */


/**************************************************************/
void API_SPI_Init(void);
void API_SPI_Wait_Busy(void);
void API_SPI_Enable(void);
void API_SPI_Disable(void);
uint32_t API_SPI_Read(uint8_t *buffer, uint32_t len);
uint32_t API_SPI_Write(uint8_t *buffer, uint32_t len);
void API_SPI_FlushRx(void);

#endif /* __M380_SPI_H */ 
