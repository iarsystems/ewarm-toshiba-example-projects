/*******************************************************************************
* File Name          : spiflash.c
* Version            : V1.0
* Date				 : 2010/02/XX
* Description        : SPI Flash device access Control
*******************************************************************************/

#include "..\mcu\TMPM380_SYS.h"
#include "..\mcu\m380_spi.h"
#include "..\mcu\m380_port.h"
#include "spiflash.h"

#define STS1_BUSY		(1<<0)		/* Busy status */
#define STS1_WEL		(1<<1)		/* Write Enable Latch */
#define STS1_BP(n)		((n)<<2)	/* Block Protect */
#define STS1_BP_MSK		(7<<2)
#define STS1_TB			(1<<5)		/* Top/Bottom Protect */
#define STS1_SEC		(1<<6)		/* Sector Protect */
#define STS1_SRP0		(1<<7)		/* Status Reg Protect 0 */

#define STS2_SRP1		(1<<0)		/* Status Reg Protect 1 */
#define STS2_QE			(1<<1)		/* Quad enable */
#define STS2_SUS		(1<<7)		/* Suspend status */


/********************************************************************
 * Extern Definition
 ********************************************************************/

/********************************************************************
 * Variable Definition
 ********************************************************************/

/********************************************************************
 * Constant Definition
 ********************************************************************/

/********************************************************************
 * Function Definition
 ********************************************************************/

/*************************************************************************
 * Function Name: 
 * Parameters: none
 * Return:
 * Description: 
 *************************************************************************/
void spiflash_init(void)
{
	volatile PORTM *port;
	port = &PORT.cnl[PORT_N];
	uint8_t spidat[4];

	API_SPI_Init();		/* Setup SPI interface */
	API_SPI_Enable();
	
	/* Setup CS & WP PIN */
	port = &PORT.cnl[PORT_N];
	port->IO_PxCR |= SPIFLASH_CS | SPIFLASH_WP;
	port->IO_PxPUP |= SPIFLASH_CS | SPIFLASH_WP;

	spiflash_wp(DISABLE);
	spiflash_cs(ENABLE);

	spidat[0] = CMD_WRITE_STS;
	spidat[1] = 0x00;
	spidat[2] = 0x00;
	API_SPI_Write(spidat, 3);	/* Clear status word */
	spiflash_cs(DISABLE);

}

/*************************************************************************
 * Function Name: spiflash_wait_busy
 * Parameters: none
 * Return:
 * Description: 
 *************************************************************************/
void spiflash_wait_busy(void)
{
	uint8_t data;
	while (1) {
		spiflash_cs(ENABLE);
		data = CMD_READ_STS1;
		API_SPI_Write(&data, 1);
		API_SPI_Read(&data, 1);
		spiflash_cs(DISABLE);
		if (!(data & STS1_BUSY))
			break;
	}
}


/*************************************************************************
 * Function Name: 
 * Parameters: none
 * Return:
 * Description: 
 *************************************************************************/
void spiflash_cs(uint8_t cs_enable)
{
	volatile PORTM *port;
	port = &PORT.cnl[PORT_N];
	if (cs_enable) {
		port->IO_Px &= ~SPIFLASH_CS;
	}
	else {
		port->IO_Px |= SPIFLASH_CS;
	}
}

/*************************************************************************
 * Function Name: 
 * Parameters: none
 * Return:
 * Description: 
 *************************************************************************/
void spiflash_wp(uint8_t wp_enable)
{
	volatile PORTM *port;
	port = &PORT.cnl[PORT_N];
	if (wp_enable) {
		port->IO_Px &= ~SPIFLASH_WP;
	}
	else {
		port->IO_Px |= SPIFLASH_WP;
	}
}


/*************************************************************************
 * Function Name: 
 * Parameters: none
 * Return:
 * Description: 
 *************************************************************************/
void spiflash_wr(uint8_t wr_enable)
{
	uint8_t data;

	spiflash_cs(ENABLE);
	if (wr_enable) {
		data = CMD_WRITE_ENABLE;
	}
	else {
		data = CMD_WRITE_DISABLE;
	}
	API_SPI_Write(&data, 1);
	spiflash_cs(DISABLE);
}


/*************************************************************************
 * Function Name: 
 * Parameters: none
 * Return:
 * Description: 
 *************************************************************************/
uint32_t spiflash_read(uint32_t spi_address, uint8_t *buffer, uint32_t len)
{
	uint8_t spidat[4];
	volatile uint32_t readlen;

	spiflash_cs(ENABLE);
	spidat[0] = CMD_READ;
	spidat[1] = (spi_address>>16)&0xFF;
	spidat[2] = (spi_address>>8)&0xFF;
	spidat[3] = spi_address&0xFF;
	API_SPI_Write(spidat, 4);	/* send READ command */

	readlen = API_SPI_Read(buffer, len);
	spiflash_cs(DISABLE);
	return readlen;
}


/*************************************************************************
 * Function Name: 
 * Parameters: none
 * Return:
 * Description: 
 *************************************************************************/
uint32_t spiflash_erase(uint32_t block_addr, uint32_t block_size)
{
	uint8_t spidat[4], block_cnt;
	
	spiflash_wait_busy();
	spiflash_wp(ENABLE);
	
	block_cnt = (block_size + BLOCK_SIZE -1)/BLOCK_SIZE;
	while (block_cnt--) {
		spiflash_wr(ENABLE);
		spiflash_cs(ENABLE);
		spidat[0] = CMD_ERASE_BLOCK;
		spidat[1] = (block_addr>>16)&0xFF;
		spidat[2] = (block_addr>>8)&0xFF;
		spidat[3] = block_addr&0xFF;
		API_SPI_Write(spidat, 4);	/* send ERASE command */
		spiflash_cs(DISABLE);
		spiflash_wait_busy();
		block_addr += BLOCK_SIZE;
	}

	spiflash_wp(DISABLE);
	return 0;
}




/*************************************************************************
 * Function Name: 
 * Parameters: none
 * Return:
 * Description: 
 *************************************************************************/
uint32_t spiflash_write(uint32_t page_addr, uint8_t *buffer, uint32_t dlen)
{
	uint8_t spidat[4];
	uint32_t copylen;
	
	spiflash_wait_busy();
	spiflash_wp(ENABLE);
	
	while (dlen) {
		spiflash_wr(ENABLE);
		spiflash_cs(ENABLE);
		spidat[0] = CMD_PAGE_PROGRAM;
		spidat[1] = (page_addr>>16)&0xFF;
		spidat[2] = (page_addr>>8)&0xFF;
		spidat[3] = page_addr&0xFF;
		API_SPI_Write(spidat, 4);	/* send PROGRAM command */
		
		copylen = dlen > PAGE_SIZE? PAGE_SIZE: dlen;
		API_SPI_Write(buffer, copylen);	/* send data */
		
		spiflash_cs(DISABLE);
		spiflash_wait_busy();
		page_addr += PAGE_SIZE;
		dlen -= copylen;
	}
	spiflash_wp(DISABLE);
	return 0;
}


/*********************************** END OF FILE ******************************/
