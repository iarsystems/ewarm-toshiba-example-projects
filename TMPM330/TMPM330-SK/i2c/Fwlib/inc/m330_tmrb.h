/*******************************************************************************
* File Name 		 : m330_tmrb.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : TMRB header
********************************************************************************/

/* avoid double definition  */
#ifndef __M330_TMRB_H
#define __M330_TMRB_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* PORT initial data */

#define IO_TMRB_TBxEN_Init			((u_int8)0x00)
#define IO_TMRB_TBxRUN_Init			((u_int8)0x00)
#define IO_TMRB_TBxCR_Init			((u_int8)0x00)
#define IO_TMRB_TBxMOD_Init			((u_int8)0x20)
#define IO_TMRB_TBxFFCR_Init		((u_int8)0xC3)
//R only	#define IO_TMRB_TBxST_Init			((u_int8)0x00)
#define IO_TMRB_TBxIM_Init			((u_int8)0x00)
#define IO_TMRB_TBxUC0_Init			((u_int16)0x0000)
#define IO_TMRB_TBxRG0_Init			((u_int16)0x0000)
#define IO_TMRB_TBxRG1_Init			((u_int16)0x0000)
//R only	#define IO_TMRB_TBxCP0_Init			((u_int16)0x0000)
//R only	#define IO_TMRB_TBxCP1_Init			((u_int16)0x0000)

/* TMRB ff0 control mask */
#define IO_TMRB_FF0CTL_MASK			((u_int8)0xFC)

/* TMRB ff0 control mask */
#define IO_TMRB_INTMASK_MASK		((u_int8)0xF8)

/* TMRB Sofy Capture Timing mask */
#define IO_TMRB_CAPTIMING_MASK		((u_int8)0xE7)

/* TMRB Timer Count Clock mask */
#define IO_TMRB_CNTCLK_MASK		((u_int8)0xFC)

typedef enum { TMRB_0 = 0, 
			   TMRB_1 = 1,
			   TMRB_2 = 2,
			   TMRB_3 = 3,
			   TMRB_4 = 4,
			   TMRB_5 = 5,
			   TMRB_6 = 6,
			   TMRB_7 = 7,
			   TMRB_8 = 8,
			   TMRB_9 = 9
			 } IpTMRB_ChSel;							/* TMRB CH data */

typedef enum { TMRB_STOP = 0, TMRB_RUN = 1 }			IpTMRB_TmrState;		/* TBnRUN<TBnPRUN><TBnRUN> */
typedef enum { TMRB_SYNCOFF = 0, TMRB_SYNCON = 1 }		IpTMRB_SyncMode;		/* TBnCR<TBnSYNC> */
typedef enum { TMRB_CLR_DISABLE = 0, TMRB_CLR_ENABLE = 1 }	IpTMRB_UpcntrState;		/* TBnMOD<TBnCLE> */


#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */

	/* TBxMOD */			/* API_TMRB_SofyCapTiming */
#define IP_TMRB_SCT_DIS				0x00			/* Software Capture Timing		Disable 			 */
#define IP_TMRB_SCT_IN0R_IN1R		0x08			/* Software Capture Timing		TBnIN0Å™,TBnIN1Å™ 	 */
#define IP_TMRB_SCT_IN0R_IN1F		0x10			/* Software Capture Timing		TBnIN0Å™,TBnIN1Å´ 	 */
#define IP_TMRB_SCT_TRGR_TRGF		0x18			/* Software Capture Timing		CAPTRGÅ™,CAPTRGÅ´ 	 */
	/* TBxMOD */			/* API_TMRB_ClkSel */
#define IP_TMRB_CLK_IN0				0x00			/* Timer Count Clock	TBnIN0	 */
#define IP_TMRB_CLK_T1				0x01			/* Timer Count Clock	É”T1	 */
#define IP_TMRB_CLK_T4				0x10			/* Timer Count Clock	É”T4	 */
#define IP_TMRB_CLK_T16				0x11			/* Timer Count Clock	É”T16	 */

	/* TBxFFCR */			/* API_TMRB_FF_Ctl */
#define IP_TMRB_FF0_INV				0x00			/* TBnFF0 Control	Invert		 */
#define IP_TMRB_FF0_SET				0x01			/* TBnFF0 Control	Set			 */
#define IP_TMRB_FF0_CLR				0x02			/* TBnFF0 Control	Clear		 */




/**************************************************************/

void API_TMRB_Init(SFR_TMRBx_t * TmrbChSel);
void API_TMRB_IP_Enable(SFR_TMRBx_t * TmrbChSel,IpFunctionState NewState);
void API_TMRB_PreRun(SFR_TMRBx_t * TmrbChSel,IpTMRB_TmrState TmrpState);
void API_TMRB_CountRun(SFR_TMRBx_t * TmrbChSel,IpTMRB_TmrState TmrcState);
void API_TMRB_RunSet(SFR_TMRBx_t * TmrbChSel,IpTMRB_TmrState TmrpState,IpTMRB_TmrState TmrcState);
void API_TMRB_W_Buffer(SFR_TMRBx_t * TmrbChSel,IpFunctionState NewState);
void API_TMRB_SyncMode(SFR_TMRBx_t * TmrbChSel,IpTMRB_SyncMode SyncMode);
void API_TMRB_Idle(SFR_TMRBx_t * TmrbChSel,IpFunctionState IdleState);
void API_TMRB_SoftCapOn(SFR_TMRBx_t * TmrbChSel);
void API_TMRB_SoftCapTiming(SFR_TMRBx_t * TmrbChSel,u_int8 CapTiming);
void API_TMRB_UpCntClearEnable(SFR_TMRBx_t * TmrbChSel,IpFunctionState UpCntClearState);
void API_TMRB_ClkSel(SFR_TMRBx_t * TmrbChSel,u_int8 CntClk);
void API_TMRB_Ff_RevTiming(SFR_TMRBx_t * TmrbChSel,IpFunctionState FFRev_c1t1,IpFunctionState FFRev_c0t1,IpFunctionState FFRev_e1t1,IpFunctionState FFRev_e0t1);
void API_TMRB_FF_Ctl(SFR_TMRBx_t * TmrbChSel,u_int8 FF_Ctl);
u_int8 API_TMRB_IntStatusRead(SFR_TMRBx_t * TmrbChSel);
void API_TMRB_IntMaskSet(SFR_TMRBx_t * TmrbChSel,IpFunctionState MaskOF,IpFunctionState MaskRg1,IpFunctionState MaskRg0);
void API_TMRB_CrSet(SFR_TMRBx_t * TmrbChSel,u_int8 tbxcr);
void API_TMRB_ModSet(SFR_TMRBx_t * TmrbChSel,u_int8 tbxmod);
void API_TMRB_FFCrSet(SFR_TMRBx_t * TmrbChSel,u_int8 tbxffcr);
u_int16 API_TMRB_UC_Read(SFR_TMRBx_t * TmrbChSel);
u_int16 API_TMRB_RG0_Read(SFR_TMRBx_t * TmrbChSel);
void API_TMRB_RG0_Write(SFR_TMRBx_t * TmrbChSel,u_int16 tbxrg0);
u_int16 API_TMRB_RG1_Read(SFR_TMRBx_t * TmrbChSel);
void API_TMRB_RG1_Write(SFR_TMRBx_t * TmrbChSel,u_int16 tbxrg1);
u_int16 API_TMRB_CP0_Read(SFR_TMRBx_t * TmrbChSel);
u_int16 API_TMRB_CP1_Read(SFR_TMRBx_t * TmrbChSel);



#endif /* avoid double definition  */





