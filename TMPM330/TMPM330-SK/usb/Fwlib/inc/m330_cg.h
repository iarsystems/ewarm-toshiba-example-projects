/*******************************************************************************
* File Name 		 : m330_cg.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : cg header
********************************************************************************/

/* avoid double definition */
#ifndef __M330_CG_H
#define __M330_CG_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* CG initialize */

#define IO_CG_SYSCR0_Init		((u_int8)0x00)
#define IO_CG_SYSCR1_Init		((u_int8)0x00)
#define IO_CG_SYSCR2_Init		((u_int8)0x01)
#define IO_CG_OSCCR0_Init		((u_int8)0x10)
#define IO_CG_OSCCR1_Init		((u_int8)0x03)
#define IO_CG_STBYCR0_Init		((u_int8)0x03)
#define IO_CG_STBYCR1_Init		((u_int8)0x01)
#define IO_CG_STBYCR2_Init		((u_int8)0x00)
#define IO_CG_PLLSEL_Init		((u_int8)0x00)
#define IO_CG_CKSEL_Init		((u_int8)0x00)

typedef enum { CG_FGEAR = 0, CG_FC = 1 } 							IpCG_PerClk;	/* SYSCR1<FPSEL> */
typedef enum { CG_WUPSel_X1 = 0, CG_WUPSel_XT1 = 1 }				IpCG_WUPSel;	/* OSCCR0<WUPSEL> */
typedef enum { CG_STOP = 0, CG_OSCILLATION = 1 }					IpCG_OsciState;	/* OSCCR0<PLLON> */
typedef enum { CG_StopPortDrv_STOP = 0, CG_StopPortDrv_ACTIVE = 1 } IpCG_DrvState;	/* STBYCR2<DRVE> */
typedef enum { CG_X1 = 0, CG_PLL = 1 }								IpCG_PllState;	/* PLLSEL<PLLSEL> */
typedef enum { CG_SYS_Clk_fc = 0, CG_SYS_Clk_fs = 1 }				IpCG_SYS_Clk;	/* CKSEL<SYSCK> */


/* CG WUP ON */
#define IO_CG_WUPON_Set			((u_int8)0x01)

/* CG FcGear mask */
#define IO_CG_FcGear_MASK			((u_int8)0xF8)
/* CG IO_Clk mask */
#define IO_CG_PRCLK_MASK			((u_int8)0xF8)
/* CG Scout mask */
#define IO_CG_SCOUT_MASK			((u_int8)0xFC)
/* CG Warmup Time mask */
#define IO_CG_WUPTIME_MASK			((u_int8)0x8F)
/* CG standymode mask */
#define IO_CG_STBYMODE_MASK			((u_int8)0xF8)

#define STOP		0
#define ACTIVE		1




	/* Batch setting symbol */

	/* SYSCR0 */			/* API_CG_FcGearSet */
#define IP_CG_FC		0x00		/* fc			 */
//						0x01		/* Reserved		 */
//						0x02		/* Reserved		 */
//						0x03		/* Reserved		 */
#define IP_CG_FC_2		0x04		/* fc/2			 */
#define IP_CG_FC_4		0x05		/* fc/4			 */
#define IP_CG_FC_8		0x06		/* fc/8			 */
	/* SYSCR1 */			/* API_CG_IO_ClkSel */
#define IP_CG_FPE		0x00		/* fperiph			 */
#define IP_CG_FPE_2		0x01		/* fperiph/2		 */
#define IP_CG_FPE_4		0x02		/* fperiph/4		 */
#define IP_CG_FPE_8		0x03		/* fperiph/8		 */
#define IP_CG_FPE_16	0x04		/* fperiph/16		 */
#define IP_CG_FPE_32	0x05		/* fperiph/32		 */
	/* SYSCR2 */			/* API_CG_ScoutSel */
#define IP_CG_FS		0x00		/* fs			 */
//						0x01		/* Reserved		 */
#define IP_CG_FSYS		0x02		/* fsys			 */
#define IP_CG_FYT0		0x03		/* É”T0			 */

	/* OSCCR0 */			/* API_CG_WupTimeSel */
#define IP_CG_X1_0		0x00		/* X1is selected,WUP none		 */
#define IP_CG_X1_1		0x10		/* X1is selected,2(10)/Input frequency		 */
#define IP_CG_X1_2		0x20		/* X1is selected,2(11)/Input frequency		 */
#define IP_CG_X1_3		0x30		/* X1is selected,2(12)/Input frequency		 */
#define IP_CG_X1_4		0x40		/* X1is selected,2(13)/Input frequency		 */
#define IP_CG_X1_5		0x50		/* X1is selected,2(14)/Input frequency		 */
#define IP_CG_X1_6		0x60		/* X1is selected,2(15)/Input frequency		 */
#define IP_CG_X1_7		0x70		/* X1is selected,2(16)/Input frequency		 */
#define IP_CG_XT1_0		0x00		/* XT1is selected,WUP None		 */
#define IP_CG_XT1_1		0x10		/* XT1is selected,2(6)/Input frequency		 */
#define IP_CG_XT1_2		0x20		/* XT1is selected,2(7)/Input frequency		 */
#define IP_CG_XT1_3		0x30		/* XT1is selected,2(8)/Input frequency		 */
#define IP_CG_XT1_4		0x40		/* XT1is selected,2(15)/Input frequency		 */
#define IP_CG_XT1_5		0x50		/* XT1is selected,2(16)/Input frequency		 */
#define IP_CG_XT1_6		0x60		/* XT1is selected,2(17)/Input frequency		 */
#define IP_CG_XT1_7		0x70		/* XT1is selected,2(18)/Input frequency		 */

	/* STBYCR0 */			/* API_CG_StbyModeSel */
//							0x00		/* Reserved		 */
#define IP_CG_STBY_STOP		0x01		/* STBY STOP		 */
#define IP_CG_STBY_SLEEP	0x02		/* STBY SLEEP		 */
#define IP_CG_STBY_IDLE		0x03		/* STBY IDLE		 */





/**************************************************************/

void API_CG_Init(void);
void API_CG_FcGearSet(u_int8 FcGear);
void API_CG_PerClkSel(IpCG_PerClk PerClk);
void API_CG_IO_ClkSel(u_int8 Prclk);
void API_CG_ScoutSel(u_int8 Scout);
void API_CG_WupTimeSel(u_int8 WupTime, IpCG_WUPSel WupCount);
void API_CG_PLL_ON(IpCG_OsciState PllOsciState);
u_int8 API_CG_WupStatusRead(void);
void API_CG_WupStart(void);
void API_CG_FsEnable(IpCG_OsciState FsOsciState);
void API_CG_FcEnable(IpCG_OsciState FcOsciState);
void API_CG_StbyModeSel(u_int8 Stbymode);
void API_CG_R_FsEnable(IpCG_OsciState RFsOsciState);
void API_CG_R_FcEnable(IpCG_OsciState RFcOsciState);
void API_CG_StopPortDrvSel(IpCG_DrvState DrvState);
void API_CG_PLL_Sel(IpCG_PllState PllState);
void API_CG_SYS_ClkSel(IpCG_SYS_Clk SYS_Clk);
u_int8 API_CG_SYS_ClkStatus(void);
void API_CG_SYSCR_Set(u_int8 syscr0, u_int8 syscr1, u_int8 syscr2);
void API_CG_OSCCR0_Set(u_int8 osccr0);
void API_CG_OSCCR1_Set(u_int8 osccr1);
void API_CG_STBYCR_Set(u_int8 stbycr0, u_int8 stbycr1, u_int8 stbycr2);


#endif /* avoid double definition */





