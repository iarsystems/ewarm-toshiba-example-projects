/*******************************************************************************
* File Name 		 : m330_sbi.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SBI header
********************************************************************************/

/* avoid double definition */
#ifndef __M330_SBI_H
#define __M330_SBI_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* SBI initial data */
#define IO_SBI_CR0_INIT			((u_int8)0x00)
#define IO_SBI_CR1_I2C_INIT		((u_int8)0x09)
#define IO_SBI_CR1_SIO_INIT		((u_int8)0x08)
#define IO_SBI_DBR_I2C_INIT		((u_int8)0x00)
//	define IO_SBI_DBR_SIO_INIT		•s’è
#define IO_SBI_I2CAR_INIT		((u_int8)0x00)
#define IO_SBI_CR2_I2C_INIT		((u_int8)0x10)
#define IO_SBI_CR2_SIO_INIT		((u_int8)0xF3)
//Read Only		#define IO_SBI_SR_I2C_INIT		((u_int8)0x10)
//Read Only		#define IO_SBI_SR_SIO_INIT		((u_int8)0xF3)
#define IO_SBI_BR0_I2C_INIT		((u_int8)0xBE)
#define IO_SBI_BR0_SIO_INIT		((u_int8)0xBE)

/* SBI ModeRead mask */
#define IO_SBI_MODEREAD_MASK		((u_int8)0x0C)
/* SBI ModeSet mask */
#define IO_SBI_MODESET_MASK		((u_int8)0xF3)

#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */

	/* SBIxCR2<SBIM1><SBIM0> */			/* API_SBI_ModeSet */
#define IP_SBI_PORTMODE		0x00		/* PORT Mode	 */
#define IP_SBI_SIOMODE		0x04		/* SIO Mode		 */
#define IP_SBI_I2CMODE		0x08		/* I2CBUS Mode	 */


/**************************************************************/

void API_SBI_Init(SFR_SBIx_t * SbiChSel);
void API_SBI_IP_Enable(SFR_SBIx_t * SbiChSel,IpFunctionState NewState);
void API_SBI_SndDataSet(SFR_SBIx_t * SbiChSel,u_int8 sbidbr);
u_int8 API_SBI_RcvDataRead(SFR_SBIx_t * SbiChSel);
void API_SBI_ModeSet(SFR_SBIx_t * SbiChSel,u_int8 Sbimode);
void API_SBI_Idle(SFR_SBIx_t * SbiChSel,IpFunctionState NewState);
u_int8 API_SBI_StatusRead(SFR_SBIx_t * SbiChSel);
void API_SBI_CR1_Set(SFR_SBIx_t * SbiChSel,u_int8 sbicr1);
void API_SBI_CR2_Set(SFR_SBIx_t * SbiChSel,u_int8 sbicr2);
u_int8 API_SBIi_SoftResetStatusRead(SFR_SBIx_t * SbiChSel);
void API_SBIi_SlvAddressSet(SFR_SBIx_t * SbiChSel,u_int8 sbii2car);
void API_SBIs_TrnStartStop(SFR_SBIx_t * SbiChSel,IpFunctionState NewState);
void API_SBIs_ForceStop(SFR_SBIx_t * SbiChSel,IpFunctionState NewState);



#endif /* avoid double definition  */





