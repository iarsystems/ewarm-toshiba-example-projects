/*******************************************************************************
* File Name 		 : m380_tmrb.h
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : TMRB header
********************************************************************************/

#ifndef __M380_TMRB_H
#define __M380_TMRB_H

#include "..\typedef.h"
#include "TMPM380_SYS.h"

typedef enum { 
	TMRB_0 = 0,
	TMRB_1 = 1,
	TMRB_2 = 2,
	TMRB_3 = 3,
	TMRB_4 = 4,
	TMRB_5 = 5,
	TMRB_6 = 6,
	TMRB_7 = 7
} IpTMRB_ChSel;							/* TMRB CH data */

typedef enum { TMRB_STOP = 0, TMRB_RUN = 1 }					IpTMRB_Run;			/* TBnRUN */

void API_TMRB_Init(IpTMRB_ChSel tmrbChSel);
void API_TMRB_Run(IpTMRB_ChSel tmrbChSel, IpTMRB_Run tmrbrun);
void API_TMRB_RunSet(IpTMRB_ChSel tmrbChSel, uint8_t tbxrun);
void API_TMRB_ModSet(IpTMRB_ChSel tmrbChSel,uint8_t tbxmod);
void API_TMRB_CRSet(IpTMRB_ChSel tmrbChSel, uint8_t tbxcr);
void API_TMRB_FFSet(IpTMRB_ChSel tmrbChSel,uint8_t tbxff);
void API_TMRB_REG0_Write(IpTMRB_ChSel tmrbChSel,uint16_t tbxrg0);
void API_TMRB_REG1_Write(IpTMRB_ChSel tmrbChSel,uint16_t tbxrg1);
void API_TMRB_IntMaskSet(IpTMRB_ChSel tmrbChSel, uint8_t tbxim);



#endif /* __M380_TMRB_H */

/*************************** END OF FILE **************************************/

