/*******************************************************************************
* File Name 		 : m330_rmc.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : typedef
********************************************************************************/


#include "m330_rmc.h"



/*******************************************************************************
* Function Name  : API_RMC_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_RMC_Init(SFR_RMCx_t * RmcChSel)
{
			RmcChSel->IO_RMCxEN.reg = 0x01;
			RmcChSel->IO_RMCxREN.reg = 0x00;
			RmcChSel->IO_RMCxRCR1.reg = IO_RMC_RCR1_Init;
			RmcChSel->IO_RMCxRCR2.reg = IO_RMC_RCR2_Init;
			RmcChSel->IO_RMCxRCR3.reg = IO_RMC_RCR3_Init;
			RmcChSel->IO_RMCxRCR4.reg = IO_RMC_RCR4_Init;
			RmcChSel->IO_RMCxEN.reg = 0x00;
}


/*******************************************************************************
* Function Name  : API_RMC_IP_Enable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_RMC_IP_Enable(SFR_RMCx_t * RmcChSel,IpFunctionState NewState)
{
//	assert_param(IP_FUNCTION_STATUS(NewState));


	BITBAND_IP(RmcChSel->IO_RMCxEN.reg,BIT0) = (u_int8)NewState;

}

/*******************************************************************************
* Function Name  : API_RMC_Idle
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_RMC_Idle(SFR_RMCx_t * RmcChSel,IpFunctionState NewState)
{
//	assert_param(IP_FUNCTION_STATUS(NewState));

	BITBAND_IP(RmcChSel->IO_RMCxEN.reg,BIT1) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_RMC_RcvEnable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_RMC_RcvEnable(SFR_RMCx_t * RmcChSel,IpFunctionState NewState)
{
//	assert_param(IP_FUNCTION_STATUS(NewState));

	BITBAND_IP(RmcChSel->IO_RMCxREN.reg,BIT0) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_RMC_RcvRegInit
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_RMC_RcvRegInit(SFR_RMCx_t * RmcChSel)
{
			RmcChSel->IO_RMCxRCR1.reg = IO_RMC_RCR1_Init;
			RmcChSel->IO_RMCxRCR2.reg = IO_RMC_RCR2_Init;
			RmcChSel->IO_RMCxRCR3.reg = IO_RMC_RCR3_Init;
			RmcChSel->IO_RMCxRCR4.reg = IO_RMC_RCR4_Init;
}

/*******************************************************************************
* Function Name  : API_RMC_RcvRegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_RMC_RcvRegSet(SFR_RMCx_t * RmcChSel,u_int32 rmcrcr1,u_int32 rmcrcr2,u_int16 rmcrcr3,u_int8 rmcrcr4)
{
			RmcChSel->IO_RMCxRCR1.reg = rmcrcr1;
			RmcChSel->IO_RMCxRCR2.reg = rmcrcr2;
			RmcChSel->IO_RMCxRCR3.reg = rmcrcr3;
			RmcChSel->IO_RMCxRCR4.reg = rmcrcr4;
}

/*******************************************************************************
* Function Name  : API_RMC_RcvDataRead
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_RMC_RcvDataRead(SFR_RMCx_t * RmcChSel,RMC_RcvData_t * RcvBuf)
{

	RcvBuf->RmcR_Buf1.reg = RmcChSel->IO_RMCxRBUF1.reg;
	RcvBuf->RmcR_Buf2.reg = RmcChSel->IO_RMCxRBUF2.reg;
	RcvBuf->RmcR_Buf3.reg = RmcChSel->IO_RMCxRBUF3.reg;
}

/*******************************************************************************
* Function Name  : API_RMC_RcvIntStatus
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int16 API_RMC_RcvIntStatus(SFR_RMCx_t * RmcChSel)
{
	u_int16	RcvIntStatus;
	
	RcvIntStatus = RmcChSel->IO_RMCxRSTAT.reg;

	return RcvIntStatus;
}

