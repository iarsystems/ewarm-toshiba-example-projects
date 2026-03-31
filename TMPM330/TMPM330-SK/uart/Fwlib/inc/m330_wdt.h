/*******************************************************************************
* File Name 		 : m330_wdt.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : WDT header
********************************************************************************/

/* avoid double definition */
#ifndef __M330_WDT_H
#define __M330_WDT_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* WDT initial data */
#define IO_WDT_MOD_INIT			(u_int8)0x82
#define IO_WDT_CR_INIT			(u_int8)0x00

/* WDT WDTTIME mask */
#define IO_WDT_WDTTIME_MASK		(u_int8)0x8F


#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */

	/* WDMOD<WDTP2-0> */			/* API_WDT_Set_WdtTime */
#define IP_WDT_FSYS_216		0x00		/* 2^16/fsys	 */
#define IP_WDT_FSYS_218		0x10		/* 2^18/fsys	 */
#define IP_WDT_FSYS_220		0x20		/* 2^20/fsys	 */
#define IP_WDT_FSYS_222		0x30		/* 2^22/fsys	 */
#define IP_WDT_FSYS_224		0x40		/* 2^24/fsys	 */
#define IP_WDT_FSYS_226		0x50		/* 2^26/fsys	 */
	/* WDMOD<RESCR> */				/* API_WDT_Set_WdtOutput */
#define IP_WDT_NMI			0x00		/* NMI ON	 */
#define IP_WDT_WDTOUT		0x01		/* WDTOUT RESET	 */
	/* WDCR */						/* API_WDT_Set_WdtCtrl */
#define IP_WDT_DISABLECODE	0xB1		/* NMI ON	 */
#define IP_WDT_CLEARCODE	0x4E		/* WDTOUT RESET	 */


/**************************************************************/
void API_WDT_Init(void);
void API_WDT_Set_WdtMode(u_int8 wdmod);
void API_WDT_Set_WdtEnaDis(IpFunctionState NewState);
void API_WDT_Set_WdtTime(u_int8 WdtTime);
void API_WDT_Set_WdtIdle(IpFunctionState NewState);
void API_WDT_Set_WdtOutput(u_int8 WdtOutput);
void API_WDT_Set_WdtCtrl(u_int8 wdcr);


#endif /* Avoid double definition  */





