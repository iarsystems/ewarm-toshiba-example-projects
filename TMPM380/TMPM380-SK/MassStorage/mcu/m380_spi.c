/*******************************************************************************
* File Name 		 : m380_spi.c
* Version			 : V1.0
* Date				 : 2010/02/xx
* Description		 : SPI interface source
********************************************************************************/
#include "TMPM380_SYS.h"


#include "m380_spi.h"
#include "m380_port.h"


/*******************************************************************************
* Function Name  : API_SPI_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI_Init(void)
{
	volatile PORTM *port;

	SSP0.SSPCPSR = 2;			/* CPSDVSR = 2 */
	SSP0.SSPCR0 = (8-1);		/* SCR = 0, DSS = 8-bit */
	SSP0.SSPCR1 = SSPCR1_SOD;	/* Master mode */
	SSP0.SSPIMSC = 0;

	port = &PORT.cnl[PORT_C];
	port->IO_PxFR2	|= 0xF;		/* Enable SSP functions */
	port->IO_PxCR	|= 0x5;
	port->IO_PxIE	|= 0x2;
	port->IO_PxPUP	|= 0x2;
}


/*******************************************************************************
* Function Name  : API_SPI_Wait_Busy
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI_Wait_Busy(void)
{
	while (SSP0.SSPSR & SSPSR_BSY);
}



/*******************************************************************************
* Function Name  : API_SPI_Enable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI_Enable(void)
{
	SSP0.SSPCR1 |= SSPCR1_SSE;	/* Enable SSP */
}

/*******************************************************************************
* Function Name  : API_SPI_Disable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI_Disable(void)
{
	SSP0.SSPCR1 &= ~SSPCR1_SSE;	/* Disable SSP */
}


/*******************************************************************************
* Function Name  : API_SPI_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : number of bytes read from SPI device
*******************************************************************************/
uint32_t API_SPI_Read(uint8_t *buffer, uint32_t len)
{
	uint32_t cnt;
	volatile uint16_t data;

	for (cnt = 0; cnt < len; cnt ++) {
		while (!(SSP0.SSPSR & SSPSR_TNF));
		SSP0.SSPDR = 0;
		while (!(SSP0.SSPSR & SSPSR_RNE));
		data = SSP0.SSPDR;
		*buffer++ = (uint8_t)data;
	}
	return cnt;
}


/*******************************************************************************
* Function Name  : API_SPI_Write
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
uint32_t API_SPI_Write(uint8_t *buffer, uint32_t len)
{
	uint32_t cnt;
	volatile uint16_t data;

	SSP0.SSPCR1 |= SSPCR1_SSE;	/* Enable SSP */
	for (cnt = 0; cnt < len; cnt ++) {
		while (!(SSP0.SSPSR & SSPSR_TNF));
		data = ((uint16_t)*buffer++)&0xFF;
		SSP0.SSPDR = data;
	}
	/* Wait until all data is sent */
	while (!(SSP0.SSPSR & SSPSR_TFE));
	API_SPI_Wait_Busy();
	/* Remove the dummy data from FIFO */
	while (SSP0.SSPSR & SSPSR_RNE) {
		data = SSP0.SSPDR;
	}

	return cnt;
}


/*******************************************************************************
* Function Name  : API_SPI_FlushRx
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI_FlushRx(void)
{
	volatile uint16_t tmpdat;
	volatile PORTM *port;
	
	port = &PORT.cnl[PORT_C];
	API_SPI_Disable();
	port->IO_PxFR2	&= ~0xF;	/* Disable SSP functions */
	while (SSP0.SSPSR & SSPSR_RNE) {
		tmpdat = SSP0.SSPDR;
	}
	port->IO_PxFR2	|= 0xF;		/* Enable SSP functions */
	API_SPI_Enable();
}

