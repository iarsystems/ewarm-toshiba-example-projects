/*******************************************************************************
* File Name 		 : m330_wdt.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : WDT liblary source
********************************************************************************/


#include "m330_wdt.h"


/*******************************************************************************
* Function Name  : API_WDT_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_WDT_Init(void)
{
	WDT->IO_WDMOD.reg = IO_WDT_MOD_INIT;
	WDT->IO_WDCR.reg = IO_WDT_CR_INIT;
}

/*******************************************************************************
* Function Name  : API_WDT_Set_WdtMode
* Description	 : 
* Input 		 : WDMOD
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_WDT_Set_WdtMode(u_int8 wdmod)
{
	WDT->IO_WDMOD.reg = wdmod;
}

/*******************************************************************************
* Function Name  : API_WDT_Set_WdtEnaDis
* Description	 : 
* Input 		 : WDMOD<WDTE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_WDT_Set_WdtEnaDis(IpFunctionState NewState)
{
	BITBAND_IP(WDT->IO_WDMOD.reg,BIT7) = (u_int8)NewState;
	/* Disable Code Write */
	if((u_int8)NewState == DISABLE){
		API_WDT_Set_WdtCtrl(IP_WDT_DISABLECODE);
	}
}

/*******************************************************************************
* Function Name  : API_WDT_Set_WdtTime
* Description	 : 
* Input 		 : WDMOD<WDTP2-0>
* Output		 : WdtTime(setting data)
* Return		 : 
*******************************************************************************/
void API_WDT_Set_WdtTime(u_int8 WdtTime)
{
	WDT->IO_WDMOD.reg &= IO_WDT_WDTTIME_MASK;
	WDT->IO_WDMOD.reg |= WdtTime;
}

/*******************************************************************************
* Function Name  : API_WDT_Set_WdtIdle
* Description	 : 
* Input 		 : WDMOD<I2WDT>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_WDT_Set_WdtIdle(IpFunctionState NewState)
{
	BITBAND_IP(WDT->IO_WDMOD.reg,BIT2) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_WDT_Set_WdtOutput
* Description	 : 
* Input 		 : WDMOD<RESCR>
* Output		 : WdtOutput(setting data)
* Return		 : 
*******************************************************************************/
void API_WDT_Set_WdtOutput(u_int8 WdtOutput)
{
	BITBAND_IP(WDT->IO_WDMOD.reg,BIT1) = (u_int8)WdtOutput;
}

/*******************************************************************************
* Function Name  : API_WDT_Set_WdtCtrl
* Description	 : 
* Input 		 : WDCR
* Output		 : wdcr(setting data)
* Return		 : 
*******************************************************************************/
void API_WDT_Set_WdtCtrl(u_int8 wdcr)
{
	WDT->IO_WDCR.reg = wdcr;
}

