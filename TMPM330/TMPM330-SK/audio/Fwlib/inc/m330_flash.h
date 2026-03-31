/*******************************************************************************
* File Name 		 : m330_flash.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : FLASH header
********************************************************************************/

/* avoid double definition */
#ifndef __M330_FLASH_H
#define __M330_FLASH_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* FLASH initial data */
#define IO_FLASH_SECBIT_INIT		0x01

/* FLASH Block Protect State MASK bit */
#define FLASH_BPS_SHIFT				16
#define FLASH_UI32BIT5_0_MASK		(u_int8)0x0000003F


#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */

	/* SECBIT<D0>/<SECBIT> */	/* API_FLASH_SecbitSet */
#define IP_FLASH_SECBIT0					0x00	/* security bit 0	 */
#define IP_FLASH_SECBIT1					0x01	/* security bit 1	 */


/**************************************************************/
void API_FLASH_Init(void);
u_int8 API_FLASH_BlproRead(void);
u_int8 API_FLASH_RdyBsyRead(void);
u_int8 API_FLASH_SecbitRead(void);
void API_FLASH_SecbitSet(u_int8 secbit);


#endif /* avoid double definition */



