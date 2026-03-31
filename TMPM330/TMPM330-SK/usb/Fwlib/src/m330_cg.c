/*******************************************************************************
* File Name 		 : m330_cg.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : cg liblary source
********************************************************************************/


#include "m330_cg.h"


/*******************************************************************************
* Function Name  : API_CG_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_Init(void)

{
	CG->IO_SYSCR0.reg = IO_CG_SYSCR0_Init;
	CG->IO_SYSCR1.reg = IO_CG_SYSCR1_Init;
	CG->IO_SYSCR2.reg = IO_CG_SYSCR2_Init;
	
	CG->IO_OSCCR0.reg = IO_CG_OSCCR0_Init;
	CG->IO_OSCCR1.reg = IO_CG_OSCCR1_Init;

	CG->IO_STBYCR0.reg = IO_CG_STBYCR0_Init;
	CG->IO_STBYCR1.reg = IO_CG_STBYCR1_Init;
	CG->IO_STBYCR2.reg = IO_CG_STBYCR2_Init;

	CG->IO_PLLSEL.reg = IO_CG_PLLSEL_Init;
	CG->IO_CKSEL.reg = IO_CG_CKSEL_Init;
}


/*******************************************************************************
* Function Name  : API_CG_FcGearSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_FcGearSet(u_int8 FcGear)
{
	CG->IO_SYSCR0.reg &= IO_CG_FcGear_MASK;
	CG->IO_SYSCR0.reg |= FcGear;
}

/*******************************************************************************
* Function Name  : API_CG_PerClkSel
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_PerClkSel(IpCG_PerClk PerClk)
{
//	assert_param(IP_CG_PerClk_STATUS(IpCG_PerClk));
	BITBAND_IP(CG->IO_SYSCR1.reg,BIT4) = (u_int8)PerClk;	/*  */
}

/*******************************************************************************
* Function Name  : API_CG_IO_ClkSel
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_IO_ClkSel(u_int8 Prclk)
{
	CG->IO_SYSCR1.reg &= IO_CG_PRCLK_MASK;
	CG->IO_SYSCR1.reg |= Prclk;
}

/*******************************************************************************
* Function Name  : API_CG_ScoutSel
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_ScoutSel(u_int8 Scout)
{
	CG->IO_SYSCR2.reg &= IO_CG_SCOUT_MASK;
	CG->IO_SYSCR2.reg |= Scout;
}

/*******************************************************************************
* Function Name  : API_CG_WupTimeSel
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_WupTimeSel(u_int8 WupTime, IpCG_WUPSel WupCount)
{
	/* WupTime */
	CG->IO_OSCCR0.reg &= IO_CG_WUPTIME_MASK;
	CG->IO_OSCCR0.reg |= WupTime;
	/* WupCount */
	BITBAND_IP(CG->IO_OSCCR0.reg,BIT3) = (u_int8)WupCount;
}

/*******************************************************************************
* Function Name  : API_CG_PLL_ON
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_PLL_ON(IpCG_OsciState PllOsciState)
{
	BITBAND_IP(CG->IO_OSCCR0.reg,BIT2) = (u_int8)PllOsciState;
}

/*******************************************************************************
* Function Name  : API_CG_WupStatusRead
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_CG_WupStatusRead(void)
{
	u_int8	wup_status;
	wup_status = BITBAND_IP(CG->IO_OSCCR0.reg,BIT1);
	return wup_status;
}

/*******************************************************************************
* Function Name  : API_CG_WupStart
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_WupStart(void)
{
	CG->IO_OSCCR0.reg |= IO_CG_WUPON_Set;
}

/*******************************************************************************
* Function Name  : API_CG_FsEnable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_FsEnable(IpCG_OsciState FsOsciState)
{
	BITBAND_IP(CG->IO_SYSCR1.reg,BIT1) = (u_int8)FsOsciState;
}

/*******************************************************************************
* Function Name  : API_CG_FcEnable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_FcEnable(IpCG_OsciState FcOsciState)
{
	BITBAND_IP(CG->IO_SYSCR1.reg,BIT0) = (u_int8)FcOsciState;
}

/*******************************************************************************
* Function Name  : API_CG_StbyModeSel
* Description	 : 
* Input 		 : Stbymode(000,100,101,110)
* Output		 : Stbymode(000,100,101,110)
* Return		 : 
*******************************************************************************/
void API_CG_StbyModeSel(u_int8 Stbymode)
{
	CG->IO_STBYCR0.reg &= IO_CG_STBYMODE_MASK;
	CG->IO_STBYCR0.reg |= Stbymode;
}

/*******************************************************************************
* Function Name  : API_CG_R_FsEnable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_R_FsEnable(IpCG_OsciState RFsOsciState)
{
	BITBAND_IP(CG->IO_STBYCR1.reg,BIT1) = (u_int8)RFsOsciState;
}

/*******************************************************************************
* Function Name  : API_CG_R_FcEnable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_R_FcEnable(IpCG_OsciState RFcOsciState)
{
	BITBAND_IP(CG->IO_STBYCR1.reg,BIT0) = (u_int8)RFcOsciState;
}

/*******************************************************************************
* Function Name  : API_CG_StopPortDrvSel
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_StopPortDrvSel(IpCG_DrvState DrvState)
{
	BITBAND_IP(CG->IO_STBYCR2.reg,BIT0) = (u_int8)DrvState;
}

/*******************************************************************************
* Function Name  : API_CG_PLL_Sel
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_PLL_Sel(IpCG_PllState PllState)
{
	BITBAND_IP(CG->IO_PLLSEL.reg,BIT0) = (u_int8)PllState;
}

/*******************************************************************************
* Function Name  : API_CG_SYS_ClkSel
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_SYS_ClkSel(IpCG_SYS_Clk SYS_Clk)
{
	BITBAND_IP(CG->IO_CKSEL.reg,BIT1) = (u_int8)SYS_Clk;
}

/*******************************************************************************
* Function Name  : API_CG_SYS_ClkStatus
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_CG_SYS_ClkStatus(void)
{
	u_int8	clk_status;
	clk_status = BITBAND_IP(CG->IO_CKSEL.reg,BIT0);
	return clk_status;
}

/*******************************************************************************
* Function Name  : API_CG_SYSCR_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_SYSCR_Set(u_int8 syscr0, u_int8 syscr1, u_int8 syscr2)
{
	CG->IO_SYSCR0.reg = syscr0;
	CG->IO_SYSCR1.reg = syscr1;
	CG->IO_SYSCR2.reg = syscr2;
}

/*******************************************************************************
* Function Name  : API_CG_OSCCR0_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_OSCCR0_Set(u_int8 osccr0)
{
	CG->IO_OSCCR0.reg = osccr0;
}

/*******************************************************************************
* Function Name  : API_CG_OSCCR1_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_OSCCR1_Set(u_int8 osccr1)
{
	CG->IO_OSCCR1.reg = osccr1;
}

/*******************************************************************************
* Function Name  : API_CG_STBYCR_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_STBYCR_Set(u_int8 stbycr0, u_int8 stbycr1, u_int8 stbycr2)
{
	CG->IO_STBYCR0.reg = stbycr0;
	CG->IO_STBYCR1.reg = stbycr1;
	CG->IO_STBYCR2.reg = stbycr2;
}



