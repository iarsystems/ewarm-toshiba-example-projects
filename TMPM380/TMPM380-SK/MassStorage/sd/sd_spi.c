/*******************************************************************************
* File Name 		 : sd_spi.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SD Interface
********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <intrinsics.h>
#include <assert.h>

#include "TMPM380_SYS.h"
#include "m380_port.h"
#include "m380_spi.h"
#include "sd_spi.h"

#define SSP1_T0_PCLK	(40MHZ)
#define CS_PIN		0x08
#define WP_PIN		0x10
#define CD_PIN		0x20
#define SPI_FIFOSZ		8

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
	SdDly_1ms(1);
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
	SdDly_1ms(1);
}

/*************************************************************************
 * Function Name: SdChipSelect
 * Parameters: Boolean Select
 * Return: none
 *
 * Description: SD Chip select control
 * Select = true  - Chip is enable
 * Select = false - Chip is disable
 *
 *************************************************************************/
void SdChipSelect (Boolean Select)
{
	volatile PORTM *port;
	port = &PORT.cnl[PORT_N];
	if (Select) {
		port->IO_Px	&= ~CS_PIN;
	}
	else {
		port->IO_Px	|= CS_PIN;
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
	volatile PORTM *port;
	port = &PORT.cnl[PORT_N];
	
	return ((port->IO_Px & CD_PIN) == 0);
}

/*************************************************************************
 * Function Name: SdWriteProtect
 * Parameters: none
 * Return: Boolean - true cart is protected
 *                 - false cart no protected
 *
 * Description: SD Write protect check
 *
 *************************************************************************/
Boolean SdWriteProtect (void)
{
	volatile PORTM *port;
	port = &PORT.cnl[PORT_N];
	
	return ((port->IO_Px & WP_PIN) != 0);
}

/*************************************************************************
 * Function Name: SdSetClockFreq
 * Parameters: uint32_t Frequency
 * Return: uint32_t
 *
 * Description: Set SPI ckl frequency
 *
 *************************************************************************/
uint32_t SdSetClockFreq (uint32_t Frequency)
{
	uint32_t Div;
	uint32_t SysFreq = SSP1_T0_PCLK;
	for(Div = 2; Div < 254; Div+=2) {
		if(Frequency * Div > SysFreq) {
			break;
		}
	}
	SSP1.SSPCPSR = Div;

	// Return real frequency
	return (SysFreq/Div);
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
	volatile PORTM *port;
	port = &PORT.cnl[PORT_N];
	
	/* CD (PN5) and WP (PN4) pin setup */
	port->IO_PxCR	&= ~(WP_PIN | CD_PIN);
	port->IO_PxIE	|= (WP_PIN | CD_PIN);
	port->IO_PxPUP	|= (WP_PIN | CD_PIN);

	/* CS (PN3)pin setup */
	port->IO_PxCR	|= CS_PIN;
	port->IO_PxPUP	|= CS_PIN;
	port->IO_Px	|= CS_PIN;
	
	// SPI init
	API_SPI1_Init();
	API_SPI1_FlushRx();
	API_SPI1_Enable();

}

/*************************************************************************
 * Function Name: SdTransferByte
 * Parameters: uint8_t ch
 * Return: uint8_t
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
uint8_t SdTransferByte (uint8_t ch)
{
	volatile uint16_t data;

	while (!(SSP1.SSPSR & SSPSR_TNF));
	SSP1.SSPDR = (uint16_t)ch;
	API_SPI1_Wait_Busy();
	while (!(SSP1.SSPSR & SSPSR_RNE));
	return (uint8_t)SSP1.SSPDR;
}

/*************************************************************************
 * Function Name: SdSendBlock
 * Parameters: uint8_t *pData, uint32_t Size
 *
 * Return: void
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
void SdSendBlock (uint8_t *pData, uint32_t Size)
{
	uint32_t i=0;

	while (Size >= SPI_FIFOSZ) {
		API_SPI1_Write(pData+i, SPI_FIFOSZ);
		i += SPI_FIFOSZ;
		Size -= SPI_FIFOSZ;
	}
	if (Size) {
		API_SPI1_Write(pData+i, Size);
	}
}

/*************************************************************************
 * Function Name: SdReceiveBlock
 * Parameters: uint8_t *pData, uint32_t Size
 *
 * Return: void
 *
 * Description: Read byte from SPI
 *
 *************************************************************************/
void SdReceiveBlock (uint8_t *pData, uint32_t Size)
{
	uint32_t i=0;

	while (Size >= SPI_FIFOSZ) {
		API_SPI1_Read(pData+i, SPI_FIFOSZ);
		i += SPI_FIFOSZ;
		Size -= SPI_FIFOSZ;
	}
	if (Size) {
		API_SPI1_Read(pData+i, Size);
	}
}

/*************************************************************************
 * Function Name: SdDly_1ms
 * Parameters: uint32_t Delay
 * Return: none
 *
 * Description: Delay [msec]
 *
 *************************************************************************/
void SdDly_1ms (uint32_t Delay)
{
	volatile uint32_t i;
	
	for(;Delay;--Delay) {
		for(i = SD_DLY_1MSEC;i;--i);
	}
}
