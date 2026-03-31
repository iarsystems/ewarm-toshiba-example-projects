/*******************************************************************************
* File Name 		 : m380_spi1.c
* Version			 : V1.0
* Date				 : 2010/02/xx
* Description		 : SPI interface source
********************************************************************************/
#include "TMPM380_SYS.h"


#include "m380_spi.h"
#include "m380_port.h"


/*******************************************************************************
* Function Name  : API_SPI1_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI1_Init(void)
{
	volatile PORTM *port;

	SSP1.SSPCPSR = 20;			/* CPSDVSR = 2 */
	SSP1.SSPCR0 = (8-1);		/* SCR = 0, DSS = 8-bit */
	SSP1.SSPCR1 = SSPCR1_SOD;	/* Master mode */
	SSP1.SSPIMSC = 0;

	port = &PORT.cnl[PORT_N];
	port->IO_PxFR1	&= ~0x8;
	port->IO_PxFR1	|= 0x7;		/* Enable SSP functions */
	port->IO_PxCR	|= 0x5;
	port->IO_PxIE	|= 0x2;
	port->IO_PxPUP	|= 0x2;
}


/*******************************************************************************
* Function Name  : API_SPI1_Wait_Busy
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI1_Wait_Busy(void)
{
	while (SSP1.SSPSR & SSPSR_BSY);
}



/*******************************************************************************
* Function Name  : API_SPI1_Enable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI1_Enable(void)
{
	SSP1.SSPCR1 |= SSPCR1_SSE;	/* Enable SSP */
}

/*******************************************************************************
* Function Name  : API_SPI1_Disable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI1_Disable(void)
{
	SSP1.SSPCR1 &= ~SSPCR1_SSE;	/* Disable SSP */
}


/*******************************************************************************
* Function Name  : API_SPI1_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : number of bytes read from SPI device
*******************************************************************************/
uint32_t API_SPI1_Read(uint8_t *buffer, uint32_t len)
{
	uint32_t cnt;
	volatile uint16_t data;

	for (cnt = 0; cnt < len; cnt ++) {
		while (!(SSP1.SSPSR & SSPSR_TNF));
		SSP1.SSPDR = 0;
		while (!(SSP1.SSPSR & SSPSR_RNE));
		data = SSP1.SSPDR;
		*buffer++ = (uint8_t)data;
	}
	return cnt;
}


/*******************************************************************************
* Function Name  : API_SPI1_Write
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
uint32_t API_SPI1_Write(uint8_t *buffer, uint32_t len)
{
	uint32_t cnt;
	volatile uint16_t data;

	SSP1.SSPCR1 |= SSPCR1_SSE;	/* Enable SSP */
	for (cnt = 0; cnt < len; cnt ++) {
		while (!(SSP1.SSPSR & SSPSR_TNF));
		data = ((uint16_t)*buffer++)&0xFF;
		SSP1.SSPDR = data;
	}
	/* Wait until all data is sent */
	while (!(SSP1.SSPSR & SSPSR_TFE));
	API_SPI1_Wait_Busy();
	/* Remove the dummy data from FIFO */
	while (SSP1.SSPSR & SSPSR_RNE) {
		data = SSP1.SSPDR;
	}

	return cnt;
}


/*******************************************************************************
* Function Name  : API_SPI1_FlushRx
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SPI1_FlushRx(void)
{
	volatile uint16_t tmpdat;

	API_SPI1_Disable();
	while (SSP1.SSPSR & SSPSR_RNE) {
		tmpdat = SSP1.SSPDR;
	}
	API_SPI1_Enable();
}

