/*******************************************************************************
* File Name 		 : m330_tmrb.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : TMRB liblary source
********************************************************************************/


#include "m330_tmrb.h"


/*******************************************************************************
* Function Name  : API_TMRB_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_Init(SFR_TMRBx_t * TmrbChSel)
{
	API_TMRB_IP_Enable(TmrbChSel,ENABLE);
	//TmrbChSel->IO_TBxEN.reg = IO_TMRB_TBxEN_Init;
	TmrbChSel->IO_TBxRUN.reg = IO_TMRB_TBxRUN_Init;
	TmrbChSel->IO_TBxCR.reg = IO_TMRB_TBxCR_Init;
	TmrbChSel->IO_TBxMOD.reg = IO_TMRB_TBxMOD_Init;
	TmrbChSel->IO_TBxFFCR.reg = IO_TMRB_TBxFFCR_Init;
//R only	TmrbChSel->IO_TBxST.reg = IO_TMRB_TBxEN_Init;
	TmrbChSel->IO_TBxIM.reg = IO_TMRB_TBxIM_Init;
	TmrbChSel->IO_TBxUC0.reg = IO_TMRB_TBxUC0_Init;
	TmrbChSel->IO_TBxRG0.reg = IO_TMRB_TBxRG0_Init;
	TmrbChSel->IO_TBxRG1.reg = IO_TMRB_TBxRG1_Init;
//R only	TmrbChSel->IO_TBxCP0.reg = IO_TMRB_TBxEN_Init;
//R only	TmrbChSel->IO_TBxCP1.reg = IO_TMRB_TBxEN_Init;
	API_TMRB_IP_Enable(TmrbChSel,DISABLE);
}

/*******************************************************************************
* Function Name  : API_TMRB_IP_Enable
* Description	 : 
* Input 		 : TBxEN.7
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_IP_Enable(SFR_TMRBx_t * TmrbChSel,IpFunctionState NewState)
{
	BITBAND_IP(TmrbChSel->IO_TBxEN.reg,BIT7) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_TMRB_PreRun
* Description	 : 
* Input 		 : TBxRUN.2
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_PreRun(SFR_TMRBx_t * TmrbChSel,IpTMRB_TmrState TmrpState)
{
	BITBAND_IP(TmrbChSel->IO_TBxRUN.reg,BIT2) = (u_int8)TmrpState;
}

/*******************************************************************************
* Function Name  : API_TMRB_CountRun
* Description	 : 
* Input 		 : TBxRUN.0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_CountRun(SFR_TMRBx_t * TmrbChSel,IpTMRB_TmrState TmrcState)
{
	BITBAND_IP(TmrbChSel->IO_TBxRUN.reg,BIT0) = (u_int8)TmrcState;
}

/*******************************************************************************
* Function Name  : API_TMRB_RunSet
* Description	 : 
* Input 		 : TBxRUN.2,TBxRUN.0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_RunSet(SFR_TMRBx_t * TmrbChSel,IpTMRB_TmrState TmrpState,IpTMRB_TmrState TmrcState)
{
	BITBAND_IP(TmrbChSel->IO_TBxRUN.reg,BIT2) = (u_int8)TmrpState;
	BITBAND_IP(TmrbChSel->IO_TBxRUN.reg,BIT0) = (u_int8)TmrcState;
}

/*******************************************************************************
* Function Name  : API_TMRB_W_Buffer
* Description	 : 
* Input 		 : TBxCR.7
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_W_Buffer(SFR_TMRBx_t * TmrbChSel,IpFunctionState NewState)
{
	BITBAND_IP(TmrbChSel->IO_TBxCR.reg,BIT7) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_TMRB_SyncMode
* Description	 : 
* Input 		 : TBxCR.5
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_SyncMode(SFR_TMRBx_t * TmrbChSel,IpTMRB_SyncMode SyncMode)
{
	BITBAND_IP(TmrbChSel->IO_TBxCR.reg,BIT5) = (u_int8)SyncMode;
}

/*******************************************************************************
* Function Name  : API_TMRB_Idle
* Description	 : 
* Input 		 : TBxCR.3
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_Idle(SFR_TMRBx_t * TmrbChSel,IpFunctionState IdleState)
{
	BITBAND_IP(TmrbChSel->IO_TBxCR.reg,BIT3) = (u_int8)IdleState;
}

/*******************************************************************************
* Function Name  : API_TMRB_SoftCapOn
* Description	 : 
* Input 		 : TBxMOD.5
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_SoftCapOn(SFR_TMRBx_t * TmrbChSel)
{
	BITBAND_IP(TmrbChSel->IO_TBxMOD.reg,BIT5) = 0;
}

/*******************************************************************************
* Function Name  : API_TMRB_SofyCapTiming
* Description	 : 
* Input 		 : TBxMOD.4-3
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_SoftCapTiming(SFR_TMRBx_t * TmrbChSel,u_int8 CapTiming)
{
	TmrbChSel->IO_TBxMOD.reg &= IO_TMRB_CAPTIMING_MASK;
	TmrbChSel->IO_TBxMOD.byte[0] |= CapTiming;
}

/*******************************************************************************
* Function Name  : API_TMRB_UpCntClearEnable
* Description	 : 
* Input 		 : TBxMOD.2
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_UpCntClearEnable(SFR_TMRBx_t * TmrbChSel,IpFunctionState UpCntClearState)
{
	BITBAND_IP(TmrbChSel->IO_TBxMOD.reg,BIT2) = (u_int8)UpCntClearState;
}

/*******************************************************************************
* Function Name  : API_TMRB_ClkSel
* Description	 : 
* Input 		 : TBxMOD.1-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_ClkSel(SFR_TMRBx_t * TmrbChSel,u_int8 CntClk)
{
	TmrbChSel->IO_TBxMOD.reg &= IO_TMRB_CNTCLK_MASK;
	TmrbChSel->IO_TBxMOD.byte[0] |= CntClk;
}

/*******************************************************************************
* Function Name  : API_TMRB_Ff_RevTiming
* Description	 : 
* Input 		 : IO_TBxFFCR.5-2
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_Ff_RevTiming(SFR_TMRBx_t * TmrbChSel,IpFunctionState FFRev_c1t1,IpFunctionState FFRev_c0t1,
IpFunctionState FFRev_e1t1,IpFunctionState FFRev_e0t1)
{
	BITBAND_IP(TmrbChSel->IO_TBxFFCR.reg,BIT5) = (u_int8)FFRev_c1t1;
	BITBAND_IP(TmrbChSel->IO_TBxFFCR.reg,BIT4) = (u_int8)FFRev_c0t1;
	BITBAND_IP(TmrbChSel->IO_TBxFFCR.reg,BIT3) = (u_int8)FFRev_e1t1;
	BITBAND_IP(TmrbChSel->IO_TBxFFCR.reg,BIT2) = (u_int8)FFRev_e0t1;
}

/*******************************************************************************
* Function Name  : API_TMRB_FF_Ctl
* Description	 : 
* Input 		 : TBxFFCR.1-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_FF_Ctl(SFR_TMRBx_t * TmrbChSel,u_int8 FF_Ctl)
{
	//wangfb
	TmrbChSel->IO_TBxFFCR.reg &= IO_TMRB_FF0CTL_MASK;
	TmrbChSel->IO_TBxFFCR.byte[0] |= FF_Ctl;
}

/*******************************************************************************
* Function Name  : API_TMRB_IntStatusRead
* Description	 : 
* Input 		 : 
* Output		 : TBxST.2-0
* Return		 : 
*******************************************************************************/
u_int8 API_TMRB_IntStatusRead(SFR_TMRBx_t * TmrbChSel)
{
	u_int8	TmrIntStatus;
	TmrIntStatus = TmrbChSel->IO_TBxST.byte[0];
	return TmrIntStatus;
}

/*******************************************************************************
* Function Name  : API_TMRB_IntMaskSet
* Description	 : 
* Input 		 : TBxIM.2-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_IntMaskSet(SFR_TMRBx_t * TmrbChSel,IpFunctionState MaskOF,IpFunctionState MaskRg1,IpFunctionState MaskRg0)
{
	BITBAND_IP(TmrbChSel->IO_TBxIM.reg,BIT2) = (u_int8)MaskOF;
	BITBAND_IP(TmrbChSel->IO_TBxIM.reg,BIT1) = (u_int8)MaskRg1;
	BITBAND_IP(TmrbChSel->IO_TBxIM.reg,BIT0) = (u_int8)MaskRg0;
}

/*******************************************************************************
* Function Name  : API_TMRB_CrSet
* Description	 : 
* Input 		 : TBxCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_CrSet(SFR_TMRBx_t * TmrbChSel,u_int8 tbxcr)
{
	TmrbChSel->IO_TBxCR.reg = tbxcr;
}

/*******************************************************************************
* Function Name  : API_TMRB_ModSet
* Description	 : 
* Input 		 : TBxMOD
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_ModSet(SFR_TMRBx_t * TmrbChSel,u_int8 tbxmod)
{
	TmrbChSel->IO_TBxMOD.reg = tbxmod;
}

/*******************************************************************************
* Function Name  : API_TMRB_FFCrSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_FFCrSet(SFR_TMRBx_t * TmrbChSel,u_int8 tbxffcr)
{
	TmrbChSel->IO_TBxFFCR.reg = tbxffcr;
}

/*******************************************************************************
* Function Name  : API_TMRB_UC_Read
* Description	 : 
* Input 		 : 
* Output		 : TBxUC0.15-0
* Return		 : 
*******************************************************************************/
u_int16 API_TMRB_UC_Read(SFR_TMRBx_t * TmrbChSel)
{
	u_int16	CapUc_Data;
	CapUc_Data = TmrbChSel->IO_TBxUC0.reg;
	return CapUc_Data;
}

/*******************************************************************************
* Function Name  : API_TMRB_RG0_Read
* Description	 : 
* Input 		 : 
* Output		 : TBxRG0.15-0
* Return		 : 
*******************************************************************************/
u_int16 API_TMRB_RG0_Read(SFR_TMRBx_t * TmrbChSel)
{
	u_int16	Tc0_Data;
	Tc0_Data = TmrbChSel->IO_TBxRG0.reg;
	return Tc0_Data;
}

/*******************************************************************************
* Function Name  : API_TMRB_RG0_Write
* Description	 : 
* Input 		 : TBxRG0.15-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_RG0_Write(SFR_TMRBx_t * TmrbChSel,u_int16 tbxrg0)
{
	TmrbChSel->IO_TBxRG0.reg = tbxrg0;
}

/*******************************************************************************
* Function Name  : API_TMRB_RG1_Read
* Description	 : 
* Input 		 : 
* Output		 : TBxRG1.15-0
* Return		 : 
*******************************************************************************/
u_int16 API_TMRB_RG1_Read(SFR_TMRBx_t * TmrbChSel)
{
	u_int16	Tc1_Data;
	Tc1_Data = TmrbChSel->IO_TBxRG1.reg;
	return Tc1_Data;
}

/*******************************************************************************
* Function Name  : API_TMRB_RG1_Write
* Description	 : 
* Input 		 : TBxCP1.15-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_TMRB_RG1_Write(SFR_TMRBx_t * TmrbChSel,u_int16 tbxrg1)
{
	TmrbChSel->IO_TBxRG1.reg = tbxrg1;
}

/*******************************************************************************
* Function Name  : API_TMRB_CP0_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int16 API_TMRB_CP0_Read(SFR_TMRBx_t * TmrbChSel)
{
	u_int16	Cp0_Data;
	Cp0_Data = TmrbChSel->IO_TBxCP0.reg;
	return Cp0_Data;
}

/*******************************************************************************
* Function Name  : API_TMRB_CP1_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int16 API_TMRB_CP1_Read(SFR_TMRBx_t * TmrbChSel)
{
	u_int16	Cp1_Data;
	Cp1_Data = TmrbChSel->IO_TBxCP1.reg;
	return Cp1_Data;
}



