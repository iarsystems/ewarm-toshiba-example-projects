/*******************************************************************************
* File Name 		 : m330_rmc.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SFR define
********************************************************************************/

/* avoid double definition */
#ifndef __M330_RMC_H
#define __M330_RMC_H

#include "m330_ip.h"

typedef enum { RMC0CH = 0, RMC1CH =1 } IpRMC_RMC_ChSel;

/* CEC recive register initial data */
#define IO_RMC_RCR1_Init		((u_int32)0x00000000)
#define IO_RMC_RCR2_Init		((u_int32)0x0000FFFF)
#define IO_RMC_RCR3_Init		((u_int16)0x0000)
#define IO_RMC_RCR4_Init		((u_int8)0x00)


	/* Batch setting symbol */

	/* RMCRCR1 */

#define IP_RMC_LIEN		0x80000000		/* RMCLIEN			 */
#define IP_RMC_EDIEN	0x40000000		/* RMCEDIEN			 */
#define IP_RMC_LD		0x00200000		/* RMCLD			 */
#define IP_RMC_PHM		0x80000000		/* RMCPHM			 */

	/* RMCRCR4 */

#define IP_RMC_PO		0x80			/* RMCPO			 */

/*****************************************************************/




	/*	RMC Receive Data type DEF.	*/

typedef struct {
	IO_SFR32_u		RmcR_Buf1;
	IO_SFR32_u		RmcR_Buf2;
	IO_SFR8_u		RmcR_Buf3;
} RMC_RcvData_t;


/*****************************************************************/

void API_RMC_Init(SFR_RMCx_t * RmcChSel);
void API_RMC_IP_Enable(SFR_RMCx_t * RmcChSel,IpFunctionState NewState);
void API_RMC_Idle(SFR_RMCx_t * RmcChSel,IpFunctionState NewState);
void API_RMC_RcvEnable(SFR_RMCx_t * RmcChSel,IpFunctionState NewState);
void API_RMC_RcvRegInit(SFR_RMCx_t * RmcChSel);
void API_RMC_RcvRegSet(SFR_RMCx_t * RmcChSel,u_int32 rmcrcr1,u_int32 rmcrcr2,u_int16 rmcrcr3,u_int8 rmcrcr4);
void API_RMC_RcvDataRead(SFR_RMCx_t * RmcChSel,RMC_RcvData_t * RcvBuf);
u_int16 API_RMC_RcvIntStatus(SFR_RMCx_t * RmcChSel);


#endif /*  avoid double definition */
