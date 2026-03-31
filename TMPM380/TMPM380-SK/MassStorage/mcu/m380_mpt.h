/*******************************************************************************
* File Name 		 : m380_mpt.h
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : MPT header
********************************************************************************/

#ifndef __M380_MPT_H
#define __M380_MPT_H

#include "..\typedef.h"
#include "TMPM380_SYS.h"

typedef enum { 
	MPT_0 = 0,
	MPT_1 = 1,
	MPT_2 = 2,
} IpMPT_ChSel;							/* MPT CH data */

typedef enum { MPT_TMR = 0, MPT_IGBT = 1 }					IpMPT_Mode;			/* TBnEN */
typedef enum { MPT_STOP = 0, MPT_RUN = 1 }					IpMPT_Run;			/* TBnRUN */

void API_MPT_Init(IpMPT_ChSel mptChSel);
void API_MPT_ModSet(IpMPT_ChSel mptChSel, IpMPT_Mode mptmode);
void API_MPT_Run(IpMPT_ChSel mptChSel, IpMPT_Run mptrun);
void API_MPT_RunSet(IpMPT_ChSel mptChSel, uint8_t mptxrun);
void API_MTTB_ModSet(IpMPT_ChSel mptChSel,uint8_t tbxmod);
void API_MTTB_CRSet(IpMPT_ChSel mptChSel, uint8_t tbxcr);
void API_MTTB_FFSet(IpMPT_ChSel mptChSel,uint8_t tbxff);
void API_MTTB_REG0_Write(IpMPT_ChSel mptChSel,uint16_t tbxrg0);
void API_MTTB_REG1_Write(IpMPT_ChSel mptChSel,uint16_t tbxrg1);
void API_MTTB_IntMaskSet(IpMPT_ChSel mptChSel, uint8_t tbxim);
void API_MTIG_CRSet(IpMPT_ChSel mptChSel, uint16_t igxcr);
void API_MTIG_Restart(IpMPT_ChSel mptChSel, uint8_t igxrestart);
void API_MTIG_ICRSet(IpMPT_ChSel mptChSel, uint8_t igxicr);
void API_MTIG_OCRSet(IpMPT_ChSel mptChSel, uint8_t igxocr);
void API_MTIG_REG2_Write(IpMPT_ChSel mptChSel, uint16_t igxreg2);
void API_MTIG_REG3_Write(IpMPT_ChSel mptChSel, uint16_t igxreg3);
void API_MTIG_REG4_Write(IpMPT_ChSel mptChSel, uint16_t igxreg4);

#endif /* __M380_MPT_H */

/*************************** END OF FILE **************************************/

