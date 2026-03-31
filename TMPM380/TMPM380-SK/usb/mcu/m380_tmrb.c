/*******************************************************************************
* File Name 		 : m380_tmrb.c
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : TMRB liblary source
********************************************************************************/

#include "..\typedef.h"
#include "TMPM380_SYS.h"

#include "m380_tmrb.h"

#define SET_TMRBPTR      volatile TMR_16M *tmr;                  \
                         tmr = &TMR16.cnl[tmrbChSel]

/*******************************************************************************
* Function Name  : API_TMRB_Init
* Description	 : 16bitタイマー 初期化
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_Init(IpTMRB_ChSel tmrbChSel)
{
	SET_TMRBPTR;

	tmr->TBnEN   = 0x80;
	
	tmr->TBnRUN  = 0x00;
	tmr->TBnCR   = 0x00;
	tmr->TBnMOD  = 0x20;
	tmr->TBnFFCR = 0xC3;
	tmr->TBnIM   = 0x00;
	
	
	tmr->TBnRG0 = 0x0000;
	tmr->TBnRG1 = 0x0000;
	
}

/*******************************************************************************
* Function Name  : API_TMRB_Run
* Description	 : 16bitTimer Start, Stop
* Input 		 : TBxRUN
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_Run(IpTMRB_ChSel tmrbChSel, IpTMRB_Run tmrbrun)
{
	SET_TMRBPTR;
	if (tmrbrun == TMRB_RUN) {
		tmr->TBnRUN = BIT8(0,0,0,0,0,1,0,1);
	}
	else {
		tmr->TBnRUN = BIT8(0,0,0,0,0,0,0,0);
	}


}

/*******************************************************************************
* Function Name  : API_TMRB_RunSet
* Description	 : 16bitタイマー TBnRUN設定
* Input 		 : TBxRUN
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_RunSet(IpTMRB_ChSel tmrbChSel, uint8_t tbxrun)
{
	SET_TMRBPTR;
	tmr->TBnRUN = tbxrun;
}

/*******************************************************************************
* Function Name  : API_TMRB_ModSet
* Description	 : 16bitタイマー TBnMOD設定
* Input 		 : TBxMOD
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_ModSet(IpTMRB_ChSel tmrbChSel, uint8_t tbxmod)
{
	SET_TMRBPTR;
	tmr->TBnMOD = tbxmod;
}

/*******************************************************************************
* Function Name  : API_TMRB_CRSet
* Description	 : 16bitタイマー TBnCR設定
* Input 		 : TBxCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_CRSet(IpTMRB_ChSel tmrbChSel, uint8_t tbxcr)
{
	SET_TMRBPTR;
	tmr->TBnCR = tbxcr;
}

/*******************************************************************************
* Function Name  : API_TMRB_FFSet
* Description	 : 16bitタイマー TBnFF設定
* Input 		 : TBxFFCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_FFSet(IpTMRB_ChSel tmrbChSel, uint8_t tbxff)
{
	SET_TMRBPTR;
	tmr->TBnFFCR = tbxff;
}

/*******************************************************************************
* Function Name  : API_TMRB_REG0_Write
* Description	 : 16bitタイマー REG0設定
* Input 		 : TBxRG0.15-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_REG0_Write(IpTMRB_ChSel tmrbChSel, uint16_t tbxreg0)
{
	SET_TMRBPTR;
	tmr->TBnRG0= tbxreg0;
}

/*******************************************************************************
* Function Name  : API_TMRB_REG1_Write
* Description	 : 16bitタイマー REG1設定
* Input 		 : TBxRG1.15-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_REG1_Write(IpTMRB_ChSel tmrbChSel, uint16_t tbxreg1)
{
	SET_TMRBPTR;
	tmr->TBnRG1= tbxreg1;
}

/*******************************************************************************
* Function Name  : API_TMRB_IntMaskSet
* Description	 : 16bitタイマー 割込みマスク設定
* Input 		 : TBxIM.2-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_IntMaskSet(IpTMRB_ChSel tmrbChSel, uint8_t tbxim)
{
	SET_TMRBPTR;
	tmr->TBnIM= tbxim;
}


/*********************************** END OF FILE ******************************/
