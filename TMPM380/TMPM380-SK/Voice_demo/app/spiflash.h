/*******************************************************************************
* File Name          : spiflash.h
* Version            : V1.0
* Date				 : 2010/02/XX
* Description        : SPIFlash Header
*******************************************************************************/
#ifndef __SPIFLASH_H
#define __SPIFLASH_H

#include "../typedef.h"


#define SPIFLASH_CS		(1<<7)		/* Chip Select */
#define SPIFLASH_WP		(1<<6)		/* Write Protect */

#define ENABLE			1
#define DISABLE			0

#define PAGE_SIZE   		(256)
#define SECTOR_SIZE   		(4096)
#define BLOCK_SIZE   		(64*1024)
#define PAGE_PER_SECTOR		(SECTOR_SIZE/PAGE_SIZE)
#define SECTOR_PER_BLOCK	(BLOCK_SIZE/SECTOR_SIZE)
#define PAGE_PER_BLOCK		(BLOCK_SIZE/PAGE_SIZE)
#define FLASH_SIZE			(32*BLOCK_SIZE)


#define CMD_WRITE_ENABLE		0x06
#define CMD_WRITE_DISABLE		0x04
#define CMD_READ_STS1			0x05
#define CMD_READ_STS2			0x35
#define CMD_WRITE_STS			0x01
#define CMD_PAGE_PROGRAM		0x02
#define CMD_QPAGE_PROGRAM		0x32
#define CMD_ERASE_SECTOR		0x20
#define CMD_ERASE_BLOCK			0xD8
#define CMD_ERASE_CHIP			0xC7
#define CMD_ERASE_SUSPEND		0x75
#define CMD_ERASE_RESUME		0x7A
#define CMD_POWER_DOWN			0xB9
#define CMD_READ				0x03
#define CMD_READ_FAST			0x0B
#define CMD_RELEASE_PDOWN		0xAB
#define CMD_RESET				0xFFFF

#define SPIFLASH_BASE			0xC0000000
#define F_OFS(a)		((uint32_t)(a)-SPIFLASH_BASE)

/* Function declaration */
void spiflash_init(void);
void spiflash_wait_busy(void);
void spiflash_cs(uint8_t cs_enable);
void spiflash_wp(uint8_t wp_enable);
void spiflash_wr(uint8_t wr_enable);
uint32_t spiflash_read(uint32_t spi_address, uint8_t *buffer, uint32_t len);
uint32_t spiflash_erase(uint32_t block_addr, uint32_t block_size);
uint32_t spiflash_write(uint32_t spi_address, uint8_t *buffer, uint32_t len);


#endif  /*__SPIFLASH_H */
/*********************************** END OF FILE ******************************/
